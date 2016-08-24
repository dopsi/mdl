#include "ansi_display_driver.hpp"

#include "document/code_line_element.hpp"
#include "tools/ansi_wrapper.hpp"

#include <iostream>
using namespace std;

typedef AnsiWrapper::Color Color;

void AnsiDisplayDriver::display(Document * doc) {
	display(doc, cout);
}

void AnsiDisplayDriver::display(Document * doc, ostream & output) {
	Paragraph *p(nullptr);
	LineElement *l(nullptr);
	CodeLineElement *code_le(nullptr);

	AnsiWrapper wrapper(output);

	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];
		switch (p->level()) {
			case Paragraph::Level::Title1:
				wrapper.fg(Color::Blue);
				wrapper.underline();
				break;
			case Paragraph::Level::Title2:
				wrapper << "  ";
				wrapper.fg(Color::Blue);
				break;
			case Paragraph::Level::Title3:
				wrapper << "    ";
				wrapper.fg(Color::Blue);
				break;
			case Paragraph::Level::Quote:
				wrapper << "    ";
				wrapper.fg(Color::Blue);
				wrapper.reverse();
				break;
			case Paragraph::Level::UList1:
				wrapper << "    ";
				wrapper.fg(Color::Cyan);
				wrapper << "* ";
				wrapper.reset();
				break;
			default:
				wrapper << "    ";
				break;

		}
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			code_le = dynamic_cast<CodeLineElement*>(l);

			if (code_le) {
				wrapper.reverse();
			}

			wrapper << l->content();
			
			wrapper.reset();

		}
		wrapper.reset();
		wrapper << endl;
	}
}

