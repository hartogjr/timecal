/* BSD 3-Clause License
 *
 * Copyright (c) 2020, Simon de Hartog <simon@dehartog.name>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * vim:set ts=4 sw=4 noexpandtab: */

#include <cerrno>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include "calculations.h"

namespace SdH {

	hourMinute_t add(const hourMinute_t & duration, const hourMinute_t & refTime = now()) const
	{

	}

	hourMinute_t now(void) const
	{
		time_t epoch = 0;
		hourMinute_t retval = {0, 0};
		struct tm * tmptr = nullptr;

		/* The time(2) man-page says:
		 * SYNOPSIS: time_t time(time_t *tloc);
		 * When tloc is NULL, the call cannot fail.
		 * So no error checking required! ;-D */
		epoch = time(NULL);
		errno = 0;
		tmptr = localtime(&epoch);

		if (tmptr == nullptr) {
			std::ostringstream oss;
			oss << "Failed breaking down current time";
			if (errno) oss << ": " << strerror(errno);
			throw std::runtime_error(oss.str());
		}

		retval.hour = tmptr->tm_hour;
		retval.minute = tmptr->tm_min;
		return retval;
	}


int run(const std::string & duration, const std::string & reftime = "")
{
	uint8_t refhour, refmin;

	if (reftime.empty()) {
		setCurrentTime();
		refhour = curhour;
		refmin = curmin;
	} else {
		size_t pos = reftime.find(':');
		switch (pos) {
			case 1:
				if (reftime[0] < '0' || reftime[0] > '9') {
					return help("Reference hour and minute should only contain digits");
				}
				refhour = reftime[0] - '0';
				break;

			case 2:
				if (
					reftime[0] < '0' ||
					reftime[0] > '2' ||
					reftime[1] < '0' ||
					reftime[1] > '9' ||
					(
					 	reftime[0] == '2' &&
						reftime[1] > '3'
					)
				) {
					return help("Invalid reference hour specified");
		if (
			pos == std::string::npos ||
			pos < 1 ||
			pos > 2
		) {
			std::string msg = "Invalid reference time \"";
			msg.append(reftime);
			msg.append("\" specified");
			return help(msg);

int main(int argc, char *argv[])
{
	size_t pos = std::string::npos;

	// C++ version of basename(3)
	appname = argv[0];
	pos = appname.rfind('/');
	if (pos != std::string::npos) appname.erase(0, pos+1);

	switch (argc) {
		case 3:

			break;

		case 2:

			break;

		default:
			return help();

	}

	return 0;
}

	}

} // SdH namespace
