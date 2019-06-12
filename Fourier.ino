#include <U8glib.h>
#include "arduinoFFT.h"

// Crear objeto pantalla
U8GLIB_ST7920_128X64 u8g(13, 11, 12, U8G_PIN_NONE);

#define MUESTRAS 128             // Potencia de 2
#define FRECUENCIA_SAMPLEO 1000 //Hz


arduinoFFT FFT = arduinoFFT();

unsigned int periodo;
unsigned long tiempo;


double vReal[MUESTRAS];
double vImag[MUESTRAS];

void draw(double* datos)
{
  int index = 0;
  for (int i = 1; i < 128; i += 4)
  {
    if(datos[index] > 127)
    {
      //(x, y, ancho, alto)
      u8g.drawBox(i, 1, 2, 127);
    }
    else{
      u8g.drawBox(i, 1, 2, (int)datos[index]);
    }
    ++index;
  }
}

void setup(void)
{
  Serial.begin(9600);
  periodo = round(1000000 * (1.0 / FRECUENCIA_SAMPLEO));
}

void loop(void) {
  u8g.firstPage();
  //obtener muestras
  for (int i = 0; i < MUESTRAS; i++)
  {
    tiempo = micros();

    vReal[i] = analogRead(0);
    vImag[i] = 0;


    while (micros() < (tiempo + periodo)) {
    }
  }

  // realizar fft
  FFT.Windowing(vReal, MUESTRAS, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, MUESTRAS, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, MUESTRAS);

  //graficar
  do {
    draw(vReal);

  } while ( u8g.nextPage() );
  delay(200);
}
