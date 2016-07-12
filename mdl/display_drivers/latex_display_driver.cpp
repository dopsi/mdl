#include "latex_display_driver.hpp"

#include "../../libmdl/includes/document/bold_line_element.hpp"
#include "../../libmdl/includes/document/italic_line_element.hpp"
#include "../../libmdl/includes/document/code_line_element.hpp"
#include "../../libmdl/includes/document/url_line_element.hpp"

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
	size_t delim_pos(0);
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
				delim_pos = delim_list.find_first_not_of(l->content());
				delim = delim_list[delim_pos];
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
				if (p->last()) {
					cout << "\\end{verbatim}" << endl << endl;
					is_verbatim = false;
				}
				break;
			case Paragraph::Level::Quote:
				cout << endl;
				if (p->last()) {
					cout << "\\end{quotation}" << endl << endl;
					is_quotation = false;
				}
				break;
			case Paragraph::Level::UList1:
				cout << endl;
				if (p->last()) {
					cout << "\\end{itemize}" << endl << endl;
					is_ulist = false;
				}
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
