#include "types.hpp"
#include "util.hpp"

using namespace types;

Type* Type::actual()
{
	return this;
}

Type::~Type()
{}

bool Type::coerceTo(Type* t)
{
	return false;
}

INT::INT()
{}

bool INT::coerceTo(Type* t)
{
	return util::instanceof<INT>(t->actual());
}

STRING::STRING()
{}

bool STRING::coerceTo(Type* t)
{
	return util::instanceof<STRING>(t->actual());
}

VOID::VOID()
{}

bool VOID::coerceTo(Type* t)
{
	return util::instanceof<VOID>(t->actual());
}

ARRAY::ARRAY(Type* element)
	: m_element(element)
{}

ARRAY::~ARRAY()
{
	delete m_element;
}

bool ARRAY::coerceTo(Type* t)
{
	return this == t->actual();
}


RECORD::RECORD(symbol::Symbol* fieldName, Type* fieldType, RECORD* tail)
	: m_fieldName(fieldName), m_fieldType(fieldType), m_tail(tail)
{}

RECORD::~RECORD()
{
	delete m_fieldType;
	delete m_tail;
}

bool RECORD::coerceTo(Type* t)
{
	Type* a = t->actual();
	return (util::instanceof<RECORD>(a) || util::instanceof<NIL>(a));
}

void RECORD::gen(symbol::Symbol* name, Type* type, RECORD* tail)
{
	m_fieldName = name;
	m_fieldType = type;
	m_tail = tail;
}

bool RECORD::isNull(RECORD* r)
{
	return r == nullptr || (r->m_fieldName == nullptr && r->m_fieldType == nullptr && r->m_tail == nullptr);
}

symbol::Symbol* RECORD::fieldName() const
{
	return m_fieldName;
}

Type* RECORD::fieldType() const
{
	return m_fieldType;
}

RECORD* RECORD::tail() const
{
	return m_tail;
}

void RECORD::setTailToNull()
{
	m_tail = nullptr;
}

NIL::NIL()
{}

bool NIL::coerceTo(Type* t)
{
	Type* a = t->actual();
	return util::instanceof<RECORD>(a) || util::instanceof<NIL>(a);
}


NAME::NAME(symbol::Symbol* name)
	: m_name(name), m_binding(nullptr)
{}

NAME::~NAME()
{
	delete m_binding;
}

bool NAME::isLoop()
{
	Type* b = m_binding;
	m_binding = nullptr;

	bool anyx;

	if (b == nullptr)
		anyx = true;
	else if (util::instanceof<NAME>(b))
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
	return actual()->coerceTo(t);
}

void NAME::bind(Type* t)
{
	m_binding = t;
}
