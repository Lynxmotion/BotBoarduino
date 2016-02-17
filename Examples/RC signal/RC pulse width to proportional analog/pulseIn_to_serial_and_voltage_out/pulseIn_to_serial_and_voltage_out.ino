// Setup constants
#define RC_input  12        // Input signal from RC receiver
#define A_output  11        // Output signal (PWM/analog approximation) from microcontroller

// RC pulse width signal
//#define CST_RC_MIN      1000   // Typical RC receiver are 1000-2000 us, 1500 center.
//#define CST_RC_MAX      2000
//#define CST_RC_CENTER   1500
#define CST_RC_MIN       500     // Advanced RC receivers and microcontrollers can use extended ranges, such as the SSC-32U [RB-Lyn-850].
#define CST_RC_MAX      2500
#define CST_RC_CENTER   1500

// Analog conversion
#define CST_ANALOG_MIN    0     // Fully off. In reality, the analog voltage is simulated and should may be still a bit higher than 0 V DC. We recommend that you use a minimum higher than 0, at least 10-15.
#define CST_ANALOG_MAX  255     // Fully on.

// Note: To get a proper analog voltage out of the PWM output, a low-pass filter (single pole) should be used on the PWM output before being used as an analog value.

void setup()
{
  Serial.begin(9600);
  Serial.println("< Starting >");
  delay(1000);
}

// Variables
int pulseWidth;
int analogOut;
double voltageApprox;
double percentageVCC;

void loop()
{
  Serial.println("\t> Loop start...");
  
  // Obtain length of pulse (in us) from RC receiver signal
  pulseWidth = pulseIn(RC_input, HIGH);
  Serial.print("\t\t>> Raw input signal: "); Serial.print(pulseWidth, DEC); Serial.println(" us");
  
  // Map the pulse width to its equivalent analog range
  pulseWidth = constrain(pulseWidth, CST_RC_MIN, CST_RC_MAX);
  Serial.print("\t\t>> Contrained input signal: "); Serial.print(pulseWidth, DEC); Serial.println(" us");
  analogOut = map(pulseWidth, CST_RC_MIN, CST_RC_MAX, CST_ANALOG_MIN, CST_ANALOG_MAX);
  Serial.print("\t\t>> Raw analog output: "); Serial.print(analogOut, DEC); Serial.println("");
  
  // Calculate voltage approximation and percentage of VCC
  voltageApprox = (((double)analogOut * 5) / 256);
  Serial.print("\t\t>> Voltage approximation: "); Serial.print(voltageApprox, DEC); Serial.println(" V DC");
  percentageVCC = (((double)analogOut * 100) / 256);
  Serial.print("\t\t>> Percentage of VCC: "); Serial.print(percentageVCC, DEC); Serial.println(" %");
  
  // Output the voltage (PWM output)
  analogWrite(A_output, analogOut);

  // Pause
  delay(1000);
}
