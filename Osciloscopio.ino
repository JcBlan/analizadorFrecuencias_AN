#include <U8glib.h>
U8GLIB_ST7920_128X64 u8g(13, 11, 12, U8G_PIN_NONE);

int x, y; int Buffer[128];

void setup( )
{
  Serial.begin(9600);
}
void loop( )
{
  int valor = 63;
  for (x = 0; x < 128; x++)
  {
    //Buffer[x] = 63 - (analogRead(A0) >> 4);   // Valor de lectura UTILIZAR ESTE

    
    Buffer[x] =  abs(63 * cos(x >> 2));    // Valor de prueba BORRAR
    
    //Serial.println(Buffer[x]);
  }
  u8g.firstPage();
  do
  {
    for (x = 0; x < 127; x++)
    {
      u8g.drawLine(x, Buffer[x], x, Buffer[x + 1]);
    }
    u8g.drawLine(64, 0, 64, 63);
    u8g.drawLine(0, 32, 128, 32);
    for (x = 0; x < 128; x += 8)
    {
      u8g.drawLine(x, 31, x, 33);
    }
    for (x = 0; x < 64; x += 8)
    {
      u8g.drawLine(63, x, 65, x);
    }
    u8g.drawFrame(0, 0, 128, 64);
  }
  while ( u8g.nextPage( ));
  delay(200);
}
