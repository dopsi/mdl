#ifndef MDL_TROFF_DISPLAY_DRIVER_HPP
#define MDL_TROFF_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

class TroffDisplayDriver : protected DisplayDriver {
	public:
		TroffDisplayDriver(bool standalone) :
			DisplayDriver(standalone) {};
		~TroffDisplayDriver() {};
		virtual void display(Document * doc);
		virtual void display(Document * doc, std::ostream & output);
};

#endif // MDL_TROFF_DISPLAY_DRIVER_HPP
