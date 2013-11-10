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

// Mostly copied verbatim from ScummVM's

/** @file util.hpp
 *  Utility templates and functions.
 */

#ifndef UTIL_HPP
#define UTIL_HPP

#include <cmath>
#include <cstdarg>

#include "types.hpp"

#ifdef MIN
	#undef MIN
#endif

#ifdef MAX
	#undef MAX
#endif

#ifdef ARRAYSIZE
	#undef ARRAYSIZE
#endif

//
// GCC specific stuff
//
#if defined(__GNUC__)
	#define NORETURN_POST __attribute__((__noreturn__))
	#define PACKED_STRUCT __attribute__((__packed__))
	#define GCC_PRINTF(x,y) __attribute__((__format__(printf, x, y)))

	#if !defined(FORCEINLINE) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
		#define FORCEINLINE inline __attribute__((__always_inline__))
	#endif
#else
	#define PACKED_STRUCT
	#define GCC_PRINTF(x,y)
#endif

//
// Fallbacks / default values for various special macros
//
#ifndef FORCEINLINE
	#define FORCEINLINE inline
#endif

#ifndef NORETURN_PRE
	#define NORETURN_PRE
#endif

#ifndef NORETURN_POST
	#define NORETURN_POST
#endif

#ifndef STRINGBUFLEN
	#define STRINGBUFLEN 1024
#endif

#ifndef MAXPATHLEN
	#define MAXPATHLEN 256
#endif

template<typename T> inline T ABS (T x)      { return (x>=0) ? x : -x; }
template<typename T> inline T MIN (T a, T b) { return (a<b)  ? a :  b; }
template<typename T> inline T MAX (T a, T b) { return (a>b)  ? a :  b; }
template<typename T> inline T CLIP (T v, T amin, T amax)
	{ if (v < amin) return amin; else if (v > amax) return amax; else return v; }

/**
 * Template method which swaps the values of its two parameters.
 */
template<typename T> inline void SWAP(T &a, T &b) { T tmp = a; a = b; b = tmp; }

static inline uint32 NEXTPOWER2(uint32 x) {
	if (x == 0)
		return 1;

	x--;

	x |= x >> 1; x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16;

	return x + 1;
}

static inline uint64 NEXTPOWER2(uint64 x) {
	if (x == 0)
		return 1;

	x--;

	x |= x >> 1; x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16; x |= x >> 32;

	return x + 1;
}

#ifdef HAVE_FABS
template<> inline double ABS(double x) { return fabs(x); }
#endif
#ifdef HAVE_FABSF
template<> inline float ABS(float x) { return fabsf(x); }
#endif

#ifdef HAVE_FMIN
template<> inline double MIN(double a, double b) { return fmin(a, b); }
#endif
#ifdef HAVE_FMINF
template<> inline float MIN(float a, float b) { return fminf(a, b); }
#endif

#ifdef HAVE_FMAX
template<> inline double MAX(double a, double b) { return fmax(a, b); }
#endif
#ifdef HAVE_FMAXF
template<> inline float MAX(float a, float b) { return fmaxf(a, b); }
#endif

/**
 * Macro which determines the number of entries in a fixed size array.
 */
#define ARRAYSIZE(x) ((int)(sizeof(x) / sizeof(x[0])))

/**
* Print a warning message to the text console (stderr).
* Automatically prepends the text "WARNING: " and appends
* an exclamation mark and a newline.
*/
void warning(const char *s, ...) GCC_PRINTF(1, 2);
/**
* Print a status message to the text console (stderr).
* Automatically appends a newline.
*/
void status(const char *s, ...) GCC_PRINTF(1, 2);

void NORETURN_PRE error(const char *s, ...) GCC_PRINTF(1, 2) NORETURN_POST;

#endif // UTIL_HPP
