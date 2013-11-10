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

/** @file types.hpp
 *  Low-level type definitions to handle fixed width types portably.
 */

#ifndef TYPES_HPP
#define TYPES_HPP

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#ifdef HAVE_STDINT_H
	#include <stdint.h>
#endif // HAVE_STDINT_H
#ifdef HAVE_INTTYPES_H
	#include <inttypes.h>
#endif // HAVE_INTTYPES_H
#ifdef HAVE_SYS_TYPES_H
	#include <sys/types.h>
#endif // HAVE_SYS_TYPES_H

#if defined (HAVE_STDINT_H)
	typedef int8_t int8;
	typedef uint8_t uint8;
	typedef int16_t int16;
	typedef uint16_t uint16;
	typedef int32_t int32;
	typedef uint32_t uint32;
	typedef int64_t int64;
	typedef uint64_t uint64;
#elif defined (HAVE_INTTYPES_H)
	typedef int8_t int8;
	typedef uint8_t uint8;
	typedef int_16_t int16;
	typedef uint16_t uint16;
	typedef int32_t int32;
	typedef uint32_t uint32;
	typedef int64_t int64;
	typedef uint64_t uint64;
#elif defined (HAVE_SYS_TYPES_H)
	typedef int8_t int8;
	typedef u_int8_t uint8;
	typedef int16_t int16;
	typedef u_int16_t uint16;
	typedef int32_t int32;
	typedef u_int32_t uint32;
	typedef int64_t int64;
	typedef u_int64_t uint64;
#else
	// TODO: Add a fall-back type detection to the configure script
	#error No way to derive fixed-width variable types
#endif

typedef uint8 byte;
typedef unsigned int uint;

#endif // TYPES_HPP
