#ifndef MDP_ULIST2_PARAGRAPH_HPP
#define MDP_ULIST2_PARAGRAPH_HPP

#include "paragraph.hpp"

/**
 * @brief Unordered list paragraph (level 2)
 *
 * Every list element is represented by one instance of UList2Paragraph.
 **/
class UList2Paragraph : public Paragraph {
	public:
		UList2Paragraph() : Paragraph() {}
		UList2Paragraph(Paragraph * p) : Paragraph(p) {}
		virtual Level level(void) const;
};

#endif // MDP_ULIST2_PARAGRAPH_HPP

