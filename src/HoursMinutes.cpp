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
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "HoursMinutes.h"

namespace SdH {

	uint8_t HoursMinutes::parseChar(const char char_i)
	{
		if (char_i < '0' || char_i > '9') {
			throw std::invalid_argument(
				std::string("Invalid character '") + char_i + "' in time string"
			);
		}

		return char_i - '0';
	}

	uint8_t HoursMinutes::parse(const std::string & str_i, const uint8_t max_i)
	{
		if (str_i.empty() || str_i == "0" || str_i == "00") return 0;

		uint8_t rv = 0; // Return Value

		switch (str_i.size()) {
			case 2:
				rv = parseChar(str_i[0]) * 10 + parseChar(str_i[1]);
				break;

			case 1:
				rv = parseChar(str_i[0]);
				break;

			default:
				throw std::invalid_argument("Integer string longer than two characters");
		}

		if (rv > max_i) {
			std::ostringstream oss;

			oss << "String value \"" << str_i << "\" is a valid integer but is larger than ";
			oss << static_cast<uint16_t>(max_i);
			throw std::overflow_error(oss.str());
		}

		return rv;
	}

	void HoursMinutes::set(const std::string & hm_i)
	{
		size_t pos = 0;
		uint8_t tmphrs = 0;
		uint8_t tmpmin = 0;

		if (hm_i.empty() || hm_i == ":") {
			reset();
			return;
		}

		pos = hm_i.find(':');
		if (pos == std::string::npos) {
			// No hours specified, just minutes
			tmpmin = parse(hm_i, 59);
			hours_a = 0;
			minutes_a = tmpmin;
			return;
		}

		tmphrs = parse(hm_i.substr(0, pos), 23);
		tmpmin = parse(hm_i.substr(pos+1), 59);
		hours_a = tmphrs;
		minutes_a = tmpmin;
	}

	void HoursMinutes::set(const time_t & time_i)
	{
		struct tm *tmptr = nullptr;

		tmptr = localtime(&time_i);
		if (tmptr == nullptr) {
			throw std::runtime_error("Unable to break down time to parts");
		}

		hours_a = tmptr->tm_hour;
		minutes_a = tmptr->tm_min;
	}

	HoursMinutes & HoursMinutes::operator+=(const HoursMinutes & rhs_i)
	{
		hours_a += rhs_i.hours_a;
		minutes_a += rhs_i.minutes_a;
		if (minutes_a > 59) {
			hours_a++;
			minutes_a %= 60;
		}

		if (hours_a > 23) hours_a %= 24;

		return (*this);
	}

} // SdH namespace

std::ostream & operator<<(std::ostream & os, const SdH::HoursMinutes & hm)
{
	os << std::dec << std::setw(2) << std::setfill('0') <<
		static_cast<uint16_t>(hm.hours()) << ':' << static_cast<uint16_t>(hm.minutes());
	return os;
}
