#include "ncurses_display_driver.hpp"

#include "../document/url_line_element.hpp"
#include "../document/code_line_element.hpp"

#include <cassert>

using namespace std;

#define WIN_TITLE_PAIR 1
#define TITLE1_PAIR 2
#define ULIST1_PAIR 3
#define COLOR_NONE -1

NcursesDisplayDriver::NcursesDisplayDriver() :
	DisplayDriver(), _stdscr(initscr()),
	_width(COLS),
	_title_window(newwin(1,_width,0,0)),
	_display_window(newwin(LINES-4,_width,2,0)),
	_footer_window(newwin(1, _width, LINES-1, 0)),
	_display_offset(0) {
	//Check if all windows have been initialized
	while(!_title_window) {
		_title_window = newwin(1,_width,0,0);
	}
	
	while(!_display_window) {
		_display_window = newwin(LINES-4,_width,2,0);
	}

	while(!_footer_window) {
		_footer_window = newwin(1, _width, LINES-1, 0);
	}
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
	bool go(true), update_title(true), update_body(true), update_footer(true);
	int offset(0);
	string fullname, filename, path;
	int max_offset(0);

	while (go) {
		if (update_title) {
			update_title = false;
			werase(_title_window);
			fullname = doc->filename();
			filename = fullname.substr(fullname.find_last_of('/')+1);
			if (!fullname.find("/")) {
				path = fullname.substr(0, fullname.find_last_of('/'));
			} else {
				path = ".";
			}
			wattron(_title_window, COLOR_PAIR(WIN_TITLE_PAIR));
			wprintw(_title_window, string("mdl - "+filename+" ["+path+"]").c_str());
			wattroff(_title_window, COLOR_PAIR(WIN_TITLE_PAIR));
			wrefresh(_title_window);
		}
	
		if (update_body) {
			update_body = false;
			max_offset = render(doc, offset);
			wrefresh(_display_window);
		}

		if (update_footer) {
			update_footer = false;
			werase(_footer_window);
			wprintw(_footer_window, "%d line(s) hidden on top", offset);
			wrefresh(_footer_window);
		}

		switch(getch()) {
			case 'q': // quit program
				go = false;
				break;
			case KEY_DOWN:
				if (offset <= max_offset-(LINES-4)) {
					++offset;
					update_body = true;
					update_footer = true;
				}
				break;
			case KEY_UP:
				if (offset > 0) {
					--offset;
					update_footer = true;
					update_body = true;
				}
				break;
			case KEY_PPAGE:
				offset -= LINES-4;
				update_body = true;
				update_footer = true;
				if (offset < 0) {
					offset = 0;
				}
				break;
			case KEY_NPAGE:
				offset += LINES-4;
				update_body = true;
				update_footer = true;
				if (offset >= max_offset-(LINES-4)) {
					offset = max_offset-(LINES-4);
				}
				break;
			case ' ':
				offset += (LINES-4)/2;
				update_body = true;
				update_footer = true;
				if (offset >= max_offset-(LINES-4)) {
					offset = max_offset-(LINES-4);
				}
				break;
			default:
				break;
		}
	}
}

int NcursesDisplayDriver::render(Document* doc, const int & line_offset) const {
	werase(_display_window);
	Paragraph *p(nullptr);
	LineElement *l(nullptr);
	bool is_first(true);
	int cursor_x, cursor_y(-line_offset);
	string tmp_str;
	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];
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
			case Paragraph::Level::Code:
				if (!is_first) {
					cursor_y+=1;
				}
				cursor_x=0;
				break;
			case Paragraph::Level::Quote:
				wattron(_display_window, A_REVERSE);
				wattron(_display_window, COLOR_PAIR(TITLE1_PAIR));
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
		if (bounds_check(_display_window, cursor_y, cursor_x)) {
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
		}
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			tmp_str = l->content();
			if (dynamic_cast<UrlLineElement*>(l)) { // this is an UrlLineElement
				wattron(_display_window, A_UNDERLINE);
				wattron(_display_window, COLOR_PAIR(ULIST1_PAIR));
			} else if (dynamic_cast<CodeLineElement*>(l)) { // this is a CodeLineElement
				wattron(_display_window, A_REVERSE);
			}
			if (tmp_str.size() < _width - cursor_x) {
				if (bounds_check(_display_window, cursor_y, cursor_x)) {
					wprintw(_display_window, tmp_str.c_str());
				}
			} else {
				for (size_t i(0); i < tmp_str.size(); i+=_width) {
					if (i != 0) {
						cursor_x = 0;
						cursor_y += 1;
						wmove(_display_window, cursor_y, cursor_x);
					}
					if (bounds_check(_display_window, cursor_y, cursor_x)) {
						wprintw(_display_window, tmp_str.substr(i, _width).c_str());
					}
				}
			}
			if (dynamic_cast<UrlLineElement*>(l)) { // this is an UrlLineElement
				wattroff(_display_window, COLOR_PAIR(ULIST1_PAIR));
				wattroff(_display_window, A_UNDERLINE);
			} else if (dynamic_cast<CodeLineElement*>(l)) { // this is a CodeLineElement
				wattroff(_display_window, A_REVERSE);
			}

		}
		switch (p->level()) {
			case Paragraph::Level::Title1:
				wattroff(_display_window, A_UNDERLINE);
			case Paragraph::Level::Title2:
				wattroff(_display_window, COLOR_PAIR(TITLE1_PAIR));
				break;
			case Paragraph::Level::Code:
				mvwchgat(_display_window, cursor_y, 0, -1, A_REVERSE, 0, NULL);
				wmove(_display_window, cursor_y, cursor_x);
				break;
			case Paragraph::Level::Quote:
				mvwchgat(_display_window, cursor_y, 0, -1, A_REVERSE, TITLE1_PAIR, NULL);
				wattroff(_display_window, A_REVERSE);
				wattroff(_display_window, COLOR_PAIR(TITLE1_PAIR));
				break;
			default:
				break;
	
		}
	}

	return cursor_y+line_offset;
}

bool NcursesDisplayDriver::bounds_check(WINDOW* w, int y, int x) const {
	int win_x, win_y;
	getmaxyx(w, win_y, win_x);

	if (y > win_y or x > win_x or x < 0 or y < 0) {
		return false;
	} else {
		return true;
	}
}
