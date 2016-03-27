#ifndef MDP_ULIST1_PARAGRAPH_HPP
#define MDP_ULIST1_PARAGRAPH_HPP

#include "paragraph.hpp"

class UList1Paragraph : public Paragraph {
	public:
		UList1Paragraph() : Paragraph() {}
		UList1Paragraph(Paragraph * p) : Paragraph(p) {}
		virtual Level level(void) const;
};

#endif // MDP_ULIST1_PARAGRAPH_HPP

