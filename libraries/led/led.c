/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 01/05/2023
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#define NUMBER_OF_LEDS 4

#include <util/delay.h>
#include <avr/io.h>

void enableLed(int lednumber) {
  if (lednumber < 0 || lednumber >= NUMBER_OF_LEDS) return; // Als lednumber niet tussen 0 en 3 is, return (dus stoppen)
  DDRB |= (1 << (PB2 + lednumber)); // Juiste pin op 1 zetten
}
 
void enableLeds(uint8_t leds) {
  leds &= 0b00001111;
  DDRB |= (leds << PB2); // Juiste pin op 1 zetten
}
 
void enableAllLeds() { enableLeds(0b00001111); } // Alle leds aanzetten
 
void lightUpLed(int lednumber) {
  if (lednumber < 0 || lednumber >= NUMBER_OF_LEDS) return; // Als lednumber niet tussen 0 en 3 is, return (dus stoppen)
  PORTB &= ~(1 << (PB2 + lednumber)); // Juiste pin op 0 zetten
}
 
void lightUpLeds(uint8_t leds) {
  leds &= 0b00001111;
  PORTB &= ~(leds << PB2); // Juiste pin op 0 zetten
}
 
void lightUpAllLeds() { lightUpLeds(0b00001111); } // Alle leds uitzetten
 
void lightDownLed(int lednumber) {
  if (lednumber < 0 || lednumber >= NUMBER_OF_LEDS) return; // Als lednumber niet tussen 0 en 3 is, return (dus stoppen)
  PORTB |= (1 << (PB2 + lednumber)); // Juiste pin op 1 zetten
}
 
void lightDownLeds(uint8_t leds) {
  leds &= 0b00001111;  
  PORTB |= (leds << PB2); // Juiste pin op 1 zetten
}
 
void lightDownAllLeds() { lightDownLeds(0b00001111); } // Alle leds uitzetten

void dimLed(int lednumber, int percentage, int duration) {
    for (int i = duration; i > 0; i -= 10) { // Is de opgegeven tijdsperiode. (Stap waarde 10)
        lightDownLed(lednumber); // Led x uitzetten.
        _delay_ms(percentage/10); // De tijd dat de Led uit moet staan. (Stap waarde 10)
        lightUpLed(lednumber); // Led x aanzetten.
        _delay_ms((100-percentage)/10); // De tijd dat de Led aan moet staan. (Stap waarde 10)
    }
}

void fadeInLed(int lednumber, int duration) {
    for (int percentage = 1; percentage <= 100; percentage++) { // Door alle mogelijke percentages gaan. (1% tot 100%)
        dimLed(lednumber, percentage, (duration/100));
    }
    lightUpLed(lednumber); // Eindpositie van Led.
}

void fadeOutLed(int lednumber, int duration) {
    for (int percentage = 100; percentage > 1; percentage--) { // Door alle mogelijke percentages gaan. (100% tot 1%)
        dimLed(lednumber, percentage, (duration/100));
    }
    lightDownLed(lednumber); // Eindpositie van Led.
}

void flipLed(int lednumber) {
  if (lednumber < 0 || lednumber >= NUMBER_OF_LEDS) return;

  // Huidige status van de LED lezen
  int pin_mask = (1 << (PB2 + lednumber)); // Aan is 1 | uit is 0
  int current_state = (PINB & pin_mask) ? 1 : 0;

  // Status van de LED omdraaien
  if (current_state) {
    lightDownLed(lednumber); // Als LED aanstaat, uitzetten
  } else {
    lightUpLed(lednumber); // Als LED uitstaat, aanzetten
  }
}

void flashLed(int lednumber, int duration) {
  int numFlickers = 5;
  if (lednumber < 0 || lednumber >= NUMBER_OF_LEDS) return;

  int flickerDuration = duration / numFlickers;
  for(int i = 0; i < numFlickers; i++) {
    lightUpLed(lednumber);
    _delay_ms(flickerDuration);
    lightDownLed(lednumber);
    _delay_ms(flickerDuration);
  }
}

void heartbeat(int duration) {
  lightUpAllLeds();
  _delay_ms(duration / 2);
  lightDownAllLeds();
  _delay_ms(duration / 2);
}

void countdown() {
  lightUpAllLeds();
  for (int i = 3; i >= 0; i--) {
    _delay_ms(500);
    lightDownLed(i);
  }
}