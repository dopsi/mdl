#include "ncurses_display_driver.hpp"

#include "document/url_line_element.hpp"
#include "document/code_line_element.hpp"
#include "document/bold_line_element.hpp"
#include "document/italic_line_element.hpp"

#include <cassert>

#include <unistd.h>

#include <iostream>
using namespace std;

#define WIN_TITLE_PAIR 1
#define TITLE1_PAIR 2
#define ULIST1_PAIR 3
#define RED_PAIR 4
#define COLOR_NONE -1

NcursesDisplayDriver::NcursesDisplayDriver() :
	DisplayDriver(true), _stdscr(initscr()),
	_title_window(newwin(1,_tty.columns(),0,0)),
	_display_window(newwin(_tty.lines()-4,_tty.columns(),2,0)),
	_footer_window(newwin(1, _tty.columns(), _tty.lines()-1, 0)),
	_url_window(newwin(1, _tty.columns(), 2, 0)),
	_display_offset(0) {
	//Check if all windows have been initialized
	while(!_title_window) {
		_title_window = newwin(1,_tty.columns(),0,0);
	}
	
	while(!_display_window) {
		_display_window = newwin(_tty.lines()-4,_tty.columns(),2,0);
	}

	while(!_footer_window) {
		_footer_window = newwin(1, _tty.columns(), _tty.lines()-1, 0);
	}
	assert(has_colors());

	// Begin ncurses mode
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	// Set up colors
	start_color();
	use_default_colors();
	init_pair(WIN_TITLE_PAIR, COLOR_YELLOW, COLOR_NONE);
	init_pair(TITLE1_PAIR, COLOR_BLUE, COLOR_NONE);
	init_pair(ULIST1_PAIR, COLOR_CYAN, COLOR_NONE);
	init_pair(RED_PAIR, COLOR_RED, COLOR_NONE);

	// Refresh screen, to enable the windows
	refresh();
}

NcursesDisplayDriver::~NcursesDisplayDriver() {
	endwin();
}

void NcursesDisplayDriver::display(Document * doc) {
	check_capabilities();
	bool go(true),
	     update_title(true),
	     update_body(true),
	     update_footer(true),
	     display_urls(false);
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

		int display_h, display_w; // display_w required for getmaxyx
		getmaxyx(_display_window,display_h,display_w);
		int url_h, url_w; // url_w required for getmaxyx
		getmaxyx(_url_window,url_h,url_w);

		if (update_body or !display_urls) {
			update_body = false;
			max_offset = render(doc, offset);
			if (!display_urls) {
				wresize(_display_window, _tty.lines()-4, _tty.columns());
				wrefresh(_display_window);
			}
		}

		if (display_urls) {
			wrefresh(_url_window);
			wresize(_display_window, _tty.lines()-4-url_h, _tty.columns());
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
			case 'u':
				display_urls = !display_urls;
				break;
			case KEY_DOWN:
				if (offset <= max_offset-display_h) {
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
				offset -= display_h;
				update_body = true;
				update_footer = true;
				if (offset < 0) {
					offset = 0;
				}
				break;
			case KEY_NPAGE:
				offset += display_h;
				update_body = true;
				update_footer = true;
				if (offset >= max_offset-display_h) {
					offset = max_offset-display_h;
				}
				break;
			case ' ':
				offset += display_h/2;
				update_body = true;
				update_footer = true;
				if (offset >= max_offset-display_h) {
					offset = max_offset-display_h;
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
	UrlLineElement *u(nullptr);

	bool is_first(true);
	int cursor_x, cursor_y(-line_offset);
	string tmp_str;
	attr_t current = 0;
	short current_color = 0;
	int url_count(0);
	int displayed_url_count(0);
	int olist1_index(1);

	mvwin(_url_window, 2, 0);
	wresize(_url_window, 1, _tty.columns());
	wattron(_url_window, A_UNDERLINE);
	mvwprintw(_url_window, 0, 0, "Url list");
	wattroff(_url_window, A_UNDERLINE);

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
			case Paragraph::Level::Title3:
				wattron(_display_window, COLOR_PAIR(TITLE1_PAIR));
				if (!is_first) {
					cursor_y+=2;
				}
				cursor_x=3;
				break;
			case Paragraph::Level::UList1:
			case Paragraph::Level::OList1:
				if (!is_first) {
					cursor_y+=1;
				}
				cursor_x=0;
				break;
			case Paragraph::Level::UList2:
				if (!is_first) {
					cursor_y+=1;
				}
				cursor_x=2;
				break;
			case Paragraph::Level::Code:
				if (!is_first) {
					cursor_y+=1;
				}
				cursor_x=4;
				mvwchgat(_display_window, cursor_y, 0, -1, A_REVERSE, 0, NULL);
				break;
			case Paragraph::Level::Quote:
				wattron(_display_window, A_REVERSE);
				wattron(_display_window, COLOR_PAIR(TITLE1_PAIR));
				if (!is_first) {
					cursor_y+=1;
				}
				cursor_x=0;
				mvwchgat(_display_window, cursor_y, 0, -1, A_REVERSE, TITLE1_PAIR, NULL);
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
				case Paragraph::Level::OList1:
					wattron(_display_window, COLOR_PAIR(ULIST1_PAIR));
					wprintw(_display_window, "%d)", olist1_index);
					wattroff(_display_window, COLOR_PAIR(ULIST1_PAIR));
					wprintw(_display_window, " ");
					++olist1_index;
					break;
				default:
					break;
			}
		}
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			tmp_str = l->content();
			if ( (u=dynamic_cast<UrlLineElement*>(l)) and bounds_check(_display_window, cursor_y, cursor_x) ) { // this is an UrlLineElement
				wattr_get(_display_window, &current, &current_color, nullptr);
				wattron(_display_window, A_UNDERLINE);
				wattron(_display_window, COLOR_PAIR(ULIST1_PAIR));
				++url_count;
				if (bounds_check(_display_window, cursor_y, cursor_x)) {
					++displayed_url_count;
					wresize(_url_window, displayed_url_count+1, _tty.columns());
					mvwprintw(_url_window, displayed_url_count, 0, "[%d] %s", url_count, u->url().c_str());
				}
			} else if (dynamic_cast<CodeLineElement*>(l)) { // this is a CodeLineElement
				wattr_get(_display_window, &current, &current_color, nullptr);
				if (current&A_REVERSE) {
					wattroff(_display_window, A_REVERSE);
				} else {
					wattron(_display_window, A_REVERSE);
				}
			} else if (dynamic_cast<BoldLineElement*>(l)) { // Bold element
				wattron(_display_window, A_BOLD);
			} else if (dynamic_cast<ItalicLineElement*>(l)) { // Italic element
				wattron(_display_window, A_ITALIC);
			}
			if (tmp_str.size() < _tty.columns() - cursor_x) {
				if (bounds_check(_display_window, cursor_y, cursor_x)) {
					wprintw(_display_window, tmp_str.c_str());
				}
			} else {
				for (size_t k(0); k < tmp_str.size(); k+=_tty.columns()) {
					if (k != 0) {
						cursor_x = 0;
						cursor_y += 1;
						wmove(_display_window, cursor_y, cursor_x);
					}
					if (bounds_check(_display_window, cursor_y, cursor_x)) {
						wprintw(_display_window, tmp_str.substr(k, _tty.columns()).c_str());
					}
				}
			}
			if (dynamic_cast<UrlLineElement*>(l) and bounds_check(_display_window, cursor_y, cursor_x)) { // this is an UrlLineElement
				wprintw(_display_window, "[%d]", url_count);
				wattr_set(_display_window, current, current_color, nullptr);
			} else if (dynamic_cast<CodeLineElement*>(l)) { // this is a CodeLineElement
				if (current&A_REVERSE) {
					wattron(_display_window, A_REVERSE);
				} else {
					wattroff(_display_window, A_REVERSE);
				}
			} else if (dynamic_cast<BoldLineElement*>(l)) { // Bold element
				wattroff(_display_window, A_BOLD);
			} else if (dynamic_cast<ItalicLineElement*>(l)) { // Italic element
				wattroff(_display_window, A_ITALIC);
			}
		}
		switch (p->level()) {
			case Paragraph::Level::Title1:
				wattroff(_display_window, A_UNDERLINE);
			case Paragraph::Level::Title2:
			case Paragraph::Level::Title3:
				wattroff(_display_window, COLOR_PAIR(TITLE1_PAIR));
				break;
			case Paragraph::Level::Code:
				wattroff(_display_window, A_REVERSE);
				wmove(_display_window, cursor_y, cursor_x);
				break;
			case Paragraph::Level::Quote:
				wattroff(_display_window, A_REVERSE);
				wattroff(_display_window, COLOR_PAIR(TITLE1_PAIR));
				break;
			default:
				break;
	
		}
		if (p->level() != Paragraph::Level::OList1) {
			olist1_index = 1;
		}
	}
	
	mvwin(_url_window, _tty.lines()-3-displayed_url_count, 0);

	return cursor_y+line_offset;
}

bool NcursesDisplayDriver::bounds_check(WINDOW* w, int y, int x) {
	int win_x, win_y;
	getmaxyx(w, win_y, win_x);

	return !(y > (win_y - 1) or x > (win_x - 1) or x < 0 or y < 0);
}

void NcursesDisplayDriver::check_capabilities(void) const {
	if (!tigetstr("sitm") or !tigetstr("ritm")) {
		werase(_display_window);
		wattr_set(_display_window, A_NORMAL, RED_PAIR, nullptr);
		wprintw(_display_window, "Italics capability not detected for this terminal");
		int y, x; // x required for getyx
		getyx(_display_window, y, x);
		wmove(_display_window, y+1, 0);
		wprintw(_display_window, "Press any key to continue");
		wrefresh(_display_window);
		sleep(1);
		getch();
	}
}

void NcursesDisplayDriver::display(Document * doc, ostream & output) {
	output << string("Error: NcursesDisplayDriver is not suited for output to a file") << endl;
}
