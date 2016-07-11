#ifndef MDP_TITLE2_PARAGRAPH_HPP
#define MDP_TITLE2_PARAGRAPH_HPP

#include "paragraph.hpp"

/**
 * @brief Title2 paragraph
 **/
class Title2Paragraph : public Paragraph {
	public:
		Title2Paragraph() : Paragraph() {}
		Title2Paragraph(Paragraph * p) : Paragraph(p) {}
		virtual Level level(void) const;
};

#endif // MDP_TITLE2_PARAGRAPH_HPP
