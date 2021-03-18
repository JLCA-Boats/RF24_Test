#include <printf.h>
#include <SPI.h>
#include <RF24.h>


const uint64_t pipeIn = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10);   
struct Received_data {
  byte pwm;
};

Received_data received_data;

int ch1_value = 0;

void reset_the_Data()  {
  received_data.pwm = 0;
}


void setup() {
  reset_the_Data();
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108); 
  radio.openReadingPipe(1,pipeIn);
  printf_begin();
  radio.startListening();
  radio.setPayloadSize(1);
  radio.printPrettyDetails();

}

unsigned long lastRecvTime = 0;

void receive_the_data() {
  while ( radio.available() ) {
  radio.read(&received_data, sizeof(received_data));
  lastRecvTime = millis(); 
}
}

void loop() {

  receive_the_data();

  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    reset_the_Data();

  } 

  ch1_value = map(received_data.pwm, 0, 255, 0, 255);
  Serial.print("Radio available: ");
  Serial.println(radio.available());
  Serial.print("Recibo (");
  Serial.print(lastRecvTime);
  Serial.print("): "); 
  Serial.println(ch1_value);
  
}
