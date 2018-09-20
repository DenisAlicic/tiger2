#ifndef ABSYN_HPP
#define ABSYN_HPP 

#include "symbol.hpp"

namespace absyn {
	class Absyn {
		public:
			int m_pos;
			Absyn(int pos);
			virtual ~Absyn();
	};

	class Ty : public Absyn {
		public:
			Ty(int pos);
	};

	class Exp : public Absyn {
		public:
			Exp(int pos);
	};

	class Var : public Absyn {
		public:
			Var(int pos);
	};

	class Dec : public Absyn {
		public:
			Dec(int pos);
	};


	class ArrayExp : public Exp {
		public:
			symbol::Symbol* m_typ;
			Exp* m_size, *m_init;

			ArrayExp(int pos, symbol::Symbol* typ, Exp* size, Exp* init);
			~ArrayExp();
	};

	class NilExp : public Exp {
		public:
			NilExp(int pos);
	};

	class ArrayTy : public Ty {
		public:
			symbol::Symbol* m_typ;

			ArrayTy(int pos, symbol::Symbol* typ);
			~ArrayTy();
	};

	class AssignExp : public Exp {
		public:
			Var* m_var;
			Exp* m_exp;

			AssignExp(int pos, Var* var, Exp* exp);
			~AssignExp();
	};

	class BreakExp : public Exp {
		public:
			BreakExp(int pos);
	};

	class ExpList {
		public:
			Exp* m_head;
			ExpList* m_tail;

			ExpList(Exp* head, ExpList* tail);
			~ExpList();
	};

	class CallExp : public Exp {
		public:
			symbol::Symbol* m_func;
			ExpList* m_args;

			CallExp(int pos, symbol::Symbol* func, ExpList* args);
			~CallExp();
	};

	class DecList {
		public:
			Dec* m_head;
			DecList* m_tail;

			DecList(Dec* head, DecList* tail);
			~DecList();
	};

	class FieldExpList : public Absyn {
		public:
			symbol::Symbol* m_name;
			Exp* m_init;
			FieldExpList* m_tail;

			FieldExpList(int pos, symbol::Symbol* name, Exp* init, FieldExpList* tail);
			~FieldExpList();
	};

	class FieldList : public Absyn {
		public:
			symbol::Symbol* m_name;
			symbol::Symbol* m_typ;
			FieldList* m_tail;
			bool m_escape;

			FieldList(int pos, symbol::Symbol* name, symbol::Symbol* typ, FieldList* tail);
			~FieldList();
	};

	class FieldVar : public Var {
		public:
			Var* m_var;
			symbol::Symbol* m_field;

			FieldVar(int pos, Var* var, symbol::Symbol* field);
			~FieldVar();
	};

	class NameTy : public Ty {
		public:
			symbol::Symbol* m_name;

			NameTy(int pos, symbol::Symbol* name);
			~NameTy();
	};

	class VarDec : public Dec {
		public:
			symbol::Symbol* m_name;
			bool m_escape;
			NameTy* m_typ;
			Exp* m_init;

			VarDec(int pos, symbol::Symbol* name, NameTy* typ, Exp* init);
			~VarDec();
	};

	class ForExp : public Exp {
		public:
			VarDec* m_var;
			Exp* m_hi, *m_body;

			ForExp(int pos, VarDec* var, Exp* hi, Exp* body);
			~ForExp();
	};

	class FunctionDec : public Dec {
		public:
			bool m_inline;
			symbol::Symbol* m_name;
			FieldList* m_params;
			NameTy* m_result;
			Exp* m_body;
			FunctionDec* m_next;

			FunctionDec(int pos, symbol::Symbol* name, FieldList* params, NameTy* result, Exp* body, FunctionDec* next);
			~FunctionDec();
	};

	class IfExp : public Exp {
		public:
			Exp* m_test, *m_thenclause, *m_elseclause;

			IfExp(int pos, Exp* test, Exp* thenclause, Exp* elseclause = nullptr);
			~IfExp();
	};

	class IntExp : public Exp {
		public:
			int m_value;

			IntExp(int pos, int value);
	};

	class LetExp : public Exp {
		public:
			DecList* m_decs;
			Exp* m_body;

			LetExp(int pos, DecList* decs, Exp* body);
			~LetExp();
	};

	class OpExp : public Exp {
		public:
			static int PLUS , MINUS , MUL , DIV , EQ , NE , LT , LE , GT , GE;
			Exp* m_left, *m_right;
			int m_oper;

			OpExp(int pos, Exp* left, int oper, Exp* right);
			~OpExp();
	};

	class RecordExp : public Exp {
		public:
			symbol::Symbol* m_typ;
			FieldExpList* m_fields;

			RecordExp(int pos, symbol::Symbol* typ, FieldExpList* fields);
			~RecordExp();
	};

	class RecordTy : public Ty {
		public:
			FieldList* m_fields;

			RecordTy(int pos, FieldList* fields);
			~RecordTy();
	};

	class SeqExp : public Exp {
		public: 
			ExpList* m_list;

			SeqExp(int pos, ExpList* list);
			~SeqExp();
	};

	class SimpleVar : public Var {
		public: 
			symbol::Symbol* m_name;

			SimpleVar(int pos, symbol::Symbol* name);
			~SimpleVar();
	};

	class StringExp : public Exp {
		public:
			std::string m_value;

			StringExp(int pos, std::string value);
	};

	class SubscriptVar : public Var {
		public:
			Var* m_var;
			Exp* m_index;

			SubscriptVar(int pos, Var* var, Exp* index);
			~SubscriptVar();
	};

	class TypeDec : public Dec {
		public:
			symbol::Symbol* m_name;
			Ty* m_ty;
			TypeDec* m_next;

			TypeDec(int pos, symbol::Symbol* name, Ty* ty, TypeDec* next);
			~TypeDec();
	};


	class VarExp : public Exp {
		public:
			Var* m_var;

			VarExp(int pos, Var* var);
			~VarExp();
	};

	class WhileExp : public Exp {
		public:
			Exp* m_test, *m_body;

			WhileExp(int pos, Exp* test, Exp* body);
			~WhileExp();
	};

	class Print {
		public:
			std::ostream& m_out;

			Print(std::ostream& out);
			void indent(int d);
			void say(const std::string& s);
			void say(int i);
			void say(bool b);
			void sayln(const std::string& s);
			void prVar(SimpleVar* v, int d);
			void prVar(FieldVar* v, int d);
			void prVar(SubscriptVar* v, int d);
			void prVar(Var* v, int d);
			void prExp(OpExp* e, int d);
			void prExp(VarExp* e, int d);
			void prExp(NilExp* e, int d);
			void prExp(IntExp* e, int d);
			void prExp(StringExp* e, int d);
			void prExp(CallExp* e, int d);
			void prExp(RecordExp* e, int d);
			void prExp(SeqExp* e, int d);
			void prExp(AssignExp* e, int d);
			void prExp(IfExp* e, int d);
			void prExp(WhileExp* e, int d);
			void prExp(ForExp* e, int d);
			void prExp(BreakExp* e, int d);
			void prExp(LetExp* e, int d);
			void prExp(ArrayExp* e, int d);

			void prExp(Exp* e, int d);
			void prDec(FunctionDec* d, int i);
			void prDec(VarDec* d, int i);
			void prDec(TypeDec* d, int i);
			void prDec(Dec* d, int i);
			void prTy(NameTy* t, int i);
			void prTy(RecordTy* t, int i);
			void prTy(ArrayTy* t, int i);
			void prTy(Ty* t, int i);
			void prFieldlist(FieldList* f, int d);
			void prExplist(ExpList* e, int d);
			void prDecList(DecList* v, int d);
			void prFieldExpList(FieldExpList* f, int d);
	};

}; // end of namespace

#endif /* ABSYN_HPP */
