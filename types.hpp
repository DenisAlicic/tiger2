#ifndef TYPES_HPP
#define TYPES_HPP 

#include "symbol.hpp"

namespace types {

	class Type {
		public:
			virtual Type* actual();
			virtual bool coerceTo(Type* t);
			virtual ~Type();
	};

	class ARRAY : public Type {
		public:
			Type* m_element;

			ARRAY(Type* element);
			bool coerceTo(Type* t) override;
	};

	class INT : public Type {
		public:
			INT();

			bool coerceTo(Type* t) override;
	};

	class STRING : public Type {
		public:
			STRING();

			bool coerceTo(Type* t) override;
	};

	class VOID : public Type {
		public:
			VOID();

			bool coerceTo(Type* t) override;
	};

	class RECORD : public Type {
		public:
			symbol::Symbol* m_fieldName;
			Type* m_fieldType;
			RECORD* m_tail;

			RECORD(symbol::Symbol* fieldName = nullptr, Type* fieldType = nullptr, RECORD* tail = nullptr);

			bool coerceTo(Type* t) override;
			void gen(symbol::Symbol* n, Type* t, RECORD* x);
			static bool isNull(RECORD* r);
	};

	class NIL : public Type {
		public:
			NIL();

			bool coerceTo(Type* t) override;

	};

	class NAME : public Type {
		private: 
			Type* m_binding;

		public:
			 symbol::Symbol* m_name;

			 NAME(symbol::Symbol* name);
			 bool isLoop();
			 Type* actual() override;
			 bool coerceTo(Type* t) override;
			 void bind(Type* t);
	};
};

#endif /* TYPES_HPP */
