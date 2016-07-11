#include "latex_display_driver.hpp"

#include <iostream>
using namespace std;

void LaTeXDisplayDriver::display(Document * doc) {
	Paragraph *p = nullptr;
	LineElement *l = nullptr;

	cout << "\\documentclass{article}" << endl;
	cout << "\\usepackage[english]{babel}" << endl;
	cout << "\\usepackage[utf8]{inputenc}" << endl;
	cout << "\\usepackage[T1]{fontenc}" << endl;
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
			default:
				break;

		}
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			cout << l->content();
		}
		switch (p->level()) {
			case Paragraph::Level::Title1:
			case Paragraph::Level::Title2:
				cout << "}";
				break;
			default:
				break;

		}
		cout << endl << endl;
	}
	cout << "\\end{document}" << endl;

}

