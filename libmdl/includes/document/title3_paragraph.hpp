#ifndef MDP_TITLE3_PARAGRAPH_HPP
#define MDP_TITLE3_PARAGRAPH_HPP

#include "paragraph.hpp"

/**
 * @brief Title3 paragraph
 **/
class Title3Paragraph : public Paragraph {
	public:
		Title3Paragraph() : Paragraph() {}
		Title3Paragraph(Paragraph * p) : Paragraph(p) {}
		virtual Level level(void) const;
};

#endif // MDP_TITLE3_PARAGRAPH_HPP
