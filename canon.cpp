#include "canon.hpp"
#include "tree.hpp"
#include "temp.hpp"
#include <map>
#include <iostream>
#include <cstdlib>

using namespace canon;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

BasicBlocks::BasicBlocks(tree::StmList* stms){
    m_done = new temp::Label();
    mkBlocks(stms);
}

void BasicBlocks::addStm(tree::Stm* s){
	// std::cout <<"addStm(tree::Stm* s)"  << std::endl;
    m_lastStm = m_lastStm->m_tail = new tree::StmList(s,nullptr);
}

void BasicBlocks::doStms(tree::StmList* l){
	// std::cout << "doStms(tree::StmList* l)" << std::endl;
    if(l == nullptr){
        doStms(new tree::StmList(new tree::JUMP(m_done),nullptr));
    }
    else if (instanceof<tree::JUMP>(l->m_head) || instanceof<tree::CJUMP>(l->m_head)){
        addStm(l->m_head);
        mkBlocks(l->m_tail);
    }
    else if (instanceof<tree::LABEL>(l->m_head)){
        doStms(new tree::StmList(new tree::JUMP(((tree::LABEL*)(l->m_head))->m_label),l));
    }
    else{
        addStm(l->m_head);
        doStms(l->m_tail);

    }
}

void BasicBlocks::mkBlocks(tree::StmList* l){
	// std::cout << "mkBlocks(tree::StmList* l)" << std::endl;
    if(l == nullptr){
        return;
    }
    else if(instanceof<tree::LABEL>(l->m_head)){
        m_lastStm = new tree::StmList(l->m_head,nullptr);
        if(m_lastBlock == nullptr){
            m_lastBlock = m_blocks = new StmListList(m_lastStm,nullptr);
        }
        else{
            m_lastBlock = m_lastBlock->m_tail = new StmListList(m_lastStm, nullptr);
        }
        doStms(l->m_tail);
    }
    else{
        mkBlocks(new tree::StmList(new tree::LABEL(new temp::Label()),l));
    }
}

BasicBlocks::~BasicBlocks(){
    //TODO
}



MoveCall::MoveCall(tree::TEMP* d, tree::CALL* s)
    : m_dst(d), m_src(s)
{}

tree::ExpList* MoveCall::kids(){
    return m_src->kids();
}

tree::Stm* MoveCall::build(const tree::ExpList& kids){
    return new tree::MOVE(m_dst, m_src->build(kids));
}

MoveCall::~MoveCall(){
    //TODO
    //
}



ExpCall::ExpCall(tree::CALL* c)
    : m_call(c)
{}
tree::ExpList* ExpCall::kids(){
    return m_call->kids();
}
tree::Stm* ExpCall::build(const tree::ExpList& kids){
    return new tree::Exp(m_call->build(kids));
}
ExpCall::~ExpCall(){
    //TODO
}



StmExpList::StmExpList(tree::Stm* s, tree::ExpList* e)
    : m_stm(s), m_exps(e)
{}
StmExpList::~StmExpList(){
    //TODO
}

Canon::Canon(){
}

StmExpList* Canon::m_nopNull = new StmExpList(new tree::Exp(new tree::CONST(0)), nullptr); 


bool Canon::isNop(tree::Stm* a){
    return instanceof<tree::Exp>(a) && instanceof<tree::CONST>(((tree::Exp*)a)->m_exp);
}

tree::Stm* Canon::seq(tree::Stm* a, tree::Stm* b){
	// std::cout << "seq(tree::Stm* a, tree::Stm* b)" << std::endl;
    if(isNop(a)){
        return b;
    }
    else if(isNop(b)){
        return a;
    }
    else{
        return new tree::SEQ(a, b);
    }
}

bool Canon::commute(tree::Stm* a, tree::Exp* b){
    return isNop(a) || instanceof<tree::NAME>(b) || instanceof<tree::CONST>(b);
}

tree::Stm* Canon::do_stm(tree::SEQ* s){
	// std::cout << "do_stm(tree::SEQ* s)" << std::endl;
	// if (instanceof<tree::MOVE>(s->m_right))
	// {
	// 	std::cout << "move" << std::endl;
	// 	exit(0);
	// }
    return seq(do_stm(s->m_left),do_stm(s->m_right));
}

tree::Stm* Canon::do_stm(tree::MOVE* s){
	// std::cout << "do_stm(tree::MOVE* s)" << std::endl;
    if(instanceof<tree::TEMP>(s->m_dist) && instanceof<tree::CALL>(s->m_source)) {
        return reorder_stm(new MoveCall((tree::TEMP*)(s->m_dist), (tree::CALL*)(s->m_source)));
    }
    else if(instanceof<tree::ESEQ>(s->m_dist)) {
        return do_stm(new tree::SEQ(((tree::ESEQ*)(s->m_dist))->m_stm,
                    new tree::MOVE(((tree::ESEQ*)(s->m_dist))->m_exp,
                        s->m_source)));
    }
    else{
        return reorder_stm(s);
    }
}

tree::Stm* Canon::do_stm(tree::Exp* s){
	// std::cout << "do_stm(tree::Exp* s)" << std::endl;
    if(instanceof<tree::CALL>(s->m_exp)) {
        return reorder_stm(new ExpCall((tree::CALL*)(s->m_exp)));
    }
    else{
        return reorder_stm(s);
    }
}

tree::Stm* Canon::do_stm(tree::Stm* s){
	// std::cout << "do_stm(tree::Stm* s)" << std::endl;
    if(instanceof<tree::SEQ>(s)){
        return do_stm((tree::SEQ*)(s));
    }
    else if(instanceof<tree::MOVE>(s)){
        return do_stm((tree::MOVE*)(s));
    }
    else if(instanceof<tree::Exp>(s)){
        return do_stm((tree::Exp*)(s));
    }
    else{
        return reorder_stm(s);
    }
}

tree::Stm* Canon::reorder_stm(tree::Stm* s){
	// std::cout << "reorder_stm(tree::Stm* s)" << std::endl;
    StmExpList* x = reorder(s->kids());
    return seq(x->m_stm, s->build(*(x->m_exps)));
}

tree::ESEQ* Canon::do_exp(tree::ESEQ* e){
	// std::cout << "do_exp(tree::ESEQ* e)" << std::endl;
    tree::Stm* stms = do_stm(e->m_stm);
    tree::ESEQ* b = do_exp(e->m_exp);
    return new tree::ESEQ(seq(stms, b->m_stm), b->m_exp);
}

tree::ESEQ* Canon::do_exp(tree::Exp* e){
	// std::cout << "do_exp(tree::Exp* e)" << std::endl;
    if(instanceof<tree::ESEQ>(e)){
        return do_exp((tree::ESEQ*)(e));
    }
    else{
        return reorder_exp(e);
    }
}

tree::ESEQ* Canon::reorder_exp(tree::Exp* e){
    //debuger kaze da u ovoj funkciji puca
	// std::cout << "reorder_exp(tree::Exp* e)" << std::endl;
    StmExpList* x = reorder(e->kids());
    return new tree::ESEQ(x->m_stm,(tree::Exp*)(e->build(*(x->m_exps))));
}


StmExpList* Canon::reorder(tree::ExpList* exps){
	// std::cout << "reorder(tree::ExpList* exps)" << std::endl;
    if(exps == nullptr)
	{
		return m_nopNull;
	}
    else{
        tree::Exp* a = exps->m_head; // zasto je ovde nullptr?
		
        if(instanceof<tree::CALL>(a)){
            temp::Temp* t = new temp::Temp();
            tree::Exp* e = new tree::ESEQ(new tree::MOVE(new tree::TEMP(t), a), new tree::TEMP(t));
            return reorder(new tree::ExpList(e, exps->m_tail));
        }
        else{
            tree::ESEQ* aa = do_exp(a);
            StmExpList* bb = reorder(exps->m_tail);
            if(commute(bb->m_stm, aa->m_exp)){
                return new StmExpList(seq(aa->m_stm, bb->m_stm), new tree::ExpList(aa->m_exp, bb->m_exps));
            }
            else{
                temp::Temp* t = new temp::Temp();
                return new StmExpList(seq(aa->m_stm, seq(new tree::MOVE(new tree::TEMP(t), aa->m_exp), bb->m_stm)),
                        new tree::ExpList(new tree::TEMP(t), bb->m_exps));
            }
        }
    }
}

tree::StmList* Canon::linear(tree::SEQ* s, tree::StmList* l){
    return linear(s->m_left,linear(s->m_right,l));
}

tree::StmList* Canon::linear(tree::Stm* s, tree::StmList* l){
    if(instanceof<tree::SEQ>(s)){
        return linear((tree::SEQ*)(s), l);
    }
    else{
		// if (instanceof<tree::MOVE>(s)){
		// 	std::cout << "move" << std::endl;
		// }
		// else{
		// 	std::cout << "usao" << std::endl;
		// }
		// exit(0);
        return new tree::StmList(s, l);
    }
}
tree::StmList* Canon::linearize(tree::Stm* s){
    return linear(do_stm(s), nullptr);
}



StmListList::StmListList(tree::StmList* h,StmListList* t)
    : m_head(h), m_tail(t)
{}
StmListList::~StmListList(){
    //TODO
}



tree::StmList* TraceSchedule::getLast(tree::StmList* block){
    tree::StmList* l = block;
    while(l->m_tail->m_tail != nullptr)
        l = l->m_tail;
    return l;
}
void TraceSchedule::trace(tree::StmList* l){
    while(true){
        tree::LABEL* lab = (tree::LABEL*)(l->m_head);
        m_table->erase(lab->m_label);
        tree::StmList* last = getLast(l);
        tree::Stm* s = last->m_tail->m_head;
        if(instanceof<tree::JUMP>(s)){
            tree::JUMP* j = (tree::JUMP*)(s);
            tree::StmList* target = (tree::StmList*)((m_table->find(j->m_targets->m_head))->second);
            if(j->m_targets->m_tail == nullptr && target != nullptr){
                last->m_tail = target;
                l = target;
            }
            else{
                last->m_tail->m_tail = getNext();
                return;
            }
        }
        else if(instanceof<tree::CJUMP>(s)){
            tree::CJUMP* j = (tree::CJUMP*)(s); 
            tree::StmList* t = (tree::StmList*)((m_table->find(j->m_iftrue))->second);
            tree::StmList* f = (tree::StmList*)((m_table->find(j->m_iffalse))->second);
            if(f != nullptr){
                last->m_tail->m_tail = f;
                l = f;
            }
            else if (t != nullptr){
                last->m_tail->m_head = new tree::CJUMP(tree::CJUMP::notRel(j->m_relop),j->m_left,j->m_right, j->m_iffalse, j->m_iftrue);
                last->m_tail->m_tail = t;
                l = t;
            }
            else{
                temp::Label* ff = new temp::Label();
                last->m_tail->m_head = new tree::CJUMP(j->m_relop, j->m_left, j->m_right, j->m_iftrue, ff);
                last->m_tail->m_tail = new tree::StmList(new tree::LABEL(ff), new tree::StmList(new tree::JUMP(j->m_iffalse), getNext()));
                return;
            }
            
        }
        else{
            std::cerr << "Bad basic block in TraceSchedule" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}
tree::StmList* TraceSchedule::getNext(){
    if(m_theBlocks->m_blocks == nullptr){
        return new tree::StmList(new tree::LABEL(m_theBlocks->m_done),nullptr);
    }
    else{
        tree::StmList* s = m_theBlocks->m_blocks->m_head;
        tree::LABEL* lab = (tree::LABEL*)(s->m_head);
        if(m_table->count(lab->m_label) > 0){
            trace(s);
            return s;
        }
        else{
            m_theBlocks->m_blocks = m_theBlocks->m_blocks->m_tail;
            return getNext();
        }
    }
}
TraceSchedule::TraceSchedule(BasicBlocks* b){
    m_theBlocks = b;
    for(StmListList* l = b->m_blocks; l != nullptr; l = l->m_tail)
        m_table->insert(std::pair<temp::Label*, tree::StmList*>(((tree::LABEL*)(l->m_head->m_head))->m_label, l->m_head));
    m_stms = getNext();
    m_table = nullptr;
}
TraceSchedule::~TraceSchedule(){
    //TODO
}



