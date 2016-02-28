#include "plaintext_display_driver.hpp"

#include <iostream>
using namespace std;

void PlainTextDisplayDriver::display(Document * doc) {
	Paragraph *p = nullptr;
	LineElement *l = nullptr;

	cout << "Document contains : " << doc->size() << " paragraphs" << endl;
	cout << "=== BEGIN ===" << endl;
	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];
		switch (p->level()) {
			case Paragraph::Level::Title1:
				break;
			case Paragraph::Level::Title2:
				cout << "  ";
				break;
			default:
				cout << "    ";
				break;

		}
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			cout << l->content();
		}
		cout << endl;
	}
	cout << "=== END OF PROGRAM ===" << endl;
}

