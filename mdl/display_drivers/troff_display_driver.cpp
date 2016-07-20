#include "troff_display_driver.hpp"

#include "document/bold_line_element.hpp"
#include "document/italic_line_element.hpp"
#include "document/code_line_element.hpp"
#include "document/url_line_element.hpp"

#include <iostream>
using namespace std;

void TroffDisplayDriver::display(Document * doc) {
	display(doc, cout);
}

void TroffDisplayDriver::display(Document * doc, ostream & output) {
	Paragraph *p = nullptr;
	LineElement *l = nullptr;

	BoldLineElement *bold_le(nullptr);
	ItalicLineElement *italic_le(nullptr);
	CodeLineElement *code_le(nullptr);
	UrlLineElement *url_le(nullptr);

	bool is_verbatim(false), 
		is_quotation(false),
		is_ulist(false);

	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];

		switch (p->level()) {
			case Paragraph::Level::Title1:
				output << ".TH ";
				break;
			case Paragraph::Level::Title2:
				output << ".SH ";
				break;
			case Paragraph::Level::Title3:
				output << ".SS ";
				break;
			case Paragraph::Level::UList1:
				output << ".TP" << endl << ".BR " << endl;
				break;
			case Paragraph::Level::Code:
			case Paragraph::Level::Quote:
			default:
				output << ".PP" << endl;
				break;
		}

		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];

			bold_le = dynamic_cast<BoldLineElement*>(l);
			italic_le = dynamic_cast<ItalicLineElement*>(l);
			code_le = dynamic_cast<CodeLineElement*>(l);
			url_le = dynamic_cast<UrlLineElement*>(l);

			if (italic_le) {
				output << "\\fI";
			} else if (bold_le) {
				output << "\\fB";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
			}
			
			if (url_le) {
				output << endl << ".IR " << url_le->url() << endl;
			} else {
				output << l->content();
			}

			if (italic_le or bold_le) {
				output << "\\fR";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
			}
		}
		
		switch (p->level()) {
			case Paragraph::Level::Code:
				break;
			case Paragraph::Level::Quote:
				break;
			case Paragraph::Level::UList1:
			case Paragraph::Level::Title1:
			case Paragraph::Level::Title2:
			default:
				output << endl;
				break;
		}
	}
}

/* vim: set ts=4 sw=4: */
