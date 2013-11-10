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

/** @file fx2lptool.cpp
 *  The project's main entry point.
 */

#include <stdio.h>
#include <libusb.h>

#include "util.hpp"
#include "error.hpp"
#include "fx2lp.hpp"

int main(void) {
	try {
		FX2LP fx2lp(0x0925, 0x3881);

		fx2lp.init();

		byte data[8];
		fx2lp.readEEPROM(data, 8);

		printf("Got data: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
		       data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);

		printf("Verifying vendor/product ID... %s\n", fx2lp.verifyVendorProductID() ? "pass" : "fail");

	} catch(Exception &e) {
		printException(e);
		return -1;
	}

	return 0;
}
