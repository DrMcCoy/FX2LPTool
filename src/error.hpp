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

/** @file error.h
 *  Basic exceptions to throw.
 */

#ifndef ERROR_H
#define ERROR_H

#include <stack>
#include <string>
#include <exception>

/** Exeption that provides a stack of explanations. */
class StackException : public std::exception {
public:
	typedef std::stack<std::string> Stack;

	StackException();
	StackException(const char *s, ...);
	StackException(const StackException &e);
	~StackException() throw();

	void add(const char *s, ...);

	const char *what() const throw();

	Stack &getStack();

private:
	Stack _stack;
};

typedef StackException Exception;

extern const Exception kOpenError;
extern const Exception kReadError;
extern const Exception kSeekError;
extern const Exception kWriteError;

void printException(Exception &e, const std::string &prefix = "ERROR: ");

#endif // ERROR_H
