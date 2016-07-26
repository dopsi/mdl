#ifndef MDL_DISPLAY_DRIVER_HPP
#define MDL_DISPLAY_DRIVER_HPP

#include "document/document.hpp"

/**
 * @brief Generic display driver interface
 *
 * The DisplayDriver::display() function does need to be reimplemented to 
 * do the actual displaying.
 *
 * @see NcursesDisplayDriver and PlaintextDisplayDriver for default implementations
 **/
class DisplayDriver {
	public:
		/**
		 * @brief Constructor
		 *
		 * This constructor does nothing. In the derived class, it 
		 * can be used to initialize the display system.
		 *
		 * @param standalone Set the display driver to output 
		 * standalone data (see DisplayDriver::_standalone).
		 **/
		DisplayDriver(
			bool standalone
			);

		/**
		 * @brief Destructor
		 *
		 * Nothing is done here. In the derived class, it can
		 * be used to stop the display system.
		 **/
		virtual ~DisplayDriver() {};

		/**
		 * @brief The actual display function to be reimplemented.
		 *
		 * This function will be called by the program to be used as 
		 * the main loop for the display system. It need to be 
		 * implemented.
		 *
		 * The output of this function should be sent to STDOUT.
		 *
		 * This function can often simply be a wrapper around
		 * DisplayDriver::display(doc, std::cout).
		 *
		 * @param doc A pointer to the Document object to be displayed.
		 **/
		virtual void display(Document * doc) = 0;

		/**
		 * @brief The actual display function to be reimplemented.
		 *
		 * This function will be called by the program to be used as 
		 * the main loop for the display system. It need to be 
		 * implemented.
		 *
		 * The output of this function should be sent to the given 
		 * output file.
		 *
		 * @param doc A pointer to the Document object to be displayed.
		 * @param output The output file, which must already be open, 
		 * and will not be closed.
		 **/
		virtual void display(Document * doc, std::ostream & output) = 0;

	protected:
		/**
		 * @brief Wrap the output to make it stand-alone.
		 *
		 * This flag is set by default, and **must** be used to determine
		 * if the output must be standalone.
		 *
		 * @example This can set to false to output HTML or LaTex 
		 * fragments instead of a full file.
		 **/
		bool _standalone;
};

#endif // MDL_DISPLAY_DRIVER_HPP
