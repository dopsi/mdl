#include "md_display_driver.hpp"

#include "document/code_line_element.hpp"
#include "document/url_line_element.hpp"
#include "document/bold_line_element.hpp"
#include "document/italic_line_element.hpp"

#include <iostream>
using namespace std;

void MdDisplayDriver::display(Document * doc) {
	display(doc, cout);
}

void MdDisplayDriver::display(Document * doc, ostream & output) {
	Paragraph *p(nullptr);
	LineElement *l(nullptr);
	CodeLineElement *code_le(nullptr);
	ItalicLineElement *italic_le(nullptr);
	BoldLineElement *bold_le(nullptr);
	UrlLineElement *url_le(nullptr);

	int olist1_index(1);

	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];

		switch (p->level()) {
			case Paragraph::Level::Title1:
				output << "# ";
				break;
			case Paragraph::Level::Title2:
				output << "## ";
				break;
			case Paragraph::Level::Title3:
				output << "### ";
				break;
			case Paragraph::Level::UList1:
				output << "* ";
				break;
			case Paragraph::Level::OList1:
				output << olist1_index << ") ";
				++olist1_index;
				break;
			case Paragraph::Level::Quote:
				output << "> ";
				break;
			case Paragraph::Level::Code:
				output << "    ";
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
				output << "`";
			} else if (url_le) {
				output << "[";
			} else if (bold_le) {
				output << "**";
			} else if (italic_le) {
				output << "*";
			}

			output << l->content();
			
			if (code_le and p->level() != Paragraph::Level::Code) {
				output << "`";
			} else if (url_le) {
				output << "](" << url_le->url() << ")";
			} else if (bold_le) {
				output << "**";
			} else if (italic_le) {
				output << "*";
			}
		}

		if (p->level() != Paragraph::Level::OList1) {
			olist1_index = 1;
		}

		output << endl << endl;
	}
}

