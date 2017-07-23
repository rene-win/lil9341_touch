#include <stdint.h>
#include <SPI.h>
#include <ili9341_touch.h>


void setup()
{
    Serial.begin(115200);
    Tch.Init();
}

void loop()
{
  
  long x, y;
  
  while (Tch.dataAvailable() == true)
  {
    Tch.read();
    x = Tch.getX();
    y = Tch.getY();
    if ((x!=-1) and (y!=-1)) {
      Serial.print(x);
      Serial.print(',');
      Serial.println(y);
    }
  }
  
}
