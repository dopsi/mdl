#ifndef MDL_MD_PARSER_HPP
#define MDL_MD_PARSER_HPP

#include "parser.hpp"

/**
 * @brief Markdown parser
 **/
class MdParser : public Parser {
	public:
		MdParser(const std::string & filename);
		~MdParser();
		virtual void parse();
};

#endif // MDL_MD_PARSER_HPP
