#include "includes/parser.hpp"

Parser::Parser(const std::string & filename) :
	_filename(filename),
	_input_file(filename),
	_document(nullptr)
{
	if (!_input_file.good()) {
		throw std::runtime_error("The file stream is not good.");
	}
}

Parser::~Parser() {
	_input_file.close();
	delete _document;
}

Document* Parser::get_document(void) const {
	return _document;
}
