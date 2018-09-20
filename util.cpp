#include "util.hpp"

using namespace util;

BoolList::BoolList(bool head, BoolList* tail)
	: m_head(head), m_tail(tail)
{}

BoolList::~BoolList()
{
	delete m_tail;
}

