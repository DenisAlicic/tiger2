#ifndef ASSEM_HPP
#define ASSEM_HPP 

#include <string>
#include "temp.hpp"

namespace assem {
	class Targets {
		public:
			temp::LabelList* m_labels;

			Targets(temp::LabelList* labels);
	};

	class Instr {
		public:
			std::string m_assem;

			Instr(std::string assem);
			virtual temp::TempList* use() = 0;
			virtual temp::TempList* def() = 0;
			virtual Targets* jumps() = 0;
			virtual ~Instr();
			temp::Temp* nthTemp(temp::TempList* l, int i);
			temp::Label* nthLabel(temp::LabelList* l, int i);
			std::string format(temp::TempMap* m);
			
	};

	class InstrList {
		public: 
			Instr* m_head;
			InstrList* m_tail;

			InstrList(Instr* head, InstrList* tail);
			static InstrList* append(InstrList* i1, InstrList* i2);
	};


	class LABEL : public Instr {
		public:
			temp::Label* m_label;

			LABEL(std::string a, temp::Label* label);

			temp::TempList* use();
			temp::TempList* def();
			Targets* jumps();
	};

	class MOVE : public Instr {
		public:
			temp::Temp* m_dst;
			temp::Temp* m_src;

			MOVE(std::string a, temp::Temp* dst, temp::Temp* src);

			temp::TempList* use();
			temp::TempList* def();
			Targets* jumps();
	};

	class OPER : public Instr {
		public:
			temp::TempList* m_dst;
			temp::TempList* m_src;
			Targets* m_jump;

			OPER(std::string a, temp::TempList* dst, temp::TempList* src, temp::LabelList* jump = nullptr);

			temp::TempList* use();
			temp::TempList* def();
			Targets* jumps();
	};
}; // end of namespace

#endif /* ASSEM_HPP */
