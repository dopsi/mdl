#ifndef MDL_MD_DISPLAY_DRIVER_HPP
#define MDL_MD_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

/**
 * @brief Plaintext display driver
 **/
class MdDisplayDriver : public DisplayDriver {
	public:
		MdDisplayDriver() : DisplayDriver(true) {}
		virtual ~MdDisplayDriver() {}
		virtual void display(Document * doc);
		virtual void display(Document * doc, std::ostream & output);
};

#endif // MDL_MD_DISPLAY_DRIVER_HPP
