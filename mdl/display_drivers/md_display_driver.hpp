#ifndef MDL_MD_DISPLAY_DRIVER_HPP
#define MDL_MD_DISPLAY_DRIVER_HPP

#include "display_driver.hpp"

/**
 * @brief Plaintext display driver
 *
 * This class does output a space padded document
 **/
class MdDisplayDriver : protected DisplayDriver {
	public:
		MdDisplayDriver() : DisplayDriver() {}
		virtual ~MdDisplayDriver() {}
		virtual void display(Document * doc);
		virtual void display(Document * doc, std::ostream & output);
};

#endif // MDL_MD_DISPLAY_DRIVER_HPP
