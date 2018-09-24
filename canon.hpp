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
    //BasicBlocks groups statements into sequences of straight-line code
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
			static StmExpList* m_nopNull;

            Canon();
            static bool isNop(tree::Stm* a);
			static bool commute(tree::Stm* a, tree::Exp* b);
            static tree::Stm* seq(tree::Stm* a, tree::Stm* b);

			// pull all the ESEQ s out of a statement or expression
            static tree::Stm* do_stm(tree::SEQ* s);
            static tree::Stm* do_stm(tree::MOVE* s);
            static tree::Stm* do_stm(tree::Exp* s);
            static tree::Stm* do_stm(tree::Stm* s);
            static tree::ESEQ* do_exp(tree::ESEQ* e);
            static tree::ESEQ* do_exp(tree::Exp* e);


			// The reorder function takes a list of expressions and returns a pair of (statement, expression-list). The statement contains all the things that must be executed before the expression-list When there are no ESEQ s at all we will use EXP ( CONST 0), which does nothing, as the statement.
            static StmExpList* reorder(tree::ExpList* exps);
			static tree::Stm* reorder_stm(tree::Stm* s);
            static tree::ESEQ* reorder_exp(tree::Exp* e);

			//Linearize removes ESEQs and moves te CALLs to top level
			static tree::StmList* linearize(tree::Stm* s); 
            static tree::StmList* linear(tree::SEQ* s, tree::StmList* l);
            static tree::StmList* linear(tree::Stm* s, tree::StmList* l);
    };

    //TraceSchedule orders the blocks so that every CJUMP is followed by its "false" label
    class TraceSchedule {
        public:
            tree::StmList* m_stms;
            BasicBlocks* m_theBlocks;
            std::map<temp::Label*, tree::StmList*>* m_table = new std::map<temp::Label*, tree::StmList*>();
            
            tree::StmList* getLast(tree::StmList* block);
            void trace(tree::StmList* l);
            tree::StmList* getNext();
            TraceSchedule(BasicBlocks* b);
            ~TraceSchedule();

    };
};

#endif


