#ifndef MDL_MD_PARSER_HPP
#define MDL_MD_PARSER_HPP

#include "../../includes/parser.hpp"

/**
 * @brief Markdown parser
 **/
class MdParser : public Parser {
	private:
		LineElement* parse_line(Paragraph *p, const std::string & line);
	public:
		MdParser(const std::string & filename);
		~MdParser();
		virtual void parse();
};

#endif // MDL_MD_PARSER_HPP
