#ifndef MIPS_HPP
#define MIPS_HPP 

#include "frame.hpp"
#include "tree.hpp"
#include "temp.hpp"
#include "util.hpp"
#include <vector>

namespace mips {

	class MipsFrame;

	class InFrame : public frame::Access {
		public:
			MipsFrame* m_frame;
			int m_offset;

			InFrame(MipsFrame* frame, int offset);
			tree::Exp* exp(tree::Exp* framePtr) override;
			tree::Exp* expFromStack(tree::Exp* stackPtr) override;
	};

	class InReg : public frame::Access {
		public:
			temp::Temp* m_reg;

			InReg();
			tree::Exp* exp(tree::Exp* framePtr) override;
			tree::Exp* expFromStack(tree::Exp* stackPtr) override;
	};

	class CodeGen {
		public:
			frame::Frame* m_frame;
			assem::InstrList* m_last = nullptr, *m_ilist = nullptr;

			CodeGen(frame::Frame* f);

			void emit(assem::Instr* inst); 
			temp::TempList* L(temp::Temp* h, temp::TempList* l); 
			assem::InstrList* codegen(tree::Stm* t); 
			void munchStm(tree::Stm* s); 
			void munchStm(tree::Exp* e); 
			void munchStm(tree::SEQ* s); 
			void munchStm(tree::MOVE* m); 
			void munchStm(tree::LABEL* l); 
			void munchStm(tree::JUMP* j); 
			void munchStm(tree::CJUMP* j); 
			temp::Temp* munchExp(tree::Exp* m); 
			temp::Temp* munchExp(tree::MEM* m); 
			temp::Temp* munchExp(tree::CONST* e); 
			temp::Temp* munchExp(tree::TEMP* t); 
			temp::Temp* munchExp(tree::NAME* n); 
			temp::Temp* munchExp(tree::BINOP* b); 
			temp::Temp* munchExp(tree::CALL* c); 
	};

	class MipsFrame : public frame::Frame {
		public:
			int allocDown = 0;
			std::vector<tree::Stm*> m_saveArgs;
			temp::Temp* m_fp = new temp::Temp(0);
			temp::Temp* m_sp = new temp::Temp(1);
			temp::Temp* m_ra = new temp::Temp(2);
			temp::Temp* m_rv = new temp::Temp(3);
			temp::Temp* m_zero = new temp::Temp(4);
			temp::TempList* m_argRegs = new temp::TempList(new temp::Temp(5), new temp::TempList(new temp::Temp(6), new temp::TempList(new temp::Temp(7), new temp::TempList(new temp::Temp(8), nullptr))));
			temp::TempList* m_calleeSaves = nullptr;
			temp::TempList* m_callerSaves = nullptr;
			int m_numOfcalleeSaves = 8;

			MipsFrame();
			frame::Frame* newFrame(temp::Label* name, util::BoolList* formals) override;
			frame::Access* allocLocal(bool escape) override;
			tree::Stm* procEntryExit1(tree::Stm* body) override;
			assem::InstrList* procEntryExit2(assem::InstrList* body) override;
			assem::InstrList* procEntryExit3(assem::InstrList* body) override;
			std::string string(temp::Label* label, const std::string& value) override;


			temp::Temp* FP() override;
			temp::Temp* SP() override;
			temp::Temp* RA() override;
			temp::Temp* RV() override;

			tree::Exp* externalCall(const std::string& func, tree::ExpList* args) override;
			std::string tempMap(temp::Temp* temp) const override;
			assem::InstrList* codegen(tree::Stm* s) override;
			std::set<temp::Temp*> registers() override;
	};

};

#endif /* MIPS_HPP */
