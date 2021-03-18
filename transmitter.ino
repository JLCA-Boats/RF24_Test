#include <printf.h>
#include <SPI.h>
#include <RF24.h>


const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL;
RF24 radio(9, 10);  

struct radio_channels {
  byte pwm;
  
};

radio_channels to_send;

void setup() {
  
  Serial.begin(9600);
  radio.begin();
  printf_begin();
  radio.setAutoAck(true);
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108); 
  radio.setRetries(15, 15);
  radio.openWritingPipe(my_radio_pipe);
  to_send.pwm = 0;
  Serial.println("Start Radio");
  radio.stopListening();
  radio.setPayloadSize(1);
  radio.printPrettyDetails();

}

void loop() {

  to_send.pwm = map(analogRead(A0), 0, 1024, 0, 255);
  radio.setPayloadSize(sizeof(to_send.pwm));

  if(radio.write(&to_send, sizeof(to_send))){
    Serial.print("Sending: ");
  }else {
   Serial.print("Not sent: ") ;
   }
  Serial.println(map(analogRead(A0), 0, 1024, 0, 255));


}
