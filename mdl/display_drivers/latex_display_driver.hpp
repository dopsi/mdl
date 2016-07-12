#ifndef MDL_LATEX_DISPLAY_DRIVER_HPP
#define MDL_LATEX_DISPLAY_DRIVER_HPP

#include "../../includes/display_driver.hpp"

/**
 * @brief LaTeX implementation of the displaydriver class
 **/
class LaTeXDisplayDriver : public DisplayDriver {
	public:
		LaTeXDisplayDriver() {};
		virtual ~LaTeXDisplayDriver() {};
		virtual void display(Document *doc);
};

#endif // MDL_LATEX_DISPLAY_DRIVER_HPP
