#ifndef SYMBOL_HPP
#define SYMBOL_HPP 

#include <string>
#include <unordered_map>
#include <vector>

namespace symbol {
	class Symbol {
		private:
			std::string m_name;
			Symbol(std::string name);
			static std::unordered_map<std::string, Symbol*> dict;
		public:
			std::string toString();
			static Symbol* symbol(const std::string& n);
	};

	class Binder {
		public:
			void* m_value;
			Symbol* m_prevtop;
			Binder* m_tail;

			Binder(void* value, Symbol* prevtop, Binder* tail);
	};

	class Table {
		private:
			std::unordered_map<Symbol*, Binder*> m_dict;
			Symbol* m_top;
			Binder* m_marks;

		public:
			Table();
			void* get(Symbol* key);
			void put(Symbol* key, void* value);
			void beginScope();
			void endScope();
			std::vector<Symbol*> keys();
	};
}; // end of namespace

#endif /* SYMBOL_HPP */
