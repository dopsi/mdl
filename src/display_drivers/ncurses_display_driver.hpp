#ifndef MDL_NCURSES_DISPLAY_DRIVER_HPP
#define MDL_NCURSES_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

#include "../document/paragraph.hpp"

#include <ncurses.h>

class NcursesDisplayDriver : public DisplayDriver {
	private:
		WINDOW* _stdscr;
		WINDOW* _title_window;
		WINDOW* _display_window;
		WINDOW* _footer_window;
		int _display_offset;
		int _width;
		void render(Document * doc, const int & line_offset) const;
		bool bounds_check(WINDOW* w, int y, int x) const;
	public:
		NcursesDisplayDriver();
		virtual ~NcursesDisplayDriver();
		virtual void display(Document *doc);
};

#endif // MDL_NCURSES_DISPLAY_DRIVER_HPP
