#include <NeoCol.h>
#include <stdlib.h>

unsigned int8 NeoGreen [NeoNum];
unsigned int8 NeoBlue [NeoNum];
unsigned int8 NeoRed [NeoNum];

void NeoBit (int Bit)
{
   if (Bit == 1)
   { output_high (NeoPin); delay_cycles (6); output_low (NeoPin); } // delay_cycles (3); // Bit '1'
   else
   { output_high (NeoPin); delay_cycles (3); output_low (NeoPin); } // delay_cycles (6); // Bit '0'
}
void NeoInit (void)
{
   unsigned int8 NeoPixel;
   for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)
   {
      if (NeoPixel < 3)
         { NeoGreen[NeoPixel] = 64; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; }
      else if ((NeoPixel >= 3) & (NeoPixel < 6))
         { NeoGreen[NeoPixel] = 64; NeoBlue[NeoPixel] = 64; NeoRed[NeoPixel] = 0; }
      else if ((NeoPixel >= 6) & (NeoPixel < NeoNum))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 64; }
   }
}
void NeoDraw (void)
{
   unsigned int8 NeoPixel;
   signed int8 BitCount;
   for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)
   {
      for (BitCount = 7; BitCount >= 0; BitCount--)
         NeoBit(bit_test(NeoGreen[NeoPixel], BitCount));
      for (BitCount = 7; BitCount >= 0; BitCount--)
         NeoBit(bit_test(NeoRed[NeoPixel], BitCount));
      for (BitCount = 7; BitCount >= 0; BitCount--)
         NeoBit(bit_test(NeoBlue[NeoPixel], BitCount));
   }
   output_low (NeoPin);
}
void NeoRotate (void)
{
   unsigned int8 NeoPixel;
   for (NeoPixel = 0; NeoPixel < NeoNum - 1; NeoPixel++)
   {
      NeoGreen[NeoPixel] = NeoGreen[NeoPixel + 1];
      NeoBlue[NeoPixel] = NeoBlue[NeoPixel + 1];
      NeoRed[NeoPixel] = NeoRed[NeoPixel + 1];
   }
   NeoGreen[NeoNum - 1] = NeoGreen[0];
   NeoBlue[NeoNum - 1] = NeoBlue[0];
   NeoRed[NeoNum - 1] = NeoRed[0];
}
void main()
{
   NeoInit ();
   NeoDraw ();
   while(false)
   {
      NeoDraw ();
      NeoRotate ();
      delay_ms (25);
   }
}
