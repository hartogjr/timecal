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
 * vim:set ts=4 sw=4 noet: */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <HoursMinutes.h>

#define CHECKNAME hoursminutesCheck

#define VALIDATE(STR, HRS, MINUTES) \
{ \
	CPPUNIT_ASSERT_NO_THROW(SdH::HoursMinutes hm(STR)); \
	SdH::HoursMinutes hm(STR); \
	CPPUNIT_ASSERT_EQUAL(static_cast<uint8_t>(HRS), hm.hours()); \
	CPPUNIT_ASSERT_EQUAL(static_cast<uint8_t>(MINUTES), hm.minutes()); \
}

class CHECKNAME;

CPPUNIT_TEST_SUITE_REGISTRATION(CHECKNAME);

class CHECKNAME : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(CHECKNAME);
	CPPUNIT_TEST(constructors);
	CPPUNIT_TEST_SUITE_END();

	public:

	CHECKNAME()
	{ }

	void constructors() {
		// Empty constructor
		{
			CPPUNIT_ASSERT_NO_THROW(SdH::HoursMinutes hm);
			SdH::HoursMinutes hm;
			CPPUNIT_ASSERT_EQUAL(static_cast<uint8_t>(0), hm.hours());
			CPPUNIT_ASSERT_EQUAL(static_cast<uint8_t>(0), hm.minutes());
		}

		// We assume the default compiler-generated copy constructor works as
		// expected ;-)

		// String constructor, with zeroes first
		VALIDATE("", 0, 0);
		VALIDATE("0", 0, 0);
		VALIDATE("00", 0, 0);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000"), std::invalid_argument);
		VALIDATE(":", 0, 0);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("::"), std::invalid_argument);
		VALIDATE(":0", 0, 0);
		VALIDATE(":00", 0, 0);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm(":000"), std::invalid_argument);
		VALIDATE("0:", 0, 0);
		VALIDATE("0:0", 0, 0);
		VALIDATE("0:00", 0, 0);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("0:000"), std::invalid_argument);
		VALIDATE("00:", 0, 0);
		VALIDATE("00:0", 0, 0);
		VALIDATE("00:00", 0, 0);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("00:000"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000:"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000:0"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000:00"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000:000"), std::invalid_argument);

		// String constructor with only single digit minutes
		VALIDATE("7", 0, 7);
		VALIDATE("07", 0, 7);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("007"), std::invalid_argument); // Invalid James Bond time!
		VALIDATE(":7", 0, 7);
		VALIDATE(":07", 0, 7);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm(":007"), std::invalid_argument); // Invalid James Bond time!
		VALIDATE("0:7", 0, 7);
		VALIDATE("0:07", 0, 7); // Proper James Bond time!
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("0:007"), std::invalid_argument);
		VALIDATE("00:7", 0, 7); // Also valid James Bond time!
		VALIDATE("00:07", 0, 7);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("00:007"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000:7"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000:07"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000:007"), std::invalid_argument);

		// String constructor with double digit minutes
		VALIDATE("42", 0, 42);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("042"), std::invalid_argument);
		VALIDATE(":42", 0, 42);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm(":042"), std::invalid_argument);
		VALIDATE("0:42", 0, 42);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("0:042"), std::invalid_argument);
		VALIDATE("00:42", 0, 42);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("00:042"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000:42"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("000:042"), std::invalid_argument);

		VALIDATE("9:5", 9, 5);
		VALIDATE("7:13", 7, 13);
		VALIDATE("10:3", 10, 3);
		VALIDATE("11:48", 11, 48);
		VALIDATE("6:", 6, 0);
		VALIDATE("22:", 22, 0);

		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("InvalidTime"), std::invalid_argument);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("28:92"), std::overflow_error);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("11:87"), std::overflow_error);
		CPPUNIT_ASSERT_THROW(SdH::HoursMinutes hm("42:19"), std::overflow_error);
	}

};

#undef CHECKNAME
