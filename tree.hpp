#ifndef TREE_HPP
#define TREE_HPP 

#include "temp.hpp"
#include <iostream>

namespace tree {
	class ExpList;

	class Stm {
	public:
		virtual ExpList* kids() = 0;
		virtual Stm* build(const ExpList& kids) = 0;
	};

	class StmList {
	public:
		Stm* m_head;
		StmList* m_tail;
		StmList(Stm* head, StmList* tail);
		// TODO free
	};

	class Exp : public Stm {
	public:
		Exp* m_exp;
		Exp(Exp* exp);
		ExpList* kids() override;
		Stm* build(const ExpList& kids) override;
		//TODO free
	};

	class ExpList {
	public:
		Exp* m_head;
		ExpList* m_tail;

		ExpList(Exp* head, ExpList* tail);
		//TODO free
	};

	class TEMP : public Exp {
	public:
		temp::Temp* m_temp;
		TEMP(temp::Temp* temp);
		ExpList* kids() override;
		Exp* build(const ExpList& kids) override;
		//TODO free
	};

	enum Binop {  
		PLUS, MINUS, MUL, DIV, AND, OR, XOR
	};

	enum Relop {
		EQ, NE, LT, GT, LE, GE
	};

	class BINOP : public Exp {
	public:
		Binop m_binop;
		Exp* m_left, *m_right;

		BINOP(Binop binop, Exp* left, Exp* right);
		BINOP(int binop, Exp* left, Exp* right);
		ExpList* kids() override;
		Exp* build(const ExpList& kids) override;
		//TODO free
	};

	class NAME : public Exp {
	public:
		temp::Label* m_label;
		NAME(temp::Label* label);
		ExpList* kids() override;
		Exp* build(const ExpList& kids) override;
		//TODO free
	};

	class CJUMP : public Stm {
	public:
		Relop m_relop;
		Exp* m_left, *m_right;
		temp::Label* m_iftrue, *m_iffalse;

		CJUMP(Relop relop, Exp* left, Exp* right, temp::Label* iftrue, temp::Label* iffalse);
		CJUMP(int relop, Exp* left, Exp* right, temp::Label* iftrue, temp::Label* iffalse);
		static Relop notRel(Relop relop);
		ExpList* kids() override;
		Stm* build(const ExpList& kids) override;
		//TODO free
	};

	class JUMP : public Stm {
	public:
		Exp* m_exp;
		temp::LabelList* m_targets;
		JUMP(Exp* exp, temp::LabelList* targets);
		JUMP(temp::Label* target);
		ExpList* kids() override;
		Stm* build(const ExpList& kids) override;

		~JUMP();
		//TODO free
	};

	class CONST : public Exp {
	public:
		int m_value;
		CONST(int value);
		ExpList* kids() override;
		Exp* build(const ExpList& kids) override;
	};

	class ESEQ : public Exp {
	public:
		Stm* m_stm;
		Exp* m_exp;
		ESEQ(Stm* stm, Exp* exp);
		ExpList* kids() override;
		Exp* build(const ExpList& kids) override;
		//TODO free
	};

	class LABEL : public Stm {
	public:
		temp::Label* m_label;
		LABEL(temp::Label* label);
		ExpList* kids() override;
		Stm* build(const ExpList& kids) override;
		//TODO free
	};

	class MEM : public Exp {
	public:
		Exp* m_exp;
		MEM(Exp* exp);
		ExpList* kids() override;
		Exp* build(const ExpList& kids) override;
		//TODO free
	};

	class MOVE : public Stm {
	public:
		Exp* m_dist, *m_source;
		MOVE(Exp* dist, Exp* source);
		ExpList* kids() override;
		Stm* build(const ExpList& kids) override;
		//TODO free
	};

	class SEQ : public Stm {
	public:
		Stm* m_left, *m_right;
		SEQ(Stm* left, Stm* right);
		ExpList* kids() override;
		Stm* build(const ExpList& kids) override;
		//TODO free
	};

	class CALL : public Exp {
	public:
		Exp* m_func;
		ExpList* m_args;
		CALL(Exp* func, ExpList* args);
		ExpList* kids() override;
		Exp* build(const ExpList& kids) override;
		//TODO free
	};

	class Print {
	public:
		std::ostream& m_out;
		temp::TempMap* m_tmap;
		Print(std::ostream& out, temp::TempMap* tmap = new temp::DefaultMap());
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
		void prExp(BINOP* s, int d) const;
		void prExp(MEM* s, int d) const;
		void prExp(TEMP* s, int d) const;
		void prExp(ESEQ* s, int d) const;
		void prExp(NAME* s, int d) const;
		void prExp(CONST* s, int d) const;
		void prExp(CALL* s, int d) const;
		void prExp(Exp* s, int d) const;
		void prStm(Stm* s) const;
		void prExp(Exp* e) const;
	};
}; // end of namespace

#endif /* TREE_HPP */
