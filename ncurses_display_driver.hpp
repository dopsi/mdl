#ifndef MDL_NCURSES_DISPLAY_DRIVER_HPP
#define MDL_NCURSES_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

#include <ncurses.h>

class NcursesDisplayDriver : public DisplayDriver {
	private:
		WINDOW* _window;
	public:
		NcursesDisplayDriver();
		virtual ~NcursesDisplayDriver();
		virtual void display(Document *doc);
};

#endif // MDL_NCURSES_DISPLAY_DRIVER_HPP
