#ifndef FINDESCAPE_HPP
#define FINDESCAPE_HPP 

#include "absyn.hpp"
#include "symbol.hpp"

namespace findescape {

	class Escape {
		public:
			int m_depth;

			Escape(int depth);
			virtual void setEscape() = 0;
			virtual ~Escape();
	};

	class FormalEscape : public Escape {
		public:
			absyn::FieldList* m_fl;

			FormalEscape(int depth, absyn::FieldList* fl);
			void setEscape() override;
	};

	class VarEscape : public Escape {
		public:
			absyn::VarDec* m_vd;

			VarEscape(int depth, absyn::VarDec* vd);
			void setEscape();
	};

	class FindEscape {
		public:
			symbol::Table* m_escEnv;

			FindEscape();
			void traverseVar(int depth, absyn::Var* v);
			void traverseExp(int depth, absyn::Exp* e);
			void traverseDec(int depth, absyn::Dec* d);
			void findEscape(absyn::Exp* e);
	};
};
#endif /* FINDESCAPE_HPP */
