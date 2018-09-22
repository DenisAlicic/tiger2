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

	// example: array of int
	class ARRAY : public Type {
		public:
			Type* m_element;

			ARRAY(Type* element);
			~ARRAY();

			bool coerceTo(Type* t) override;
	};

	// example: {name:string, age:int}
	class RECORD : public Type {
		private:
			symbol::Symbol* m_fieldName;
			Type* m_fieldType;
			RECORD* m_tail;

		public:
			RECORD(symbol::Symbol* fieldName = nullptr, Type* fieldType = nullptr, RECORD* tail = nullptr);
			~RECORD();

			bool coerceTo(Type* t) override;
			void gen(symbol::Symbol* name, Type* type, RECORD* tail);
			static bool isNull(RECORD* r);
			symbol::Symbol* fieldName() const;
			Type* fieldType() const;
			RECORD* tail() const;
			void setTailToNull();
	};

	class NIL : public Type {
		public:
			NIL();

			bool coerceTo(Type* t) override;
	};

	// example: type myint = int
	class NAME : public Type {
		private: 
			symbol::Symbol* m_name;
			Type* m_binding;

		public:
			NAME(symbol::Symbol* name);
			~NAME();

			Type* actual() override;
			bool coerceTo(Type* t) override;
			bool isLoop();
			void bind(Type* t);
	};
};

#endif /* TYPES_HPP */
