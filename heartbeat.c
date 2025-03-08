/*************************************************************************
* Title		: heartbeat.c
* Author	: Dimitri Dening
* Created	: 08.03.2025 19:02:43
* Software	: Microchip Studio V7
* Hardware	: Atmega2560
* License	: MIT License
* Usage		: see Doxygen manual
*
*       Copyright (C) 2025 Dimitri Dening
*
*       Permission is hereby granted, free of charge, to any person obtaining a copy
*       of this software and associated documentation files (the "Software"), to deal
*       in the Software without restriction, including without limitation the rights
*       to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*       copies of the Software, and to permit persons to whom the Software is
*       furnished to do so, subject to the following conditions:
*
*       The above copyright notice and this permission notice shall be included in all
*       copies or substantial portions of the Software.
*
*       THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*       IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*       FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*       AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*       LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*       OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*       SOFTWARE.
*
*************************************************************************/

/* General libraries */
#include <avr/io.h>
#include <avr/interrupt.h>

/* User defined libraries */
#include "led_lib.h"

static void timer1_init(void) {
	// Set Timer1 to CTC mode
	TCCR1B |= (1 << WGM12);
	
	// Set prescaler to 1024
	TCCR1B |= (1 << CS12) | (1 << CS10);

	// Set compare match value for 1s interval (assuming 10MHz clock)
	OCR1A = 9765;

	// Enable Timer1 Compare Match A interrupt
	TIMSK1 |= (1 << OCIE1A);

	// Enable global interrupts
	// sei();
}

ISR(TIMER1_COMPA_vect) {
	led_toggle(LED_HEARTBEAT);
}

void heartbeat_init(void) {
	
	timer1_init();
}
