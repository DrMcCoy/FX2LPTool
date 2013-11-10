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

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <string>
#include <vector>

#include <libusb.h>

#include "util.hpp"
#include "error.hpp"
#include "fx2lp.hpp"


enum Action {
	kActionRead   = 0,
	kActionVerify    ,
	kActionWrite     ,
	kActionMAX
};

struct CommandLine;
typedef int (*commandfunc)(CommandLine command);

struct Command {
	Action action;
	const char *str;
	int args;
	commandfunc func;
};

int commandRead(CommandLine command);
int commandVerify(CommandLine command);
int commandWrite(CommandLine command);

static const Command kCommands[kActionMAX] = {
	{ kActionRead  , "readeeprom", 4, &commandRead   },
	{ kActionVerify, "verifyid"  , 4, &commandVerify },
	{ kActionWrite , "setid"     , 6, &commandWrite  }
};

struct CommandLine {
	std::string name;
	const Command *command;
	std::vector<uint16> args;

	CommandLine() { }
	CommandLine(const std::string &n, const Command *c) : name(n), command(c) { }
};

void printHelp(const char *name);

CommandLine parseCommandLine(int argc, char **argv);
const Command *parseCommand(const char *s);
uint16 parseID(const char *s);
int executeCommand(CommandLine command);

std::string readInput();

void dumpEEPROM(const char *prefix, byte *data, const char *suffix);


int main(int argc, char **argv) {
	CommandLine command;
	try {
		command = parseCommandLine(argc, argv);
	} catch (...) {
		printHelp(argv[0]);
		return -1;
	}

	return executeCommand(command);
}


CommandLine parseCommandLine(int argc, char **argv) {
	if (argc < 2)
		throw Exception("Not enough arguments");

	const Command *command = parseCommand(argv[1]);
	if (argc != command->args)
		throw Exception("Invalid amount of arguments");

	CommandLine cLine(argv[0], command);
	for (int i = 2; i < command->args; i++)
		cLine.args.push_back(parseID(argv[i]));

	return cLine;
}

const Command *parseCommand(const char *s) {
	for (int i = 0; i < kActionMAX; i++)
		if (!std::strcmp(kCommands[i].str, s))
			return &kCommands[i];

	throw Exception("Invalid command");
}

uint16 parseID(const char *s) {
	char *e;

	uint16 n = std::strtol(s, &e, 0);
	if (*e != '\0')
		throw Exception("Invalid number");

	return n;
}


int executeCommand(CommandLine command) {
	return (*command.command->func)(command);
}


void dumpEEPROM(const char *prefix, byte *data, const char *suffix) {
		std::printf("%s0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X%s", prefix,
		            data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], suffix);
}

int commandRead(CommandLine command) {
	try {
		FX2LP fx2lp(command.args[0], command.args[1]);

		byte data[8];
		fx2lp.readEEPROM(data, 8);

		dumpEEPROM("", data, "\n");

	} catch(Exception &e) {
		printException(e);
		return -2;
	}

	return 0;
}

int commandVerify(CommandLine command) {
	try {
		FX2LP fx2lp(command.args[0], command.args[1]);

		bool pass = fx2lp.verifyVendorProductID();

		std::printf("Verifying vendor/product ID... %s\n", pass ? "pass" : "fail");
		if (!pass)
			return -10;

	} catch(Exception &e) {
		printException(e);
		return -3;
	}

	return 0;
}

std::string readInput() {
	char buffer[4096];

	fgets(buffer, sizeof(buffer), stdin);

	char *e;
	if ((e = strrchr(buffer, '\n')))
		*e = '\0';
	if ((e = strrchr(buffer, '\r')))
		*e = '\0';

	return buffer;
}

int commandWrite(CommandLine command) {
	try {
		FX2LP fx2lp(command.args[0], command.args[1]);

		bool pass = fx2lp.verifyVendorProductID();
		if (!pass)
			throw Exception("Failed to verify current vendor/product ID");

		byte data[8], dataOut[8];
		fx2lp.readEEPROM(data, 8);
		std::memcpy(dataOut, data, 8);

		dataOut[1] =  command.args[2] & 0x00FF;
		dataOut[2] = (command.args[2] & 0xFF00) >> 8;
		dataOut[3] =  command.args[3] & 0x00FF;
		dataOut[4] = (command.args[3] & 0xFF00) >> 8;

		std::printf("Would change the vendor/product ID from 0x%04X 0x%04X to 0x%04X 0x%04X.\n",
		            command.args[0], command.args[1], command.args[2], command.args[3]);
		std::printf("That means changing the 8 bytes in the EEPROM from\n");
		dumpEEPROM("", data, "\n");
		std::printf("to\n");
		dumpEEPROM("", dataOut, ".\n");
		std::printf("Is that correct? (y/N)\n");

		std::string input = readInput();
		if (input != "y") {
			std::printf("Not acknowledged. Aborting...\n");
			return -11;
		}

		std::printf("\nWriting...\n");

		fx2lp.writeEEPROM(dataOut, 8);

		std::printf("Verifying that the new data has been written...\n\n");
		fx2lp.readEEPROM(data, 8);

		if (std::memcmp(data, dataOut, 8)) {
			std::printf("Uh-oh, something went wrong. Reading back returned this instead:\n");
			dumpEEPROM("", data, "\n");
			return -12;
		}

		std::printf("Everything looks fine. Please take out your device\n");
		std::printf("and plug it back in again for the change to take effect.\n");

	} catch(Exception &e) {
		printException(e);
		return -4;
	}

	return 0;
}


void printHelp(const char *name) {
	std::printf("FX2LPTool - Tool to manipulate Cypress EZ-USB FX2LP devices\n");
	std::printf("Usage: %s <command> <vendor ID> <product ID> [<command options>]\n\n", name);
	std::printf("The vendor ID and product ID can be specified in decimal or, when\n");
	std::printf("prefixed with 0x, in hexadecimal, or, when prefixed with a 0, in octal.\n\n");
	std::printf("Valid commands are:\n");
	std::printf("  - readeeprom\n");
	std::printf("    Read the contents of the device's EEPROM\n");
	std::printf("  - verifyid\n");
	std::printf("    Verify the EEPROM contents with the vendor/product IDs\n");
	std::printf("  - setid <new vendor ID> <new product ID>\n");
	std::printf("    Set the vendor and product IDs.\n");
	std::printf("    For known IDs, please see the README.md\n\n");
	std::printf("Examples:\n");
	std::printf("%s readeeprom 0x0925 0x3881\n", name);
	std::printf("%s verifyid 0x0925 0x3881\n", name);
	std::printf("%s setid 0x0925 0x3881 0x08A9 0x0014\n", name);
}
