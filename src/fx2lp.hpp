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

/** @file fx2lpp.hpp
 *  Handling the FX2LP device fiddling.
 */

#ifndef FX2LP_HPP
#define FX2LP_HPP

#include <libusb.h>

#include "types.hpp"

int fx2_reset(libusb_device_handle *h, int cpu_enable);
int fx2_load_vendax(libusb_device_handle *h);

class FX2LP {
public:
		FX2LP(uint16 vendorID, uint16 productID);
		~FX2LP();

		void init();
		void deinit();

		void readEEPROM(byte *data, uint16 size);

		bool verifyVendorProductID();


private:
		static const uint16 kCPUAddress = 0xE600;
		static const byte   kVendAX[];

		uint16 _vendorID;
		uint16 _productID;

		libusb_device_handle *_usbHandle;


		void reset(bool enableCPU);
		void writeIntelHex(const byte *data, uint32 size);

		void loadVendAX();

		void controlTransfer(uint16 type, uint16 request, uint16 value, uint16 index, byte *data, uint16 length);
};

#endif // FX2LP_HPP
