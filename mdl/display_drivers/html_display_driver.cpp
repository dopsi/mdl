#include "html_display_driver.hpp"

#include "document/bold_line_element.hpp"
#include "document/italic_line_element.hpp"
#include "document/code_line_element.hpp"
#include "document/url_line_element.hpp"

#include <iostream>
using namespace std;

HtmlDisplayDriver::HtmlDisplayDriver(bool standalone) :
	DisplayDriver(standalone) {
}

HtmlDisplayDriver::~HtmlDisplayDriver() {
}

void HtmlDisplayDriver::display(Document *doc) {
	display(doc, cout);
}

void HtmlDisplayDriver::display(Document *doc, ostream & output) {
	Paragraph *p = nullptr;
	LineElement *l = nullptr;

	BoldLineElement *bold_le(nullptr);
	ItalicLineElement *italic_le(nullptr);
	CodeLineElement *code_le(nullptr);
	UrlLineElement *url_le(nullptr);

	bool is_verbatim(false), 
		 is_quotation(false),
		 is_ulist(false),
		 is_olist(false);

	if (_standalone) {
		output << "<!doctype html>" << endl;
		output << "<html lang=\"fr\">" << endl;
		output << "<head>" << endl;
		output << "<meta charset=\"utf-8\">" << endl;
		output << "<title>mdl generated HTML page</title>" << endl;
		output << "</head>" << endl;
		output << "<body>" << endl;
	}

	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];

		switch (p->level()) {
			case Paragraph::Level::Title1:
				output << "<h1>";
				break;
			case Paragraph::Level::Title2:
				output << "<h2>";
				break;
			case Paragraph::Level::Title3:
				output << "<h3>";
				break;
			case Paragraph::Level::Code:
				if (!is_verbatim) {
					output << "<code>" << endl;
					is_verbatim = true;
				}
				break;
			case Paragraph::Level::UList1:
				if (!is_ulist) {
					output << "<ul>" << endl;
					is_ulist = true;
				}
				output << "<li>";
				break;
			case Paragraph::Level::OList1:
				if (!is_olist) {
					output << "<ol>" << endl;
					is_olist = true;
				}
				output << "<li>";
				break;
			case Paragraph::Level::Quote:
				if (!is_quotation) {
					output << "<blockquote>" << endl;
					is_quotation = true;
				}
				break;
			default:
				output << "<p>" << endl;
				break;
		}

		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];

			bold_le = dynamic_cast<BoldLineElement*>(l);
			italic_le = dynamic_cast<ItalicLineElement*>(l);
			code_le = dynamic_cast<CodeLineElement*>(l);
			url_le = dynamic_cast<UrlLineElement*>(l);

			if (italic_le) {
				output << "<i>";
			} else if (bold_le) {
				output << "<b>";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
				output << "<code>";
			} else if (url_le) {
				output << "<a href=\"" << url_le->url() << "\">";
			}

			output << l->content();

			if (url_le) {
				output << "</a>";
			} else if (bold_le) {
				output << "</b>";
			} else if (italic_le) {
				output << "</i>";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
				output << "</code>";
			}
		}
		
		switch (p->level()) {
			case Paragraph::Level::Code:
				output << endl;
				if (p->last()) {
					output << "</code>" << endl << endl;
					is_verbatim = false;
				}
				break;
			case Paragraph::Level::Quote:
				output << endl;
				if (p->last()) {
					output << "</blockquote>" << endl << endl;
					is_quotation = false;
				}
				break;
			case Paragraph::Level::UList1:
				output << "</li>" << endl;
				if (p->last()) {
					output << "</ul>" << endl << endl;
					is_ulist = false;
				}
				break;
			case Paragraph::Level::OList1:
				output << "</li>" << endl;
				if (p->last()) {
					output << "</ol>" << endl << endl;
					is_olist = false;
				}
				break;
			case Paragraph::Level::Title1:
				output << "</h1>" << endl;
				break;
			case Paragraph::Level::Title2:
				output << "</h2>" << endl;
				break;
			case Paragraph::Level::Title3:
				output << "</h3>" << endl;
				break;
			default:
				output << "</p>" << endl;
				break;
		}
	}
	if (_standalone) {
		output << "</body>" << endl;
		output << "</html>" << endl;
	}
}

/* vim: set ts=4 sw=4: */
