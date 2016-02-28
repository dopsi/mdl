#ifndef MDP_TITLE1_PARAGRAPH_HPP
#define MDP_TITLE1_PARAGRAPH_HPP

#include "paragraph.hpp"

class Title1Paragraph : public Paragraph {
	public:
		Title1Paragraph() : Paragraph() {}
		Title1Paragraph(Paragraph * p) : Paragraph(p) {}
		virtual Level level(void) const;
};

#endif // MDP_TITLE1_PARAGRAPH_HPP
