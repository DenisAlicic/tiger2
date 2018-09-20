#include "assem.hpp"
#include <sstream>

using namespace assem;

Targets::Targets(temp::LabelList* labels)
	: m_labels(labels)
{}

Instr::Instr(std::string assem)
	: m_assem(std::move(assem))
{}

Instr::~Instr()
{}

temp::Temp* Instr::nthTemp(temp::TempList* l, int i)
{
	if (i == 0)
		return l->m_head;
	else
		return nthTemp(l->m_tail, i - 1);
}

temp::Label* Instr::nthLabel(temp::LabelList* l, int i)
{
	if (i == 0)
		return l->m_head;
	else
		return nthLabel(l->m_tail, i - 1);
}


std::string Instr::format(temp::TempMap* m)
{
	temp::TempList* dst = def();
	temp::TempList* src = use();
	Targets* j = jumps();
	temp::LabelList* jump = (j == nullptr) ? nullptr : j->m_labels;
	std::stringstream s;
	int len = m_assem.length();
	for (int i = 0; i < len; i++)
		if (m_assem[i] == '`')
			switch (m_assem[++i]) {
				case 's': {
					int n = m_assem[++i]-'0';
					s << m->tempMap(nthTemp(src, n));
					break;
				}
				case 'd': {
					int n = m_assem[++i]-'0';
					s << m->tempMap(nthTemp(dst, n));
					break;
				}
				case 'j': {
					int n = m_assem[++i]-'0';
					s << nthLabel(jump, n)->toString();
					break;
				}
				case '`': {
					s << '`';
					break;
				}
				default:
					throw "bad Assem format";
			}
		else
			s << m_assem[i];

	return s.str();
}


InstrList::InstrList(Instr* head, InstrList* tail)
	: m_head(head), m_tail(tail)
{}

InstrList* InstrList::append(InstrList* i1, InstrList* i2)
{
	InstrList* t = nullptr;

	for (InstrList* t1 = i1; t1 != nullptr; t1 = t1->m_tail)
		t = new InstrList(t1->m_head, t);

	InstrList* ret = i2;

	for (InstrList* t2 = t; t2 != nullptr; t2 = t2->m_tail)
		ret = new InstrList(t2->m_head, ret);

	return ret;
}

LABEL::LABEL(std::string a, temp::Label* label)
	: Instr(a), m_label(label)
{}

temp::TempList* LABEL::use()
{
	return nullptr;
}

temp::TempList* LABEL::def()
{
	return nullptr;
}

Targets* LABEL::jumps()
{
	return nullptr;
}

MOVE::MOVE(std::string a, temp::Temp* dst, temp::Temp* src)
	: Instr(a), m_dst(dst), m_src(src)
{}

temp::TempList* MOVE::use()
{
	return new temp::TempList(m_src, nullptr);
}

temp::TempList* MOVE::def()
{
	return new temp::TempList(m_dst, nullptr);
}

Targets* MOVE::jumps()
{
	return nullptr;
}

OPER::OPER(std::string a, temp::TempList* dst, temp::TempList* src, temp::LabelList* jump)
	: Instr(a), m_dst(dst), m_src(src), m_jump((jump==nullptr) ? nullptr : new Targets(jump))
{}


temp::TempList* OPER::use()
{
	return m_src;
}

temp::TempList* OPER::def()
{
	return m_dst;
}

Targets* OPER::jumps()
{
	return m_jump;
}
