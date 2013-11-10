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

/** @file version.cpp
 *  Basic FX2LPTool version information
 */

#include "version.hpp"

#if defined(HAVE_CONFIG_H)
	#include "config.h"
#endif

// Define default values if the real ones can't be determined

#ifndef PACKAGE_NAME
	#define PACKAGE_NAME "FX2LPTool"
#endif

#ifndef PACKAGE_VERSION
	#define PACKAGE_VERSION "0.0.0"
#endif

#ifndef FX2LPTOOL_REVDESC
	#define FX2LPTOOL_REVDESC "unknown"
#endif

#ifndef FX2LPTOOL_REV
	#define FX2LPTOOL_REV "unk"
#endif

#ifndef FX2LPTOOL_BUILDDATE
	#define FX2LPTOOL_BUILDDATE __DATE__ " " __TIME__
#endif

// If we're in full release mode, the revision is ignored
#ifdef FX2LPTOOL_RELEASE
	#undef FX2LPTOOL_REV
	#define FX2LPTOOL_REV ""
#endif

// Distributions may append an extra version string
#ifdef FX2LPTOOL_DISTRO
	#undef FX2LPTOOL_REV
	#define FX2LPTOOL_REV FX2LPTOOL_DISTRO
#endif

const char *FX2LPTOOL_NAME            = PACKAGE_NAME;
const char *FX2LPTOOL_VERSION         = PACKAGE_VERSION;
const char *FX2LPTOOL_NAMEVERSION     = PACKAGE_NAME " " PACKAGE_VERSION FX2LPTOOL_REV;
const char *FX2LPTOOL_NAMEVERSIONFULL = PACKAGE_NAME " " PACKAGE_VERSION FX2LPTOOL_REV " [" FX2LPTOOL_REVDESC "] (" FX2LPTOOL_BUILDDATE ")";
