#include "temp.hpp"

using namespace temp;

int Temp::m_count = 40;

Temp::Temp(int i)
	: m_num(i)
{}

Temp::Temp()
	: m_num(m_count++)
{}

std::string Temp::toString() const
{
	return "t" + std::to_string(m_num);
}


int Label::m_count = 0;

Label::Label(std::string name)
	: m_name(name.empty() ? "L"+std::to_string(m_count++) : std::move(name))
{}


Label::Label(symbol::Symbol* s)
	: Label(s->toString())
{}

std::string Label::toString() const
{
	return m_name;
}


LabelList::LabelList(Label* head, LabelList* tail)
	: m_head(head), m_tail(tail)
{}

std::string DefaultMap::tempMap(Temp* temp) const
{
	return temp->toString();
}

TempList::TempList(Temp* head, TempList* tail)
	: m_head(head), m_tail(tail)
{}

CombineMap::CombineMap(TempMap* tmap1, TempMap* tmap2)
	: m_tmap1(tmap1), m_tmap2(tmap2)
{}

std::string CombineMap::tempMap(Temp* temp) const
{
	std::string s = m_tmap1->tempMap(temp);
	if (!s.empty())
		return s;
	return m_tmap2->tempMap(temp);
}
