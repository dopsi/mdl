#ifndef MDL_HTML_DISPLAY_DRIVER_HPP
#define MDL_HTML_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

/**
 * @brief HTML implementation of the DisplayDriver class
 **/
class HtmlDisplayDriver : public DisplayDriver {
	public:
		HtmlDisplayDriver(bool standalone);
		virtual ~HtmlDisplayDriver();
		virtual void display(Document *doc);
		virtual void display(Document *doc, std::ostream & output);
};

#endif // MDL_HTML_DISPLAY_DRIVER_HPP
