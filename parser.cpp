#include "parser.hpp"

Parser::Parser(const std::string & filename) :
	_input_file(filename),
	_document(nullptr)
{
}

Parser::~Parser() {
	_input_file.close();
}

Document* Parser::get_document(void) const {
	return _document;
}
