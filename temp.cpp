#include "temp.hpp"

using namespace temp;

int Temp::s_count = 40;

Temp::Temp(int i)
	: m_num(i)
{}

Temp::Temp()
	: m_num(s_count++)
{}

std::string Temp::toString() const
{
	return "t" + std::to_string(m_num);
}


int Label::s_count = 0;

Label::Label(std::string name)
	: m_name(name.empty() ? "L" + std::to_string(s_count++) : std::move(name))
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

LabelList::~LabelList()
{
	// delete m_head;
	// delete m_tail;
}

Label* LabelList::head() const
{
	return m_head;
}

LabelList* LabelList::tail() const
{
	return m_tail;
}

TempList::TempList(Temp* head, TempList* tail)
	: m_head(head), m_tail(tail)
{}

Temp* TempList::head() const
{
	return m_head;
}

TempList* TempList::tail() const
{
	return m_tail;
}

TempList::~TempList()
{
	// delete m_head;
	// delete m_tail;
}

std::string DefaultMap::tempMap(Temp* temp) const
{
	return temp->toString();
}

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

CombineMap::~CombineMap()
{
	// delete m_tmap1;
	// delete m_tmap2;
}
