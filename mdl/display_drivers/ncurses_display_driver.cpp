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
	DisplayDriver(true),
	_width(COLS),
	_title_window(new NCursesColorWindow(1,_width,0,0)),
	_display_window(new NCursesColorWindow(LINES-4,_width,2,0)),
	_footer_window(new NCursesColorWindow(1, _width, LINES-1, 0)),
	_url_window(new NCursesColorWindow(1, _width, 2, 0)),
	_display_offset(0) {
	assert(_title_window);
	assert(_display_window);
	assert(_url_window);
	assert(_footer_window);

	// Begin ncurses mode
	cbreak();
	noecho();
	_title_window->keypad(TRUE);
	_display_window->keypad(TRUE);
	_url_window->keypad(TRUE);
	_footer_window->keypad(TRUE);
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
			_title_window->erase();
			fullname = doc->filename();
			filename = fullname.substr(fullname.find_last_of('/')+1);
			if (!fullname.find("/")) {
				path = fullname.substr(0, fullname.find_last_of('/'));
			} else {
				path = ".";
			}
			_title_window->attron(COLOR_PAIR(WIN_TITLE_PAIR));
			_title_window->printw(string("mdl - "+filename+" ["+path+"]").c_str());
			_title_window->attroff(COLOR_PAIR(WIN_TITLE_PAIR));
			_title_window->refresh();
		}

		int display_h, display_w;
		_display_window->getmaxyx(display_h,display_w);
		int url_h, url_w;
		_url_window->getmaxyx(url_h,url_w);

		if (update_body or !display_urls) {
			update_body = false;
			max_offset = render(doc, offset);
			if (!display_urls) {
				_display_window->wresize(LINES-4, COLS);
				_display_window->refresh();
			}
		}

		if (display_urls) {
			_url_window->refresh();
			_display_window->wresize(LINES-4-url_h, COLS);
			_display_window->refresh();
		}
	
		if (update_footer) {
			update_footer = false;
			_footer_window->erase();
			_footer_window->printw("%d line(s) hidden on top", offset);
			_footer_window->refresh();
		}

		switch(_display_window->getch()) {
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
	_display_window->erase();
	Paragraph *p(nullptr);
	LineElement *l(nullptr);
	UrlLineElement *u(nullptr);

	bool is_first(true);
	int cursor_x, cursor_y(-line_offset);
	string tmp_str;
	int current;
	int url_count(0);
	int displayed_url_count(0);
	int olist1_index(1);

	_url_window->mvwin(2, 0);
	_url_window->wresize(1, COLS);
	_url_window->attron(A_UNDERLINE);
	_url_window->printw(0, 0, "Url list");
	_url_window->attroff(A_UNDERLINE);

	for (size_t i(0); i < doc->size(); ++i) {
		p = (*doc)[i];
		switch (p->level()) {
			case Paragraph::Level::Title1:
				_display_window->attron(A_UNDERLINE);
				_display_window->attron(COLOR_PAIR(TITLE1_PAIR));
				if (!is_first) {
					cursor_y+=2;
				}
				cursor_x=9;
				break;
			case Paragraph::Level::Title2:
				_display_window->attron(COLOR_PAIR(TITLE1_PAIR));
				if (!is_first) {
					cursor_y+=2;
				}
				cursor_x=5;
				break;
			case Paragraph::Level::Title3:
				_display_window->attron(COLOR_PAIR(TITLE1_PAIR));
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
				_display_window->chgat(cursor_y, 0, -1, A_REVERSE, 0, NULL);
				break;
			case Paragraph::Level::Quote:
				_display_window->attron(A_REVERSE);
				_display_window->attron(COLOR_PAIR(TITLE1_PAIR));
				if (!is_first) {
					cursor_y+=1;
				}
				cursor_x=0;
				_display_window->chgat(cursor_y, 0, -1, A_REVERSE, TITLE1_PAIR, NULL);
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
		_display_window->move(cursor_y, cursor_x);
		if (bounds_check(_display_window, cursor_y, cursor_x)) {
			switch (p->level()) {
				case Paragraph::Level::UList1:
				case Paragraph::Level::UList2:
					_display_window->attron(COLOR_PAIR(ULIST1_PAIR));
					_display_window->printw("*");
					_display_window->attroff(COLOR_PAIR(ULIST1_PAIR));
					_display_window->printw(" ");
					break;
				case Paragraph::Level::OList1:
					_display_window->attron(COLOR_PAIR(ULIST1_PAIR));
					_display_window->printw("%d)", olist1_index);
					_display_window->attroff(COLOR_PAIR(ULIST1_PAIR));
					_display_window->printw(" ");
					++olist1_index;
					break;
				default:
					break;
			}
		}
		for (size_t j(0); j < p->size(); ++j) {
			l = (*p)[j];
			tmp_str = l->content();
			if ( (u=dynamic_cast<UrlLineElement*>(l)) and bounds_check(_display_window, cursor_y, cursor_x)) { // this is an UrlLineElement
				current = _display_window->attrget();
				_display_window->attron(A_UNDERLINE);
				_display_window->attron(COLOR_PAIR(ULIST1_PAIR));
				++url_count;
				if (bounds_check(_display_window, cursor_y, cursor_x)) {
					++displayed_url_count;
					_url_window->wresize(displayed_url_count+1, COLS);
					_url_window->printw(displayed_url_count, 0, "[%d] %s", url_count, u->url().c_str());
				}
			} else if (dynamic_cast<CodeLineElement*>(l)) { // this is a CodeLineElement
				current = _display_window->attrget();
				if (current&A_REVERSE) {
					_display_window->attroff(A_REVERSE);
				} else {
					_display_window->attron(A_REVERSE);
				}
			} else if (dynamic_cast<BoldLineElement*>(l)) { // Bold element
				_display_window->attron(A_BOLD);
			} else if (dynamic_cast<ItalicLineElement*>(l)) { // Italic element
				_display_window->attron(A_ITALIC);
			}
			if (tmp_str.size() < _width - cursor_x) {
				if (bounds_check(_display_window, cursor_y, cursor_x)) {
					_display_window->printw(tmp_str.c_str());
				}
			} else {
				for (size_t i(0); i < tmp_str.size(); i+=_width) {
					if (i != 0) {
						cursor_x = 0;
						cursor_y += 1;
						_display_window->move(cursor_y, cursor_x);
					}
					if (bounds_check(_display_window, cursor_y, cursor_x)) {
						_display_window->printw(tmp_str.substr(i, _width).c_str());
					}
				}
			}
			if (dynamic_cast<UrlLineElement*>(l) and bounds_check(_display_window, cursor_y, cursor_x)) { // this is an UrlLineElement
				_display_window->printw("[%d]", url_count);
				_display_window->attrset(current);
			} else if (dynamic_cast<CodeLineElement*>(l)) { // this is a CodeLineElement
				if (current&A_REVERSE) {
					_display_window->attron(A_REVERSE);
				} else {
					_display_window->attroff(A_REVERSE);
				}
			} else if (dynamic_cast<BoldLineElement*>(l)) { // Bold element
				_display_window->attroff(A_BOLD);
			} else if (dynamic_cast<ItalicLineElement*>(l)) { // Italic element
				_display_window->attroff(A_ITALIC);
			}
		}
		switch (p->level()) {
			case Paragraph::Level::Title1:
				_display_window->attroff(A_UNDERLINE);
			case Paragraph::Level::Title2:
			case Paragraph::Level::Title3:
				_display_window->attroff(COLOR_PAIR(TITLE1_PAIR));
				break;
			case Paragraph::Level::Code:
				_display_window->attroff(A_REVERSE);
				_display_window->move(cursor_y, cursor_x);
				break;
			case Paragraph::Level::Quote:
				_display_window->attroff(A_REVERSE);
				_display_window->attroff(COLOR_PAIR(TITLE1_PAIR));
				break;
			default:
				break;
	
		}
		if (p->level() != Paragraph::Level::OList1) {
			olist1_index = 1;
		}
	}
	
	_url_window->mvwin(LINES-3-displayed_url_count, 0);

	return cursor_y+line_offset;
}

bool NcursesDisplayDriver::bounds_check(NCursesWindow* w, int y, int x) {
	int win_x, win_y;
	w->getmaxyx(win_y, win_x);

	if (y > (win_y-1) or x > (win_x-1) or x < 0 or y < 0) {
		return false;
	} else {
		return true;
	}
}

void NcursesDisplayDriver::check_capabilities(void) const {
	if (!tigetstr("sitm") or !tigetstr("ritm")) {
		_display_window->erase();
		_display_window->attron(A_NORMAL);
		_display_window->attron(COLOR_PAIR(RED_PAIR));
		_display_window->printw("Italics capability not detected for this terminal");
		int y, x;
		_display_window->getyx(y, x);
		_display_window->move(y+1, 0);
		_display_window->printw("Press any key to continue");
		_display_window->refresh();
		sleep(1);
		getch();
	}
}

void NcursesDisplayDriver::display(Document * doc, ostream & output) {
	output << string("Error: NcursesDisplayDriver is not suited for output to a file") << endl;
}
