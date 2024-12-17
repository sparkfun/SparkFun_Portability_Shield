/*
  Read the 5-way switch and card detect on the Portability Shield
  By: Nathan Seidle
  SparkFun Electronics
  Date: November 24th, 2024
  License: This code is public domain but you buy me a drink if you use this
  and we meet someday (Drink license).
  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/27510

  This example demonstrates how to read the 5-way nav switch and detect if the SD card is inserted.
  The !INT pin of the GPIO expander IC (PCA9554) triggers an interrupt any time a button is pressed or
  an SD card is inserted/removed.

  Hardware Connections:
  Connect the Portability shield to the RTK Postcard or other controller board
  Open output window at 115200bps
  Press button on navigation switch
*/

#include <SparkFun_I2C_Expander_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_I2C_Expander_Arduino_Library

SFE_PCA95XX io(PCA95XX_PCA9554); // Create an instance with the PCA9554 IC

int gpioExpander_up = 0;
int gpioExpander_down = 1;
int gpioExpander_right = 2;
int gpioExpander_left = 3;
int gpioExpander_center = 4;
int gpioExpander_cardDetect = 5;

int gpioExpander_interrupt = 14; //INT of PCA9554 is connected to ESP14. Goes low when button is pressed.

bool buttonPressed = false;

void IRAM_ATTR gpioExpanderISR()
{
  buttonPressed = true;
}

void setup()
{
  Serial.begin(115200);
  delay(250);
  Serial.println("Portability Shield Example");

  Wire.begin(7, 20); //SDA, SCL. I2C0 on Portability Shield

  // Initialize the PCA95xx with its default I2C address
  if (io.begin() == false)
  {
    Serial.println("PCA9554 not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }
  Serial.println("Portability Shield online!");

  pinMode(gpioExpander_interrupt, INPUT_PULLUP);

  io.pinMode(gpioExpander_up, INPUT);
  io.pinMode(gpioExpander_down, INPUT);
  io.pinMode(gpioExpander_left, INPUT);
  io.pinMode(gpioExpander_right, INPUT);
  io.pinMode(gpioExpander_center, INPUT);
  io.pinMode(gpioExpander_cardDetect, INPUT);

  uint8_t currentState = io.getInputRegister() & 0b00111111; //Ignore unconnected GPIO6/7
  if (currentState & 0b00100000)
    Serial.println("SD Card detected");
  else
    Serial.println("No card detected");

  //Setup interrupt service routine (ISR)
  attachInterrupt(gpioExpander_interrupt, gpioExpanderISR, CHANGE);
}

void loop()
{
  if (buttonPressed == true)
  {
    //Get all the pins in one read
    uint8_t currentState = io.getInputRegister() & 0b00111111; //Ignore unconnected GPIO6/7

    // Pins are pulled high so when we see low, button is being pressed
    if ((currentState & (1 << gpioExpander_up)) == 0)
      Serial.print("Up");
    if ((currentState & (1 << gpioExpander_down)) == 0)
      Serial.print("Down");
    if ((currentState & (1 << gpioExpander_left)) == 0)
      Serial.print("Left");
    if ((currentState & (1 << gpioExpander_right)) == 0)
      Serial.print("Right");
    if ((currentState & (1 << gpioExpander_center)) == 0)
      Serial.print("Center");

    Serial.println();

    buttonPressed = false;
  }

  delay(100);
}
