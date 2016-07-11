#ifndef MDP_QUOTE_PARAGRAPH_HPP
#define MDP_QUOTE_PARAGRAPH_HPP

#include "paragraph.hpp"

/**
 * @brief Quote paragraph
 **/
class QuoteParagraph : public Paragraph {
	public:
		QuoteParagraph() : Paragraph() {}
		QuoteParagraph(Paragraph * p) : Paragraph(p) {}
		virtual Level level(void) const;
};

#endif // MDP_QUOTE_PARAGRAPH_HPP
