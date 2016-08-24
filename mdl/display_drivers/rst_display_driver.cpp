#include "rst_display_driver.hpp"

#include "document/code_line_element.hpp"
#include "document/url_line_element.hpp"
#include "document/bold_line_element.hpp"
#include "document/italic_line_element.hpp"

#include <iostream>
#include <sstream>
using namespace std;

void RstDisplayDriver::display(Document * doc) {
	display(doc, cout);
}

void RstDisplayDriver::display(Document * doc, ostream & output) {
	Paragraph *p(nullptr);
	LineElement *l(nullptr);
	CodeLineElement *code_le(nullptr);
	ItalicLineElement *italic_le(nullptr);
	BoldLineElement *bold_le(nullptr);
	UrlLineElement *url_le(nullptr);
	size_t text_len(0);
	stringstream url_data;

	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];

		switch (p->level()) {
			case Paragraph::Level::UList1:
				output << "- ";
				break;
			case Paragraph::Level::OList1:
				output << "#) ";
				break;
			case Paragraph::Level::Quote:
				output << "    ";
				break;
			case Paragraph::Level::Code:
				output << "::" << endl << endl;
				break;
			default:
				break;

		}
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			
			code_le = dynamic_cast<CodeLineElement*>(l);
			url_le = dynamic_cast<UrlLineElement*>(l);
			bold_le = dynamic_cast<BoldLineElement*>(l);
			italic_le = dynamic_cast<ItalicLineElement*>(l);
			
			if (code_le and p->level() != Paragraph::Level::Code) {
				output << "``";
			} else if (url_le) {
				output << "`";
			} else if (bold_le) {
				output << "**";
			} else if (italic_le) {
				output << "*";
			}

			text_len += l->content().length();
			output << l->content();
			
			if (code_le and p->level() != Paragraph::Level::Code) {
				output << "``";
			} else if (url_le) {
				output << "`_";
				url_data << ".. _" << l->content() << " : " << url_le->url() << endl;
			} else if (bold_le) {
				output << "**";
			} else if (italic_le) {
				output << "*";
			}
		}

		switch (p->level()) {
			case Paragraph::Level::Title1:
				output << endl << std::string(text_len, '=');
				break;
			case Paragraph::Level::Title2:
				output << endl << std::string(text_len, '-');
				break;
			case Paragraph::Level::Title3:
				output << endl << std::string(text_len, '~');
				break;
			default:
				break;

		}

		text_len = 0;
		output << endl << endl;
	}

	output << url_data.str();
}

