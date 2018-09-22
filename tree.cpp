#include "tree.hpp"
#include "util.hpp"

using namespace tree;
using namespace temp;

Stm::~Stm()
{}

StmList::StmList(Stm* head, StmList* tail)
	: m_head(head), m_tail(tail)
{}

StmList::~StmList()
{
	// delete m_head;
	// delete m_tail;
}

Exp::Exp(Exp* exp)
	: m_exp(exp)
{}

Exp::~Exp()
{
	// delete m_exp;
}

ExpList* Exp::kids()
{
	return new ExpList(m_exp, nullptr);
}

Stm* Exp::build(const ExpList& kids)
{
	return new Exp(kids.m_head);
}

ExpList::ExpList(Exp* head, ExpList* tail)
	: m_head(head), m_tail(tail)
{}

ExpList::~ExpList()
{
	// delete m_head;
	// delete m_tail;
}

TEMP::TEMP(Temp* temp)
	: Exp(nullptr), m_temp(temp)
{}

TEMP::~TEMP()
{
	// delete m_temp;
}

ExpList* TEMP::kids()
{
	return nullptr;
}

Exp* TEMP::build(const ExpList& kids)
{
	return this;
}


BINOP::BINOP(Binop binop, Exp* left, Exp* right)
	: Exp(nullptr), m_binop(binop), m_left(left), m_right(right)
{
}

BINOP::BINOP(int binop, Exp* left, Exp* right)
	: Exp(nullptr), m_left(left), m_right(right)
{
	if (binop == PLUS)
		m_binop = tree::PLUS;
		// BINOP(PLUS, left, right);
	if (binop == MINUS)
		m_binop = tree::MINUS;
		// BINOP(MINUS, left, right);
	if (binop == MUL)
		m_binop = tree::MUL;
		// BINOP(MUL, left, right);
	if (binop == DIV)
		m_binop = tree::DIV;
		// BINOP(DIV, left, right);
	if (binop == AND)
		m_binop = tree::AND;
		// BINOP(AND, left, right);
	if (binop == OR)
		m_binop = tree::OR;
		// BINOP(OR, left, right);
	if (binop == XOR)
		m_binop = tree::XOR;
		// BINOP(XOR, left, right);
	
	// ako se stavi BIONP onda je m_left i m_right null (ne znam zasto)
}

BINOP::~BINOP()
{
	// delete m_left;
	// delete m_right;
}

ExpList* BINOP::kids()
{
	return new ExpList(m_left, new ExpList(m_right, nullptr));
}

Exp* BINOP::build(const ExpList& kids)
{
	return new BINOP(m_binop, kids.m_head, kids.m_tail->m_head);
}

CJUMP::CJUMP(Relop relop, Exp* left, Exp* right, Label* iftrue, Label* iffalse)
	: m_relop(relop), m_left(left), m_right(right), m_iftrue(iftrue), m_iffalse(iffalse)
{}

CJUMP::CJUMP(int relop, Exp* left, Exp* right, temp::Label* iftrue, temp::Label* iffalse)
	: m_left(left), m_right(right), m_iftrue(iftrue), m_iffalse(iffalse)
{

	if (relop == EQ)
		m_relop = EQ;
		// CJUMP(EQ, left, right, iftrue, iffalse);
	if (relop == NE)
		m_relop = NE;
		// CJUMP(NE, left, right, iftrue, iffalse);
	if (relop == LT)
		m_relop = LT;
		// CJUMP(LT, left, right, iftrue, iffalse);
	if (relop == LE)
		m_relop = LE;
		// CJUMP(LE, left, right, iftrue, iffalse);
	if (relop == GE)
		m_relop = GE;
		// CJUMP(GE, left, right, iftrue, iffalse);
	if (relop == GT)
		m_relop = GT;
		// CJUMP(GT, left, right, iftrue, iffalse);
}

CJUMP::~CJUMP()
{
	// delete m_left;
	// delete m_right;
	// delete m_iftrue;
	// delete m_iffalse;
}

ExpList* CJUMP::kids()
{
	return new ExpList(m_left, new ExpList(m_right, nullptr));
}

Stm* CJUMP::build(const ExpList& kids)
{
	return new CJUMP(m_relop, kids.m_head, kids.m_tail->m_head, m_iftrue, m_iffalse);
}

Relop CJUMP::notRel(Relop relop)
{
	switch (relop) {
		case EQ:
			return NE;
		case NE:
			return EQ;
		case LT:
			return GE;
		case GE:
			return LT;
		case GT:
			return LE;
		case LE:
			return GT;
		default:
			throw "unknown relop";
	}

	return EQ;
}



CONST::CONST(int value)
	: Exp(nullptr), m_value(value)
{}

ExpList* CONST::kids()
{
	return nullptr;
}

Exp* CONST::build(const ExpList& kids)
{
	return this;
}

ESEQ::ESEQ(Stm* stm, Exp* exp)
	: Exp(nullptr), m_stm(stm), m_exp(exp)
{}

ESEQ::~ESEQ()
{}

ExpList* ESEQ::kids()
{
	throw "cannot apply kids() to ESEQ";
}

Exp* ESEQ::build(const ExpList& kids)
{
	throw "cannot apply build() to ESEQ";
}

NAME::NAME(Label* label)
	: Exp(nullptr), m_label(label)
{}

NAME::~NAME()
{
	// delete m_label;
}

ExpList* NAME::kids()
{
	return nullptr;
}

Exp* NAME::build(const ExpList& kids)
{
	return this;
}

JUMP::JUMP(Exp* exp, LabelList* targets)
	: m_exp(exp), m_targets(targets)
{}

JUMP::JUMP(Label* target)
	: m_exp(new NAME(target)), m_targets(new LabelList(target, nullptr))
{}

JUMP::~JUMP()
{
	// delete m_targets;
}

ExpList* JUMP::kids()
{
	return new ExpList(m_exp, nullptr);
}

Stm* JUMP::build(const ExpList& kids)
{
	return new JUMP(kids.m_head, m_targets);
}

LABEL::LABEL(Label* label)
	: m_label(label)
{}

LABEL::~LABEL()
{
	// TODO
}

ExpList* LABEL::kids()
{
	return nullptr;
}

Stm* LABEL::build(const ExpList& kids)
{
	return this;
}

MEM::MEM(Exp* exp)
	: Exp(nullptr), m_exp(exp)
{}

MEM::~MEM()
{
	// TODO
}

ExpList* MEM::kids()
{
	return new ExpList(m_exp, nullptr);
}

Exp* MEM::build(const ExpList& kids)
{
	return new MEM(kids.m_head);
}

MOVE::MOVE(Exp* dist, Exp* source)
	: m_dist(dist), m_source(source)
{}

MOVE::~MOVE()
{
	// TODO
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

ExpList* MOVE::kids()
{
	if (util::instanceof<MEM>(m_dist))
		return new ExpList(((MEM*)m_dist)->m_exp, new ExpList(m_source, nullptr));

	return new ExpList(m_source, nullptr);
}

Stm* MOVE::build(const ExpList& kids)
{
	if (util::instanceof<MEM>(m_dist))
		return new MOVE(new MEM(kids.m_head), kids.m_tail->m_head);

	return new MOVE(m_dist, kids.m_head);
}

SEQ::SEQ(Stm* left, Stm* right)
	: m_left(left), m_right(right)
{}

SEQ::~SEQ()
{
	// TODO
}

ExpList* SEQ::kids()
{
	throw "cannot apply kids() to SEQ";
}

Stm* SEQ::build(const ExpList& kids)
{
	throw "cannot apply build() to SEQ";
}

CALL::CALL(Exp* func, ExpList* args)
	: Exp(nullptr), m_func(func), m_args(args)
{}

CALL::~CALL()
{
	// TODO
}

ExpList* CALL::kids()
{
	return new ExpList(m_func, m_args);
}

Exp* CALL::build(const ExpList& kids)
{
	return new CALL(kids.m_head, kids.m_tail);
}

Print::Print(std::ostream& out, TempMap* tmap)
	: m_out(out), m_tmap(tmap)
{}

Print::~Print()
{
	// TODO
}

void Print::indent(int d) const
{
	for (int i = 0; i < d; i++) {
		m_out << std::string(" ");
	}
}

void Print::say(const std::string& s) const
{
	m_out << s;
}

void Print::sayln(const std::string& s) const
{
	say(s);
	m_out << std::endl;
}

void Print::prStm(SEQ* s, int d) const
{
	indent(d);
	sayln(std::string("SEQ("));
	prStm(s->m_left, d + 1);
	sayln(std::string(","));
	prStm(s->m_right, d + 1);
	say(std::string(")"));
}

void Print::prStm(LABEL* s, int d) const
{
	indent(d);
	say(std::string("LABEL "));
	say(s->m_label->toString());
}

void Print::prStm(JUMP* s, int d) const
{
	indent(d);
	sayln(std::string("JUMP("));
	prExp(s->m_exp, d + 1);
	say(std::string(")"));
}

void Print::prStm(CJUMP* s, int d) const
{
	indent(d);
	say(std::string("CJUMP("));
	switch (s->m_relop) {
	case EQ:
		say(std::string("EQ"));
		break;
	case NE:
		say(std::string("NE"));
		break;
	case LT:
		say(std::string("LT"));
		break;
	case GT:
		say(std::string("GT"));
		break;
	case LE:
		say(std::string("LE"));
		break;
	case GE:
		say(std::string("GE"));
		break;
	default:
		throw "Print.prStm.CJUMP";
	}
	sayln(std::string(","));
	prExp(s->m_left, d + 1);
	sayln(std::string(","));
	prExp(s->m_right, d + 1);
	sayln(std::string(","));
	indent(d + 1);
	say(s->m_iftrue->toString());
	say(std::string(","));
	say(s->m_iffalse->toString());
	say(std::string(")"));
}

void Print::prStm(MOVE* s, int d) const
{
	indent(d);
	sayln(std::string("MOVE("));
	prExp(s->m_dist, d + 1);
	sayln(std::string(","));
	prExp(s->m_source, d + 1);
	say(std::string(")"));
}

void Print::prStm(Exp* s, int d) const
{
	indent(d);
	sayln(std::string("EXP("));
	prExp(s->m_exp, d + 1);
	say(std::string(")"));
}

void Print::prStm(Stm* s, int d) const
{
	if (util::instanceof<SEQ>(s))
		prStm((SEQ*)s, d);
	else if (util::instanceof<LABEL>(s))
		prStm((LABEL*) s, d);
	else if (util::instanceof<JUMP>(s))
		prStm((JUMP*) s, d);
	else if (util::instanceof<CJUMP>(s))
		prStm((CJUMP*) s, d);
	else if (util::instanceof<MOVE>(s))
		prStm((MOVE*) s, d);
	else if (util::instanceof<Exp>(s))
		prStm((Exp*) s, d);
	else
		throw "Print.prStm";
}

void Print::prExp(BINOP* s, int d) const
{
	indent(d);
	say(std::string("BINOP("));
	switch (s->m_binop) {
	case PLUS:
		say(std::string("PLUS"));
		break;
	case MINUS:
		say(std::string("MINUS"));
		break;
	case MUL:
		say(std::string("MUL"));
		break;
	case DIV:
		say(std::string("DIV"));
		break;
	case AND:
		say(std::string("AND"));
		break;
	case OR:
		say(std::string("OR"));
		break;
	case XOR:
		say(std::string("XOR"));
		break;
	default:
		throw "Print.prExp.BINOP";
	}
	sayln(std::string(","));
	prExp(s->m_left, d + 1);
	sayln(std::string(","));
	prExp(s->m_right, d + 1);
	say(std::string(")"));
}

void Print::prExp(MEM* s, int d) const
{
	indent(d);
	sayln(std::string("MEM("));
	prExp(s->m_exp, d + 1);
	say(std::string(")"));
}

void Print::prExp(TEMP* s, int d) const
{
	indent(d);
	say(std::string("TEMP "));
	say(m_tmap->tempMap(s->m_temp));
}

void Print::prExp(ESEQ* s, int d) const
{
	indent(d);
	sayln(std::string("ESEQ("));
	prStm(s->m_stm, d + 1);
	sayln(std::string(","));
	prExp(s->m_exp, d + 1);
	say(std::string(")"));
}

void Print::prExp(NAME* s, int d) const
{
	indent(d);
	say(std::string("NAME "));
	say(s->m_label->toString());
}
void Print::prExp(CONST* s, int d) const
{
	indent(d);
	say(std::string("CONST "));
	say(std::to_string(s->m_value));
}

void Print::prExp(CALL* s, int d) const
{
	indent(d);
	sayln(std::string("CALL("));
	prExp(s->m_func, d + 1);
	for (ExpList* a = s->m_args; a != nullptr; a = a->m_tail) {
		sayln(std::string(","));
		prExp(a->m_head, d + 2);
	}
	say(std::string(")"));
}

void Print::prExp(Exp* s, int d) const
{
	if (util::instanceof<BINOP>(s))
		prExp((BINOP*)s, d);
	else if (util::instanceof<MEM>(s))
		prExp((MEM*)s, d);
	else if (util::instanceof<TEMP>(s))
		prExp((TEMP*)s, d);
	else if (util::instanceof<ESEQ>(s))
		prExp((ESEQ*)s, d);
	else if (util::instanceof<NAME>(s))
		prExp((NAME*)s, d);
	else if (util::instanceof<CONST>(s))
		prExp((CONST*)s, d);
	else if (util::instanceof<CALL>(s))
		prExp((CALL*)s, d);
	else
		throw "Print.prExp";
}

void Print::prStm(Stm* s) const
{
	prStm(s, 0);
	say(std::string("\n"));
}

void Print::prExp(Exp* e) const
{
	prExp(e, 0);
	say(std::string("\n"));
}
