#include <Servo.h>
#include <SPI.h>
#include <RFID.h>
Servo ozan;
RFID detected_card(10, 9);
byte correct_card[5] = {131,143,124,17 ,97};
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  detected_card.init();
  
  pinMode(7,OUTPUT); //green LED
  pinMode(6,OUTPUT); //red LED
  pinMode(5,OUTPUT); //buzzer 
ozan.attach(8);
ozan.write(0);
}

void loop()
{
          digitalWrite(6,1);
        digitalWrite(7,0);
        digitalWrite(5,0);
        ozan.write(0);

 //find out card number
  if (detected_card.isCard()) {  // if the card is detected..

    
    if (detected_card.readCardSerial()) {  // Read card serial number , 
      Serial.println("Kart Bulundu ID : ");
      Serial.print(detected_card.serNum[0]);
      Serial.print(" , ");
      Serial.print(detected_card.serNum[1]);
      Serial.print(" , ");
      Serial.print(detected_card.serNum[2]);
      Serial.print(" , ");
      Serial.print(detected_card.serNum[3]);
      Serial.print(" , ");
      Serial.print(detected_card.serNum[4]);
      Serial.println(" ");

//find out card number
      if (detected_card.serNum[0]==correct_card[0] && detected_card.serNum[1]==correct_card[1] && detected_card.serNum[2]==correct_card[2] && detected_card.serNum[3]==correct_card[3] && detected_card.serNum[4]==correct_card[4] ){
        
        digitalWrite(7,1);
        digitalWrite(5,1);
        digitalWrite(6,0);
        ozan.write(90);
        delay(2000);
        digitalWrite(5,0);
        digitalWrite(7,0);
        ozan.write(0);
      }
      


      



    }
  }
  detected_card.halt(); // card can be read again...
}