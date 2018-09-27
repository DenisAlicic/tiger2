#include "translate.hpp"
#include "util.hpp"
#include <iostream>

using namespace translate;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

Ex::Ex(tree::Exp* exp)
	: m_exp(exp)
{}

tree::Exp* Ex::unEx()
{
	return m_exp;
}

tree::Stm* Ex::unNx()
{
	return new tree::Exp(m_exp);
}

tree::Stm* Ex::unCx(temp::Label* t, temp::Label* f)
{
	return new tree::CJUMP(tree::NE, m_exp, new tree::CONST(0), t, f);
}

// converts to 1 or 0 
tree::Exp* Cx::unEx()
{
	temp::Temp* r = new temp::Temp();
	temp::Label* t = new temp::Label();
	temp::Label* f = new temp::Label();

	return new tree::ESEQ(
			new tree::SEQ(
				new tree::MOVE(new tree::TEMP(r), new tree::CONST(1)),
			new tree::SEQ(
				unCx(t, f),  // still virtual here
			new tree::SEQ(
				new tree::LABEL(f), 
			new tree::SEQ(
				new tree::MOVE(new tree::TEMP(r), new tree::CONST(0)),
				new tree::LABEL(t))))), 
			new tree::TEMP(r));
}

tree::Stm* Cx::unNx()
{
	return new tree::Exp(unEx());
}

Nx::Nx(tree::Stm* stm)
	: m_stm(stm)
{}

tree::Exp* Nx::unEx()
{
	return nullptr;
}

tree::Stm* Nx::unNx()
{
	return m_stm;
}

tree::Stm* Nx::unCx(temp::Label* t, temp::Label* f)
{
	return nullptr;
}

Access::Access(Level* l, frame::Access* acc)
	: m_home(l), m_acc(acc)
{}

AccessList::AccessList(Access* head, AccessList* accl)
	: m_head(head), m_next(accl)
{}

Level::Level(Level* parent, symbol::Symbol* name, util::BoolList* fmls)
	: m_parent(parent)
{
	// pass one argument by default for static link
	util::BoolList* bl = new util::BoolList(true, fmls);
	m_frame = parent->m_frame->newFrame(new temp::Label(name), bl);
	for (frame::AccessList* f = m_frame->m_formals; f != nullptr; f = f->m_next)
		m_formals = new AccessList(new Access(this, f->m_head), m_formals);
}

Level::Level(frame::Frame* frm)
	: m_frame(frm), m_parent(nullptr)
{}

Access* Level::staticLink()
{
	return m_formals->m_head;
}

Access* Level::allocLocal(bool escape)
{
	return new Access(this, m_frame->allocLocal(escape));
}

RelCx::RelCx(int oper, Exp* left, Exp* right)
	: m_left(left), m_right(right)
{
	switch (oper) {
		case tree::EQ:
			m_oper = tree::EQ;
			break;
		case tree::NE:
			m_oper = tree::NE;
			break;
		case tree::LT:
			m_oper = tree::LT;
			break;
		case tree::LE:
			m_oper = tree::LE;
			break;
		case tree::GT:
			m_oper = tree::GT;
			break;
		case tree::GE:
			m_oper = tree::GE;
			break;
	}
}

tree::Stm* RelCx::unCx(temp::Label* t, temp::Label* f)
{
	return new tree::CJUMP(m_oper, m_left->unEx(), m_right->unEx(), t, f);
}

ForExp::ForExp(Level* home, Access* var, Exp* low, Exp* high, Exp* body, temp::Label* out)
	: m_currentL(home), m_var(var), m_low(low), m_high(high), m_body(body), m_out(out)
{}

tree::Exp* ForExp::unEx()
{
	std::cerr << "WhileExp.unCx()" << std::endl;
	return nullptr;
}

tree::Stm* ForExp::unNx()
{
	Access* hbound = m_currentL->allocLocal(true);
	temp::Label* begin = new temp::Label();
	temp::Label* increment = new temp::Label();

	return new tree::SEQ(
		new tree::MOVE(
			m_var->m_acc->exp(new tree::TEMP(m_currentL->m_frame->FP())), 
			m_low->unEx()), // init var (i = low)
	new tree::SEQ(
		new tree::MOVE(
			hbound->m_acc->exp(new tree::TEMP(m_currentL->m_frame->FP())),
			m_high->unEx()), // init hbound
	new tree::SEQ(
		new tree::CJUMP(
			tree::LE,
			m_var->m_acc->exp(new tree::TEMP(m_currentL->m_frame->FP())),
			hbound->m_acc->exp(new tree::TEMP(m_currentL->m_frame->FP())),
			begin,
			m_out), // check if i <= hbound
	new tree::SEQ(
		new tree::LABEL(begin),
	new tree::SEQ(
		m_body->unNx(),
	new tree::SEQ(
		new tree::CJUMP(
			tree::LT,
			m_var->m_acc->exp(new tree::TEMP(m_currentL->m_frame->FP())),
			hbound->m_acc->exp(new tree::TEMP(m_currentL->m_frame->FP())),
			increment,
			m_out), // check if i < hbound
	new tree::SEQ(
		new tree::LABEL(increment),
	new tree::SEQ(
		new tree::MOVE(
			m_var->m_acc->exp(new tree::TEMP(m_currentL->m_frame->FP())),
			new tree::BINOP(
				tree::PLUS,
				m_var->m_acc->exp(new tree::TEMP(m_currentL->m_frame->FP())),
				new tree::CONST(1))), // i++
	new tree::SEQ(
		new tree::JUMP(begin), 
		new tree::LABEL(m_out))))))))));
}

tree::Stm* ForExp::unCx(temp::Label* t, temp::Label* f)
{
	std::cerr << "cannot apply ForExp.unEx()" << std::endl;
	return nullptr;
}

IfExp::IfExp(Exp* test, Exp* thenexp, Exp* elseexp)
	: m_test(test), m_thenexp(thenexp), m_elseexp(elseexp)
{}

// returns then or else branch
tree::Exp* IfExp::unEx()
{
	temp::Temp* resultexp = new temp::Temp();
	temp::Label* join = new temp::Label();
	temp::Label* t = new temp::Label();
	temp::Label* f = new temp::Label();

	return new tree::ESEQ(
				new tree::SEQ(
					m_test->unCx(t, f),
				new tree::SEQ(
					new tree::LABEL(t),
				new tree::SEQ(
					new tree::MOVE(
						new tree::TEMP(resultexp), 
						m_thenexp->unEx()),
				new tree::SEQ(
					new tree::JUMP(join),
				new tree::SEQ(
					new tree::LABEL(f), 
				new tree::SEQ(
					new tree::MOVE(
						new tree::TEMP(resultexp),
						m_elseexp->unEx()),
					new tree::LABEL(join))))))), 
			new tree::TEMP(resultexp));
}

tree::Stm* IfExp::unNx()
{
	temp::Label* join = new temp::Label();
	temp::Label* t = new temp::Label();
	temp::Label* f = new temp::Label();

	if (m_elseexp == nullptr)
		return new tree::SEQ(
					m_test->unCx(t, join), 
				new tree::SEQ(
					new tree::LABEL(t), 
				new tree::SEQ(
					m_thenexp->unNx(),
					new tree::LABEL(join))));

	return new tree::SEQ(
				m_test->unCx(t, f),
			new tree::SEQ(
				new tree::LABEL(t), 
			new tree::SEQ(
				m_thenexp->unNx(), 
			new tree::SEQ(
				new tree::JUMP(join),
			new tree::SEQ(
				new tree::LABEL(f), 
			new tree::SEQ(
				m_elseexp->unNx(), 
				new tree::LABEL(join)))))));
}

tree::Stm* IfExp::unCx(temp::Label* t, temp::Label* f)
{
	return new tree::CJUMP(tree::NE, unEx(), new tree::CONST(0), t, f);
}

WhileExp::WhileExp(Exp* test, Exp* body, temp::Label* out)
	: m_test(test), m_body(body), m_out(out)
{}

tree::Exp* WhileExp::unEx()
{
	std::cerr << "WhileExp.unEx()" << std::endl;
	return nullptr;
}

tree::Stm* WhileExp::unNx()
{
	temp::Label* begin = new temp::Label();
	temp::Label* t = new temp::Label();

	return new tree::SEQ(
				new tree::LABEL(begin), 
			new tree::SEQ(
				m_test->unCx(t, m_out),
			new tree::SEQ(
				new tree::LABEL(t), 
			new tree::SEQ(
				m_body->unNx(), 
			new tree::SEQ(
				new tree::JUMP(begin), 
				new tree::LABEL(m_out))))));
}

tree::Stm* WhileExp::unCx(temp::Label* t, temp::Label* f)
{
	std::cerr << "WhileExp.unCx()" << std::endl;
	return nullptr;
}

int Library::WORDSIZE = 4;

Translate::Translate(frame::Frame* f)
	: m_frame(f)
{}

frag::Frag* Translate::getResult()
{
	return m_frags;
}

void Translate::addFrag(frag::Frag* frag)
{
	frag->m_next = m_frags;
	m_frags = frag;
}

void Translate::procEntryExit(Level* level, Exp* body, bool returnValue)
{
	tree::Stm* b = (returnValue) ? new tree::MOVE(new tree::TEMP(level->m_frame->RV()), body->unEx())
								 : body->unNx();

	b = level->m_frame->procEntryExit1(b);
	addFrag(new frag::ProcFrag(b, level->m_frame));
}

Exp* Translate::transNoExp()
{
	return new Ex(new tree::CONST(0));
}

Exp* Translate::transIntExp(int value)
{
	return new Ex(new tree::CONST(value));
}

Exp* Translate::transStringExp(std::string& s)
{
	temp::Label* lab = new temp::Label();
	addFrag(new frag::DataFrag(lab, m_frame->string(lab, s)));
	return new Ex(new tree::NAME(lab));
}

Exp* Translate::transNilExp()
{
	return new Ex(new tree::CONST(0));
}

Exp* Translate::transOpExp(int oper, Exp* left, Exp* right)
{
	if (oper >= tree::PLUS && oper <= tree::DIV)
		return new Ex(new tree::BINOP(oper, left->unEx(), right->unEx()));

	return new RelCx(oper, left, right);
}

Exp* Translate::transStringRelExp(Level* currentL, int oper, Exp* left, Exp* right)
{
	tree::Exp* comp = currentL->m_frame->externalCall(
										"stringEqual",
										new tree::ExpList(
											left->unEx(), 
										new tree::ExpList(
											right->unEx(),
											nullptr)));

	return new RelCx(oper, new Ex(comp), new Ex(new tree::CONST(1)));
}

Exp* Translate::transAssignExp(Exp* lvalue, Exp* exp)
{
	return new Nx(new tree::MOVE(lvalue->unEx(), exp->unEx()));
}

Exp* Translate::transCallExp(Level* currentL, Level* dest, temp::Label* name, std::vector<Exp*>& args_value)
{
	// setup arguments
	tree::ExpList* args = nullptr;
	for (int i = args_value.size() - 1; i >= 0; i--)
		args = new tree::ExpList(((Exp*)args_value[i])->unEx(), args);

	// setup fp (static link)
	Level* l = currentL;
	tree::Exp* currentFP = new tree::TEMP(l->m_frame->FP());
	while (l != dest->m_parent) {
		currentFP = l->staticLink()->m_acc->exp(currentFP); 
		l = l->m_parent;
	}

	// static link is always first in the list of args
	args = new tree::ExpList(currentFP, args);
	return new Ex(new tree::CALL(new tree::NAME(name), args));
} 

Exp* Translate::transStdCallExp(Level* currentL, temp::Label* name, std::vector<Exp*>& args_value)
{
	tree::ExpList* args = nullptr;
	for (int i = args_value.size() - 1; i >= 0; i--)
		args = new tree::ExpList(((Exp*)args_value[i])->unEx(), args);

	return new Ex(currentL->m_frame->externalCall(name->toString(), args));
}

Exp* Translate::stmcat(Exp* e1, Exp* e2)
{
	if (e1 == nullptr) {
		if (e2 != nullptr)
			return new Nx(e2->unNx());
		return transNoExp();
	} 
	
	if (e2 == nullptr)
		return new Nx(e1->unNx());

	return new Nx(new tree::SEQ(e1->unNx(), e2->unNx()));
}

Exp* Translate::exprcat(Exp* e1, Exp* e2)
{
	if (e1 == nullptr) 
		return new Ex(e2->unEx());

	return new Ex(new tree::ESEQ(e1->unNx(), e2->unEx()));
}

Exp* Translate::transRecordExp(Level* currentL, std::vector<Exp*>& field)
{
	temp::Temp* addr = new temp::Temp();

	tree::Exp* rec_id = currentL->m_frame->externalCall(
											"allocRecord",
											new tree::ExpList(
												new tree::CONST((field.size() == 0 ? 1 : field.size()) * Library::WORDSIZE),
												nullptr));

	tree::Stm* stm = transNoExp()->unNx();

	for (int i = field.size() - 1; i >= 0; i--) {
		tree::Exp* offset = new tree::BINOP(
								tree::PLUS,
								new tree::TEMP(addr), 
								new tree::CONST(i * Library::WORDSIZE));

		tree::Exp* value = (field[i])->unEx();
		// store a  value in the offset
		stm = new tree::SEQ(
					new tree::MOVE(new tree::MEM(offset), value),
					stm);
	}

	// store record id in addr and return addr
	return new Ex(new tree::ESEQ(
					new tree::SEQ(
						new tree::MOVE(new tree::TEMP(addr), rec_id), 
						stm),
					new tree::TEMP(addr)));
}

Exp* Translate::transArrayExp(Level* currentL, Exp* init, Exp* size)
{
	tree::Exp* alloc = currentL->m_frame->externalCall(
											"initArray",
											new tree::ExpList(
												size->unEx(), 
											new tree::ExpList(
												init->unEx(),
												nullptr)));
	return new Ex(alloc);
}

Exp* Translate::transIfExp(Exp* test, Exp* e1, Exp* e2)
{
	return new IfExp(test, e1, e2);
}

Exp* Translate::transWhileExp(Exp* test, Exp* body, temp::Label* out)
{
	return new WhileExp(test, body, out);
}

Exp* Translate::transForExp(Level* currentL, Access* var, Exp* low, Exp* high, Exp* body, temp::Label* out)
{
	return new ForExp(currentL, var, low, high, body, out);
}

Exp* Translate::transBreakExp(temp::Label* l)
{
	return new Nx(new tree::JUMP(l));
}

Exp* Translate::transSimpleVar(Access* acc, Level* currentL)
{
	tree::Exp* currentFP = new tree::TEMP(currentL->m_frame->FP());

	Level* l = currentL;
	while (l != acc->m_home) {
		currentFP = l->staticLink()->m_acc->exp(currentFP);
		l = l->m_parent;
	}

	return new Ex(acc->m_acc->exp(currentFP));
}

Exp* Translate::transSubscriptVar(Exp* var, Exp* index)
{
	tree::Exp* arr_addr = var->unEx();
	tree::Exp* arr_offset = new tree::BINOP(tree::MUL, index->unEx(), new tree::CONST(Library::WORDSIZE));
	return new Ex(new tree::MEM(new tree::BINOP(tree::PLUS, arr_addr, arr_offset)));
}

Exp* Translate::transFieldVar(Exp* var, int fig)
{
	tree::Exp* rec_addr = var->unEx();
	tree::Exp* rec_offset = new tree::CONST(fig * Library::WORDSIZE);
	return new Ex(new tree::MEM(new tree::BINOP(tree::PLUS, rec_addr, rec_offset)));
}
