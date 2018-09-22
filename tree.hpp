#ifndef TREE_HPP
#define TREE_HPP 

#include "temp.hpp"
#include <iostream>

namespace tree {
	enum Binop {  
		PLUS, MINUS, MUL, DIV, AND, OR, XOR
	};

	enum Relop {
		EQ, NE, LT, GT, LE, GE
	};

	class ExpList;

	class Stm {
		public:
			virtual ExpList* kids() = 0;
			virtual Stm* build(const ExpList& kids) = 0;
			virtual ~Stm();
	};

	class StmList {
		public:
			Stm* m_head;
			StmList* m_tail;

			StmList(Stm* head, StmList* tail);
			~StmList();
	};

	class Exp : public Stm {
		public:
			Exp* m_exp;

			Exp(Exp* exp);
			~Exp();
			ExpList* kids() override;
			Stm* build(const ExpList& kids) override;
	};

	class ExpList {
		public:
			Exp* m_head;
			ExpList* m_tail;

			ExpList(Exp* head, ExpList* tail);
			~ExpList();
	};

	class CONST : public Exp {
		public:
			int m_value;

			CONST(int value);
			ExpList* kids() override;
			Exp* build(const ExpList& kids) override;
	};

	class TEMP : public Exp {
		public:
			temp::Temp* m_temp;

			TEMP(temp::Temp* temp);
			~TEMP();
			ExpList* kids() override;
			Exp* build(const ExpList& kids) override;
	};

	// example: label for strings
	class NAME : public Exp {
		public:
			temp::Label* m_label;

			NAME(temp::Label* label);
			~NAME();
			ExpList* kids() override;
			Exp* build(const ExpList& kids) override;
	};
	
	// MEM (e) The contents of wordSize bytes of memory starting at address e (where wordSize is defined in the Frame module). Note that when MEM is used as the left child of a MOVE , it means “store,” but anywhere else it means “fetch.”
	class MEM : public Exp {
		public:
			Exp* m_exp;

			MEM(Exp* exp);
			~MEM();
			ExpList* kids() override;
			Exp* build(const ExpList& kids) override;
	};

	class BINOP : public Exp {
		public:
			Binop m_binop;
			Exp* m_left, *m_right;

			BINOP(Binop binop, Exp* left, Exp* right);
			BINOP(int binop, Exp* left, Exp* right);
			~BINOP();
			ExpList* kids() override;
			Exp* build(const ExpList& kids) override;
	};
	
	// ESEQ (s, e) The statement s is evaluated for side effects, then e is evaluated for a result.
	class ESEQ : public Exp {
		public:
			Stm* m_stm;
			Exp* m_exp;

			ESEQ(Stm* stm, Exp* exp);
			~ESEQ();
			ExpList* kids() override;
			Exp* build(const ExpList& kids) override;
	};

	class LABEL : public Stm {
		public:
			temp::Label* m_label;

			LABEL(temp::Label* label);
			~LABEL();
			ExpList* kids() override;
			Stm* build(const ExpList& kids) override;
	};

	// Transfer control (jump) to address e. The destination e may be a literal label, as in NAME (lab), or it may be an address calculated by any other kind of expression. The list of labels specifies all the possible locations that the expression e can evaluate to; this is necessary for dataflow analysis later. The common case of jumping to a known label l is written as JUMP ( NAME l, new LabelList (l, null ))
	class JUMP : public Stm {
		public:
			Exp* m_exp;
			temp::LabelList* m_targets;

			JUMP(Exp* exp, temp::LabelList* targets);
			JUMP(temp::Label* target);
			~JUMP();
			ExpList* kids() override;
			Stm* build(const ExpList& kids) override;
	};


	// conditional jump
	class CJUMP : public Stm {
		public:
			Relop m_relop;
			Exp* m_left, *m_right;
			temp::Label* m_iftrue, *m_iffalse;

			CJUMP(Relop relop, Exp* left, Exp* right, temp::Label* iftrue, temp::Label* iffalse);
			CJUMP(int relop, Exp* left, Exp* right, temp::Label* iftrue, temp::Label* iffalse);
			~CJUMP();
			ExpList* kids() override;
			Stm* build(const ExpList& kids) override;
			static Relop notRel(Relop relop);
	};


	class MOVE : public Stm {
		public:
			Exp* m_dist, *m_source;

			MOVE(Exp* dist, Exp* source);
			~MOVE();
			ExpList* kids() override;
			Stm* build(const ExpList& kids) override;
	};

	class SEQ : public Stm {
		public:
			Stm* m_left, *m_right;

			SEQ(Stm* left, Stm* right);
			~SEQ();
			ExpList* kids() override;
			Stm* build(const ExpList& kids) override;
	};

	class CALL : public Exp {
		public:
			Exp* m_func; // call function by label (Exp is NAME)
			ExpList* m_args;

			CALL(Exp* func, ExpList* args);
			~CALL();
			ExpList* kids() override;
			Exp* build(const ExpList& kids) override;
	};

	class Print {
		public:
			std::ostream& m_out;
			temp::TempMap* m_tmap;

			Print(std::ostream& out, temp::TempMap* tmap = new temp::DefaultMap());
			~Print();
			void indent(int d) const;
			void say(const std::string& s) const;
			void sayln(const std::string& s) const;

			void prStm(SEQ* s, int d) const;
			void prStm(LABEL* s, int d) const;
			void prStm(JUMP* s, int d) const;
			void prStm(CJUMP* s, int d) const;
			void prStm(MOVE* s, int d) const;
			void prStm(Exp* s, int d) const;
			void prStm(Stm* s, int d) const;
			void prStm(Stm* s) const;

			void prExp(BINOP* s, int d) const;
			void prExp(MEM* s, int d) const;
			void prExp(TEMP* s, int d) const;
			void prExp(ESEQ* s, int d) const;
			void prExp(NAME* s, int d) const;
			void prExp(CONST* s, int d) const;
			void prExp(CALL* s, int d) const;
			void prExp(Exp* s, int d) const;
			void prExp(Exp* e) const;
	};
}; // end of namespace

#endif /* TREE_HPP */
