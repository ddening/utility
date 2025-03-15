/*************************************************************************
* Title		: memory.c
* Author	: Dimitri Dening
* Created	: 14.03.2025 15:15:35
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
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <util/delay.h>

/* User defined libraries */
#include "uart.h"

#define MAX_TRACK 100
#define MESSAGE_LENGTH 200
#define UART_DEBUG 1

typedef struct {
	void* ptr;
	size_t size;
	const char* file;
	int line;
} mem_track_t;

static mem_track_t mem_track[MAX_TRACK];
static size_t mem_count = 0;

void debug_log(const char* msg) {
	#if UART_DEBUG
	uart_put(msg);
	#else
	printf(msg);
	printf("\n");
	#endif
}

void* debug_malloc(size_t size, const char* file, int line) {
	void* ptr = malloc(size);
	if (ptr && mem_count < MAX_TRACK) {
		char msg[MESSAGE_LENGTH];
		mem_track[mem_count++] = (mem_track_t){ ptr, size, file, line };
		snprintf(msg, sizeof(msg), "Alloc %lu bytes at %s:%d", (unsigned long)size, file, line);
		debug_log(msg);
	}
	return ptr;
}

void debug_free(void* ptr, const char* file, int line) {
	char msg[MESSAGE_LENGTH];
	for (size_t i = 0; i < mem_count; i++) {
		if (mem_track[i].ptr == ptr) {
			snprintf(msg, sizeof(msg), "Freed %lu bytes from %s:%d", (unsigned long)mem_track[i].size, file, line);
			debug_log(msg);
			mem_track[i] = mem_track[--mem_count];  // Remove from tracking
			free(ptr);
			return;
		}
	}
	snprintf(msg, sizeof(msg), "Warning: Attempt to free untracked memory at %s:%d", file, line);
	debug_log(msg);
}

void memory_report(void) {
	_delay_ms(500);
	char msg[MESSAGE_LENGTH];
	snprintf(msg, sizeof(msg), "=== Memory Report ===");
	debug_log(msg);
	if (mem_count == 0) {
		snprintf(msg, sizeof(msg), "No memory leaks detected.");
		debug_log(msg);
	}
	else {
		for (size_t i = 0; i < mem_count; i++) {
			snprintf(msg, sizeof(msg), "Leaked %lu bytes at %s:%d",
			(unsigned long)mem_track[i].size, mem_track[i].file, mem_track[i].line);
			debug_log(msg);
		}
	}
}