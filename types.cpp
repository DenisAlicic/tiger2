#include "types.hpp"

using namespace types;

Type* Type::actual() {
	return this;
}

Type::~Type()
{}

bool Type::coerceTo(Type* t) {
	return false;
}

ARRAY::ARRAY(Type* element)
	: m_element(element)
{}

bool ARRAY::coerceTo(Type* t) {
	return this == t->actual();
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

INT::INT()
{}

bool INT::coerceTo(Type* t)
{
	return instanceof<INT>(t->actual());
}

STRING::STRING()
{}

bool STRING::coerceTo(Type* t)
{
	return instanceof<STRING>(t->actual());
}

VOID::VOID()
{}

bool VOID::coerceTo(Type* t)
{
	return instanceof<VOID>(t->actual());
}


RECORD::RECORD(symbol::Symbol* fieldName, Type* fieldType, RECORD* tail)
	: m_fieldName(fieldName), m_fieldType(fieldType), m_tail(tail)
{}

bool RECORD::coerceTo(Type* t)
{
	Type* a = t->actual();
	return (instanceof<RECORD>(a) || instanceof<NIL>(a));
}

void RECORD::gen(symbol::Symbol* n, Type* t, RECORD* x)
{
	m_fieldName = n;
	m_fieldType = t;
	m_tail = x;
}

bool RECORD::isNull(RECORD* r)
{
	if (r == nullptr || (r->m_fieldName == nullptr && r->m_fieldType == nullptr && r->m_tail == nullptr))
		return true;
	return false;
}

NIL::NIL()
{}

bool NIL::coerceTo(Type* t)
{
	Type* a = t->actual();
	return (instanceof<RECORD>(a) || instanceof<NIL>(a));
}


NAME::NAME(symbol::Symbol* name)
	: m_name(name)
{}

 bool NAME::isLoop()
{
	Type* b = m_binding;
	bool anyx;
	m_binding = nullptr;
	if (b == nullptr)
		anyx = true;
	else if (instanceof<NAME>(b))
		anyx = ((NAME*)b)->isLoop();
	else
		anyx = false;
	m_binding = b;
	return anyx;
}

Type* NAME::actual()
{
	return m_binding->actual();
}

bool NAME::coerceTo(Type* t)
{
	return this->actual()->coerceTo(t);
}

void NAME::bind(Type* t)
{
	m_binding = t;
}
