#ifndef MDL_TROFF_DISPLAY_DRIVER_HPP
#define MDL_TROFF_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

class TroffDisplayDriver : public DisplayDriver {
	public:
		TroffDisplayDriver() {};
		~TroffDisplayDriver() {};
		virtual void display(Document * doc);
		virtual void display(Document * doc, std::ostream & output);
};

#endif // MDL_TROFF_DISPLAY_DRIVER_HPP
