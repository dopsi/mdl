#include "latex_display_driver.hpp"

#include "../document/bold_line_element.hpp"
#include "../document/italic_line_element.hpp"

#include <iostream>
using namespace std;

void LaTeXDisplayDriver::display(Document * doc) {
	Paragraph *p = nullptr;
	LineElement *l = nullptr;

	BoldLineElement *bold_le(nullptr);
	ItalicLineElement *italic_le(nullptr);

	bool is_verbatim(false), 
		 is_quotation(false),
		 is_ulist(false);

	cout << "\\documentclass{article}" << endl;
	cout << "\\usepackage[english]{babel}" << endl;
	cout << "\\usepackage[utf8]{inputenc}" << endl;
	cout << "\\usepackage[T1]{fontenc}" << endl;
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

			if (italic_le) {
				cout << "\\textit{";
			} else if (bold_le) {
				cout << "\\textbf{";
			}
			cout << l->content();

			if (italic_le or bold_le) {
				cout << "}";
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
