#ifndef MDL_OPTIONS_HPP
#define MDL_OPTIONS_HPP

#include <string>

/**
 * @brief The command line options handler
 *
 * This class does handle the command line options provided to 
 * the program. In the future, it may also handle configurations
 * files.
 **/
class MdlOptions {
	private:
		bool _standalone; /**< @brief The standalone flag. **/
		std::string _display_driver; /**< @brief The name of the display driver **/
		std::string _input_file; /**< @brief The name of the input file **/
		std::string _output_file; /**< @brief The name of the output file **/
	public:
		/**
		 * @brief Constructor
		 *
		 * This constructor does take as arguments the arguments provided
		 * to the program.
		 *
		 * @param argc The number of arguments provided to the program
		 * @param argv Array of C-strings cointaining the arguments
		 **/
		MdlOptions(int argc, const char *const *argv);
		
		/**
		 * @brief Destructor
		 **/
		~MdlOptions();

		/**
		 * @brief Standalone getter
		 *
		 * @return true if the output must be standalone, false otherwise
		 **/
		bool standalone(void) const;

		/**
		 * @brief Display driver name getter
		 *
		 * This function returns the name of the display driver
		 *
		 * @return The name of the display driver. This may not be an empty 
		 * string.
		 **/
		std::string display_driver(void) const;

		/**
		 * @brief Input file getter
		 *
		 * This return value is never and empty string. However, it is not 
		 * guaranteed to be a valid file.
		 *
		 * @return The name of the input file.
		 **/
		std::string input_file(void) const;

		/**
		 * @brief Input file getter
		 *
		 * @return The name of the output file. This may be and empty string.
		 **/
		std::string output_file(void) const;
};

#endif // MDL_OPTIONS_HPP
