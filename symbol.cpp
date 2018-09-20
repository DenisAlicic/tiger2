#include "symbol.hpp"

using namespace symbol;

std::unordered_map<std::string, Symbol*> Symbol::dict;

Symbol::Symbol(std::string name)
	: m_name(std::move(name))
{}

std::string Symbol::toString()
{
	return m_name;
}

Symbol* Symbol::symbol(const std::string& n)
{
	Symbol* s;

	auto x = dict.find(n);
	if (x == dict.end()) {
		s = new Symbol(n);
		dict[n] = s;
	}
	else
		s = x->second;

	return s;
}


Binder::Binder(void* value, Symbol* prevtop, Binder* tail)
	: m_value(value), m_prevtop(prevtop), m_tail(tail)
{}

Table::Table() 
	: m_top(nullptr), m_marks(nullptr)
{}


void* Table::get(Symbol* key)
{
	auto x = m_dict.find(key);
	if (x == m_dict.end()) 
		return nullptr;

	return x->second->m_value;
}

void Table::put(Symbol* key, void* value)
{
	Binder* b  = new Binder(value, m_top, m_dict[key]);
	m_dict[key] = b;
	m_top = key;
}

void Table::beginScope()
{
	m_marks = new Binder(nullptr, m_top, m_marks);
	m_top = nullptr;
}

void Table::endScope()
{
	while (m_top != nullptr) {
		Binder* e = m_dict[m_top];
		if (e->m_tail != nullptr)
			m_dict[m_top] = e->m_tail;
		else
			m_dict.erase(m_top);
		m_top = e->m_prevtop;
		delete e;
	}

	m_top = m_marks->m_prevtop;
	auto marksTmp = m_marks->m_tail;
	delete m_marks;
	m_marks = marksTmp;
}

std::vector<Symbol*> Table::keys()
{
	std::vector<Symbol*> k;
	for (auto&& p : m_dict) {
		k.push_back(p.first);
	}

	return k;
}
