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

/** Class handling all FX2LP interfacing. */
class FX2LP {
public:
		/** Constructor for the FX2LP handling class
		 *
		 *  @param vendorID  Vendor ID of the USB device.
		 *  @param productID Product ID of the USB device.
		 */
		FX2LP(uint16 vendorID, uint16 productID);
		~FX2LP();

		/** Read the device's EEPROM. */
		void readEEPROM(byte *data, uint16 size);
		/** Write the device's EEPROM. */
		void writeEEPROM(byte *data, uint16 size);

		/** Read the device's EEPROM and verify that it matches with the specified data. */
		bool verifyEEPROM(byte *data, uint16 size);

		/** Read the device's EEPROM and verify that the vendor/product IDs match. */
		bool verifyVendorProductID();


private:
		static const uint16 kCPUAddress = 0xE600; ///< Address of the CPU program memory.
		static const byte   kVendAX[];            ///< Default vendor program.

		uint16 _vendorID;  ///< The vendor ID of the USB device.
		uint16 _productID; ///< The product ID of the USB device.

		libusb_device_handle *_usbHandle; ///< The handle of the USB device.


		void init();
		void deinit();

		/** Reset the FX2LP device. */
		void reset(bool enableCPU);
		/** Write an intel hex file into the CPU program memory. */
		void writeIntelHex(const byte *data, uint32 size);

		/** Load the default vendor program into the CPU program memory. */
		void loadVendAX();

		/** Perform an USB control transfer. */
		void controlTransfer(uint16 type, uint16 request, uint16 value, uint16 index, byte *data, uint16 length);
};

#endif // FX2LP_HPP
