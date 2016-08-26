#ifndef MDL_TROFF_DISPLAY_DRIVER_HPP
#define MDL_TROFF_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

/**
 * @brief Troff display driver
 *
 * This class does output a document suitable for man display
 **/
class TroffDisplayDriver : public DisplayDriver {
	public:
		TroffDisplayDriver(bool standalone) :
			DisplayDriver(standalone) {};
		~TroffDisplayDriver() {};
		virtual void display(Document * doc);
		virtual void display(Document * doc, std::ostream & output);
};

#endif // MDL_TROFF_DISPLAY_DRIVER_HPP
