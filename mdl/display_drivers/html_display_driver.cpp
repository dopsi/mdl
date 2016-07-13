#include "html_display_driver.hpp"

#include "document/paragraph.hpp"

#include "document/bold_line_element.hpp"
#include "document/italic_line_element.hpp"
#include "document/code_line_element.hpp"
#include "document/url_line_element.hpp"

#include <iostream>
using namespace std;

void HtmlDisplayDriver::display(Document *doc) {
	Paragraph *p = nullptr;
	LineElement *l = nullptr;

	BoldLineElement *bold_le(nullptr);
	ItalicLineElement *italic_le(nullptr);
	CodeLineElement *code_le(nullptr);
	UrlLineElement *url_le(nullptr);

	bool is_verbatim(false), 
		 is_quotation(false),
		 is_ulist(false);

	cout << "" << endl;
	cout << "<!doctype html>" << endl;
	cout << "<html lang=\"fr\">" << endl;
	cout << "<head>" << endl;
	cout << "<meta charset=\"utf-8\">" << endl;
	cout << "<title>mdl generated HTML page</title>" << endl;
	cout << "</head>" << endl;
	cout << "<body>" << endl;
	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];

		switch (p->level()) {
			case Paragraph::Level::Title1:
				cout << "<h1>";
				break;
			case Paragraph::Level::Title2:
				cout << "<h2>";
				break;
			case Paragraph::Level::Code:
				if (!is_verbatim) {
					cout << "<code>" << endl;
					is_verbatim = true;
				}
				break;
			case Paragraph::Level::UList1:
				if (!is_ulist) {
					cout << "<ul>" << endl;
					is_ulist = true;
				}
				cout << "<li>";
				break;
			case Paragraph::Level::Quote:
				if (!is_quotation) {
					cout << "<blockquote>" << endl;
					is_quotation = true;
				}
				break;
			default:
				cout << "<p>" << endl;
				break;
		}

		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];

			bold_le = dynamic_cast<BoldLineElement*>(l);
			italic_le = dynamic_cast<ItalicLineElement*>(l);
			code_le = dynamic_cast<CodeLineElement*>(l);
			url_le = dynamic_cast<UrlLineElement*>(l);

			if (italic_le) {
				cout << "<i>";
			} else if (bold_le) {
				cout << "<b>";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
				cout << "<code>";
			} else if (url_le) {
				cout << "<a href=\"" << url_le->url() << "\">";
			}

			cout << l->content();

			if (url_le) {
				cout << "</a>";
			} else if (bold_le) {
				cout << "</b>";
			} else if (italic_le) {
				cout << "</i>";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
				cout << "</code>";
			}
		}
		
		switch (p->level()) {
			case Paragraph::Level::Code:
				cout << endl;
				if (p->last()) {
					cout << "</code>" << endl << endl;
					is_verbatim = false;
				}
				break;
			case Paragraph::Level::Quote:
				cout << endl;
				if (p->last()) {
					cout << "</blockquote>" << endl << endl;
					is_quotation = false;
				}
				break;
			case Paragraph::Level::UList1:
				cout << "</li>" << endl;
				if (p->last()) {
					cout << "</ul>" << endl << endl;
					is_ulist = false;
				}
				break;
			case Paragraph::Level::Title1:
				cout << "</h1>" << endl;
				break;
			case Paragraph::Level::Title2:
				cout << "</h2>" << endl;
				break;
			default:
				cout << "</p>" << endl;
				break;
		}
	}
	cout << "</body>" << endl;
	cout << "</html>" << endl;
}

/* vim: set ts=4 sw=4: */
