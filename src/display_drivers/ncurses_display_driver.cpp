#include "ncurses_display_driver.hpp"

#include <cassert>

using namespace std;

#define WIN_TITLE_PAIR 1
#define TITLE1_PAIR 2
#define ULIST1_PAIR 3
#define COLOR_NONE -1

NcursesDisplayDriver::NcursesDisplayDriver() :
	DisplayDriver(), _stdscr(initscr()),
	_title_window(newwin(3,COLS,0,0)),
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
	init_pair(ULIST1_PAIR, COLOR_CYAN, COLOR_NONE);

	// Refresh screen, to enable the windows
	refresh();
}

NcursesDisplayDriver::~NcursesDisplayDriver() {
	endwin();
}

void NcursesDisplayDriver::display(Document * doc) {
	bool go(true), update_title(true), update_body(true);
	size_t offset(0);
	string fullname, filename, path;

	if (update_title) {
		update_title = false;
		fullname = doc->filename();
		filename = fullname.substr(fullname.find_last_of('/')+1);
		path = fullname.substr(0, fullname.find_last_of('/'));
		wattron(_title_window, COLOR_PAIR(WIN_TITLE_PAIR));
		wprintw(_title_window, string("mdl - "+filename+" ["+path+"]").c_str());
		wattroff(_title_window, COLOR_PAIR(WIN_TITLE_PAIR));
	}

	if (update_body) {
		update_body = false;
		wrefresh(_title_window);
		render(doc, offset);
		wrefresh(_display_window);
	}

	while (go) {
		switch(getch()) {
			case 'q': // quit program
				go = false;
				break;
			case KEY_DOWN:
				++offset;
				update_body = true;
				break;
			case KEY_UP:
				--offset;
				update_body = true;
				break;
			default:
				break;
		}

		if (offset < 0) {
			offset = 0;
		} else if (offset >= doc->size()) {
			offset = doc->size() - 1;
		}
	}
}

void NcursesDisplayDriver::render(Document* doc, const size_t & line_offset) const {
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
			case Paragraph::Level::UList1:
				if (!is_first) {
					cursor_y+=1;
				}
				cursor_x=0;
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
		switch (p->level()) {
			case Paragraph::Level::UList1:
				wattron(_display_window, COLOR_PAIR(ULIST1_PAIR));
				wprintw(_display_window, "*");
				wattroff(_display_window, COLOR_PAIR(ULIST1_PAIR));
				wprintw(_display_window, " ");
				break;
			default:
				break;
		}
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
}
