#include "options.hpp"
#include "configure.hpp"

#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;
using namespace std;

MdlOptions::MdlOptions(int argc, const char *const *argv) :
	_standalone(true),
	_display_driver("ncurses"),
	_input_file(""),
	_output_file("") {
	// Set Boost program options up
	const string usage("Usage: mdl [OPTIONS] <input-file>");
	po::options_description desc(usage);
	desc.add_options()
		("help,h", "produce help message and exit")
		("display-driver,d", po::value<string>(), "set display driver")
		("input-parser,p", po::value<string>(), "set input parser")
		("input-file,i", po::value<string>(), "input file to be used")
		("output-file,o", po::value<string>(), "output file")
		("version", "print the version information and exit");
	po::positional_options_description p;
	p.add("input-file", -1);
	po::variables_map vm;
	
	try {
		po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
	} catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::program_options::unknown_option> > e) {
		cerr << "mdl: " << e.what() << endl;
		exit(1);
	}
	
	if (vm.count("help")) {
		cout << desc;
		exit(0);
	} else if (vm.count("version")) {
		cout << "mdl (version: " << MDL_VERSION_STRING << ")" << endl;
		exit(0);
	} else if (vm.empty() or vm.count("input-file") == 0) {
		cout << usage << endl;
		cout << "mdl: Missing an input file" << endl;
		exit(0);
	}

	_input_file = vm["input-file"].as<string>();
	
	if (vm.count("display-driver")) {
		_display_driver = vm["display-driver"].as<string>();
	} else {
		_display_driver = "ncurses";
	}

	if (vm.count("output-file")) {
		_output_file = vm["output-file"].as<string>();
	}
}

MdlOptions::~MdlOptions() {
}

bool MdlOptions::standalone(void) const {
	return _standalone;
}

std::string MdlOptions::output_file() const {
	return _output_file;
}

std::string MdlOptions::input_file() const {
	return _input_file;
}

std::string MdlOptions::display_driver() const {
	return _display_driver;
}
