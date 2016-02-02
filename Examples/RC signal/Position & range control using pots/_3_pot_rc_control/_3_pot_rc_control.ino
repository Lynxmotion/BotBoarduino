/*  Created on 2016-02-01 for RobotShop by scharette.
    Allows output of an RC signal based on the position of a 3-pin potentiometer (value).
    Two secondary 3-pin potentiometers are used to control the minimum and maximum range of pulsed width of the RC signal.
    The minimum can be set from 500-1450 us and the maximum can be set from 1550-2500 us.
    Typical RC signal is from 1000-2000 us (1500 us = center).
    License GNU GPL v3: http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#include <Servo.h>

// Default pins for components
#define POT_POSITION        A0
#define POT_MINIMUM         A1
#define POT_MAXIMUM         A2
#define RC_OUTPUT           11

// Defines constants for mapping values / ranges (for ADC results, values in VCC/1024)
#define POT_ADC_VAL_MIN     0
#define POT_ADC_VAL_MAX     1023
#define POT_ADC_VAL_CENTER  512

// Defines constants for mapping values / ranges (for RC signal, values in us)
#define RC_CENTER           1500
#define RC_MIN_RANGE_MIN    500
#define RC_MIN_RANGE_MAX    1450
#define RC_MAX_RANGE_MIN    1550
#define RC_MAX_RANGE_MAX    2500

int pots[] = {POT_POSITION, POT_MINIMUM, POT_MAXIMUM};    //  Contains the 3 pins for the potentiometers (can be changed above in the constants)
int val[3];                                               //  Contains the 3 values of the potentiometers (0 = position, 1 = minimum, 2 = maximum)
int servoPos = RC_CENTER;
int servoMin = RC_MIN_RANGE_MIN;
int servoMax = RC_MAX_RANGE_MAX;

Servo outputRC;

void setup()
{
  // Attach servo
  outputRC.attach(RC_OUTPUT);
  outputRC.writeMicroseconds(servoPos);
  outputRC.attach(RC_OUTPUT);
  
  // Force ADC initialization
  analogRead(pots[0]);
  
  // Start serial interface
  Serial.begin(9600);
  Serial.println("< Starting... >");
}

int i = 0;

void loop()
{
  // Start loop
  Serial.print("\t < Loop... "); Serial.print((i++), DEC); Serial.println(" >");
  
  // Get values
  for(int j = 0; j < 3; j++)
  {
    val[j] = GetValue(pots[j]);
  }
  
  // Calculate new servo min, max and position
  servoMin = map(val[1], POT_ADC_VAL_MIN, POT_ADC_VAL_MAX, RC_MIN_RANGE_MIN, RC_MIN_RANGE_MAX);
  servoMax = map(val[2], POT_ADC_VAL_MIN, POT_ADC_VAL_MAX, RC_MAX_RANGE_MIN, RC_MAX_RANGE_MAX);
  
  // Correct min/max mapping to keep RC_CENTER as the center.
  if(val[0] < POT_ADC_VAL_CENTER)
  {
    servoPos = map(val[0], POT_ADC_VAL_MIN, (POT_ADC_VAL_CENTER - 1), servoMin, RC_CENTER);
  }
  else // (val[0] >= POT_ADC_VAL_CENTER)
  {
    servoPos = map(val[0], POT_ADC_VAL_CENTER, POT_ADC_VAL_MAX, RC_CENTER, servoMax);
  }

  // Update RC signal output
  outputRC.writeMicroseconds(servoPos);
  
  // Output values
  Serial.println("\t\t< Values >");
  for(int j = 0; j < 3; j++)
  {
    Serial.print("\t\t\tVal["); Serial.print(j, DEC); Serial.print("] = "); Serial.println(val[j]);
  }
  
  // Output RC value
  Serial.println("\t\t< RC signal >");
  Serial.print("\t\t\tServo position = "); Serial.print(servoPos); Serial.println(" us");
  Serial.print("\t\t\tServo min =      "); Serial.print(servoMin); Serial.println(" us");
  Serial.print("\t\t\tServo max =      "); Serial.print(servoMax); Serial.println(" us");
  
  // Wait for next loop (The delay should be shorter if the Serial.print are disabled to have a more responsive system)
  delay(100);
}

// Does the process
int GetValue(int apin)
{
    int val;
    int temp[2];
    
    // Ready the analog converter (and wait for initialization)
    analogRead(apin);
    delayMicroseconds(100);

    // Get readings
    temp[0] = analogRead(apin);
    temp[1] = analogRead(apin);

    // Calculate average
    val = (temp[0] + temp[1]) / 2;

    return val;
}
