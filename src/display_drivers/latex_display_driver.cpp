#include "latex_display_driver.hpp"

#include "../document/bold_line_element.hpp"
#include "../document/italic_line_element.hpp"
#include "../document/code_line_element.hpp"
#include "../document/url_line_element.hpp"

#include <iostream>
using namespace std;

void LaTeXDisplayDriver::display(Document * doc) {
	Paragraph *p = nullptr;
	LineElement *l = nullptr;

	BoldLineElement *bold_le(nullptr);
	ItalicLineElement *italic_le(nullptr);
	CodeLineElement *code_le(nullptr);
	UrlLineElement *url_le(nullptr);

	string delim_list("|@,;:_");
	char delim('|');

	bool is_verbatim(false), 
		 is_quotation(false),
		 is_ulist(false);

	cout << "\\documentclass{article}" << endl;
	cout << "\\usepackage[english]{babel}" << endl;
	cout << "\\usepackage[utf8]{inputenc}" << endl;
	cout << "\\usepackage[T1]{fontenc}" << endl;
	cout << "\\usepackage{hyperref}" << endl;
	cout << "\\begin{document}" << endl;

	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];

		if (is_verbatim
			and p->level() != Paragraph::Level::Code) {
			is_verbatim = false;
			cout << "\\end{verbatim}" << endl;
		}

		if (is_quotation 
			and !is_ulist
			and !is_verbatim
			and p->level() != Paragraph::Level::Quote) {
			is_quotation = false;
			cout << "\\end{quotation}" << endl;
		}

		if (is_ulist 
			and !is_quotation
			and !is_verbatim
			and p->level() != Paragraph::Level::UList1) {
			is_ulist = false;
			cout << "\\end{itemize}" << endl;
		}

		switch (p->level()) {
			case Paragraph::Level::Title1:
				cout << "\\section{";
				break;
			case Paragraph::Level::Title2:
				cout << "\\subsection{";
				break;
			case Paragraph::Level::Code:
				if (!is_verbatim) {
					cout << "\\begin{verbatim}" << endl;
					is_verbatim = true;
				}
				break;
			case Paragraph::Level::UList1:
				if (!is_ulist) {
					cout << "\\begin{itemize}" << endl;
					is_ulist = true;
				}
				cout << "\\item ";
				break;
			case Paragraph::Level::Quote:
				if (!is_quotation) {
					cout << "\\begin{quotation}" << endl;
					is_quotation = true;
				}
				break;
			default:
				break;

		}

		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];

			bold_le = dynamic_cast<BoldLineElement*>(l);
			italic_le = dynamic_cast<ItalicLineElement*>(l);
			code_le = dynamic_cast<CodeLineElement*>(l);
			url_le = dynamic_cast<UrlLineElement*>(l);

			if (italic_le) {
				cout << "\\textit{";
			} else if (bold_le) {
				cout << "\\textbf{";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
				delim = delim_list.find_first_not_of(l->content());
				cout << "\\verb" << delim;
			} else if (url_le) {
				cout << "\\href{" << url_le->url() << "}{";
			}

			cout << l->content();

			if (italic_le or bold_le or url_le) {
				cout << "}";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
				cout << delim;
			}
		}
		
		switch (p->level()) {
			case Paragraph::Level::Code:
				cout << endl;
				break;
			case Paragraph::Level::Title1:
			case Paragraph::Level::Title2:
				cout << "}";
			default:
				cout << endl << endl;
				break;

		}
	}
	cout << "\\end{document}" << endl;
}

/* vim: set ts=4 sw=4: */
