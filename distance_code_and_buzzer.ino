#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(192,168,1,101);  

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(80, 101, 152, 45);
IPAddress myDns(192, 168, 0, 1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement


#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int buzzer = 5;//the pin of the active buzzer







void setup() {

Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed

Ethernet.begin(mac);
delay(1000);
client.connect(server, 5001);
Serial.println(client.remoteIP());
Serial.println("connection doen");


  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output

  


}


void loop() {
 buzz();
}


void SendMessage(int message)
{
  client.print(  "The distance is:" + String(message) + "\r\n");
}



void buzz(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if(distance<30){
      unsigned char i;
SendMessage(distance);
  
    //output an frequency
    for(i=0;i<10;i++)
    {
      digitalWrite(buzzer,HIGH);
      delay(1);//wait for 1ms
      digitalWrite(buzzer,LOW);
      delay(1);//wait for 1ms
    }
    //output another frequency
    for(i=0;i<10;i++)
    {
      digitalWrite(buzzer,HIGH);
      delay(2);//wait for 1ms
      digitalWrite(buzzer,LOW);
      delay(2);//wait for 1ms
    }
  
  }
}
