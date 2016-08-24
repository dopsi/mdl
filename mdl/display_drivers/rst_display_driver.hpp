#ifndef MDL_RST_DISPLAY_DRIVER_HPP
#define MDL_RST_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

/**
 * @brief reStructuredText display driver
 **/
class RstDisplayDriver : public DisplayDriver {
	public:
		RstDisplayDriver() : DisplayDriver(true) {}
		virtual ~RstDisplayDriver() {}
		virtual void display(Document * doc);
		virtual void display(Document * doc, std::ostream & output);
};

#endif // MDL_RST_DISPLAY_DRIVER_HPP
