#include "configure.hpp"
#include "parsers/md_parser.hpp"
#include "display_drivers/ncurses_display_driver.hpp"
#include "display_drivers/plaintext_display_driver.hpp"
#include "display_drivers/latex_display_driver.hpp"
#include "display_drivers/html_display_driver.hpp"
#include "display_drivers/troff_display_driver.hpp"
#include "display_drivers/ansi_display_driver.hpp"
#include "display_drivers/md_display_driver.hpp"
#include "display_drivers/rst_display_driver.hpp"

#include "options.hpp"

#include <cassert>

using namespace std;

int main(int argc, char ** argv) {
	setlocale(LC_ALL, "");

	MdlOptions op(argc, argv);
	Parser *parser(new MdParser(op.input_file()));
	DisplayDriver *driver(nullptr);
	ofstream output_file;

	string driver_string(op.display_driver());
	if (driver_string == "plain") {
		driver = new PlainTextDisplayDriver();
	} else if (driver_string == "ncurses") {
		driver = new NcursesDisplayDriver();
	} else if (driver_string == "latex") {
		driver = new LaTeXDisplayDriver(true);
	} else if (driver_string == "html") {
		driver = new HtmlDisplayDriver(true);
	} else if (driver_string == "troff") {
		driver = new TroffDisplayDriver(true);
	} else if (driver_string == "ansi") {
		driver = new AnsiDisplayDriver();
	} else if (driver_string == "md") {
		driver = new MdDisplayDriver();
	} else if (driver_string == "rst") {
		driver = new RstDisplayDriver();
	}

	assert(driver);
	assert(parser);
	
	/*
	 * This code section is not used since there is only one parser at the moment.
	 *
	if (vm.count("input-parser")) {
		// Select parser
	} else {
		// Default: MD
	}*/

	if (!op.output_file().empty()) {
		output_file.open(op.output_file());
		driver->display(parser->get_document(), output_file);
		output_file.close();
	} else {
		driver->display(parser->get_document());
	}

	delete driver;
	delete parser;

	return 0;
}
