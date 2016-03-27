#include <iostream>
#include "configure.hpp"
#include "parsers/md_parser.hpp"
#include "display_drivers/ncurses_display_driver.hpp"

using namespace std;

int main(int argc, char ** argv) {
	cout << "mdl v" << MDL_VERSION_STRING << endl;
	if (argc < 2) {
		cerr << "mdl: missing at least one argument" << endl;
		return 1;
	}

	MdParser parser(argv[1]);
	NcursesDisplayDriver drv;
	drv.display(parser.get_document());
	return 0;
}
