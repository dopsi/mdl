#include "latex_display_driver.hpp"

#include "document/bold_line_element.hpp"
#include "document/italic_line_element.hpp"
#include "document/code_line_element.hpp"
#include "document/url_line_element.hpp"

#include <iostream>
using namespace std;

void LaTeXDisplayDriver::display(Document * doc) {
	display(doc, cout);
}

void LaTeXDisplayDriver::display(Document * doc, ostream & output) {
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

	output << "\\documentclass{article}" << endl;
	output << "\\usepackage[english]{babel}" << endl;
	output << "\\usepackage[utf8]{inputenc}" << endl;
	output << "\\usepackage[T1]{fontenc}" << endl;
	output << "\\usepackage{hyperref}" << endl;
	output << "\\begin{document}" << endl;

	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];

		switch (p->level()) {
			case Paragraph::Level::Title1:
				output << "\\section{";
				break;
			case Paragraph::Level::Title2:
				output << "\\subsection{";
				break;
			case Paragraph::Level::Title3:
				output << "\\subsubsection{";
				break;
			case Paragraph::Level::Code:
				if (!is_verbatim) {
					output << "\\begin{verbatim}" << endl;
					is_verbatim = true;
				}
				break;
			case Paragraph::Level::UList1:
				if (!is_ulist) {
					output << "\\begin{itemize}" << endl;
					is_ulist = true;
				}
				output << "\\item ";
				break;
			case Paragraph::Level::Quote:
				if (!is_quotation) {
					output << "\\begin{quotation}" << endl;
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
				output << "\\textit{";
			} else if (bold_le) {
				output << "\\textbf{";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
				delim_pos = delim_list.find_first_not_of(l->content());
				delim = delim_list[delim_pos];
				output << "\\verb" << delim;
			} else if (url_le) {
				output << "\\href{" << url_le->url() << "}{";
			}

			output << l->content();

			if (italic_le or bold_le or url_le) {
				output << "}";
			} else if (code_le and p->level() != Paragraph::Level::Code) {
				output << delim;
			}
		}
		
		switch (p->level()) {
			case Paragraph::Level::Code:
				output << endl;
				if (p->last()) {
					output << "\\end{verbatim}" << endl << endl;
					is_verbatim = false;
				}
				break;
			case Paragraph::Level::Quote:
				output << endl;
				if (p->last()) {
					output << "\\end{quotation}" << endl << endl;
					is_quotation = false;
				}
				break;
			case Paragraph::Level::UList1:
				output << endl;
				if (p->last()) {
					output << "\\end{itemize}" << endl << endl;
					is_ulist = false;
				}
				break;
			case Paragraph::Level::Title1:
			case Paragraph::Level::Title2:
			case Paragraph::Level::Title3:
				output << "}";
			default:
				output << endl << endl;
				break;
		}
	}
	output << "\\end{document}" << endl;
}

/* vim: set ts=4 sw=4: */
