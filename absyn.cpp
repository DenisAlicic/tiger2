#include "absyn.hpp"
#include <iostream>

using namespace absyn;

Absyn::Absyn(int pos)
	: m_pos(pos)
{}


Absyn::~Absyn()
{}

Ty::Ty(int pos)
	: Absyn(pos)
{}

Exp::Exp(int pos)
	: Absyn(pos)
{}

Var::Var(int pos)
	: Absyn(pos)
{}

Dec::Dec(int pos)
	: Absyn(pos)
{}

ArrayExp::ArrayExp(int pos, symbol::Symbol* typ, Exp* size, Exp* init)
	: Exp(pos), m_typ(typ), m_size(size), m_init(init)
{}

ArrayExp::~ArrayExp()
{
	// delete m_typ;
	// delete m_size;
	// delete m_init;
}

ArrayTy::ArrayTy(int pos, symbol::Symbol* typ)
	: Ty(pos), m_typ(typ)
{}

ArrayTy::~ArrayTy()
{
	// delete m_typ;
}

AssignExp::AssignExp(int pos, Var* var, Exp* exp)
	: Exp(pos), m_var(var), m_exp(exp)
{}

AssignExp::~AssignExp()
{
	// delete m_var;
	// delete m_exp;
}


BreakExp::BreakExp(int pos)
	: Exp(pos)
{}

ExpList::ExpList(Exp* head, ExpList* tail)
	: m_head(head), m_tail(tail)
{}

ExpList::~ExpList()
{
	// delete m_head;
	// delete m_tail;
}

CallExp::CallExp(int pos, symbol::Symbol* func, ExpList* args)
	: Exp(pos), m_func(func), m_args(args)
{}

CallExp::~CallExp()
{
	// delete m_func;
	// delete m_args;
}


DecList::DecList(Dec* head, DecList* tail)
	: m_head(head), m_tail(tail)
{}

DecList::~DecList()
{
	// delete m_head;
	// delete m_tail;
}

FieldExpList::FieldExpList(int pos, symbol::Symbol* name, Exp* init, FieldExpList* tail)
	: Absyn(pos), m_name(name), m_init(init), m_tail(tail)
{}

FieldExpList::~FieldExpList()
{
	// delete m_name;
	// delete m_init;
	// delete m_tail;
}

FieldList::FieldList(int pos, symbol::Symbol* name, symbol::Symbol* typ, FieldList* tail)
	: Absyn(pos), m_name(name), m_typ(typ), m_tail(tail), m_escape(true)
{}

FieldList::~FieldList()
{
	// delete m_name;
	// delete m_typ;
	// delete m_tail;
}

FieldVar::FieldVar(int pos, Var* var, symbol::Symbol* field)
	: Var(pos), m_var(var), m_field(field)
{}

FieldVar::~FieldVar()
{
	// delete m_var;
	// delete m_field;
}

VarDec::VarDec(int pos, symbol::Symbol* name, NameTy* typ, Exp* init)
	: Dec(pos), m_name(name), m_escape(true), m_typ(typ), m_init(init)
{}

VarDec::~VarDec()
{
	// delete m_name;
	// delete m_typ;
	// delete m_init;
}

ForExp::ForExp(int pos, VarDec* var, Exp* hi, Exp* body)
	: Exp(pos), m_var(var), m_hi(hi), m_body(body)
{}

ForExp::~ForExp()
{
	// delete m_var;
	// delete m_hi;
	// delete m_body;
}

NameTy::NameTy(int pos, symbol::Symbol* name)
	: Ty(pos), m_name(name)
{}

NameTy::~NameTy()
{
	// delete m_name;
}

FunctionDec::FunctionDec(int pos, symbol::Symbol* name, FieldList* params, NameTy* result, Exp* body, FunctionDec* next)
	: Dec(pos), m_inline(false), m_name(name), m_params(params), m_result(result), m_body(body), m_next(next)
{}

FunctionDec::~FunctionDec()
{
	// delete m_name;
	// delete m_params;
	// delete m_result;
	// delete m_body;
	// delete m_next;
}

IfExp::IfExp(int pos, Exp* test, Exp* thenclause, Exp* elseclause)
	: Exp(pos), m_test(test), m_thenclause(thenclause), m_elseclause(elseclause)
{}

IfExp::~IfExp()
{
	// delete m_test;
	// delete m_thenclause;
	// delete m_elseclause;
}

IntExp::IntExp(int pos, int value)
	: Exp(pos), m_value(value)
{}


LetExp::LetExp(int pos, DecList* decs, Exp* body)
	: Exp(pos), m_decs(decs), m_body(body)
{}

LetExp::~LetExp()
{
	// delete m_decs;
	// delete m_body;
}

NilExp::NilExp(int pos)
	: Exp(pos)
{}

int OpExp::PLUS = 0 ,
	OpExp::MINUS = 1,
	OpExp::MUL= 2 ,
	OpExp::DIV= 3 ,
	OpExp::EQ = 4,
	OpExp::NE = 5,
	OpExp::LT = 6,
	OpExp::LE = 7,
	OpExp::GT = 8,
	OpExp::GE = 9;

OpExp::OpExp(int pos, Exp* left, int oper, Exp* right)
	: Exp(pos), m_left(left), m_right(right), m_oper(oper)
{}

OpExp::~OpExp()
{
	// delete m_left;
	// delete m_right;
}


RecordExp::RecordExp(int pos, symbol::Symbol* typ, FieldExpList* fields)
	: Exp(pos), m_typ(typ), m_fields(fields)
{}

RecordExp::~RecordExp()
{
	// delete m_typ;
	// delete m_fields;
}

RecordTy::RecordTy(int pos, FieldList* fields)
	: Ty(pos), m_fields(fields)
{}

RecordTy::~RecordTy()
{
	// delete m_fields;
}

SeqExp::SeqExp(int pos, ExpList* list)
	: Exp(pos), m_list(list)
{}

SeqExp::~SeqExp()
{
	// delete m_list;
}

SimpleVar::SimpleVar(int pos, symbol::Symbol* name)
	: Var(pos), m_name(name)
{}

SimpleVar::~SimpleVar()
{
	// delete m_name;
}

StringExp::StringExp(int pos, std::string value)
	: Exp(pos), m_value(std::move(value))
{}

SubscriptVar::SubscriptVar(int pos, Var* var, Exp* index)
	: Var(pos), m_var(var), m_index(index)
{}

SubscriptVar::~SubscriptVar()
{
	// delete m_var;
	// delete m_index;
}

TypeDec::TypeDec(int pos, symbol::Symbol* name, Ty* ty, TypeDec* next)
	: Dec(pos), m_name(name), m_ty(ty), m_next(next)
{}

TypeDec::~TypeDec()
{
	// delete m_name;
	// delete m_ty;
	// delete m_next;
}

VarExp::VarExp(int pos, Var* var)
	: Exp(pos), m_var(var)
{}

VarExp::~VarExp()
{
	// delete m_var;
}

WhileExp::WhileExp(int pos, Exp* test, Exp* body)
	: Exp(pos), m_test(test), m_body(body)
{}

WhileExp::~WhileExp()
{
	// delete m_test;
	// delete m_body;
}

Print::Print(std::ostream& out)
	: m_out(out)
{}

void Print::indent(int d)
{
  for(int i=0; i<d; i++) 
		m_out << " ";
}

void Print::say(const std::string& s)
{
	m_out << s;
}

void Print::say(int i)
{
	m_out << i;
}

void Print::say(bool b)
{
	m_out << b;
}

void Print::sayln(const std::string& s)
{
	say(s);
	m_out << std::endl;
}

void Print::prVar(SimpleVar* v, int d)
{
	say(std::string("SimpleVar(")); say(v->m_name->toString()); say(std::string(")"));
}

void Print::prVar(FieldVar* v, int d)
{
	sayln("FieldVar(");
	prVar(v->m_var, d+1); sayln(",");
	indent(d+1); say(v->m_field->toString()); say(std::string(")"));
}

void Print::prVar(SubscriptVar* v, int d)
{
	sayln("SubscriptVar(");
	prVar(v->m_var, d+1); sayln(",");
	prExp(v->m_index, d+1); say(std::string(")"));
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

void Print::prVar(Var* v, int d)
{
	indent(d);
    if (instanceof<SimpleVar>(v)) prVar((SimpleVar*)v, d);
    else if (instanceof<FieldVar>(v)) prVar((FieldVar*)v, d);
    else if (instanceof<SubscriptVar>(v)) prVar((SubscriptVar*)v, d);
    else throw "Print.prVar";
}

void Print::prExp(OpExp* e, int d)
{
	sayln("OpExp(");
    indent(d+1); 
	if (e->m_oper == OpExp::PLUS) say(std::string("PLUS"));
	if (e->m_oper == OpExp::MINUS) say(std::string("MINUS"));
	if (e->m_oper == OpExp::MUL) say(std::string("MUL"));
	if (e->m_oper == OpExp::DIV) say(std::string("DIV"));
	if (e->m_oper == OpExp::EQ) say(std::string("EQ"));
	if (e->m_oper == OpExp::NE) say(std::string("NE"));
	if (e->m_oper == OpExp::LT) say(std::string("LT"));
	if (e->m_oper == OpExp::LE) say(std::string("LE"));
	if (e->m_oper == OpExp::GT) say(std::string("GT"));
	if (e->m_oper == OpExp::GE) say(std::string("GE"));
    sayln(",");
    prExp(e->m_left, d+1); sayln(",");
    prExp(e->m_right, d+1); say(std::string(")"));
}

void Print::prExp(VarExp* e, int d)
{
	sayln("varExp("); prVar(e->m_var, d+1);
	say(std::string(")"));
}

void Print::prExp(NilExp* e, int d)
{
    say(std::string("NilExp()"));
}

void Print::prExp(IntExp* e, int d)
{
    say(std::string("IntExp(")); say(e->m_value); say(std::string(")"));
}

void Print::prExp(StringExp* e, int d)
{
    say(std::string("StringExp(")); say(e->m_value); say(std::string(")"));
}

void Print::prExp(CallExp* e, int d)
{
	say(std::string("CallExp(")); say(e->m_func->toString()); sayln(",");
	prExplist(e->m_args, d+1); say(std::string(")"));
}

void Print::prExp(RecordExp* e, int d)
{
	say(std::string("RecordExp(")); say(e->m_typ->toString());  sayln(",");
	prFieldExpList(e->m_fields, d+1); say(std::string(")"));
}

void Print::prExp(SeqExp* e, int d)
{
	sayln("SeqExp(");
	prExplist(e->m_list, d+1); say(std::string(")"));
}

void Print::prExp(AssignExp* e, int d)
{
    sayln("AssignExp(");
    prVar(e->m_var, d+1); sayln(",");
    prExp(e->m_exp, d+1); say(std::string(")"));
}

void Print::prExp(IfExp* e, int d)
{
   sayln("IfExp(");
    prExp(e->m_test, d+1); sayln(",");
    prExp(e->m_thenclause, d+1);
    if (e->m_elseclause!=nullptr) { /* else is optional */
      sayln(",");
      prExp(e->m_elseclause, d+1);
    }
    say(std::string(")"));
}

void Print::prExp(WhileExp* e, int d)
{
	sayln("WhileExp(");
	prExp(e->m_test, d+1); sayln(",");
	prExp(e->m_body, d+1); sayln(")");
}

void Print::prExp(ForExp* e, int d)
{
	sayln("ForExp("); 
    indent(d+1); prDec(e->m_var, d+1); sayln(",");
    prExp(e->m_hi, d+1); sayln(",");
    prExp(e->m_body, d+1); say(std::string(")"));
}

void Print::prExp(BreakExp* e, int d)
{
    say(std::string("BreakExp()"));
}

void Print::prExp(LetExp* e, int d)
{
    say(std::string("LetExp(")); sayln("");
    prDecList(e->m_decs, d+1); sayln(",");
    prExp(e->m_body, d+1); say(std::string(")"));
}

void Print::prExp(ArrayExp* e, int d)
{
	say(std::string("ArrayExp(")); say(e->m_typ->toString()); sayln(",");
	prExp(e->m_size, d+1); sayln(",");
	prExp(e->m_init, d+1); say(std::string(")"));
}

void Print::prExp(Exp* e, int d)
{
	indent(d);
	if (e == nullptr) return;
	if (instanceof<OpExp>(e)) prExp((OpExp*)e, d);
	else if (instanceof<VarExp>(e)) prExp((VarExp*)e, d);
	else if (instanceof<NilExp>(e)) prExp((NilExp*)e, d);
	else if (instanceof<IntExp>(e)) prExp((IntExp*)e, d);
	else if (instanceof<StringExp>(e)) prExp((StringExp*)e, d);
	else if (instanceof<CallExp>(e)) prExp((CallExp*)e, d);
	else if (instanceof<RecordExp>(e)) prExp((RecordExp*)e, d);
	else if (instanceof<SeqExp>(e)) prExp((SeqExp*)e, d);
	else if (instanceof<AssignExp>(e)) prExp((AssignExp*)e, d);
	else if (instanceof<IfExp>(e)) prExp((IfExp*)e, d);
	else if (instanceof<WhileExp>(e)) prExp((WhileExp*)e, d);
	else if (instanceof<ForExp>(e)) prExp((ForExp*)e, d);
	else if (instanceof<BreakExp>(e)) prExp((BreakExp*)e, d);
	else if (instanceof<LetExp>(e)) prExp((LetExp*)e, d);
	else if (instanceof<ArrayExp>(e)) prExp((ArrayExp*)e, d);
	else throw "Print.prExp";
}

void Print::prDec(FunctionDec* d, int i)
{
	say(std::string("FunctionDec("));
    if (d!=nullptr) {
      sayln(d->m_name->toString());
      prFieldlist(d->m_params, i+1); sayln(",");
      if (d->m_result!=nullptr) {
		indent(i+1); sayln(d->m_result->m_name->toString());
      }
      prExp(d->m_body, i+1); sayln(",");
      indent(i+1); prDec(d->m_next, i+1);
    }
    say(std::string(")"));
}

void Print::prDec(VarDec* d, int i)
{
	say(std::string("VarDec(")); say(d->m_name->toString()); sayln(",");
    if (d->m_typ!=nullptr) {
      indent(i+1); say(d->m_typ->m_name->toString());  sayln(",");
    }
    prExp(d->m_init, i+1); sayln(",");
    indent(i+1); say(d->m_escape); say(std::string(")")); 
}

void Print::prDec(TypeDec* d, int i)
{
    if (d!=nullptr) {
      say(std::string("TypeDec(")); say(d->m_name->toString()); sayln(",");
      prTy(d->m_ty, i+1); 
      if (d->m_next!=nullptr) {
		say(std::string(",")); prDec(d->m_next, i+1); 
      }
      say(std::string(")"));
    }
}

void Print::prDec(Dec* d, int i)
{
    indent(i);
    if (instanceof<FunctionDec>(d)) prDec((FunctionDec*)d, i);
    else if (instanceof<VarDec>(d)) prDec((VarDec*)d, i);
    else if (instanceof<TypeDec>(d)) prDec((TypeDec*)d, i);
    else throw "Print.prDec";
}

void Print::prTy(NameTy* t, int i)
{
  say(std::string("NameTy(")); say(t->m_name->toString()); say(std::string(")"));
}

void Print::prTy(RecordTy* t, int i)
{
    sayln("RecordTy(");
    prFieldlist(t->m_fields, i+1); say(std::string(")"));
}

void Print::prTy(ArrayTy* t, int i)
{
	 say(std::string("ArrayTy(")); say(t->m_typ->toString()); say(std::string(")"));
}

void Print::prTy(Ty* t, int i)
{
	if (t!=nullptr) {
		indent(i);
		if (instanceof<NameTy>(t)) prTy((NameTy*)t, i);
		else if (instanceof<RecordTy>(t)) prTy((RecordTy*)t, i);
		else if (instanceof<ArrayTy>(t)) prTy((ArrayTy*)t, i);
		else throw "Print.prTy";
	}
}

void Print::prFieldlist(FieldList* f, int d)
{
    indent(d);
    say(std::string("Fieldlist(")); 
    if (f!=nullptr) {
      sayln("");
      indent(d+1); say(f->m_name->toString()); sayln("");
      indent(d+1); say(f->m_typ->toString()); sayln(",");
      indent(d+1); say(f->m_escape); 
      sayln(",");
      prFieldlist(f->m_tail, d+1);
    }
    say(std::string(")"));
}

void Print::prExplist(ExpList* e, int d)
{
    indent(d);
    say(std::string("ExpList(")); 
    if (e!=nullptr) {
      sayln("");
      prExp(e->m_head, d+1); 
      if (e->m_tail != nullptr) {
		sayln(","); prExplist(e->m_tail, d+1);
      }
    }
    say(std::string(")"));
}

void Print::prDecList(DecList* v, int d)
{
    indent(d);
    say(std::string("DecList(")); 
    if (v!=nullptr) {
      sayln("");
      prDec(v->m_head, d+1); sayln(",");
      prDecList(v->m_tail, d+1);
    }
    say(std::string(")"));
}

void Print::prFieldExpList(FieldExpList* f, int d)
{
    indent(d);
    say(std::string("FieldExpList(")); 
    if (f!=nullptr) {
      sayln("");
      say(f->m_name->toString()); sayln(",");
      prExp(f->m_init, d+1); sayln(",");
      prFieldExpList(f->m_tail, d+1);
    }
    say(std::string(")"));
}
