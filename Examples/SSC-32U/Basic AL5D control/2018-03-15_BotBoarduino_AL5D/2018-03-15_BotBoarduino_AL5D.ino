// Created on:  2018-03-15
// Created by:  scharette

// *** *** *** Updates *** *** ***
// 2018-03-15   01.00   First release
//                      First moves all servomotors to center position, then moves arm servomotors 0-3 between 1200 & 1800 continuously.
//                      Also, it reads SSC-32U input H in analog mode.

#include <SoftwareSerial.h>

// Init software serial interface to SSC-32U
SoftwareSerial ssc32u(12, 13);

void setup()
{
  // Init serial on USB port (UNO, duemilanove, etc.)
  Serial.begin(115200);
  Serial.println("< Started setup >");
  
  // Init software serial (RX/TX pins are 12/13)
  Serial.println("\tInit software serial interface :: ssc32u @9600...");
  ssc32u.begin(9600);
  ssc32u.listen();
  Serial.println("\tInit completed!");
  
  // Init VH as analog input on SSC-32U
  Serial.println("\tRead VH in analog and post result ...");
  ssc32u.write("vh vh vh vh\r");
  uint8_t val = ssc32u.read(); val = ssc32u.read(); val = ssc32u.read(); val = ssc32u.read();
  Serial.print("\t\tVH = "); Serial.println(val, DEC);
  Serial.println("\tVH result completed!");
  
  // Move motors to centered position in a group move
  Serial.println("\tMoving all motors to 1500 (#0P1500 #1P1500 #2P1500 #3P1500 #4P1500 #5P1500 #6P1500\\r)");
  ssc32u.write("#0P1500 #1P1500 #2P1500 #3P1500 #4P1500 #5P1500 #6P1500\r");
  Serial.println("\tMoving motors completed!");
  
  Serial.println("< Completed setup >");
  Serial.println("");
  Serial.println("< Started loop >");
  Serial.println("");
}

// Store value of current pulse
#define ARM_PULSE_STEP    20
#define ARM_PULSE_MAX   1800
#define ARM_PULSE_MIN   1200
uint16_t pulse = 1500;
uint8_t direction = 1;
uint16_t count = 0;

void loop()
{
  // Loop header
  count +=1;
  Serial.print("> Loop #"); Serial.println(count, DEC);
  
  // Read VH in analog (IR distance sensor)
  ssc32u.write("vh vh vh vh\r");
  uint8_t val = ssc32u.read(); val = ssc32u.read(); val = ssc32u.read(); val = ssc32u.read();
  Serial.print("\t\tVH = "); Serial.println(val, DEC);
  Serial.println("");
  
  // Move arm position slightly
  Serial.print("\tArm currently "); Serial.println(pulse, DEC);
  if(direction)
  {
    // Increment pulse for each motor
    pulse += ARM_PULSE_STEP;
    
    // Check boundary
    if(pulse > ARM_PULSE_MAX)
    {
      pulse = ARM_PULSE_MAX;
      direction = 0;
    }
  }
  else
  {
    // Decrement pulse for each motor
    pulse -= ARM_PULSE_STEP;
    
    // Check boundary
    if(pulse < ARM_PULSE_MIN)
    {
      pulse = ARM_PULSE_MIN;
      direction = 1;
    }
  }
  Serial.print("\tArm moving to "); Serial.println(pulse, DEC);
  Serial.println("");
  
  // Update servomotor channel to match new pulse value (only first 4 motors :: base, shoulder, elbow, wrist)
  //       #nPmmmm             \r     [0x00]
  // ((1 + 1 + 1 + 4 + 1) * 4) + 1 + 1 null = 34
  // Buffer of 40 is large enough to keep all characters
  char output[40];
  sprintf(output, "#0P%u #1P%u #2P%u #3P%u\r", pulse, pulse, pulse, pulse);
  ssc32u.write(output);
  
  // Delay loop
  delay(100);
}
