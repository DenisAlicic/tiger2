#include "errormsg.hpp"
#include <iostream>

using namespace tiger::errormsg;

bool ErrorMsg::anyErrors = false;

LineList::LineList(int head, LineList* tail)
	: m_head(head), m_tail(tail)
{}


ErrorMsg::ErrorMsg(const std::string& f)
	: m_linePos(new LineList(-1, nullptr)), m_lineNum(1), m_filename(f)
{
	anyErrors = false;
}

void ErrorMsg::newline(int pos)
{
	m_lineNum++;
	m_linePos = new LineList(pos, m_linePos);
}

void ErrorMsg::error(int pos, const std::string& msg)
{
	int n = m_lineNum;
	LineList* p = m_linePos;
	std::string sayPos = "0.0";

	anyErrors = true;

	while (p != nullptr) {
		if (p->m_head < pos) {
			sayPos = ":" + std::to_string(n) + "." + std::to_string(pos - p->m_head);
			break;
		}
		p = p->m_tail;
		n--;
	}

	std::cout << m_filename + ":" + sayPos + ": " + msg<< std::endl;
}
