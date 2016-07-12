#ifndef MDP_TEXT_PARAGRAPH_HPP
#define MDP_TEXT_PARAGRAPH_HPP

#include "paragraph.hpp"

/**
 * @brief A basic text paragraph
 **/
class TextParagraph : public Paragraph {
	public:
		virtual Level level(void) const;
};

#endif // MDP_TEXT_PARAGRAPH_HPP
