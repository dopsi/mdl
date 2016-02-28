#ifndef MDL_DISPLAY_DRIVER_HPP
#define MDL_DISPLAY_DRIVER_HPP

#include "document.hpp"

/**
 * @brief Generic display driver interface
 **/
class DisplayDriver {
	public:
		DisplayDriver() {};
		virtual ~DisplayDriver() {};
		virtual void display(Document * doc) = 0;
};

#endif // MDL_DISPLAY_DRIVER_HPP
