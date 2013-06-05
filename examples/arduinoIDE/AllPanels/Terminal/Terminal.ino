/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */
 
#include "Nokia6300.h"
#include "Font_apple.h"

using namespace lcd;

typedef Nokia6300_Portrait_262K TftPanel;
typedef Nokia6300_Terminal_Portrait_262K TerminalAccess;

TftPanel *tft;
DefaultBacklight *backlight;
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

  tft=new TftPanel;

  // clear to black

  tft->setBackground(ColourNames::BLACK);
  tft->clearScreen();

  // create a terminal implementation
  // the font must be fixed width

  font=new Font_APPLE8;
  terminal=new TerminalAccess(tft,font);

  tft->setForeground(ColourNames::WHITE);
  tft->setBackground(ColourNames::BLACK);
  
  // fade up the backlight to 100% in 4ms steps (400ms total)

  backlight->fadeTo(100,4);
}


void loop() {

  const char *ptr;
  int i;
  char c;

  terminal->clearScreen();

  // demo the terminal as a progress indicator

  *terminal << "Loading assets...\n";

  for(i=0;i<=100;i++) {

    terminal->clearLine();
    *terminal << i << '%';

    delay(50);
  }

  // demo the terminal as an output device

  terminal->writeString("\n\n");

  ptr=demoText;
  for(c=pgm_read_byte(ptr++);c;c=pgm_read_byte(ptr++)) {

    *terminal << c;
    delay(rand() % 60);
  }
}

