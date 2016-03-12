#include "ncurses_display_driver.hpp"

#include <cassert>

using namespace std;

NcursesDisplayDriver::NcursesDisplayDriver() :
	DisplayDriver(), _stdscr(initscr()),
	_title_window(newwin(3,30,0,0)),
	_display_window(newwin(60,COLS,2,0)),
	_display_offset(0) {
	assert(_title_window);
	assert(_display_window);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	refresh();
}

NcursesDisplayDriver::~NcursesDisplayDriver() {
	endwin();
}

void NcursesDisplayDriver::display(Document * doc) {
	wprintw(_title_window, "document displayer - title");
	wrefresh(_title_window);
	Paragraph *p(nullptr);
	LineElement *l(nullptr);
	bool is_first(true);
	int cursor_x, cursor_y;
	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];
		getyx(_display_window, cursor_y, cursor_x);
			switch (p->level()) {
				case Paragraph::Level::Title1:
				case Paragraph::Level::Title2:
					if (!is_first) {
						cursor_y+=2;
					}
					cursor_x=9;
					break;
				default:
					if (!is_first) {
						cursor_y+=2;
					}
					cursor_x=0;
					break;
	
			}
		if (is_first) {
			is_first = false;
		}
		wmove(_display_window, cursor_y, cursor_x);
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			wprintw(_display_window, (l->content()).c_str());
		}
	}
	wrefresh(_display_window);
	getch();
}
