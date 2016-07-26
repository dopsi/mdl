#ifndef MDL_LATEX_DISPLAY_DRIVER_HPP
#define MDL_LATEX_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

/**
 * @brief LaTeX implementation of the DisplayDriver class
 **/
class LaTeXDisplayDriver : protected DisplayDriver {
	public:
		LaTeXDisplayDriver(bool standalone);
		virtual ~LaTeXDisplayDriver();
		virtual void display(Document *doc);
		virtual void display(Document *doc, std::ostream & output);
};

#endif // MDL_LATEX_DISPLAY_DRIVER_HPP
