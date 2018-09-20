// g++ main_tree.cpp tree.cpp temp.cpp

#include "tree.hpp"
#include "temp.hpp"

// this block translates to unCx
// if (a<b && c<d) {
// // true block
// }
// else {
// // false block
// }

tree::Stm* unCx(temp::Label* t, temp::Label* f)
{
	temp::Label* z = new temp::Label();
	tree::Exp* a =  new tree::NAME(new temp::Label("a"));
	tree::Exp* b =  new tree::NAME(new temp::Label("b"));
	tree::Exp* c =  new tree::NAME(new temp::Label("c"));
	tree::Exp* d =  new tree::NAME(new temp::Label("d"));
	return new tree::SEQ(new tree::CJUMP(tree::LT,a,b,z,f), new tree::SEQ(new tree::LABEL(z), new tree::CJUMP(tree::LT,c,d,t,f)));
}

int main()
{
	temp::Label* t = new temp::Label("TRUELABEL");
	temp::Label* f = new temp::Label("FALSELABEL");
	tree::Stm* st = unCx(t, f);
	return 0;
}
