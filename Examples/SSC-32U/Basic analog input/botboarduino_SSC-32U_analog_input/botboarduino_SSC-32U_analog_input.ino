/*
 * Created on 2016-02-18 for RobotShop by scharette.
 * 
 * This examples uses a BotBoarduino to read analog voltage inputs through an SSC-32U servomotor controller board.
 * You can find out more about these products here:
 * 
 * BotBoarduino: http://www.robotshop.com/en/lynxmotion-botboarduino-robot-controller.html
 * > [Useful links](http://www.robotshop.com/en/lynxmotion-botboarduino-robot-controller.html#Useful Links)
 * 
 * SSC-32U: http://www.robotshop.com/en/lynxmotion-ssc-32u-usb-servo-controller.html
 * > [Useful links](http://www.robotshop.com/en/lynxmotion-ssc-32u-usb-servo-controller.html#Useful Links)
 * > Especially helpful in this example is a list of the commands for the SSC-32U. These can be found in the [user manual
 * on pages 24-26](http://www.lynxmotion.com/images/data/lynxmotion_ssc-32u_usb_user_guide.pdf#page=24)
 * and [pages 32-35](http://www.lynxmotion.com/images/data/lynxmotion_ssc-32u_usb_user_guide.pdf#page=32).
 * 
 * License GNU GPL v3: http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#include <SoftwareSerial.h>

// Default pins for components
#define SS_SSC_32U_PINS_RX    13
#define SS_SSC_32U_PINS_TX    12

SoftwareSerial SSC32U(SS_SSC_32U_PINS_RX, SS_SSC_32U_PINS_TX);     // Make sure to change the defines above for whatever pins you wish to use

int analogVal[10];

void setup()
{
  // Start serial interface
  Serial.begin(9600);
  Serial.println("< Starting... >");
  
  // Start the software serial interface
  Serial.print("\t > Starting software serial interface to SSC-32U... ");
  SSC32U.begin(9600);
  SSC32U.listen();                                                  // Required for the SoftwareSerial port to receive data properly. Only one SoftSerial interface can listen at any time.
  if (SSC32U.isListening())
  {
    Serial.println("Port opened successfully.");
  }
  else
  {
    Serial.println("*!*!*!* Port error.");
  }
  delay(1000);
  
  // Confirm SSC-32U firmware version
  Serial.print("\t > Checking SSC-32U version... ");
  SSC32U.println("VER");
  delay(100);
  Serial.print("Data count = ["); Serial.print(SSC32U.available(), DEC); Serial.print("]... ");
  Serial.print("Firmware version = ");
  while(SSC32U.available() > 0)
  {
    Serial.write(SSC32U.read());
  };
  Serial.println("");
  delay(1000);
  
  // Initliaze analog pins
  Serial.print("\t > Initializing analog inputs... ");
  SSC32U.println("VA VB VC VD VE VF VG VH");
  delay(100);
  SSC32U.println("VA VB VC VD VE VF VG VH");
  delay(100);
  Serial.println("Done.");
  
  // Empty software serial RX buffer
  while(SSC32U.available() > 0)
  {
    SSC32U.read();
  };
}

int i = 0;

void loop()
{
  // Start loop
  Serial.print("\t < Loop... "); Serial.print((i++), DEC); Serial.println(" >");
  
  // Check inputs
  Serial.println("\t\t >> Checking analog values... ");
  int index = 0;
  for(index=0; index < 8; index ++)
  {
    analogVal[index] = -1;
  }
  index = 0;
  // In some cases, the last byte is not received. Also, the first Vx after a pin change may be undefined/invalid, so at least two reads are required.
  SSC32U.println("VA VA VA VA"); delay(100); SSC32U.read(); analogVal[index++] = SSC32U.read(); while(SSC32U.available() > 0) { SSC32U.read(); };
  SSC32U.println("VB VB VB VB"); delay(100); SSC32U.read(); analogVal[index++] = SSC32U.read(); while(SSC32U.available() > 0) { SSC32U.read(); };
  SSC32U.println("VC VC VC VC"); delay(100); SSC32U.read(); analogVal[index++] = SSC32U.read(); while(SSC32U.available() > 0) { SSC32U.read(); };
  SSC32U.println("VD VD VD VD"); delay(100); SSC32U.read(); analogVal[index++] = SSC32U.read(); while(SSC32U.available() > 0) { SSC32U.read(); };
  SSC32U.println("VE VE VE VE"); delay(100); SSC32U.read(); analogVal[index++] = SSC32U.read(); while(SSC32U.available() > 0) { SSC32U.read(); };
  SSC32U.println("VF VF VF VF"); delay(100); SSC32U.read(); analogVal[index++] = SSC32U.read(); while(SSC32U.available() > 0) { SSC32U.read(); };
  SSC32U.println("VG VG VG VG"); delay(100); SSC32U.read(); analogVal[index++] = SSC32U.read(); while(SSC32U.available() > 0) { SSC32U.read(); };
  SSC32U.println("VH VH VH VH"); delay(100); SSC32U.read(); analogVal[index++] = SSC32U.read(); while(SSC32U.available() > 0) { SSC32U.read(); };
  
  // Empty software serial RX buffer
  while(SSC32U.available() > 0)
  {
    SSC32U.read();
  };
  
  // Print input results
  index = 0;
  Serial.print("\t\t\t >>> VA = "); Serial.println(analogVal[index++], DEC);
  Serial.print("\t\t\t >>> VB = "); Serial.println(analogVal[index++], DEC);
  Serial.print("\t\t\t >>> VC = "); Serial.println(analogVal[index++], DEC);
  Serial.print("\t\t\t >>> VD = "); Serial.println(analogVal[index++], DEC);
  Serial.print("\t\t\t >>> VE = "); Serial.println(analogVal[index++], DEC);
  Serial.print("\t\t\t >>> VF = "); Serial.println(analogVal[index++], DEC);
  Serial.print("\t\t\t >>> VG = "); Serial.println(analogVal[index++], DEC);
  Serial.print("\t\t\t >>> VH = "); Serial.println(analogVal[index++], DEC);
  
  // Wait for next loop (The delay should be shorter if the Serial.print are disabled to have a more responsive system)
  delay(1000);
}

