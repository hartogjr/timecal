#include <cerrno>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

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
/*
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
			*/

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
