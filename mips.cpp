#include "mips.hpp"
#include "translate.hpp"

using namespace mips;


InFrame::InFrame(MipsFrame* frame, int offset)
	: m_frame(frame), m_offset(offset)
{}

tree::Exp* InFrame::exp(tree::Exp* framePtr)
{

	return new tree::MEM(new tree::BINOP(tree::PLUS, framePtr, new tree::CONST(m_offset)));
}

tree::Exp* InFrame::expFromStack(tree::Exp* stackPtr)
{
	// it is basically frame pointer plus offset
	return new tree::MEM(new tree::BINOP(tree::PLUS, stackPtr, new tree::CONST(m_offset - m_frame->allocDown - translate::Library::WORDSIZE)));
}


InReg::InReg()
	: m_reg(new temp::Temp())
{}

tree::Exp* InReg::exp(tree::Exp* framePtr)
{

	return new tree::TEMP(m_reg);
}

tree::Exp* InReg::expFromStack(tree::Exp* stackPtr)
{

	return new tree::TEMP(m_reg);
}

CodeGen::CodeGen(frame::Frame* f)
	: m_frame(f)
{}

void CodeGen::emit(assem::Instr* inst)
{
	if (m_last != nullptr) {
		m_last->m_tail = new assem::InstrList(inst, nullptr);
		m_last = m_last->m_tail;
	} else {
		m_ilist = new assem::InstrList(inst, nullptr);
		m_last = m_ilist;
	}
} 

temp::TempList* CodeGen::L(temp::Temp* h, temp::TempList* l)
{
	return new temp::TempList(h, l);
} 

assem::InstrList* CodeGen::codegen(tree::Stm* t)
{
	assem::InstrList* l;
	munchStm(t);
	l = m_ilist;
	m_last = m_ilist = nullptr;
	return l;
} 

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

void CodeGen::munchStm(tree::Stm* s)
{
	if (instanceof<tree::Exp>(s))
		munchStm((tree::Exp*)s);
	if (instanceof<tree::SEQ>(s))
		munchStm((tree::SEQ*)s);
	if (instanceof<tree::MOVE>(s))
		munchStm((tree::MOVE*)s);
	if (instanceof<tree::LABEL>(s))
		munchStm((tree::LABEL*)s);
	if (instanceof<tree::JUMP>(s))
		munchStm((tree::JUMP*)s);
	if (instanceof<tree::CJUMP>(s))
		munchStm((tree::CJUMP*)s);
} 

void CodeGen::munchStm(tree::Exp* e)
{
	munchExp(e);
} 

void CodeGen::munchStm(tree::SEQ* s)
{
	munchStm(s->m_left);
	munchStm(s->m_right);
} 

void CodeGen::munchStm(tree::MOVE* m)
{
	if (instanceof<tree::TEMP>(m->m_dist)) {
		if (instanceof<tree::CONST>(m->m_source)) {
			emit(new assem::OPER("li `d0, " + std::to_string(((tree::CONST*)m->m_source)->m_value), L(((tree::TEMP*)m->m_dist)->m_temp, nullptr), nullptr));
		} else {
			temp::Temp* t1 = munchExp(m->m_source);
			emit(new assem::OPER("move `d0, `s0", L(((tree::TEMP*)m->m_dist)->m_temp, nullptr), L(t1, nullptr)));
		}
		return;
	}

	if (instanceof<tree::MEM>(m->m_dist)) {
		tree::MEM* mem = (tree::MEM*)m->m_dist;
		if (instanceof<tree::BINOP>(mem->m_exp)) {
			tree::BINOP* mexp = (tree::BINOP*)mem->m_exp;

			if (mexp->m_binop == tree::PLUS && instanceof<tree::CONST>(mexp->m_right)) {
				temp::Temp* t1 = munchExp(m->m_source);
				temp::Temp* t2 = munchExp(mexp->m_left);
				emit(new assem::OPER("sw `s0, " + std::to_string(((tree::CONST*)mexp->m_right)->m_value) + "(`s1)", nullptr, L(t1, L(t2, nullptr))));
				return;
			}

			if (mexp->m_binop == tree::PLUS &&  instanceof<tree::CONST>(mexp->m_left)) {
				temp::Temp* t1 = munchExp(m->m_source);
				temp::Temp* t2 = munchExp(mexp->m_right);
				emit(new assem::OPER("sw `s0, " + std::to_string(((tree::CONST*)mexp->m_left)->m_value) + "(`s1)", nullptr, L(t1, L(t2, nullptr))));
				return;
			}
		}
		if (instanceof<tree::CONST>(mem->m_exp)) {
			temp::Temp* t1 = munchExp(m->m_source);
			emit(new assem::OPER("sw `s0, " + std::to_string(((tree::CONST*)mem->m_exp)->m_value), nullptr, L(t1, nullptr)));
			return;
		}

		temp::Temp* t1 = munchExp(m->m_source);
		temp::Temp* t2 = munchExp(mem->m_exp);
		emit(new assem::OPER("sw `s0, (`s1)", nullptr, L(t1, L(t2, nullptr))));
	}
} 

void CodeGen::munchStm(tree::LABEL* l)
{
	emit(new assem::LABEL(l->m_label->m_name + ": ", l->m_label));
} 

void CodeGen::munchStm(tree::JUMP* j)
{
	emit(new assem::OPER("j " + j->m_targets->m_head->toString(), nullptr, nullptr, j->m_targets));
} 

void CodeGen::munchStm(tree::CJUMP* j)
{
	std::string oper;
	switch (j->m_relop) {
	case tree::EQ:
		oper = "beq";
		break;// ==
	case tree::NE:
		oper = "bne";
		break;// !=
	case tree::GT:
		oper = "bgt";
		break;// >
	case tree::GE:
		oper = "bge";
		break;// >=
	case tree::LT:
		oper = "blt";
		break;// <
	case tree::LE:
		oper = "ble";
		break;// <=
	}

	temp::Temp* t1 = munchExp(j->m_left);
	temp::Temp* t2 = munchExp(j->m_right);

	emit(new assem::OPER(oper + " `s0, `s1, `j0", nullptr, L(t1, L(t2, nullptr)), new temp::LabelList(j->m_iftrue, new temp::LabelList(j->m_iffalse, nullptr))));
} 

temp::Temp* CodeGen::munchExp(tree::Exp* m)
{
	if (instanceof<tree::MEM>(m))
		return munchExp((tree::MEM*)m);
	if (instanceof<tree::CONST>(m))
		return munchExp((tree::CONST*)m);
	if (instanceof<tree::TEMP>(m))
		return munchExp((tree::TEMP*)m);
	if (instanceof<tree::NAME>(m))
		return munchExp((tree::NAME*)m);
	if (instanceof<tree::BINOP>(m))
		return munchExp((tree::BINOP*)m);
	if (instanceof<tree::CALL>(m))
		return munchExp((tree::CALL*)m);
	return munchExp(m->m_exp);
} 

temp::Temp* CodeGen::munchExp(tree::MEM* m)
{
	temp::Temp* ret = new temp::Temp();
	if (instanceof<tree::CONST>(m->m_exp)) {
		emit(new assem::OPER("lw `d0, " + std::to_string(((tree::CONST*)m->m_exp)->m_value), L(ret, nullptr), nullptr));
		return ret;
	}

	if (instanceof<tree::BINOP>(m->m_exp) && ((tree::BINOP*)m->m_exp)->m_binop == tree::PLUS) {
		if (instanceof<tree::CONST>(((tree::BINOP*)m->m_exp)->m_right)) {
			temp::Temp* t1 = munchExp(((tree::BINOP*)m->m_exp)->m_left);
			emit(new assem::OPER("lw `d0, " + std::to_string(((tree::CONST*)((tree::BINOP*)m->m_exp)->m_right)->m_value) + "(`s0)", L(ret, nullptr), L(t1, nullptr)));
			return ret;
		}

		if (instanceof<tree::CONST>(((tree::BINOP*)m->m_exp)->m_left)) {
			temp::Temp* t1 = munchExp(((tree::BINOP*)m->m_exp)->m_right);
			emit(new assem::OPER("lw `d0, " + std::to_string(((tree::CONST*)((tree::BINOP*)m->m_exp)->m_left)->m_value) + "(`s0)", L(ret, nullptr),
					L(t1, nullptr)));
			return ret;
		}
	}

	temp::Temp* t1 = munchExp(m->m_exp);
	emit(new assem::OPER("lw `d0, (`s0)", L(ret, nullptr), L(t1, nullptr)));
	return ret;
} 

temp::Temp* CodeGen::munchExp(tree::CONST* e)
{
	temp::Temp* ret = new temp::Temp();
	emit(new assem::OPER("li `d0, " + std::to_string(e->m_value), L(ret, nullptr), nullptr));
	return ret;
} 

temp::Temp* CodeGen::munchExp(tree::TEMP* t)
{
	return t->m_temp;
} 

temp::Temp* CodeGen::munchExp(tree::NAME* n)
{
	temp::Temp* ret = new temp::Temp();
	emit(new assem::OPER("la `d0, " + n->m_label->toString(), L(ret, nullptr), nullptr));
	return ret;
} 

temp::Temp* CodeGen::munchExp(tree::BINOP* b)
{
	temp::Temp* ret = new temp::Temp();
	std::string oper;

	switch (b->m_binop) {
	case tree::PLUS:
		oper = "add";
		break;
	case tree::MINUS:
		oper = "sub";
		break;
	case tree::MUL:
		oper = "mul";
		break;
	case tree::DIV:
		oper = "div";
		break;
	}

	if (instanceof<tree::CONST>(b->m_right)) {
		temp::Temp* t1 = munchExp(b->m_left);
		emit(new assem::OPER(oper + " `d0, `s0, " + std::to_string(((tree::CONST*)b->m_right)->m_value), L(ret, nullptr), L(t1, nullptr)));
		return ret;
	}

	if (instanceof<tree::CONST>(b->m_left)) {
		temp::Temp* t1 = munchExp(b->m_right);
		emit(new assem::OPER("li `d0, " + std::to_string(((tree::CONST*)b->m_left)->m_value), L(ret, nullptr), nullptr));
		emit(new assem::OPER(oper + " `d0, `s0, `s1", L(ret, nullptr), L(ret, L(t1, nullptr))));
		return ret;
	}

	temp::Temp* t1 = munchExp(b->m_left);
	temp::Temp* t2 = munchExp(b->m_right);
	emit(new assem::OPER(oper + " `d0, `s0, `s1", L(ret, nullptr), L(t1, L(t2, nullptr))));
	return ret;
} 

temp::Temp* CodeGen::munchExp(tree::CALL* c)
{
	temp::TempList* list = nullptr;
	int i = 0;
	for (tree::ExpList* a = c->m_args; a != nullptr; a = a->m_tail, i++) {
		temp::Temp* t = nullptr;
		if (instanceof<tree::CONST>(a->m_head))
			emit(new assem::OPER("li $a" +std::to_string(i) + ", " + std::to_string(((tree::CONST*)a->m_head)->m_value), nullptr, nullptr));
		else {
			t = munchExp(a->m_head);
			emit(new assem::OPER("move $a" + std::to_string(i) + ", `s0", nullptr, L(t, nullptr)));
		}
		if (t != nullptr)
			list = L(t, list);
	}

	emit(new assem::OPER("jal " + ((tree::NAME*)c->m_func)->m_label->toString(), ((MipsFrame*)m_frame)->m_callerSaves, list));
	return m_frame->RV();
} 

MipsFrame::MipsFrame()
{
	for (int i = 9; i <= 18; i++)
		m_callerSaves = new temp::TempList(new temp::Temp(i), m_callerSaves);
	for (int i = 19; i <= 26; i++)
		m_calleeSaves = new temp::TempList(new temp::Temp(i), m_calleeSaves);
}

frame::Frame* MipsFrame::newFrame(temp::Label* name, util::BoolList* formals)
{
	// std::cout << "newFrame="<<allocDown << std::endl;
	MipsFrame* ret = new MipsFrame();
	ret->m_name = name;
	temp::TempList* argReg = m_argRegs;
	for (util::BoolList* f = formals; f != nullptr; f = f->m_tail, argReg = argReg->m_tail) {
		frame::Access* a = ret->allocLocal(f->m_head);
		ret->m_formals = new frame::AccessList(a, ret->m_formals);
		if (argReg != nullptr) {
			ret->m_saveArgs.push_back(new tree::MOVE(a->exp(new tree::TEMP(m_fp)), new tree::TEMP(argReg->m_head)));
		}
	}
	return ret;
}

frame::Access* MipsFrame::allocLocal(bool escape)
{
	if (escape) {
		frame::Access* ret = new InFrame(this, allocDown);
		allocDown -= translate::Library::WORDSIZE;
		return ret;
	}
	else
		return new InReg();
}

tree::Stm* MipsFrame::procEntryExit1(tree::Stm* body)
{

	// save escaping args
	for (unsigned i = 0; i < m_saveArgs.size(); ++i)
		body = new tree::SEQ((tree::MOVE*)m_saveArgs[i], body);

	frame::Access* fpAcc = allocLocal(true); // local var for frame pointer register
	frame::Access* raAcc = allocLocal(true); // local var for return address register

	// save callee-save registers
	std::vector<frame::Access*> calleeAcc(m_numOfcalleeSaves);
	temp::TempList* calleeTemp = m_calleeSaves;
	for (int i = 0; i < m_numOfcalleeSaves; ++i, calleeTemp = calleeTemp->m_tail) {
		calleeAcc[i] = allocLocal(true); // local var for each callee save register
		body = new tree::SEQ(new tree::MOVE(calleeAcc[i]->exp(new tree::TEMP(m_fp)), new tree::TEMP(calleeTemp->m_head)), body);
	}

	// save return address register
	body = new tree::SEQ(new tree::MOVE(raAcc->exp(new tree::TEMP(m_fp)), new tree::TEMP(m_ra)), body);

	// store frame pointer using stack pointer
	body = new tree::SEQ(new tree::MOVE(new tree::TEMP(m_fp), new tree::BINOP(tree::PLUS, new tree::TEMP(m_sp), new tree::CONST(-allocDown - translate::Library::WORDSIZE))), body);
	body = new tree::SEQ(new tree::MOVE(fpAcc->expFromStack(new tree::TEMP(m_sp)), new tree::TEMP(m_fp)), body);

	// restore callee saved registers
	calleeTemp = m_calleeSaves;
	for (int i = 0; i < m_numOfcalleeSaves; ++i, calleeTemp = calleeTemp->m_tail)
		body = new tree::SEQ(body, new tree::MOVE(new tree::TEMP(calleeTemp->m_head), calleeAcc[i]->exp(new tree::TEMP(m_fp))));

	body = new tree::SEQ(body, new tree::MOVE(new tree::TEMP(m_ra), raAcc->exp(new tree::TEMP(m_fp))));
	body = new tree::SEQ(body, new tree::MOVE(new tree::TEMP(m_fp), fpAcc->expFromStack(new tree::TEMP(m_sp))));

	return body;
}

assem::InstrList* MipsFrame::procEntryExit2(assem::InstrList* body)
{
	return assem::InstrList::append(body, new assem::InstrList(new assem::OPER("", nullptr, new temp::TempList(m_zero, new temp::TempList(m_sp, new temp::TempList(m_ra, m_calleeSaves)))), nullptr));
}

assem::InstrList* MipsFrame::procEntryExit3(assem::InstrList* body)
{

	//an instruction to adjust the stack pointer (to allocate a new frame)
	body = new assem::InstrList(new assem::OPER("subu $sp, $sp, " + std::to_string(-allocDown), new temp::TempList(m_sp, nullptr), new temp::TempList(m_sp, nullptr)), body);
	
	// a label definition for the function name;
	body = new assem::InstrList(new assem::OPER(m_name->toString() + ":", nullptr, nullptr), body);
	
	// a return instruction ( JUMP to the return address);
	assem::InstrList* epilogue = new assem::InstrList(new assem::OPER("jr $ra", nullptr, new temp::TempList(m_ra, nullptr)), nullptr);

	//an instruction to reset the stack pointer (to deallocate the frame);
	epilogue = new assem::InstrList(new assem::OPER("addu $sp, $sp, " + std::to_string(-allocDown), new temp::TempList(m_sp, nullptr), new temp::TempList(m_sp, nullptr)), epilogue);

	body = assem::InstrList::append(body, epilogue);

	return body;
}

std::string MipsFrame::string(temp::Label* label, const std::string& value)
{
	std::string ret = label->toString() + ": " + "\n";

	if (value == "\n") {
		ret = ret + ".word " + std::to_string(value.length()) + "\n";
		ret = ret + ".asciiz \"" + "\n" + "\"";
		return ret;
	}

	ret = ret + ".word " + std::to_string(value.length()) + "\n";
	ret = ret + ".asciiz \"" + value + "\"";
	return ret;
}


temp::Temp* MipsFrame::FP()
{
	return m_fp;
}

temp::Temp* MipsFrame::SP()
{
	return m_sp;
}

temp::Temp* MipsFrame::RA()
{
	return m_ra;
}

temp::Temp* MipsFrame::RV()
{
	return m_rv;
}

tree::Exp* MipsFrame::externalCall(const std::string& func, tree::ExpList* args)
{
	return new tree::CALL(new tree::NAME(new temp::Label(func)), args);
}

std::string MipsFrame::tempMap(temp::Temp* temp) const 
{
	if (temp->toString() == "t0")
		return "$fp";
	if (temp->toString() == "t1")
		return "$sp";
	if (temp->toString() == "t2")
		return "$ra";
	if (temp->toString() == "t3")
		return "$v0";
	if (temp->toString() == "t4")
		return "$zero";

	for (int i = 5; i <= 8; i++)
		if (temp->toString() == "t" + std::to_string(i)) {
			int r = i - 5;
			return "$a" + std::to_string(r);
		}
	for (int i = 9; i <= 18; i++)
		if (temp->toString() == "t" + std::to_string(i)) {
			int r = i - 9;
			return "$t" + std::to_string(r);
		}
	for (int i = 19; i <= 26; i++)
		if (temp->toString() == "t" + std::to_string(i)) {
			int r = i - 19;
			return "$s" + std::to_string(r);
		}

	return "";
}

assem::InstrList* MipsFrame::codegen(tree::Stm* s)
{
	return (new CodeGen(this))->codegen(s);
}

std::set<temp::Temp*> MipsFrame::registers()
{
	std::set<temp::Temp*> ret;

	for (temp::TempList* tl = m_calleeSaves; tl != nullptr; tl = tl->m_tail)
		ret.insert(tl->m_head);
	for (temp::TempList* tl = m_callerSaves; tl != nullptr; tl = tl->m_tail)
		ret.insert(tl->m_head);

	return ret;
}
