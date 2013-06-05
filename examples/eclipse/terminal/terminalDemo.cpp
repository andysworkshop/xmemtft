/*
 * main.cpp
 *
 *  Created on: 8 Apr 2012
 *      Author: Andy
 */

//#include "NokiaN95_8Gb.h"
//#include "Nokia6300.h"
//#include "NokiaN82.h"
//#include "NokiaE73.h"
//#include "Generic16BitHX8347A.h"
#include "Generic16BitILI9327.h"
#include "Font_apple.h"
#include "drv/accessModes/Xmem16AccessMode.h"

using namespace lcd;

extern "C" void __cxa_pure_virtual() { for(;;); }


void *operator new(size_t size_,void *ptr_) {
	return ptr_;
}
void *operator new(size_t size_) {
	return malloc(size_);
}
void operator delete(void *ptr_) {
	free(ptr_);
}


int main(void) {

	init();
  setup();

  for(;;)
    loop();

  return 0; // not reached
}


/*
 * The orientation and colour depth that we will use
 */

//typedef Nokia6300_Landscape_262K_Gpio LcdAccess;
//typedef Nokia6300_Terminal_Landscape_262K_Gpio TerminalAccess;
//typedef NokiaN95_8Gb_Portrait_262K_TypeB LcdAccess;
//typedef NokiaN95_8Gb_Terminal_Portrait_262K_TypeB TerminalAccess;
//typedef NokiaN82_Portrait_262K LcdAccess;
//typedef NokiaN82_Terminal_Portrait_262K TerminalAccess;
//typedef NokiaE73_Landscape_16M LcdAccess;
//typedef NokiaE73_Terminal_Landscape_16M TerminalAccess;
typedef ILI9327_400x240_Portrait_64K_Gpio LcdAccess;
typedef ILI9327_400x240_Terminal_Portrait_64K_Gpio TerminalAccess;

DefaultBacklight *backlight;
LcdAccess *tft;
TerminalAccess *terminal;
Font *font;


/*
 * Demo text
 */

static const char  __attribute__((progmem)) demoText[] PROGMEM="\
Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n\n\
Mauris malesuada ornare mi, id semper eros congue nec.\n\n\
Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Aenean nec arcu ac lorem pulvinar pretium. Etiam at ultricies est.\n\n\
Nunc nisl justo, ullamcorper vitae laoreet sit amet, tristique id est. Nulla imperdiet, massa et tincidunt ultricies, quam magna blandit nulla, vel aliquam tellus ipsum nec erat.\n\n\
Suspendisse dignissim consectetur iaculis. Morbi vel felis quis nibh placerat porttitor eu dignissim mauris. Nunc posuere tincidunt felis elementum molestie.\n\n\
Nunc nulla sem, imperdiet nec ullamcorper at, feugiat eu metus. Nunc congue congue lectus, sed accumsan metus hendrerit in.\n\n\
Nulla non vestibulum leo. Nam sodales dignissim libero non ultrices.\n\n\
Maecenas eget justo nunc. Aliquam erat volutpat. Ut pulvinar, massa id adipiscing blandit, ligula purus rhoncus ante, sed scelerisque tortor magna gravida libero.\n\n\
Curabitur eget neque nec ante porttitor ornare. Morbi congue fermentum pellentesque. Suspendisse nisi tellus, suscipit sed congue ac, accumsan ac quam.\n\n\
Nullam ullamcorper purus vitae diam vestibulum ultrices. Nullam vel libero ut justo imperdiet lobortis. Nullam sed lorem vitae nulla mattis faucibus.\n\n\
Sed a turpis non turpis ullamcorper hendrerit. Nulla et magna ac nunc tristique fermentum eget in ante.";


void setup() {

	// create a backlight controller and use it
  // to switch the backlight off

  backlight=new DefaultBacklight;
  backlight->setPercentage(0);

  // reset and initialise the panel

  tft=new LcdAccess;

  // create a terminal implementation

  font=new Font_APPLE8;
  terminal=new TerminalAccess(tft,font);

  tft->setForeground(ColourNames::WHITE);
  tft->setBackground(ColourNames::BLACK);

  terminal->clearScreen();
  backlight->fadeTo(100,4);
/*
  // fade up the backlight to 100% in 4ms steps (400ms total)

  backlight->fadeTo(100,4);

  uint32_t testColours[]= {
    ColourNames::BLUE,
    ColourNames::GREEN,
    ColourNames::RED,
    ColourNames::BLACK,
    ColourNames::WHITE,
    ColourNames::MAGENTA,
    ColourNames::CYAN,
    ColourNames::YELLOW
  };

  *tft << *font;

  for(;;) {

		for(uint16_t i=0;i<sizeof(testColours)/sizeof(testColours[0]);i++) {

			LcdAccess::UnpackedColour cr;

			tft->unpackColour(testColours[i],cr);
			tft->moveTo(
				Rectangle(
						0,
						0,
						tft->getWidth(),
						tft->getHeight()
				)
			);

			tft->fillPixels(40,cr);

#if 0
			tft->setBackground(testColours[i]);

			uint32_t now=millis();
			tft->clearScreen();
			uint32_t total=millis()-now;

			*tft << Point(0,0) << (int32_t)total << "ms.";
#endif

			delay(1000);
		}
  }


*/

//  *tft << Point(0,24) << *font << "Lorem ipsum dolor sit amet";
//  *tft << *font << Point(120,0) << "o";
/*
  Xmem16AccessMode::writeCommand(ili9327::SET_COLUMN_ADDRESS);
	Xmem16AccessMode::writeData(0);
	Xmem16AccessMode::writeData(0);
	Xmem16AccessMode::writeData(0);
	Xmem16AccessMode::writeData(7);

	Xmem16AccessMode::writeCommand(ili9327::SET_PAGE_ADDRESS);
	Xmem16AccessMode::writeData(0);
	Xmem16AccessMode::writeData(0);
	Xmem16AccessMode::writeData(0);
	Xmem16AccessMode::writeData(7);

	Xmem16AccessMode::writeCommand(ili9327::WRITE_MEMORY_START);

	for(int i=0;i<64;i++) {
		Xmem16AccessMode::writeData(0xff,0xff);
	}
*/

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  delay(5000);
  digitalWrite(13,LOW);
  tft->fillRectangle(Rectangle(120,0,8,8));

 for(;;);
}


void loop() {

	const char *ptr;
	int i;
	char c;

	tft->setForeground(ColourNames::WHITE);
	tft->setBackground(ColourNames::BLACK);

	for(;;) {

		terminal->clearScreen();

		// demo the terminal as a progress indicator

		*terminal << "Loading assets...\n";

		for(i=0;i<100;i++) {

			terminal->clearLine();
			*terminal << i << '%';

			delay(50);
		}

		// demo the terminal as an output device

		terminal->writeString("\n\n");

		ptr=demoText;
		for(c=pgm_read_byte(ptr++);c;c=pgm_read_byte(ptr++)) {

			*terminal << c;
			delay(rand() % 50);
		}
	}
}
