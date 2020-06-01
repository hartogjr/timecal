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
#include <stdexcept>
#include <string>

#define UNUSED(expr) (void)(expr)

namespace SdH {

	class HoursMinutes
	{
		protected:
			/** Number of hours in 24-hour format. */
			uint8_t hours_a;

			/** Number of minutes. */
			uint8_t minutes_a;

			/** Parse a character into a number
			 * @param char_i Input character to parse
			 * @returns The integer value if parsed properly
			 * @throws std::invalid_argument if character is not a digit */
			static uint8_t parseChar(const char char_i);

			/** Parse a string into a number with a given maximum.
			 * @param str_i Input string to parse
			 * @param max_i Maximum value for int
			 * @returns The integer value if parsed properly
			 * @throws std::overflow_error if int exceeds @p max_i
			 * @throws std::invalid_argument if string can't be parsed */
			static uint8_t parse(const std::string & str_i, const uint8_t max_i);

		public:
			/** Empty constructor initializes to 00:00 */
			inline HoursMinutes() : hours_a(0), minutes_a(0) {}

			/** String constructor reads HH:MM
			 * @param hm_i String to parse
			 * @throws std::invalid_argument when string can't be parsed. */
			inline HoursMinutes(const std::string & hm_i) {
				set(hm_i);
			}

			/** Copy constructor is default. */
			HoursMinutes(const HoursMinutes & obj_i) = default;

			/** Initialization constructor.
			 * @param hour_i Number of hours in 24-hour format.
			 * @param minutes_i Number of minutes.
			 * @throws std::overflow_error when any parameter is out of range.
			 */
			inline HoursMinutes(const uint8_t hours_i, const uint8_t minutes_i) {
				hours(hours_i); minutes(minutes_i);
			}

			/** Epoch constructor.
			 * @param time_i Epoch timestamp to initialize from. */
			inline HoursMinutes(const time_t & time_i) {
				set(time_i);
			}

			/** Get the number of hours in 24-hour format.
			 * @returns Internal number of hours. */
			inline uint8_t hours() const { return hours_a; }

			/** Manually set the number of hours.
			 * @param hours_i Hours to set in 24-hour format.
			 * @throws std::overflow_error in case @p hours_i > 23. */
			inline void hours(const uint8_t hours_i) {
				if (hours_i > 23) throw std::overflow_error("Hours should be smaller than 24.");
				hours_a = hours_i;
			}

			/** Get the number of minutes.
			 * @returns Internal number of minutes. */
			inline uint8_t minutes() const { return minutes_a; }

			/** Manually set the number of minutes.
			 * @param minutes_i Number of minutes to set.
			 * @throws std::overflow_error in case @p minutes_i > 59. */
			inline void minutes(const uint8_t minutes_i) {
				if (minutes_i > 59) throw std::overflow_error("Minutes should be smaller than 60.");
				minutes_a = minutes_i;
			}

			/** Add in-place object operator.
			 * @param rhs_i Righthand side HoursMinutes object to add to this
			 * one.
			 * @returns A reference to the current object with @p rhs_i added.
			 */
			HoursMinutes & operator+=(const HoursMinutes & rhs_i);

			/** Add in-place string operator.
			 * @param rhs_i Righthand side string to parse and add to this
			 * object.
			 * @returns A reference to the current object with @p rhs_i added.
			 */
			inline HoursMinutes & operator+=(const std::string & rhs_i) {
				return (*this) += HoursMinutes(rhs_i);
			}

			/** Addition operator. */
			inline HoursMinutes operator+(const HoursMinutes & rhs_i) const {
				HoursMinutes retval(*this);
				return retval += rhs_i;
			}

			/** Check whether the set time is zero (00:00).
			 * @returns True if zero (00:00), false if another time is set. */
			inline bool isZero() const { return hours_a == 0 && minutes_a == 0; }

			/** Shortcut to get an HoursMinutes object with the current local
			 * time.
			 * @return An object with the current local time. */
			static inline HoursMinutes now() { return HoursMinutes(time(nullptr)); }

			/** Reset the time to zero (00:00) */
			inline void reset() { hours_a = 0; minutes_a = 0; }

			/** Set the time from a string formatted like HH:MM.
			 * @param hm_i String to parse
			 * @throws std::invalid_argument when string can't be parsed. */
			void set(const std::string & hm_i);

			/** Set the time from an epoch value.
			 * @param time_i Epoch timestamp to use. */
			void set(const time_t & time_i);

	};

} // SdH namespace

/** Stream output operator for SdH::HoursMinutes object. */
std::ostream & operator<<(std::ostream & os, const SdH::HoursMinutes & hm);
