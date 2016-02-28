#ifndef MDL_PLAINTEXT_DISPLAY_DRIVER_HPP
#define MDL_PLAINTEXT_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

class PlainTextDisplayDriver : public DisplayDriver {
	public:
		PlainTextDisplayDriver() : DisplayDriver() {}
		virtual ~PlainTextDisplayDriver() {}
		virtual void display(Document * doc);
};

#endif // MDL_PLAINTEXT_DISPLAY_DRIVER_HPP
