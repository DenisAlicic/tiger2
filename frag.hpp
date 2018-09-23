#ifndef FRAG_HPP
#define FRAG_HPP 

#include <string>
#include "temp.hpp"
#include "frame.hpp"

namespace frag {

	class Frag {
		public:
			Frag* m_next;

			Frag();
			virtual ~Frag() {}
	};

	// example: 
	// L16:
	// .word 2
	// .asciiz "\n"
	class DataFrag : public Frag {
		public:
			temp::Label* m_label;
			std::string m_data;

			DataFrag(temp::Label* label = nullptr, std::string data = "");
	};

	class ProcFrag : public Frag {
		public:
			tree::Stm* m_body;
			frame::Frame* m_frame;

			ProcFrag(tree::Stm* body, frame::Frame* frame);
	};

}; // end of namespace


#endif /* FRAG_HPP */
