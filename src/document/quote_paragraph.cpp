#include "quote_paragraph.hpp"

Paragraph::Level QuoteParagraph::level(void) const {
	return Paragraph::Level::Quote;
}
