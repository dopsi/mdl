#ifndef MDL_LATEX_DISPLAY_DRIVER_HPP
#define MDL_LATEX_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

/**
 * @brief LaTeX implementation of the DisplayDriver class
 **/
class LaTeXDisplayDriver : public DisplayDriver {
	public:
		LaTeXDisplayDriver() {};
		virtual ~LaTeXDisplayDriver() {};
		virtual void display(Document *doc);
		virtual void display(Document *doc, std::ostream & output);
};

#endif // MDL_LATEX_DISPLAY_DRIVER_HPP
