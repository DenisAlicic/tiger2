#include "findescape.hpp"
#include <iostream>

using namespace findescape;

Escape::~Escape()
{}

Escape::Escape(int depth)
	: m_depth(depth)
{}

FormalEscape::FormalEscape(int depth, absyn::FieldList* fl)
	: Escape(depth), m_fl(fl)
{
	m_fl->m_escape = false;
}

void FormalEscape::setEscape()
{
	m_fl->m_escape = true;
}

VarEscape::VarEscape(int depth, absyn::VarDec* vd)
	: Escape(depth), m_vd(vd)
{
	m_vd->m_escape = false;
}

void VarEscape::setEscape()
{
	m_vd->m_escape = true;
}

FindEscape::FindEscape()
	: m_escEnv(new symbol::Table())
{}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

void FindEscape::traverseVar(int depth, absyn::Var* v)
{
	if (v == nullptr)
		return;
	else if (instanceof<absyn::SimpleVar>(v)) {
		Escape* escape = (Escape*)(m_escEnv->get(((absyn::SimpleVar*)v)->m_name));
		if (escape == nullptr)
			std::cout << ((absyn::SimpleVar*)v)->m_name << std::endl;
		if (escape->m_depth < depth)
			escape->setEscape();
	} else if (instanceof<absyn::FieldVar>(v)) {
		traverseVar(depth, ((absyn::FieldVar*)v)->m_var);
	} else if (instanceof<absyn::SubscriptVar>(v)) {
		traverseVar(depth, ((absyn::SubscriptVar*)v)->m_var);
		traverseExp(depth, ((absyn::SubscriptVar*)v)->m_index);
	}
}

void FindEscape::traverseExp(int depth, absyn::Exp* e)
{
	if (e == nullptr)
		return;
	else if (instanceof<absyn::VarExp>(e))
		traverseVar(depth, ((absyn::VarExp*)e)->m_var);
	else if (instanceof<absyn::CallExp>(e)) {
		for (absyn::ExpList* el = ((absyn::CallExp*)e)->m_args; el != nullptr; el = el->m_tail)
			traverseExp(depth, el->m_head);
	} else if (instanceof<absyn::OpExp>(e)) {
		traverseExp(depth, ((absyn::OpExp*)e)->m_left);
		traverseExp(depth, ((absyn::OpExp*)e)->m_right);
	} else if (instanceof<absyn::RecordExp>(e))
		for (absyn::FieldExpList* el = ((absyn::RecordExp*)e)->m_fields; el != nullptr; el = el->m_tail)
			traverseExp(depth, el->m_init);
	else if (instanceof<absyn::SeqExp>(e))
		for (absyn::ExpList* el = ((absyn::SeqExp*)e)->m_list; el != nullptr; el = el->m_tail)
			traverseExp(depth, el->m_head);
	else if (instanceof<absyn::AssignExp>(e)) {
		traverseVar(depth, ((absyn::AssignExp*)e)->m_var);
		traverseExp(depth, ((absyn::AssignExp*)e)->m_exp);
	} else if (instanceof<absyn::IfExp>(e)) {
		traverseExp(depth, ((absyn::IfExp*)e)->m_test);
		traverseExp(depth, ((absyn::IfExp*)e)->m_thenclause);
		traverseExp(depth, ((absyn::IfExp*)e)->m_elseclause);
	} else if (instanceof<absyn::WhileExp>(e)) {
		traverseExp(depth, ((absyn::WhileExp*)e)->m_test);
		traverseExp(depth, ((absyn::WhileExp*)e)->m_body);
	} else if (instanceof<absyn::ForExp>(e)) {
		traverseDec(depth, ((absyn::ForExp*)e)->m_var);
		traverseExp(depth, ((absyn::ForExp*)e)->m_hi);
		traverseExp(depth, ((absyn::ForExp*)e)->m_body);
	} else if (instanceof<absyn::LetExp>(e)) {
		for (absyn::DecList* dl = ((absyn::LetExp*)e)->m_decs; dl != nullptr; dl = dl->m_tail)
			traverseDec(depth, dl->m_head);
		traverseExp(depth, ((absyn::LetExp*)e)->m_body);
	} else if (instanceof<absyn::ArrayExp>(e)) {
		traverseExp(depth, ((absyn::ArrayExp*)e)->m_size);
		traverseExp(depth, ((absyn::ArrayExp*)e)->m_init);
	}
}

void FindEscape::traverseDec(int depth, absyn::Dec* d)
{
	if (d == nullptr)
		return;
	else if (instanceof<absyn::VarDec>(d)) {
		traverseExp(depth, ((absyn::VarDec*)d)->m_init);
		m_escEnv->put(((absyn::VarDec*)d)->m_name, new VarEscape(depth, (absyn::VarDec*)d));
	} else if (instanceof<absyn::FunctionDec>(d)) {
		for (absyn::FunctionDec* fd = (absyn::FunctionDec*)d; fd != nullptr; fd = fd->m_next) {
			if (fd->m_inline)
				continue;
			for (absyn::FieldList* fl = (fd)->m_params; fl != nullptr; fl = fl->m_tail)
				m_escEnv->put((fl)->m_name, new FormalEscape(depth + 1, fl));
			traverseExp(depth + 1, (fd)->m_body);
		}
	}
}

void FindEscape::findEscape(absyn::Exp* e)
{
	traverseExp(0, e);
}
