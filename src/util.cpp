/* FX2LPTool - Tool to manipulate Cypress EZ-USB FX2LP devices.
 *
 * FX2LPTool is the legal property of its developers, whose names can be
 * found in the AUTHORS file distributed with this source
 * distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/** @file util.cpp
 *  Utility templates and functions.
 */

#include "util.hpp"
#include "error.hpp"

#include <cstdio>
#include <cstdlib>

void warning(const char *s, ...) {
	char buf[STRINGBUFLEN];
	va_list va;

	va_start(va, s);
	vsnprintf(buf, STRINGBUFLEN, s, va);
	va_end(va);

#ifndef DISABLE_TEXT_CONSOLE
	std::fputs("WARNING: ", stderr);
	std::fputs(buf, stderr);
	std::fputs("!\n", stderr);
#endif
}

void status(const char *s, ...) {
	char buf[STRINGBUFLEN];
	va_list va;

	va_start(va, s);
	vsnprintf(buf, STRINGBUFLEN, s, va);
	va_end(va);

#ifndef DISABLE_TEXT_CONSOLE
	std::fputs(buf, stderr);
	std::fputs("\n", stderr);
#endif
}

void NORETURN_PRE error(const char *s, ...) {
	char buf[STRINGBUFLEN];
	va_list va;

	va_start(va, s);
	vsnprintf(buf, STRINGBUFLEN, s, va);
	va_end(va);

#ifndef DISABLE_TEXT_CONSOLE
	std::fputs("ERROR: ", stderr);
	std::fputs(buf, stderr);
	std::fputs("!\n", stderr);
#endif

	std::exit(1);
}

static uint8 convertCharToHexDigit(char c) {
	if ((c >= '0') && (c <= '9'))
		return c - '0';
	if ((c >= 'A') && (c <= 'F'))
		return c - 'A' + 10;
	if ((c >= 'a') && (c <= 'f'))
		return c - 'a' + 10;

	throw Exception("Invalid hex digit (0x%02X)", c);
}

uint8 convertStringToHexByte(const char *s) {
	return convertCharToHexDigit(s[0]) << 4 | convertCharToHexDigit(s[1]);
}

uint16 convertStringToHexWord(const char *s) {
	return convertCharToHexDigit(s[0]) << 12 | convertCharToHexDigit(s[1]) << 8 |
	       convertCharToHexDigit(s[2]) <<  4 | convertCharToHexDigit(s[3]);
}
