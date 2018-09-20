#ifndef CANON_HPP
#define CANON_HPP

#include <map>
#include "tree.hpp"
#include "temp.hpp"

namespace canon {
    class StmListList {
        public:
            tree::StmList* m_head;
            StmListList* m_tail;
            StmListList(tree::StmList* h,StmListList* t);
            ~StmListList();
    };
    class BasicBlocks {
        public:
            StmListList*  m_blocks;
            temp::Label* m_done;
            StmListList* m_lastBlock;
            tree::StmList* m_lastStm;

            BasicBlocks(tree::StmList* stms);
            void addStm(tree::Stm* s);
            void doStms(tree::StmList* l);
            void mkBlocks(tree::StmList* l);
            ~BasicBlocks();
            

    };
    class MoveCall : public tree::Stm {
        public:
            tree::TEMP* m_dst;
            tree::CALL* m_src;

            MoveCall(tree::TEMP* d, tree::CALL* s);
            tree::ExpList* kids();
            tree::Stm* build(const tree::ExpList& kids);
            ~MoveCall();

    };
    class ExpCall : public tree::Stm {
        public:
            tree::CALL* m_call;
            ExpCall(tree::CALL* c);
            tree::ExpList* kids();
            tree::Stm* build(const tree::ExpList& kids);
            ~ExpCall();
    };
    class StmExpList {
        public:
            tree::Stm* m_stm;
            tree::ExpList* m_exps;

            StmExpList(tree::Stm* s, tree::ExpList* e);
            ~StmExpList();
    };
    class Canon {
        public:
            Canon();
            static bool isNop(tree::Stm* a);
            static tree::Stm* seq(tree::Stm* a, tree::Stm* b);
            static bool commute(tree::Stm* a, tree::Exp* b);
            static tree::Stm* do_stm(tree::SEQ* s);
            static tree::Stm* do_stm(tree::MOVE* s);
            static tree::Stm* do_stm(tree::Exp* s);
            static tree::Stm* do_stm(tree::Stm* s);
            static tree::Stm* reorder_stm(tree::Stm* s);
            static tree::ESEQ* do_exp(tree::ESEQ* e);
            static tree::ESEQ* do_exp(tree::Exp* e);
            static tree::ESEQ* reorder_exp(tree::Exp* e);

            static StmExpList* m_nopNull;

            static StmExpList* reorder(tree::ExpList* exps);
            static tree::StmList* linear(tree::SEQ* s, tree::StmList* l);
            static tree::StmList* linear(tree::Stm* s, tree::StmList* l);
            static tree::StmList* linearize(tree::Stm* s); 
    };
    
    class TraceSchedule {
        public:
            tree::StmList* m_stms;
            BasicBlocks* m_theBlocks;
            std::map<temp::Label*, tree::StmList*>* m_table = new std::map<temp::Label*, tree::StmList*>();
            //TODO staviti u konstruktor pravljenje mape ako je potrebno
            
            tree::StmList* getLast(tree::StmList* block);
            void trace(tree::StmList* l);
            tree::StmList* getNext();
            TraceSchedule(BasicBlocks* b);
            ~TraceSchedule();

    };
};

#endif


