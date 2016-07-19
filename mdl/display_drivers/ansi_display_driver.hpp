#ifndef MDL_ANSI_DISPLAY_DRIVER_HPP
#define MDL_ANSI_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

/**
 * @brief Ansi display driver
 *
 * This class does output a space padded document with ansi escape sequences
 **/
class AnsiDisplayDriver : public DisplayDriver {
	public:
		AnsiDisplayDriver() : DisplayDriver() {}
		virtual ~AnsiDisplayDriver() {}
		virtual void display(Document * doc);
		virtual void display(Document * doc, std::ostream & output);
};

#endif // MDL_ANSI_DISPLAY_DRIVER_HPP
