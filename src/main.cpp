#include "configure.hpp"
#include "parsers/md_parser.hpp"
#include "display_drivers/ncurses_display_driver.hpp"
#include "display_drivers/plaintext_display_driver.hpp"

#include <iostream>
#include <locale.h>

#include <boost/program_options.hpp>

using namespace std;

namespace po = boost::program_options;

int main(int argc, char ** argv) {
	setlocale(LC_ALL, "");

	// Set Boost program options up
	const string usage("Usage: mdl [OPTIONS] <input-file>");
	po::options_description desc(usage);
	desc.add_options()
		("help", po::value<string>(), "produce help message")
		("display-driver,d", po::value<string>(), "set display driver")
		("input-parser,p", po::value<string>(), "set input parser")
		("input-file,i", po::value<string>(), "input file to be used");
	po::positional_options_description p;
	p.add("input-file", -1);
	po::variables_map vm;
	
	try {
		po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
	} catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::program_options::unknown_option> > e) {
		cerr << "mdl: " << e.what() << endl;
		return 1;
	}
	
	if (vm.count("help")) {
		cout << desc;
		return 0;
	} else if (vm.empty() or vm.count("input-file") == 0) {
		cout << usage << endl;
		cout << "mdl: Missing an input file" << endl;
		return 0;
	}

	Parser *parser(new MdParser(vm["input-file"].as<string>()));
	DisplayDriver *driver;

	if (vm.count("display-driver")) {
		// Select driver
		string driver_string(vm["display-driver"].as<string>());
		if (driver_string == "plain") {
			driver = new PlainTextDisplayDriver();
		} else if (driver_string == "ncurses") {
			driver = new NcursesDisplayDriver();
		} else {
			cerr << "mdl: Unknown driver name '" << driver_string << "'" << endl;
			delete parser;
		}
	} else {
		// Default: ncurses
		driver = new NcursesDisplayDriver();
	}

	/*
	 * This code section is not used since there is only one parser at the moment.
	 *
	if (vm.count("input-parser")) {
		// Select parser
	} else {
		// Default: MD
	}*/

	driver->display(parser->get_document());

	delete driver;
	delete parser;

	return 0;
}
