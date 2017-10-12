#include <SoftwareSerial.h>
SoftwareSerial mp3(7, 8);       //or white 4-pin D7
¬¬
static int8_t Send_buf[8] = {0};      // Buffer for Send commands. 

#define button1 2                         //knop 1 zit op pin 2

#include <LiquidCrystal_I2C.h>          //importeer LCD library
#include <Wire.h>                   //importeer de kabel library tussen de LCD en arduino (i2c converter)
LiquidCrystal_I2C lcd(0x27, 2, 16);          //geef aan wat voor een soort lcd het is

void setup() {
  mp3.begin(9600);        //connect to mp3

  Send_buf[0] = 0x7e;         //Open command
  Send_buf[1] = 0xff;         //Version Info
  Send_buf[2] = 0x06;                    //Lenght (number of bytes of the command w/o starting/ending byte)
  Send_buf[3] = 0X0C;     //Type of command? (Play, pause, shuffle, volume set??)
  Send_buf[4] = 0x01;         // Give feedback? NO: 0x00 or YES: 0x01
  Send_buf[5] = (int8_t)(0x00 >> 8);    //datah – The data that will be be sent beside the command
  Send_buf[6] = (int8_t)(0x00);         //datal – The data that will be be sent beside the command
  Send_buf[7] = 0xef;       //Close command

  for (uint8_t i = 0; i < 8; i++)  {
    mp3.write(Send_buf[i]) ;    //Execute and write all the bytes tot he mp3
  }

  lcd.init();                               //start lcd opnieuw op
  lcd.backlight();                          //zet backlight van lcd aan
  lcd.clear();                            //maak lcd scherm leeg
  lcd.begin(16, 2);                       //stel aantal rijen/kolommen in op lcd die je gaat gebruiken, in dit geval alles

  lcd.clear();                                      //scherm leeghalen
  lcd.setCursor(0, 0);                            //cursor plaatsen op 1e blokje, 1e regel
  lcd.print("Push 1 for sound");                //print 1e tekst op 1e regel

}//close setup

void loop() {
  if (digitalRead(button1) == HIGH) {
    Send_buf[0] = 0x7e;         //Open command
    Send_buf[1] = 0xff;       //Version Info
    Send_buf[2] = 0x06;                //Lenght (number of bytes of the command w/o starting/ending byte)
    Send_buf[3] = 0X17;       //Type of command? (Play, pause, shuffle, volume set??)
    Send_buf[4] = 0x01;       // Give feedback? NO: 0x00 or YES: 0x01
    Send_buf[5] = (int8_t)(0x0101 >> 8);  //datah – The data that will be be sent beside the command
    Send_buf[6] = (int8_t)(0x0101);   //datal – The data that will be be sent beside the command
    Send_buf[7] = 0xef;         //Close command

    for (uint8_t i = 0; i < 8; i++)  {
      mp3.write(Send_buf[i]) ;
    }
  
    delay(2000);
    
    Send_buf[0] = 0x7e;         //Open command
    Send_buf[1] = 0xff;       //Version Info
    Send_buf[2] = 0x06;                //Lenght (number of bytes of the command w/o starting/ending byte)
    Send_buf[3] = 0X0C;       //Type of command? (Play, pause, shuffle, volume set??)
    Send_buf[4] = 0x01;       // Give feedback? NO: 0x00 or YES: 0x01
    Send_buf[5] = (int8_t)(0x00 >> 8);  //datah – The data that will be be sent beside the command
    Send_buf[6] = (int8_t)(0x00);     //datal – The data that will be be sent beside the command
    Send_buf[7] = 0xef;         //Close command

    for (uint8_t i = 0; i < 8; i++)  {
      mp3.write(Send_buf[i]) ;
    }
  }
  else {}
  delay(250);
}//close loop
