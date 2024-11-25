/*
  Display a cube on the OLED at 400kHz. Query the fuel guage periodically.
  By: Nathan Seidle
  SparkFun Electronics
  Date: November 24th, 2024
  License: This code is public domain but you buy me a drink if you use this
  and we meet someday (Drink license).
  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/27510

  This example demonstrates how to display on the 1.3" OLED and read the fuel gauge.

  Hardware Connections:
  Connect the Portability shield to the RTK Postcard or other controller board
  Open output window at 115200bps
*/
#include <Wire.h>

#include <SparkFun_Qwiic_OLED.h> //http://librarymanager/All#SparkFun_Qwiic_OLED
Qwiic1in3OLED myOLED;

int width;
int height;

// For simple frame rate calculations
long drawTotalTime = 0;
int numberOfDraws = 0;

float d = 3;
float px[] = { -d, d, d, -d, -d, d, d, -d};
float py[] = { -d, -d, d, d, -d, -d, d, d};
float pz[] = { -d, -d, -d, -d, d, d, d, d};

float p2x[8] = {0};
float p2y[8] = {0};
float r[3] = {0};

#define SHAPE_SIZE 950
#define ROTATION_SPEED 00

#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library
SFE_MAX1704X lipo(MAX1704X_MAX17048);

double voltage = 0;
double soc = 0;
unsigned long lastLipoCheck;

void setup()
{
  Serial.begin(115200);
  delay(250);
  Serial.println("OLED + Fuel gauge test");

  Wire.begin(7, 20); //SDA, SCL
  Wire.setClock(400000); //Go to 400kHz for faster OLED response
  //Wire.setClock(1000000); //Moar! It's not 1MHz but it does work.

  if (myOLED.begin() == false)
  {
    Serial.println("Device begin failed. Freezing...");
    while (true);
  }

  if (lipo.begin() == false)
  {
    Serial.println("MAX17043 not detected. Please check wiring. Freezing...");
    while (1);
  }

  Serial.println("Begin success");

  width = myOLED.getWidth();
  height = myOLED.getHeight();

  // For frame rate calc
  drawTotalTime = 0;
  numberOfDraws = 0;
}

void loop()
{
  drawCube();

  if (millis() - lastLipoCheck > 1000)
  {
    lastLipoCheck = millis();
    voltage = lipo.getVoltage();
    soc = lipo.getSOC();
    
    Serial.print("Voltage: ");
    Serial.print(voltage);  // Print the battery voltage
    Serial.println(" V");

    Serial.print("Percentage: ");
    Serial.print(soc); // Print the battery state of charge
    Serial.println(" %");

    Serial.println();
  }
}

void drawCube()
{
  r[0] = r[0] + PI / 180.0; // Add a degree
  r[1] = r[1] + PI / 180.0; // Add a degree
  r[2] = r[2] + PI / 180.0; // Add a degree
  if (r[0] >= 360.0 * PI / 180.0)
    r[0] = 0;
  if (r[1] >= 360.0 * PI / 180.0)
    r[1] = 0;
  if (r[2] >= 360.0 * PI / 180.0)
    r[2] = 0;

  // This routine gets called often, so just make these statics
  static float px2, py2, pz2, px3, py3, pz3, ax, ay, az;

  for (int i = 0; i < 8; i++)
  {
    px2 = px[i];
    py2 = cos(r[0]) * py[i] - sin(r[0]) * pz[i];
    pz2 = sin(r[0]) * py[i] + cos(r[0]) * pz[i];

    px3 = cos(r[1]) * px2 + sin(r[1]) * pz2;
    py3 = py2;
    pz3 = -sin(r[1]) * px2 + cos(r[1]) * pz2;

    ax = cos(r[2]) * px3 - sin(r[2]) * py3;
    ay = sin(r[2]) * px3 + cos(r[2]) * py3;
    az = pz3 - 150;

    p2x[i] = width / 2 + ax * SHAPE_SIZE / az;
    p2y[i] = height / 2 + ay * SHAPE_SIZE / az;
  }

  // Calculate draw time
  uint32_t startTime = millis();

  myOLED.erase();
  for (int i = 0; i < 3; i++)
  {
    myOLED.line(p2x[i], p2y[i], p2x[i + 1], p2y[i + 1]);
    myOLED.line(p2x[i + 4], p2y[i + 4], p2x[i + 5], p2y[i + 5]);
    myOLED.line(p2x[i], p2y[i], p2x[i + 4], p2y[i + 4]);
  }

  myOLED.line(p2x[3], p2y[3], p2x[0], p2y[0]);
  myOLED.line(p2x[7], p2y[7], p2x[4], p2y[4]);
  myOLED.line(p2x[3], p2y[3], p2x[7], p2y[7]);
  myOLED.display();

  // Write out our frame rate
  drawTotalTime += millis() - startTime;
  numberOfDraws++;

  // Output framerate once every 120 frames
  if (numberOfDraws % 120 == 0)
  {
    Serial.print("Frame rate: ");
    Serial.println(numberOfDraws / (float)drawTotalTime * 1000.0);

    numberOfDraws = 0;
    drawTotalTime = 0;
  }
}
