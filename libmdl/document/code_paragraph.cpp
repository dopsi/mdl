#include "../includes/document/code_paragraph.hpp"

Paragraph::Level CodeParagraph::level(void) const {
	return Paragraph::Level::Code;
}
