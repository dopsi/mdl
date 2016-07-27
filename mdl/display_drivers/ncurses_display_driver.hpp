#ifndef MDL_NCURSES_DISPLAY_DRIVER_HPP
#define MDL_NCURSES_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

#include "document/paragraph.hpp"

#include <ncurses.h>

/**
 * @brief Ncurses implementation of the DisplayDriver class
 **/
class NcursesDisplayDriver : public DisplayDriver {
	private:
		WINDOW* _stdscr; /**< @brief The screen **/
		WINDOW* _title_window; /**< @brief The title window **/
		WINDOW* _display_window; /**< @brief The display window **/
		WINDOW* _footer_window; /**< @brief The footer window **/
		WINDOW* _url_window; /**< @brief The url display window **/
		int _display_offset; /**< @brief The display_offset **/
		int _width; /**< @brief The screen width **/
		int _url_count; /**< @brief The number of urls to display **/

		/**
		 * @brief Actually render the document on the _display_window
		 *
		 * @param doc The document pointer (gotten from a Parser)
		 * @param line_offset The current line offset
		 *
		 * @return the maximum possible offset
		 **/
		int render(Document * doc, const int & line_offset) const;

		/**
		 * @brief Check the terminal capabilities
		 *
		 * This function does display a warning message on the _title_window
		 * to inform the user of the situation.
		 **/
		void check_capabilities(void) const;
		
		/**
		 * @brief Check if the given coordinates are within the window
		 *
		 * @param w The window to be checked
		 * @param y,x The coordinates
		 *
		 * @return true if the coordinates are within the window
		 **/
		static bool bounds_check(WINDOW* w, int y, int x);
	public:
		NcursesDisplayDriver();
		virtual ~NcursesDisplayDriver();
		virtual void display(Document *doc);
		virtual void display(Document *doc, std::ostream & output);
};

#endif // MDL_NCURSES_DISPLAY_DRIVER_HPP
