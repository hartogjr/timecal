#include <cerrno>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include "HoursMinutes.h"

using std::cerr, std::cin, std::cout, std::endl;

std::string appname;

int help(const std::string & msg = "")
{
	int retval = 0;

	if (!msg.empty()) {
		cerr << "Error: " << msg << endl << endl;
		retval = 1;
	}
	cerr << "Usage: " << appname << " [<HH>:<MM>] [[<HH>:]MM]" << endl;
	cerr << "This application calculates the time after a specified" << endl;
	cerr << "duration, with an optional reference time. The default" << endl;
	cerr << "reference time is now." << endl;
	cerr << "It takes care of durations that cross a day boundary." << endl;
	cerr << "When no parameters are given, it enters interactive mode." << endl;
	cerr << "In this mode, each line you enter is interpreted as a call" << endl;
	cerr << "to " << appname << " with the entered line as suffix, so" << endl;
	cerr << "containing one or two parameters." << endl;
	cerr << "[<HH>:<MM>]   Optional reference time instead of the current time." << endl;
	cerr << "              Use 24-hour time format." << endl;
	cerr << "[<HH>:]MM      Duration to add to reference time. The optional H is the number" << endl;
	cerr << "              of hours to add with a literal ':' as separator. The MM" << endl;
	cerr << "              are the number of minutes to add. " << endl << endl;
	cerr << "Examples:" << endl;
	cerr << appname << " 09:34 1:48 # will return 11:22" << endl;
	cerr << appname << " 23:12 2:54 # will return 02:06" << endl;
	return retval;
}

int main(int argc, char *argv[])
{
	size_t pos = std::string::npos;
	SdH::HoursMinutes ref, dur;
	std::string line; // Input line

	// C++ version of basename(3)
	appname = argv[0];
	pos = appname.rfind('/');
	if (pos != std::string::npos) appname.erase(0, pos+1);

	switch (argc) {
		case 3:
			try {
				ref.set(argv[1]);
				dur.set(argv[2]);
				ref += dur;
				cout << ref << endl;
				return 0;
			} catch (const std::exception & se) {
				return help(se.what());
			}

			break;

		case 2:
			if (
				!strcmp(argv[1], "-h") ||
				!strcmp(argv[1], "--help") ||
				!strcmp(argv[1], "-?") ||
				!strcmp(argv[1], "help") ||
				!strcmp(argv[1], "?")
			) {
				return help();
			}

			try {
				ref = SdH::HoursMinutes::now();
				dur.set(argv[1]);
				ref += dur;
				cout << ref << endl;
				return 0;
			} catch (const std::exception & se) {
				return help(se.what());
			}

		case 1:
			// Run the interactive loop outside this switch statement
			break;

		default:
			return help();
	}

	cout << "Welcome to " << appname << "!" << endl;
	cout << "You are in interactive mode. Use Ctrl-C, Ctrl-D, \"q\" or \"quit\" command to exit." << endl;
	cout << "Enter either a duration in [HH:]MM format, or a reference time followed by a duration." << endl;
	cout << "When only a duration a given, it is added to the current time and the resulting time" << endl;
	cout << "is returned." << endl;
	cout << "If only a duration is given, but is prefixed with a plus sign (+), the previous answer" << endl;
	cout << "is used as the reference time." << endl;
	cout << "When a reference time is also given, the duration is added to the reference time" << endl;
	cout << "and the resulting time is displayed." << endl;
	do {
		cout << "> "; cout.flush();
		std::getline(cin, line);

		if (line.empty()) continue;
		if (line == "q" || line == "quit") break;

		try {
			pos = line.find(' ');
			if (pos == std::string::npos) {
				if (line[0] == '+') {
					// Remove the plus, use previous result as new reference
					line.replace(0, 1, "");
				} else {
					// Use current time as reference
					ref = SdH::HoursMinutes::now();
				}
				dur.set(line);
			} else {
				ref.set(line.substr(0, pos));
				dur.set(line.substr(pos+1));
			}
			ref += dur;
			cout << ref << endl;
		} catch (const std::invalid_argument & ia) {
			cout << ia.what() << endl;
		} catch (const std::overflow_error & ofe) {
			cout << ofe.what() << endl;
		}

	} while (cin.good());

	return 0;
}
