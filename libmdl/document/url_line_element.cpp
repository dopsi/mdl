#include "../includes/document/url_line_element.hpp"

UrlLineElement::UrlLineElement(const std::string & content, const std::string & url) :
	LineElement(content),
	_url(url)
{}

std::string UrlLineElement::url(void) const {
	return _url;
}
