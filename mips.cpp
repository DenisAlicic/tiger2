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

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
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
	for (util::BoolList* f = formals; f != nullptr; f = f->m_tail, argReg = argReg->tail()) {
		frame::Access* a = ret->allocLocal(f->m_head);
		ret->m_formals = new frame::AccessList(a, ret->m_formals);
		if (argReg != nullptr) {
			ret->m_saveArgs.push_back(new tree::MOVE(a->exp(new tree::TEMP(m_fp)), new tree::TEMP(argReg->head())));
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
	for (int i = 0; i < m_numOfcalleeSaves; ++i, calleeTemp = calleeTemp->tail()) {
		calleeAcc[i] = allocLocal(true); // local var for each callee save register
		body = new tree::SEQ(new tree::MOVE(calleeAcc[i]->exp(new tree::TEMP(m_fp)), new tree::TEMP(calleeTemp->head())), body);
	}

	// save return address register
	body = new tree::SEQ(new tree::MOVE(raAcc->exp(new tree::TEMP(m_fp)), new tree::TEMP(m_ra)), body);

	// store frame pointer using stack pointer
	body = new tree::SEQ(new tree::MOVE(new tree::TEMP(m_fp), new tree::BINOP(tree::PLUS, new tree::TEMP(m_sp), new tree::CONST(-allocDown - translate::Library::WORDSIZE))), body);
	body = new tree::SEQ(new tree::MOVE(fpAcc->expFromStack(new tree::TEMP(m_sp)), new tree::TEMP(m_fp)), body);

	// restore callee saved registers
	calleeTemp = m_calleeSaves;
	for (int i = 0; i < m_numOfcalleeSaves; ++i, calleeTemp = calleeTemp->tail())
		body = new tree::SEQ(body, new tree::MOVE(new tree::TEMP(calleeTemp->head()), calleeAcc[i]->exp(new tree::TEMP(m_fp))));

	body = new tree::SEQ(body, new tree::MOVE(new tree::TEMP(m_ra), raAcc->exp(new tree::TEMP(m_fp))));
	body = new tree::SEQ(body, new tree::MOVE(new tree::TEMP(m_fp), fpAcc->expFromStack(new tree::TEMP(m_sp))));

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

