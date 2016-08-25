#include "plaintext_display_driver.hpp"

#include <iostream>
using namespace std;

void PlainTextDisplayDriver::display(Document * doc) {
	display(doc, cout);
}

void PlainTextDisplayDriver::display(Document * doc, ostream & output) {
	Paragraph *p = nullptr;
	LineElement *l = nullptr;

	output << "Document contains : " << doc->size() << " paragraphs" << endl;
	output << "=== BEGIN ===" << endl;
	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];
		switch (p->level()) {
			case Paragraph::Level::Title1:
				break;
			case Paragraph::Level::Title2:
				output << "  ";
				break;
			case Paragraph::Level::UList1:
				output << "* ";
				break;
			case Paragraph::Level::UList2:
				output << "  * ";
				break;
			default:
				output << "    ";
				break;

		}
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			output << l->content();
		}
		output << endl;
	}
	output << "=== END OF PROGRAM ===" << endl;
}

