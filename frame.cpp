#include "frame.hpp"

using namespace frame;


AccessList::AccessList(Access* head, AccessList* next)
	: m_head(head), m_next(next)
{}

