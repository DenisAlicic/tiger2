#ifndef SYMBOL_HPP
#define SYMBOL_HPP 

#include <string>
#include <unordered_map>
#include <vector>

namespace symbol {
	
	// page 109
	// we use this class so that all the different occurrences of any given string convert to the same symbol object
	class Symbol {
		private:
			std::string m_name;
			static std::unordered_map<std::string, Symbol*> dict;

			Symbol(std::string name);

		public:
			std::string toString() const;
			// returns symbol with given name, if it doesn't exist than creates it
			static Symbol* symbol(const std::string& name);
			static void free();
	};

	// type bindings for types, value bindings for variables and functions
	class Binder {
		friend class Table;
		private:
			void* m_value; // a value of object
			Symbol* m_prevtop;
			Binder* m_tail;

			Binder(void* value, Symbol* prevtop, Binder* tail);
			~Binder();
	};

	// page 109
	// symbol table maps identifiers to their types and locations
	class Table {
		private:
			std::unordered_map<Symbol*, Binder*> m_dict;
			Symbol* m_top;
			Binder* m_marks;

		public:
			Table();
			void* get(Symbol* key) const;
			void put(Symbol* key, void* value);
			void beginScope();
			void endScope();
	};
}; // end of namespace

#endif /* SYMBOL_HPP */
