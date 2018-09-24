#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP 

#include "tree.hpp"
#include "temp.hpp"
#include "frame.hpp"
#include "symbol.hpp"
#include "util.hpp"
#include "frag.hpp"
#include <unordered_map>
#include <vector>

namespace translate {
	class Exp {
		public:
			virtual tree::Exp* unEx() = 0;
			virtual tree::Stm* unNx() = 0;
			virtual tree::Stm* unCx(temp::Label* t, temp::Label* f) = 0;
	};

	// expression, represented as a Tree.Exp
	class Ex : public Exp {
		public:
			tree::Exp* m_exp;

			Ex(tree::Exp* exp);
			tree::Exp* unEx() override;
			tree::Stm* unNx() override;
			tree::Stm* unCx(temp::Label* t, temp::Label* f) override;
	};
	
	// conditional
	class Cx : public Exp {
		public:
			tree::Exp* unEx() override;
			tree::Stm* unNx() override;
	};

	class RelCx : public Cx {
		public:
			int m_oper;
			Exp* m_left;
			Exp* m_right;

			RelCx(int oper = 0, Exp* left = nullptr, Exp* right = nullptr);
			tree::Stm* unCx(temp::Label* t, temp::Label* f) override;
	};


	// no result, represented as a Tree statement
	class Nx : public Exp {
		public:
			tree::Stm* m_stm;

			Nx(tree::Stm* stm);
			tree::Exp* unEx() override;
			tree::Stm* unNx() override;
			tree::Stm* unCx(temp::Label* t, temp::Label* f) override;
	};
	
	// A Level is basically a Frame that knows the Frame of its parent
	// Wrapper around frame::Frame
	class Level;

	class Access {
		public:
			Level* m_home;
			frame::Access* m_acc;

			Access(Level* l, frame::Access* acc);
	};

	class AccessList {
		public:
			Access* m_head;
			AccessList* m_next;

			AccessList(Access* head, AccessList* accl);
	};

	class Level {
		public:
			frame::Frame* m_frame; // Stack frame that we enhance with static link support. 
			Level* m_parent; //	Level of the enclosing function
			AccessList* m_formals = nullptr; // Accesses to the formal arguments. 

			Level(Level* parent, symbol::Symbol* name, util::BoolList* fmls);
			Level(frame::Frame* frm);

			Access* staticLink();
			// Allocate a new local variable.
			Access* allocLocal(bool escape);
	};

	// increment is always by 1
	class ForExp : public Exp {
		public:
			Level* m_currentL;
			Access* m_var;
			Exp* m_low, *m_high, *m_body;
			temp::Label* m_out;

			ForExp(Level* home, Access* var, Exp* low, Exp* high, Exp* body, temp::Label* out);
			tree::Exp* unEx() override;
			tree::Stm* unNx() override;
			tree::Stm* unCx(temp::Label* t, temp::Label* f) override;
	};

	class IfExp : public Exp {
		public:
			Exp* m_test;
			Exp* m_thenexp;
			Exp* m_elseexp;

			IfExp(Exp* test, Exp* thenexp, Exp* elseexp);
			tree::Exp* unEx() override;
			tree::Stm* unNx() override;
			tree::Stm* unCx(temp::Label* t, temp::Label* f) override;
	};

	class WhileExp : public Exp {
		public:
			Exp* m_test;
			Exp* m_body;
			temp::Label* m_out;

			WhileExp(Exp* test = nullptr, Exp* body = nullptr, temp::Label* out = nullptr);
			tree::Exp* unEx() override;
			tree::Stm* unNx() override;
			tree::Stm* unCx(temp::Label* t, temp::Label* f) override;
	};

	class Library {
		public:
			static int WORDSIZE;
	};

	class Translate {
		public:
			frag::Frag* m_frags = nullptr;
			frame::Frame* m_frame = nullptr;

			Translate(frame::Frame* f);

			frag::Frag* getResult();

			void addFrag(frag::Frag* frag);
			void procEntryExit(Level* level, Exp* body, bool returnValue);


			Exp* transNoExp();
			Exp* transIntExp(int value);
			Exp* transStringExp(std::string& s);
			Exp* transNilExp();
			Exp* transOpExp(int oper, Exp* left, Exp* right);
			Exp* transStringRelExp(Level* currentL, int oper, Exp* left, Exp* right);
			Exp* transAssignExp(Exp* lvalue, Exp* exp);
			Exp* transCallExp(Level* currentL, Level* dest, temp::Label* name, std::vector<Exp*>& args_value); 
			Exp* transStdCallExp(Level* currentL, temp::Label* name, std::vector<Exp*>& args_value);
			Exp* stmcat(Exp* e1, Exp* e2);
			Exp* exprcat(Exp* e1, Exp* e2);
			Exp* transRecordExp(Level* currentL, std::vector<Exp*>& field);
			Exp* transArrayExp(Level* currentL, Exp* init, Exp* size);
			Exp* transIfExp(Exp* test, Exp* e1, Exp* e2);
			Exp* transWhileExp(Exp* test, Exp* body, temp::Label* out);
			Exp* transForExp(Level* currentL, Access* var, Exp* low, Exp* high, Exp* body, temp::Label* out);
			Exp* transBreakExp(temp::Label* l);
			Exp* transSimpleVar(Access* acc, Level* currentL);
			Exp* transSubscriptVar(Exp* var, Exp* index);
			Exp* transFieldVar(Exp* var, int fig);
	};

}; // end of namespace

#endif /* TRANSLATE_HPP */
