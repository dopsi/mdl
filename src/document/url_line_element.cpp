#include "url_line_element.hpp"

UrlLineElement::UrlLineElement(const std::string & content) :
	LineElement(content.substr(content.find_first_of("[")+1, content.find_last_of("]")-1)),
	_url(content.substr(content.find_first_of("(")+1, content.length()-1))
{}

std::string UrlLineElement::url(void) const {
	return _url;
}
