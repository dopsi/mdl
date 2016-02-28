#include "ncurses_display_driver.hpp"

using namespace std;

NcursesDisplayDriver::NcursesDisplayDriver() :
	DisplayDriver(), _window(initscr()) {
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
}

NcursesDisplayDriver::~NcursesDisplayDriver() {
	endwin();
}

void NcursesDisplayDriver::display(Document * doc) {
	Paragraph *p(nullptr);
	LineElement *l(nullptr);
	int cursor_x, cursor_y;
	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			printw((l->content()).c_str());
		}
		getyx(stdscr, cursor_y, cursor_x);
		switch (p->level()) {
			case Paragraph::Level::Title1:
			case Paragraph::Level::Title2:
				cursor_y+=2;
				cursor_x=0;
				break;
			default:
				cursor_y+=2;
				cursor_x=0;
				break;

		}
		move(cursor_y, cursor_x);
	}
	refresh();
	getch();
}

