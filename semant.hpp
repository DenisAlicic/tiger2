#ifndef SEMANT_HPP
#define SEMANT_HPP 

#include "translate.hpp"
#include "types.hpp"
#include "temp.hpp"
#include "symbol.hpp"
#include "errormsg.hpp"
#include "absyn.hpp"
#include <set>
#include <stack>

 

//  Translate the AST to a bunch of fragments organized in a list, each corresponding to a function or string. The order they are placed in  the list is not necessarily consistent with the natural order they appear in the source code.  If any error has occured during the tranlsation, the external variable anyErrors will be set TRUE.


namespace semant {

	class Entry {
		public:
			virtual ~Entry(){}
	};

	class ExpTy {
		public:
			translate::Exp* m_exp;
			types::Type* m_ty;

			ExpTy(translate::Exp* exp, types::Type* ty);
	};

	class FuncEntry : public Entry {
		public:
			translate::Level* m_level;
			temp::Label* m_label;
			types::RECORD* m_paramlist;
			types::Type* m_returnTy;

			FuncEntry(translate::Level* level, temp::Label* label, types::RECORD* p, types::Type* rt);
	};

	class StdFuncEntry : public FuncEntry {
		public:
			StdFuncEntry(translate::Level* l, temp::Label* lab, types::RECORD* params, types::Type* rt);
	};

	class VarEntry : public Entry {
		public:
			types::Type* m_Ty;
			translate::Access* m_acc;
			bool m_isFor;

			VarEntry(types::Type* ty, translate::Access* acc, bool isf = false);
	};
	
	// environment - setup types and standard functions
	class Env {
		public:
			symbol::Table* m_vEnv = nullptr; // for stdfunctions and vars
			symbol::Table* m_tEnv = nullptr;  // for types
			tiger::errormsg::ErrorMsg* m_errorMsg = nullptr;
			translate::Level* m_root = nullptr;
			std::set<symbol::Symbol*> m_stdFuncSet;  // names of standard functions
			
			Env(tiger::errormsg::ErrorMsg* err, translate::Level* l);
			void initTEnv();
			void initVEnv();
	};

class Semant {
	public:
		Env* m_env;
		translate::Translate* m_trans;
		translate::Level* m_level = nullptr;
		std::stack<temp::Label*> m_loopStack;
		bool m_TDecFlag = false, m_FDecFlag = false, m_TypeDecFlag = false, m_FuncDecFlag = false;

		Semant(translate::Translate* t, tiger::errormsg::ErrorMsg* err);


		frag::Frag* transProg(absyn::Exp* e);

		void transDec0(absyn::Dec* e);
		translate::Exp* transDec(absyn::Dec* e);
		void transDec0(absyn::VarDec* e);
		translate::Exp* transDec(absyn::VarDec* e);
		void transDec0(absyn::TypeDec* e);
		translate::Exp* transDec(absyn::TypeDec* e);
		void transDec0(absyn::FunctionDec* e);
		translate::Exp* transDec(absyn::FunctionDec* e);

		ExpTy* transVar(absyn::Var* e);
		ExpTy* transExp(absyn::Exp* e);
		types::Type* transTy(absyn::Ty* e);
		ExpTy* transExp(absyn::IntExp* e);
		ExpTy* transExp(absyn::StringExp* e);
		ExpTy* transExp(absyn::NilExp* e);
		ExpTy* transExp(absyn::VarExp* e);
		ExpTy* transExp(absyn::OpExp* e);
		ExpTy* transExp(absyn::AssignExp* e);
		ExpTy* transExp(absyn::CallExp* e);
		ExpTy* transExp(absyn::RecordExp* e);
		ExpTy* transExp(absyn::ArrayExp* e);
		ExpTy* transExp(absyn::IfExp* e);
		ExpTy* transExp(absyn::WhileExp* e);
		ExpTy* transExp(absyn::ForExp* e);
		ExpTy* transExp(absyn::BreakExp* e);
		ExpTy* transExp(absyn::LetExp* e);
		ExpTy* transDecList(absyn::DecList* e);
		ExpTy* transExp(absyn::SeqExp* e);
		ExpTy* transVar(absyn::SimpleVar* e);
		ExpTy* transVar(absyn::SubscriptVar* e);
		ExpTy* transVar(absyn::FieldVar* e);
		types::Type* transTy(absyn::NameTy* e);
		types::ARRAY* transTy(absyn::ArrayTy* e);
		types::RECORD* transTy(absyn::RecordTy* e);
};

};

#endif /* SEMANT_HPP */
