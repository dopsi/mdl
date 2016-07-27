#ifndef MDL_OPTIONS_HPP
#define MDL_OPTIONS_HPP

#include <string>

class MdlOptions {
	public:
		MdlOptions(int argc, char **argv);
		~MdlOptions();

		bool standalone(void) const;
		std::string display_driver(void) const;
		std::string input_file(void) const;
		std::string output_file(void) const;
	private:
		bool _standalone;
		std::string _display_driver;
		std::string _input_file;
		std::string _output_file;
};

#endif // MDL_OPTIONS_HPP
