#include "ncurses_display_driver.hpp"

#include <cassert>

using namespace std;

#define WIN_TITLE_PAIR 1
#define TITLE1_PAIR 2
#define COLOR_NONE -1

NcursesDisplayDriver::NcursesDisplayDriver() :
	DisplayDriver(), _stdscr(initscr()),
	_title_window(newwin(3,30,0,0)),
	_display_window(newwin(60,COLS,2,0)),
	_display_offset(0) {
	//Check if all windows have been initialized
	assert(_title_window);
	assert(_display_window);
	assert(has_colors());

	// Begin ncurses mode
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	// Set up colors
	start_color();
	use_default_colors();
	init_pair(WIN_TITLE_PAIR, COLOR_YELLOW, COLOR_NONE);
	init_pair(TITLE1_PAIR, COLOR_BLUE, COLOR_NONE);

	// Refresh screen, to enable the windows
	refresh();
}

NcursesDisplayDriver::~NcursesDisplayDriver() {
	endwin();
}

void NcursesDisplayDriver::display(Document * doc) {
	wattron(_title_window, COLOR_PAIR(WIN_TITLE_PAIR));
	wprintw(_title_window, "document displayer - title");
	wattroff(_title_window, COLOR_PAIR(WIN_TITLE_PAIR));
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
				wattron(_display_window, A_UNDERLINE);
				wattron(_display_window, COLOR_PAIR(TITLE1_PAIR));
				if (!is_first) {
					cursor_y+=2;
				}
				cursor_x=9;
				break;
			case Paragraph::Level::Title2:
				wattron(_display_window, COLOR_PAIR(TITLE1_PAIR));
				if (!is_first) {
					cursor_y+=2;
				}
				cursor_x=5;
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
		switch (p->level()) {
			case Paragraph::Level::Title1:
				wattroff(_display_window, A_UNDERLINE);
			case Paragraph::Level::Title2:
				wattroff(_display_window, COLOR_PAIR(TITLE1_PAIR));
			default:
				break;
	
		}
	}
	wrefresh(_display_window);
	getch();
}
