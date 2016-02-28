#ifndef MDL_PARSER_HPP
#define MDL_PARSER_HPP

#include "document.hpp"

#include <string>
#include <fstream>

/**
 * @brief Generic parser interface
 **/
class Parser {
	protected:
		std::ifstream _input_file;
		Document * _document;
	public:
		Parser(const std::string & filename);
		virtual ~Parser();
		virtual Document* get_document(void) const;
		virtual void parse() = 0;
};

#endif // MDL_PARSER_HPP
