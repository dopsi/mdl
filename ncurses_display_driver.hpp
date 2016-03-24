#ifndef MDL_NCURSES_DISPLAY_DRIVER_HPP
#define MDL_NCURSES_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

#include "paragraph.hpp"

#include <ncurses.h>

class NcursesDisplayDriver : public DisplayDriver {
	private:
		WINDOW* _stdscr;
		WINDOW* _title_window;
		WINDOW* _display_window;
		WINDOW* _footer_window;
		size_t _display_offset;
		void render(Document * doc, WINDOW * win, const size_t & line_offset) const;
	public:
		NcursesDisplayDriver();
		virtual ~NcursesDisplayDriver();
		virtual void display(Document *doc);
};

#endif // MDL_NCURSES_DISPLAY_DRIVER_HPP
