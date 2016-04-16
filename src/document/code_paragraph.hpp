#ifndef MDP_CODE_PARAGRAPH_HPP
#define MDP_CODE_PARAGRAPH_HPP

#include "paragraph.hpp"

class CodeParagraph : public Paragraph {
	public:
		CodeParagraph() : Paragraph() {}
		CodeParagraph(Paragraph * p) : Paragraph(p) {}
		virtual Level level(void) const;
};

#endif // MDP_CODE_PARAGRAPH_HPP
