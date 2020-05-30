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

#pragma once

#include <cstdint>
#include <ctime>
#include <string>

namespace SdH {

	class HourMinute
	{
		protected:
			/** Number of hours in 24-hour format. */
			uint8_t hours_a;

			/** Number of minutes. */
			uint8_t minutes_a;

		public:
			/** Empty constructor initializes to 00:00 */
			inline HourMinute() : hours_a(0), minutes_a(0) {}

			/** String constructor reads HH:MM
			 * @param hm_i String to parse
			 * @throws std::invalid_argument when string can't be parsed. */
			HourMinute(const std::string & hm_i);

			/** Copy constructor is default. */
			HourMinute(const HourMinute & obj_i) = default;

			/** Initialization constructor.
			 * @param hour_i Number of hours in 24-hour format.
			 * @param minutes_i Number of minutes.
			 * @throws std::out_of_range when any parameter is out of range.
			 */
			HourMinute(const uint8_t hours_i, const uint8_t minutes_i);

			/** Epoch constructor.
			 * @param time_i Epoch timestamp to initialize from. */
			HourMinute(const time_t & time_i);

			/** Add in-place object operator.
			 * @param rhs_i Righthand side HourMinute object to add to this
			 * one.
			 * @returns A reference to the current object with @p rhs_i added.
			 */
			HourMinute & operator+=(const HourMinute & rhs_i);

			/** Add in-place string operator.
			 * @param rhs_i Righthand side string to parse and add to this
			 * object.
			 * @returns A reference to the current object with @p rhs_i added.
			 */
			inline HourMinute & operator+=(const std::string & rhs_i) {
				return (*this) += HourMinute(rhs_i);
			}

			/** Addition operator. */
			inline HourMinute operator+(const HourMinute & rhs_i) const {
				HourMinute retval(*this);
				return retval += rhs_i;
			}

			/** Shortcut to get an HourMinute object with the current local
			 * time.
			 * @return An object with the current local time. */
			static inline HourMinute now() const { return HourMinute(time(nullptr)); }

	};

} // SdH namespace
