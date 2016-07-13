#include "troff_display_driver.hpp"

#include "document/bold_line_element.hpp"
#include "document/italic_line_element.hpp"
#include "document/code_line_element.hpp"
#include "document/url_line_element.hpp"

#include <iostream>
using namespace std;

void TroffDisplayDriver::display(Document * doc) {
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
				cout << ".TH ";
				break;
			case Paragraph::Level::Title2:
				cout << ".SH ";
				break;
			case Paragraph::Level::Code:
			case Paragraph::Level::UList1:
			case Paragraph::Level::Quote:
			default:
				cout << ".PP" << endl;
				break;
		}

		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];

			bold_le = dynamic_cast<BoldLineElement*>(l);
			italic_le = dynamic_cast<ItalicLineElement*>(l);
			code_le = dynamic_cast<CodeLineElement*>(l);
			url_le = dynamic_cast<UrlLineElement*>(l);

			if (italic_le) {
				cout << "\\fI";
			} else if (bold_le) {
				cout << "\\fB";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
			}
			
			if (url_le) {
				cout << endl << ".IR " << url_le->url() << endl;
			} else {
				cout << l->content();
			}

			if (italic_le or bold_le) {
				cout << "\\fR";
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
				cout << endl;
				break;
		}
	}
}

/* vim: set ts=4 sw=4: */
