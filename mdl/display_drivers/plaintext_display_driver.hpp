#ifndef MDL_PLAINTEXT_DISPLAY_DRIVER_HPP
#define MDL_PLAINTEXT_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

/**
 * @brief Plaintext display driver
 *
 * This class does output a space padded document
 **/
class PlainTextDisplayDriver : public DisplayDriver {
	public:
		PlainTextDisplayDriver() : DisplayDriver() {}
		virtual ~PlainTextDisplayDriver() {}
		virtual void display(Document * doc);
		virtual void display(Document * doc, std::ostream & output);
};

#endif // MDL_PLAINTEXT_DISPLAY_DRIVER_HPP
