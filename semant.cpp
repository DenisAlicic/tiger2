#include "semant.hpp"
#include <vector>
#include <set>

using namespace semant;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

ExpTy::ExpTy(translate::Exp* exp, types::Type* ty)
	: m_exp(exp), m_ty(ty)
{}

FuncEntry::FuncEntry(translate::Level* level, temp::Label* label, types::RECORD* p, types::Type* rt)
	: m_level(level), m_label(label), m_paramlist(p), m_returnTy(rt)
{}

VarEntry::VarEntry(types::Type* ty, translate::Access* acc, bool isf)
	: m_Ty(ty), m_acc(acc), m_isFor(isf)
{}

StdFuncEntry::StdFuncEntry(translate::Level* l, temp::Label* lab, types::RECORD* params, types::Type* rt)
	: FuncEntry(l, lab, params, rt)
{}

Env::Env(tiger::errormsg::ErrorMsg* err, translate::Level* l)
	: m_errorMsg(err), m_root(l)
{
	initTEnv();
	initVEnv();
}

void Env::initTEnv()
{
	m_tEnv = new symbol::Table();
	m_tEnv->put(symbol::Symbol::symbol("int"), new types::INT());
	m_tEnv->put(symbol::Symbol::symbol("string"), new types::STRING());
}

void Env::initVEnv()
{
	m_vEnv = new symbol::Table();
	
	symbol::Symbol* sym = nullptr; 
	types::RECORD* formals = nullptr; 
	types::Type* result = nullptr; 
	translate::Level* level = nullptr;


	sym = symbol::Symbol::symbol("stringEqual");
	// has two arguments left and right strings
	formals = new types::RECORD(symbol::Symbol::symbol("left"), new types::STRING(), new types::RECORD(symbol::Symbol::symbol("right"), new types::STRING(), nullptr));
	result = new types::INT();
	level = new translate::Level(m_root, sym, new util::BoolList(true, new util::BoolList(true, nullptr)));
	m_vEnv->put(sym, new StdFuncEntry(level, new temp::Label(sym), formals, result));
	m_stdFuncSet.insert(sym);
	
	
	sym = symbol::Symbol::symbol("allocRecord");
	// has one argument size of type int
	formals = new types::RECORD(symbol::Symbol::symbol("size"), new types::INT(), nullptr);
	result = new types::INT();
	level = new translate::Level(m_root, sym, new util::BoolList(true, nullptr));
	m_vEnv->put(sym, new StdFuncEntry(level, new temp::Label(sym), formals, result));
	m_stdFuncSet.insert(sym);
	
	sym = symbol::Symbol::symbol("initArray");
	// has two arguments size and initial value for each element
	formals = new types::RECORD(symbol::Symbol::symbol("size"), new types::INT(), new types::RECORD(symbol::Symbol::symbol("init"), new types::INT(), nullptr));
	result = new types::INT();
	level = new translate::Level(m_root, sym, new util::BoolList(true, new util::BoolList(true, nullptr)));
	m_vEnv->put(sym, new StdFuncEntry(level, new temp::Label(sym), formals, result));
	m_stdFuncSet.insert(sym);
	

	sym = symbol::Symbol::symbol("print");
	// has one string argument
	formals = new types::RECORD(symbol::Symbol::symbol("str"), new types::STRING(), nullptr);
	result = new types::VOID();
	level = new translate::Level(m_root, sym, new util::BoolList(true, nullptr));
	m_vEnv->put(sym, new StdFuncEntry(level, new temp::Label(sym), formals, result));
	m_stdFuncSet.insert(sym);
}



Semant::Semant(translate::Translate* t, tiger::errormsg::ErrorMsg* err)
	: m_trans(t)
{
	m_level = new translate::Level(t->m_frame);
	m_level = new translate::Level(m_level, symbol::Symbol::symbol("main"), nullptr);
	m_env = new Env(err, m_level);
}

frag::Frag* Semant::transProg(absyn::Exp* e)
{
	ExpTy* et = transExp(e);
	
	// if an error occured return nullptr
	if (tiger::errormsg::ErrorMsg::anyErrors) {
		return nullptr;
	}


	m_trans->procEntryExit(m_level, et->m_exp, false);
	m_level = m_level->m_parent;

	return m_trans->getResult();
}


ExpTy* Semant::transVar(absyn::Var* e)
{
	if (instanceof<absyn::SimpleVar>(e))
		return transVar((absyn::SimpleVar*)e);
	if (instanceof<absyn::SubscriptVar>(e))
		return transVar((absyn::SubscriptVar*)e);
	if (instanceof<absyn::FieldVar>(e))
		return transVar((absyn::FieldVar*)e);
	return nullptr;
}

ExpTy* Semant::transExp(absyn::Exp* e)
{
	if (instanceof<absyn::IntExp>(e))
	{
		// std::cout << "intexp " << ((absyn::IntExp*) e)->m_value<< std::endl;
		return transExp((absyn::IntExp*) e);
	}
	if (instanceof<absyn::StringExp>(e))
	{
		return transExp((absyn::StringExp*) e);
	}
	if (instanceof<absyn::NilExp>(e))
	{
		return transExp((absyn::NilExp*) e);
	}
	if (instanceof<absyn::VarExp>(e))
	{
		return transExp((absyn::VarExp*) e);
	}
	if (instanceof<absyn::OpExp>(e))
	{
		// std::cout << "opexp" << std::endl;
		return transExp((absyn::OpExp*) e);
	}
	if (instanceof<absyn::AssignExp>(e))
	{
		return transExp((absyn::AssignExp*) e);
	}
	if (instanceof<absyn::CallExp>(e))
	{
		return transExp((absyn::CallExp*) e);
	}
	if (instanceof<absyn::RecordExp>(e))
	{
		return transExp((absyn::RecordExp*) e);
	}
	if (instanceof<absyn::ArrayExp>(e))
	{
		return transExp((absyn::ArrayExp*) e);
	}
	if (instanceof<absyn::IfExp>(e))
	{
		return transExp((absyn::IfExp*) e);
	}
	if (instanceof<absyn::WhileExp>(e))
	{
		return transExp((absyn::WhileExp*) e);
	}
	if (instanceof<absyn::ForExp>(e))
	{
		return transExp((absyn::ForExp*) e);
	}
	if (instanceof<absyn::BreakExp>(e))
	{
		return transExp((absyn::BreakExp*) e);
	}
	if (instanceof<absyn::LetExp>(e))
	{
		return transExp((absyn::LetExp*) e);
	}
	if (instanceof<absyn::SeqExp>(e))
	{
		return transExp((absyn::SeqExp*) e);
	}
	return nullptr;
}

void Semant::transDec0(absyn::Dec* e)
{
	if (instanceof<absyn::VarDec>(e))
		transDec0((absyn::VarDec*) e);
	if (instanceof<absyn::TypeDec>(e))
		transDec0((absyn::TypeDec*) e);
	if (instanceof<absyn::FunctionDec>(e))
		transDec0((absyn::FunctionDec*) e);
}

translate::Exp* Semant::transDec(absyn::Dec* e)
{
	if (instanceof<absyn::VarDec>(e)) {
		// types are already declared, so set flag and prevent another declaration
		if (m_TypeDecFlag == true)
			m_TDecFlag = true;
		// functions are already declared, so set flag and prevent another declaration
		if (m_FuncDecFlag == true)
			m_FDecFlag = true;

		return transDec((absyn::VarDec*) e);
	}

	if (instanceof<absyn::TypeDec>(e)) {
		if (m_TypeDecFlag == false) {
			m_TypeDecFlag = true;
			return transDec((absyn::TypeDec*) e);
		}

		// type declarations should be all together, it this is true then they are separate and it is error
		if (m_TDecFlag == true) {
			m_env->m_errorMsg->error(e->m_pos, "");
			return nullptr;
		}
	}

	if (instanceof<absyn::FunctionDec>(e)) {
		if (m_FuncDecFlag == false) {
			m_FuncDecFlag = true;
			return transDec((absyn::FunctionDec*) e);
		}

		// function declarations should be all together, it this is true then they are separate and it is error
		if (m_FDecFlag == true) {
			m_env->m_errorMsg->error(e->m_pos, "");
			return nullptr;
		}
	}

	return nullptr;
}

void Semant::transDec0(absyn::VarDec* e){}

translate::Exp* Semant::transDec(absyn::VarDec* e)
{
	ExpTy* et = transExp(e->m_init);

	// should be one of these
	// 1) var a:= 0
	// 2) var b:rectype := nil
	// if it is not return nullptr
	if (e->m_typ == nullptr && instanceof<absyn::NilExp>(e->m_init)) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	if (et == nullptr && e->m_init == nullptr) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	// here e->m_init is not null
	if (et == nullptr) {
		et = new ExpTy(m_trans->transNilExp(), new types::NIL());
		e->m_init = new absyn::NilExp(e->m_pos);
	}

	// here et is not null
	if (e->m_init == nullptr) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	// type doesnt match initial value
	if (e->m_typ != nullptr && !(transExp(e->m_init)->m_ty->coerceTo((types::Type*)m_env->m_tEnv->get(e->m_typ->m_name)))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}


	translate::Access* acc = m_level->allocLocal(true);

	if (e->m_typ != nullptr)
		m_env->m_vEnv->put(e->m_name, new VarEntry((types::Type*)m_env->m_tEnv->get(e->m_typ->m_name), acc));
	else 
		m_env->m_vEnv->put(e->m_name, new VarEntry(transExp(e->m_init)->m_ty, acc));

	return m_trans->transAssignExp(m_trans->transSimpleVar(acc, m_level), et->m_exp);
}

void Semant::transDec0(absyn::TypeDec* e)
{
	std::unordered_map<symbol::Symbol*, bool> hs;

	for (absyn::TypeDec* i = e; i != nullptr; i = i->m_next) {
		if (hs.find(i->m_name) != hs.end()) {
			// it is already declared
			m_env->m_errorMsg->error(e->m_pos, "");
			return;
		}

		hs[i->m_name] = true;

		// ex: rectype
		m_env->m_tEnv->put(i->m_name, new types::NAME(i->m_name));
	}
}

translate::Exp* Semant::transDec(absyn::TypeDec* e)
{
	for (absyn::TypeDec* i = e; i != nullptr; i = i->m_next) {
		m_env->m_tEnv->put(i->m_name, new types::NAME(i->m_name));
		types::NAME* field = (types::NAME*)m_env->m_tEnv->get(i->m_name);
		// assign type with name ex: RECORD
		field->bind(transTy(i->m_ty)->actual());

		if (field->isLoop()) {
			m_env->m_errorMsg->error(i->m_pos, "");
			return nullptr;
		}
	}

	for (absyn::TypeDec* i = e; i != nullptr; i = i->m_next)
		m_env->m_tEnv->put(i->m_name, transTy(i->m_ty));

	return m_trans->transNoExp();
}

void Semant::transDec0(absyn::FunctionDec* e)
{
	for (absyn::FunctionDec* i = e; i != nullptr; i = i->m_next) {
		absyn::RecordTy* rt = new absyn::RecordTy(i->m_pos, i->m_params);
		types::RECORD* r = transTy(rt);
		if (r == nullptr)
			return;
		util::BoolList* bl = nullptr;
		for (absyn::FieldList* f = i->m_params; f != nullptr; f = f->m_tail) {
			bl = new util::BoolList(true, bl);
		}

		m_level = new translate::Level(m_level, i->m_name, bl);
		m_env->m_vEnv->put(i->m_name, new FuncEntry(m_level, new temp::Label(i->m_name), r, transTy(i->m_result)));
		m_level = m_level->m_parent;
	}
}

translate::Exp* Semant::transDec(absyn::FunctionDec* e)
{
	std::set<symbol::Symbol*> hs;
	ExpTy* et = nullptr;

	for (absyn::FunctionDec* i = e; i != nullptr; i = i->m_next) {
		// already declared
		if (hs.find(i->m_name) != hs.end()) {
			m_env->m_errorMsg->error(e->m_pos, "");
			return nullptr;
		}

		// if it has the same name as some stdfunction
		if (m_env->m_stdFuncSet.find(i->m_name) != m_env->m_stdFuncSet.end()) {
			m_env->m_errorMsg->error(e->m_pos, "");
			return nullptr;
		}

		absyn::RecordTy* rt = new absyn::RecordTy(i->m_pos, i->m_params);
		types::RECORD* r = transTy(rt);
		if (r == nullptr)
			return nullptr;

		util::BoolList* bl = nullptr;
		for (absyn::FieldList* f = i->m_params; f != nullptr; f = f->m_tail) {
			bl = new util::BoolList(true, bl);
		}

		m_level = new translate::Level(m_level, i->m_name, bl);
		m_env->m_vEnv->beginScope();

		translate::AccessList* al = m_level->m_formals->m_next; // next is because first formal is static link
		for (types::RECORD* j = r; j != nullptr; j = j->tail()) {
			if (j->fieldName() != nullptr) {
				m_env->m_vEnv->put(j->fieldName(), new VarEntry(j->fieldType(), al->m_head));
				al = al->m_next;
			}
		}

		et = transExp(i->m_body);

		if (et == nullptr) {
			m_env->m_vEnv->endScope();
			return nullptr;
		}

		// if return type doesnt match function return type
		if (!(et->m_ty->coerceTo((transTy(i->m_result)->actual())))) {
			m_env->m_errorMsg->error(i->m_pos, "");
			return nullptr;
		}

		if (!(instanceof<types::VOID>(et->m_ty->actual())))
			// has return 
			m_trans->procEntryExit(m_level, et->m_exp, true);
		else
			// void
			m_trans->procEntryExit(m_level, et->m_exp, false);

		m_env->m_vEnv->endScope();

		m_level = m_level->m_parent;
		hs.insert(i->m_name);
	}

	return m_trans->transNoExp();
}

types::Type* Semant::transTy(absyn::Ty* e)
{
	if (instanceof<absyn::ArrayTy>(e))
		return transTy((absyn::ArrayTy*) e);
	if (instanceof<absyn::RecordTy>(e))
		return transTy((absyn::RecordTy*) e);
	if (instanceof<absyn::NameTy>(e))
		return transTy((absyn::NameTy*) e);
	return nullptr;
}

ExpTy* Semant::transExp(absyn::IntExp* e)
{
	return new ExpTy(m_trans->transIntExp(e->m_value), new types::INT());
}

ExpTy* Semant::transExp(absyn::StringExp* e)
{
	return new ExpTy(m_trans->transStringExp(e->m_value), new types::STRING());
}

ExpTy* Semant::transExp(absyn::NilExp* e)
{
	return new ExpTy(m_trans->transNilExp(), new types::NIL());
}

ExpTy* Semant::transExp(absyn::VarExp* e)
{
	return transVar(e->m_var);
}

ExpTy* Semant::transExp(absyn::OpExp* e)
{
	ExpTy* el = transExp(e->m_left); 
	ExpTy* er = transExp(e->m_right); 

	if (el == nullptr || er == nullptr) {
		return nullptr;
	}
	
	
	// ==, !=
	if (e->m_oper == absyn::OpExp::EQ || e->m_oper == absyn::OpExp::NE) {
		// cannot compare two nils
		if (instanceof<types::NIL>(el->m_ty->actual()) && instanceof<types::NIL>(er->m_ty->actual())) {
			m_env->m_errorMsg->error(e->m_pos, " Nil");
			return nullptr;
		}
		
		// cannot compare two voids
		if (instanceof<types::VOID>(el->m_ty->actual()) || instanceof<types::VOID>(er->m_ty->actual())) {
			m_env->m_errorMsg->error(e->m_pos, "");
			return nullptr;
		}
		
		// compare record with nullptr
		if (instanceof<types::NIL>(el->m_ty->actual()) && instanceof<types::RECORD>(er->m_ty->actual()))
			return new ExpTy(m_trans->transOpExp(e->m_oper, el->m_exp, er->m_exp), new types::INT());

		// compare record with nullptr
		if (instanceof<types::RECORD>(el->m_ty->actual()) && instanceof<types::NIL>(er->m_ty->actual()))
			return new ExpTy(m_trans->transOpExp(e->m_oper, el->m_exp, er->m_exp), new types::INT());
		
		// if can be compared
		if (el->m_ty->coerceTo(er->m_ty)) {
			// compare two strings
			if (instanceof<types::STRING>(el->m_ty->actual()) && e->m_oper == absyn::OpExp::EQ) {
				return new ExpTy(m_trans->transStringRelExp(m_level, e->m_oper, el->m_exp, er->m_exp), new types::INT());
			}
			
			// compare two ints
			return new ExpTy(m_trans->transOpExp(e->m_oper, el->m_exp, er->m_exp), new types::INT());
		}
		
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}
	
	// LT , LE , GT , GE
	if (e->m_oper > absyn::OpExp::NE) {
		if (instanceof<types::INT>(el->m_ty->actual()) && instanceof<types::INT>(er->m_ty->actual()))
			return new ExpTy(m_trans->transOpExp(e->m_oper, el->m_exp, er->m_exp), new types::INT());

		if (instanceof<types::STRING>(el->m_ty->actual()) && instanceof<types::STRING>(er->m_ty->actual()))
			return new ExpTy(m_trans->transOpExp(e->m_oper, el->m_exp, er->m_exp), new types::STRING());
		
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}
	
	// PLUS , MINUS , MUL , DIV
	if (e->m_oper < absyn::OpExp::EQ) {
		if (instanceof<types::INT>(el->m_ty->actual()) && instanceof<types::INT>(er->m_ty->actual()))
			return new ExpTy(m_trans->transOpExp(e->m_oper, el->m_exp, er->m_exp), new types::INT());
		
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	// never reached
	return new ExpTy(m_trans->transOpExp(e->m_oper, el->m_exp, er->m_exp), new types::INT());
}

ExpTy* Semant::transExp(absyn::AssignExp* e)
{
	int pos = e->m_pos;
	absyn::Var* var = e->m_var;
	absyn::Exp* exp = e->m_exp;
	ExpTy* er = transExp(exp);
	
	// cannot assign void
	if (instanceof<types::VOID>(er->m_ty->actual())) {
		m_env->m_errorMsg->error(pos, "");
		return nullptr;
	}
	
	// cannot assign var for for
	if (instanceof<absyn::SimpleVar>(var)) {
		absyn::SimpleVar* ev = (absyn::SimpleVar*)var;
		Entry* x = (Entry*)(m_env->m_vEnv->get(ev->m_name));
		
		if (instanceof<VarEntry>(x) && ((VarEntry*)x)->m_isFor) {
			m_env->m_errorMsg->error(pos, "");
			return nullptr;
		}
	}

	ExpTy* vr = transVar(var);
	
	// if value type doesnt match var type
	if (!er->m_ty->coerceTo(vr->m_ty)) {
		m_env->m_errorMsg->error(pos, "" );
		return nullptr;
	}
	
	return new ExpTy(m_trans->transAssignExp(vr->m_exp, er->m_exp), new types::VOID());
}


ExpTy* Semant::transExp(absyn::CallExp* e)
{
	FuncEntry* fe;
	Entry* x = (Entry*)m_env->m_vEnv->get(e->m_func);
	
	if (x == nullptr || !(instanceof<FuncEntry>(x))) {
		m_env->m_errorMsg->error(e->m_pos,  e->m_func->toString());
		return nullptr;
	}

	absyn::ExpList* ex = e->m_args; // arguments passed
	fe = (FuncEntry*)x;
	types::RECORD* rc = fe->m_paramlist; // in declaration
	
	while (ex != nullptr) {

		// record doesnt match arguments
		if (rc == nullptr) {
			m_env->m_errorMsg->error(e->m_pos, "");
			return nullptr;
		}

		// type of arguments and records doesnt match
		if (!transExp(ex->m_head)->m_ty->coerceTo(rc->fieldType())) {
			m_env->m_errorMsg->error(e->m_pos, "");
			return nullptr;
		}

		ex = ex->m_tail;
		rc = rc->tail();
	}

	// number of arguments and records doesnt match
	if (ex == nullptr && !(types::RECORD::isNull(rc))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}
	
	std::vector<translate::Exp*> arrl;
	for (absyn::ExpList* i = e->m_args; i != nullptr; i = i->m_tail)
		arrl.push_back(transExp(i->m_head)->m_exp);
	
	// std function
	if (instanceof<StdFuncEntry>(x)) {
		StdFuncEntry* sf = (StdFuncEntry*)x;
		return new ExpTy(m_trans->transStdCallExp(m_level, sf->m_label, arrl), sf->m_returnTy);
	}
	
	return new ExpTy(m_trans->transCallExp(m_level, fe->m_level, fe->m_label, arrl), fe->m_returnTy);
}

ExpTy* Semant::transExp(absyn::RecordExp* e)
{
	types::Type* t = (types::Type*)m_env->m_tEnv->get(e->m_typ);
	if (t == nullptr || !(instanceof<types::RECORD>(t->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	absyn::FieldExpList* fe = e->m_fields;

	types::RECORD* rc = (types::RECORD*)(t->actual());
	if (fe == nullptr && rc != nullptr) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	while (fe != nullptr) {
		ExpTy* ie = transExp(fe->m_init);
		if (rc == nullptr || ie == nullptr || !ie->m_ty->coerceTo(rc->fieldType()) || fe->m_name != rc->fieldName()) {
			m_env->m_errorMsg->error(e->m_pos, "");
			return nullptr;
		}
		fe = fe->m_tail;
		rc = rc->tail();
	}

	std::vector<translate::Exp*> arrl;
	for (absyn::FieldExpList* i = e->m_fields; i != nullptr; i = i->m_tail)
		arrl.push_back(transExp(i->m_init)->m_exp);

	return new ExpTy(m_trans->transRecordExp(m_level, arrl), t->actual());
}

ExpTy* Semant::transExp(absyn::ArrayExp* e)
{
	types::Type* ty = (types::Type*)m_env->m_tEnv->get(e->m_typ);

	if (ty == nullptr || !(instanceof<types::ARRAY>(ty->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	ExpTy* size = transExp(e->m_size);
	// size must be int
	if (!(instanceof<types::INT>(size->m_ty->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	types::ARRAY* ar = (types::ARRAY*)ty->actual();
	ExpTy* ini = transExp(e->m_init);
	// initial value type must match array type
	if (!ini->m_ty->coerceTo(ar->m_element->actual())) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}
	return new ExpTy(m_trans->transArrayExp(m_level, ini->m_exp, size->m_exp), new types::ARRAY(ar->m_element));
}

ExpTy* Semant::transExp(absyn::IfExp* e)
{
	ExpTy* testET = transExp(e->m_test);
	ExpTy* thenET = transExp(e->m_thenclause);
	ExpTy* elseET = transExp(e->m_elseclause);

	// result of condition must be int
	if (e->m_test == nullptr || testET == nullptr || !(instanceof<types::INT>(testET->m_ty->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	// if there is not else branch then then must be void
	if (e->m_elseclause == nullptr && (!(instanceof<types::VOID>(thenET->m_ty->actual())))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	// else and then type must match
	if (e->m_elseclause != nullptr && !thenET->m_ty->coerceTo(elseET->m_ty)) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	if (elseET == nullptr)
		return new ExpTy(m_trans->transIfExp(testET->m_exp, thenET->m_exp, m_trans->transNoExp()), thenET->m_ty);

	return new ExpTy(m_trans->transIfExp(testET->m_exp, thenET->m_exp, elseET->m_exp), thenET->m_ty);
}

ExpTy* Semant::transExp(absyn::WhileExp* e)
{
	ExpTy* transt = transExp(e->m_test);
	if (transt == nullptr)
		return nullptr;

	// type of test must be int
	if (!(instanceof<types::INT>(transt->m_ty->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	temp::Label* out = new temp::Label();
	// use this stack for break
	m_loopStack.push(out);
	ExpTy* bdy = transExp(e->m_body);
	m_loopStack.pop();

	if (bdy == nullptr)
		return nullptr;

	// body type must be void
	if (!(instanceof<types::VOID>(bdy->m_ty->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	return new ExpTy(m_trans->transWhileExp(transt->m_exp, bdy->m_exp, out), new types::VOID());
}

ExpTy* Semant::transExp(absyn::ForExp* e)
{
	bool flag = false;
	
	// upper bound must be int and initial value of var in for must be int
	if (!( instanceof<types::INT>(transExp(e->m_hi)->m_ty->actual())) || !( instanceof<types::INT>(transExp(e->m_var->m_init)->m_ty->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
	}
	
	m_env->m_vEnv->beginScope();
	temp::Label* label = new temp::Label();
	m_loopStack.push(label);
	
	translate::Access* acc = m_level->allocLocal(true);
	
	m_env->m_vEnv->put(e->m_var->m_name, new VarEntry(new types::INT(), acc, true));
	
	ExpTy* body = transExp(e->m_body);
	ExpTy* high = transExp(e->m_hi);
	ExpTy* low = transExp(e->m_var->m_init);
	
	if (body == nullptr)
		flag = true;

	m_loopStack.pop();
	
	m_env->m_vEnv->endScope();
	

	if (flag)
		return nullptr;

	return new ExpTy(m_trans->transForExp(m_level, acc, low->m_exp, high->m_exp, body->m_exp, label), new types::VOID());
}

ExpTy* Semant::transExp(absyn::BreakExp* e)
{
	// no loop to break
	if (m_loopStack.empty()) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	return new ExpTy(m_trans->transBreakExp(m_loopStack.top()), new types::VOID());
}

ExpTy* Semant::transExp(absyn::LetExp* e)
{
	translate::Exp* ex = nullptr;

	m_env->m_vEnv->beginScope();
	m_env->m_tEnv->beginScope();

	ExpTy* td = transDecList(e->m_decs);
	if (td != nullptr)
		ex = td->m_exp;

	ExpTy* tb = transExp(e->m_body);
	if (tb == nullptr)
		ex = m_trans->stmcat(ex, nullptr);
	else if (instanceof<types::VOID>(tb->m_ty->actual()))
		ex = m_trans->stmcat(ex, tb->m_exp);
	else
		ex = m_trans->exprcat(ex, tb->m_exp);

	m_env->m_tEnv->endScope();
	m_env->m_vEnv->endScope();

	return new ExpTy(ex, tb->m_ty);
}

ExpTy* Semant::transDecList(absyn::DecList* e)
{
	translate::Exp* ex = nullptr;
	for (absyn::DecList* i = e; i != nullptr; i = i->m_tail)
		transDec0(i->m_head);
	for (absyn::DecList* i = e; i != nullptr; i = i->m_tail) {
		ex = m_trans->stmcat(ex, transDec(i->m_head));
	}

	return new ExpTy(ex, new types::VOID());
}

ExpTy* Semant::transExp(absyn::SeqExp* e)
{
	translate::Exp* ex = nullptr;

	for (absyn::ExpList* t = e->m_list; t != nullptr; t = t->m_tail) {
		ExpTy* x = transExp(t->m_head);

		if (t->m_tail == nullptr) {
			if (x != nullptr) {
				if (instanceof<types::VOID>(x->m_ty->actual())) {
					ex = m_trans->stmcat(ex, x->m_exp);
				} else {
					ex = m_trans->exprcat(ex, x->m_exp);
				}
			}

			if (x != nullptr)
				return new ExpTy(ex, x->m_ty);
			else
				return new ExpTy(ex, new types::VOID());
		}

		ex = m_trans->stmcat(ex, x->m_exp);
	}

	return nullptr;
}

ExpTy* Semant::transVar(absyn::SimpleVar* e)
{
	Entry* ex = (Entry*)m_env->m_vEnv->get(e->m_name);
	if (ex == nullptr || !(instanceof<VarEntry>(ex))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}
	VarEntry* evx = (VarEntry*)ex;
	return new ExpTy(m_trans->transSimpleVar(evx->m_acc, m_level), evx->m_Ty);
}

ExpTy* Semant::transVar(absyn::SubscriptVar* e)
{
	// index must be int
	if (!(instanceof<types::INT>(transExp(e->m_index)->m_ty->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	ExpTy* ev = transVar(e->m_var);
	ExpTy* ei = transExp(e->m_index);
	if (ev == nullptr || !(instanceof<types::ARRAY>(ev->m_ty->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}
	types::ARRAY* ae = (types::ARRAY*)(ev->m_ty->actual());
	return new ExpTy(m_trans->transSubscriptVar(ev->m_exp, ei->m_exp), ae->m_element);
}

ExpTy* Semant::transVar(absyn::FieldVar* e)
{
	ExpTy* et = transVar(e->m_var);
	if (!( instanceof<types::RECORD>(et->m_ty->actual()))) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}

	types::RECORD* rc = (types::RECORD*)(et->m_ty->actual());
	int count = 1;
	while (rc != nullptr) {
		if (rc->fieldName() == e->m_field) {
			return new ExpTy(m_trans->transFieldVar(et->m_exp, count), rc->fieldType());
		}
		count++;
		rc = rc->tail();
	}

	m_env->m_errorMsg->error(e->m_pos, "");
	return nullptr;
}

types::Type* Semant::transTy(absyn::NameTy* e)
{
	if (e == nullptr)
		return new types::VOID();

	types::Type* t = (types::Type*)m_env->m_tEnv->get(e->m_name);
	if (t == nullptr) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}
	return t;
}

types::ARRAY* Semant::transTy(absyn::ArrayTy* e)
{
	types::Type* t = (types::Type*)m_env->m_tEnv->get(e->m_typ);
	if (t == nullptr) {
		m_env->m_errorMsg->error(e->m_pos, "");
		return nullptr;
	}
	return new types::ARRAY(t);
}

types::RECORD* Semant::transTy(absyn::RecordTy* e)
{
	types::RECORD* rc = new types::RECORD(), *r = new types::RECORD();
	if (e == nullptr || e->m_fields == nullptr) {
		rc->gen(nullptr, nullptr, nullptr);
		return rc;
	}

	absyn::FieldList* fl = e->m_fields;
	bool first = true;

	while (fl != nullptr) {
		if (m_env->m_tEnv->get(fl->m_typ) == nullptr) {
			m_env->m_errorMsg->error(e->m_pos, "");
			return nullptr;
		}

		rc->gen(fl->m_name, (types::Type*)m_env->m_tEnv->get(fl->m_typ), new types::RECORD());

		if (first) {
			r = rc;
			first = false;
		}

		if (fl->m_tail == nullptr)
			rc->setTailToNull();
		rc = rc->tail();
		fl = fl->m_tail;
	}

	return r;
}

