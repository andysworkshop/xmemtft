#include <avr/pgmspace.h>
#include "Font.h"

namespace lcd {

  // byte definitions for FDEF_APPLE

  const uint8_t __attribute__((progmem)) FDEF_APPLE32_BYTES[] PROGMEM={ 0,0,0,0,0,0,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE33_BYTES[] PROGMEM={ 8,8,8,8,8,0,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE34_BYTES[] PROGMEM={ 20,20,20,0,0,0,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE35_BYTES[] PROGMEM={ 20,20,62,20,62,20,20,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE36_BYTES[] PROGMEM={ 8,60,10,28,40,30,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE37_BYTES[] PROGMEM={ 3,35,16,8,4,98,96,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE38_BYTES[] PROGMEM={ 4,10,10,4,42,18,44,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE39_BYTES[] PROGMEM={ 8,8,8,0,0,0,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE40_BYTES[] PROGMEM={ 16,8,4,4,4,8,16,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE41_BYTES[] PROGMEM={ 8,16,32,32,32,16,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE42_BYTES[] PROGMEM={ 8,42,28,8,28,42,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE43_BYTES[] PROGMEM={ 0,8,8,62,8,8,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE44_BYTES[] PROGMEM={ 0,0,0,0,16,16,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE45_BYTES[] PROGMEM={ 0,0,0,62,0,0,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE46_BYTES[] PROGMEM={ 0,0,0,0,0,0,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE47_BYTES[] PROGMEM={ 0,32,16,8,4,2,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE48_BYTES[] PROGMEM={ 28,34,50,42,38,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE49_BYTES[] PROGMEM={ 8,12,8,8,8,8,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE50_BYTES[] PROGMEM={ 28,34,32,24,4,2,62,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE51_BYTES[] PROGMEM={ 62,32,16,24,32,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE52_BYTES[] PROGMEM={ 16,24,20,18,62,16,16,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE53_BYTES[] PROGMEM={ 62,2,30,32,32,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE54_BYTES[] PROGMEM={ 56,4,2,30,34,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE55_BYTES[] PROGMEM={ 62,32,16,8,4,4,4,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE56_BYTES[] PROGMEM={ 28,34,34,28,34,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE57_BYTES[] PROGMEM={ 28,34,34,60,32,16,14,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE58_BYTES[] PROGMEM={ 0,0,8,0,8,0,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE59_BYTES[] PROGMEM={ 0,0,8,0,8,8,4,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE60_BYTES[] PROGMEM={ 16,8,4,2,4,8,16,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE61_BYTES[] PROGMEM={ 0,0,62,0,62,0,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE62_BYTES[] PROGMEM={ 4,8,16,32,16,8,4,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE63_BYTES[] PROGMEM={ 28,34,16,8,8,0,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE64_BYTES[] PROGMEM={ 28,34,42,58,26,2,60,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE65_BYTES[] PROGMEM={ 8,20,34,34,62,34,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE66_BYTES[] PROGMEM={ 30,34,34,30,34,34,30,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE67_BYTES[] PROGMEM={ 28,34,2,2,2,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE68_BYTES[] PROGMEM={ 30,34,34,34,34,34,30,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE69_BYTES[] PROGMEM={ 62,2,2,30,2,2,62,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE70_BYTES[] PROGMEM={ 62,2,2,30,2,2,2,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE71_BYTES[] PROGMEM={ 60,2,2,2,50,34,60,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE72_BYTES[] PROGMEM={ 34,34,34,62,34,34,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE73_BYTES[] PROGMEM={ 28,8,8,8,8,8,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE74_BYTES[] PROGMEM={ 32,32,32,32,32,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE75_BYTES[] PROGMEM={ 34,18,10,6,10,18,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE76_BYTES[] PROGMEM={ 2,2,2,2,2,2,62,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE77_BYTES[] PROGMEM={ 34,54,42,42,34,34,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE78_BYTES[] PROGMEM={ 34,34,38,42,50,34,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE79_BYTES[] PROGMEM={ 28,34,34,34,34,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE80_BYTES[] PROGMEM={ 30,34,34,30,2,2,2,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE81_BYTES[] PROGMEM={ 28,34,34,34,42,18,44,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE82_BYTES[] PROGMEM={ 30,34,34,30,10,18,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE83_BYTES[] PROGMEM={ 28,34,2,28,32,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE84_BYTES[] PROGMEM={ 62,8,8,8,8,8,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE85_BYTES[] PROGMEM={ 34,34,34,34,34,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE86_BYTES[] PROGMEM={ 34,34,34,34,34,20,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE87_BYTES[] PROGMEM={ 34,34,34,42,42,54,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE88_BYTES[] PROGMEM={ 34,34,20,8,20,34,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE89_BYTES[] PROGMEM={ 34,34,20,8,8,8,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE90_BYTES[] PROGMEM={ 62,32,16,8,4,2,62,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE91_BYTES[] PROGMEM={ 62,6,6,6,6,6,62,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE92_BYTES[] PROGMEM={ 0,2,4,8,16,32,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE93_BYTES[] PROGMEM={ 62,48,48,48,48,48,62,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE94_BYTES[] PROGMEM={ 0,0,8,20,34,0,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE95_BYTES[] PROGMEM={ 0,0,0,0,0,0,0,127,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE96_BYTES[] PROGMEM={ 4,8,16,0,0,0,0,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE97_BYTES[] PROGMEM={ 0,0,28,32,60,34,60,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE98_BYTES[] PROGMEM={ 2,2,30,34,34,34,30,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE99_BYTES[] PROGMEM={ 0,0,60,2,2,2,60,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE100_BYTES[] PROGMEM={ 32,32,60,34,34,34,60,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE101_BYTES[] PROGMEM={ 0,0,28,34,62,2,60,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE102_BYTES[] PROGMEM={ 24,36,4,30,4,4,4,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE103_BYTES[] PROGMEM={ 0,0,28,34,34,60,32,28,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE104_BYTES[] PROGMEM={ 2,2,30,34,34,34,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE105_BYTES[] PROGMEM={ 8,0,12,8,8,8,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE106_BYTES[] PROGMEM={ 16,0,24,16,16,16,18,12,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE107_BYTES[] PROGMEM={ 2,2,34,18,14,18,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE108_BYTES[] PROGMEM={ 12,8,8,8,8,8,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE109_BYTES[] PROGMEM={ 0,0,54,42,42,42,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE110_BYTES[] PROGMEM={ 0,0,30,34,34,34,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE111_BYTES[] PROGMEM={ 0,0,28,34,34,34,28,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE112_BYTES[] PROGMEM={ 0,0,30,34,34,34,30,2,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE113_BYTES[] PROGMEM={ 0,0,60,34,34,34,60,32,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE114_BYTES[] PROGMEM={ 0,0,58,6,2,2,2,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE115_BYTES[] PROGMEM={ 0,0,60,2,28,32,30,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE116_BYTES[] PROGMEM={ 8,8,60,8,8,72,48,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE117_BYTES[] PROGMEM={ 0,0,34,34,34,50,44,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE118_BYTES[] PROGMEM={ 0,0,34,34,34,20,8,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE119_BYTES[] PROGMEM={ 0,0,34,34,42,42,54,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE120_BYTES[] PROGMEM={ 0,0,34,20,8,20,34,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE121_BYTES[] PROGMEM={ 0,0,34,34,34,60,32,28,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE122_BYTES[] PROGMEM={ 0,0,62,16,8,4,62,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE123_BYTES[] PROGMEM={ 56,12,12,6,12,12,56,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE124_BYTES[] PROGMEM={ 8,8,8,8,8,8,8,8,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE125_BYTES[] PROGMEM={ 14,24,24,48,24,24,14,0,};
  const uint8_t __attribute__((progmem)) FDEF_APPLE126_BYTES[] PROGMEM={ 44,26,0,0,0,0,0,0,};

  // character definitions for FDEF_APPLE

  extern const struct FontChar __attribute__((progmem)) FDEF_APPLE_CHAR[] PROGMEM={
    { 32,8,FDEF_APPLE32_BYTES },
    { 33,8,FDEF_APPLE33_BYTES },
    { 34,8,FDEF_APPLE34_BYTES },
    { 35,8,FDEF_APPLE35_BYTES },
    { 36,8,FDEF_APPLE36_BYTES },
    { 37,8,FDEF_APPLE37_BYTES },
    { 38,8,FDEF_APPLE38_BYTES },
    { 39,8,FDEF_APPLE39_BYTES },
    { 40,8,FDEF_APPLE40_BYTES },
    { 41,8,FDEF_APPLE41_BYTES },
    { 42,8,FDEF_APPLE42_BYTES },
    { 43,8,FDEF_APPLE43_BYTES },
    { 44,8,FDEF_APPLE44_BYTES },
    { 45,8,FDEF_APPLE45_BYTES },
    { 46,8,FDEF_APPLE46_BYTES },
    { 47,8,FDEF_APPLE47_BYTES },
    { 48,8,FDEF_APPLE48_BYTES },
    { 49,8,FDEF_APPLE49_BYTES },
    { 50,8,FDEF_APPLE50_BYTES },
    { 51,8,FDEF_APPLE51_BYTES },
    { 52,8,FDEF_APPLE52_BYTES },
    { 53,8,FDEF_APPLE53_BYTES },
    { 54,8,FDEF_APPLE54_BYTES },
    { 55,8,FDEF_APPLE55_BYTES },
    { 56,8,FDEF_APPLE56_BYTES },
    { 57,8,FDEF_APPLE57_BYTES },
    { 58,8,FDEF_APPLE58_BYTES },
    { 59,8,FDEF_APPLE59_BYTES },
    { 60,8,FDEF_APPLE60_BYTES },
    { 61,8,FDEF_APPLE61_BYTES },
    { 62,8,FDEF_APPLE62_BYTES },
    { 63,8,FDEF_APPLE63_BYTES },
    { 64,8,FDEF_APPLE64_BYTES },
    { 65,8,FDEF_APPLE65_BYTES },
    { 66,8,FDEF_APPLE66_BYTES },
    { 67,8,FDEF_APPLE67_BYTES },
    { 68,8,FDEF_APPLE68_BYTES },
    { 69,8,FDEF_APPLE69_BYTES },
    { 70,8,FDEF_APPLE70_BYTES },
    { 71,8,FDEF_APPLE71_BYTES },
    { 72,8,FDEF_APPLE72_BYTES },
    { 73,8,FDEF_APPLE73_BYTES },
    { 74,8,FDEF_APPLE74_BYTES },
    { 75,8,FDEF_APPLE75_BYTES },
    { 76,8,FDEF_APPLE76_BYTES },
    { 77,8,FDEF_APPLE77_BYTES },
    { 78,8,FDEF_APPLE78_BYTES },
    { 79,8,FDEF_APPLE79_BYTES },
    { 80,8,FDEF_APPLE80_BYTES },
    { 81,8,FDEF_APPLE81_BYTES },
    { 82,8,FDEF_APPLE82_BYTES },
    { 83,8,FDEF_APPLE83_BYTES },
    { 84,8,FDEF_APPLE84_BYTES },
    { 85,8,FDEF_APPLE85_BYTES },
    { 86,8,FDEF_APPLE86_BYTES },
    { 87,8,FDEF_APPLE87_BYTES },
    { 88,8,FDEF_APPLE88_BYTES },
    { 89,8,FDEF_APPLE89_BYTES },
    { 90,8,FDEF_APPLE90_BYTES },
    { 91,8,FDEF_APPLE91_BYTES },
    { 92,8,FDEF_APPLE92_BYTES },
    { 93,8,FDEF_APPLE93_BYTES },
    { 94,8,FDEF_APPLE94_BYTES },
    { 95,8,FDEF_APPLE95_BYTES },
    { 96,8,FDEF_APPLE96_BYTES },
    { 97,8,FDEF_APPLE97_BYTES },
    { 98,8,FDEF_APPLE98_BYTES },
    { 99,8,FDEF_APPLE99_BYTES },
    { 100,8,FDEF_APPLE100_BYTES },
    { 101,8,FDEF_APPLE101_BYTES },
    { 102,8,FDEF_APPLE102_BYTES },
    { 103,8,FDEF_APPLE103_BYTES },
    { 104,8,FDEF_APPLE104_BYTES },
    { 105,8,FDEF_APPLE105_BYTES },
    { 106,8,FDEF_APPLE106_BYTES },
    { 107,8,FDEF_APPLE107_BYTES },
    { 108,8,FDEF_APPLE108_BYTES },
    { 109,8,FDEF_APPLE109_BYTES },
    { 110,8,FDEF_APPLE110_BYTES },
    { 111,8,FDEF_APPLE111_BYTES },
    { 112,8,FDEF_APPLE112_BYTES },
    { 113,8,FDEF_APPLE113_BYTES },
    { 114,8,FDEF_APPLE114_BYTES },
    { 115,8,FDEF_APPLE115_BYTES },
    { 116,8,FDEF_APPLE116_BYTES },
    { 117,8,FDEF_APPLE117_BYTES },
    { 118,8,FDEF_APPLE118_BYTES },
    { 119,8,FDEF_APPLE119_BYTES },
    { 120,8,FDEF_APPLE120_BYTES },
    { 121,8,FDEF_APPLE121_BYTES },
    { 122,8,FDEF_APPLE122_BYTES },
    { 123,8,FDEF_APPLE123_BYTES },
    { 124,8,FDEF_APPLE124_BYTES },
    { 125,8,FDEF_APPLE125_BYTES },
    { 126,8,FDEF_APPLE126_BYTES },
  };

}
