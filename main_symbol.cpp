// g++ main_symbol.cpp symbol.cpp
#include <iostream>
#include "symbol.hpp"

int* makeBinding(int value)
{
	return new int(value);
}

void printTable(symbol::Table& t)
{
	for (auto&& k : t.keys()) {
		std::cout << k->toString() << "=" << *(int*)t.get(k) << std::endl;
	}
}

int main()
{
	// simbols
    symbol::Symbol* a = symbol::Symbol::symbol("a");
    symbol::Symbol* b = symbol::Symbol::symbol("b");
    symbol::Symbol* c = symbol::Symbol::symbol("c");

	// constants
	int* v1 = makeBinding(1);
	int* v2 = makeBinding(2);
	int* v3 = makeBinding(3);
	int* v4 = makeBinding(4);

	symbol::Table t;
	t.beginScope();
	std::cout << "begin scope" << std::endl;
	t.put(a, v1);
	t.put(b, v2);

		t.beginScope();
		std::cout << "begin scope" << std::endl;
		t.put(b, v3);
		t.put(a, v4);
		t.put(c, v1);
		printTable(t);
		std::cout << "end scope" << std::endl;
		t.endScope();

	printTable(t);
	std::cout << "end scope" << std::endl;
	t.endScope();

	printTable(t);

	delete a;
	delete b;
	delete c;
	delete v1;
	delete v2;
	delete v3;
	delete v4;

	return 0;
}
