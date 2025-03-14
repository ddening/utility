/*************************************************************************
* Title		: utils.c
* Author	: Dimitri Dening
* Created	: 13.03.2025 16:37:33
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
#include <stdint.h>

/* User defined libraries */
#include "utils.h"

// Function to convert float to string manually (no %f dependency)
void float_to_string(float value, uint8_t* buffer, uint8_t buffer_size, uint8_t precision) {
	
	uint16_t whole = (uint16_t)value;  // Get integer part
	uint16_t decimal = (uint16_t)((value - whole) * 10 * precision); // Scale decimal part

	snprintf(buffer, buffer_size, "%d.%d", whole, decimal);
}