#ifndef FRAME_HPP
#define FRAME_HPP 

#include "tree.hpp"
#include "temp.hpp"
#include "util.hpp"
#include "assem.hpp"
#include <set>

// The class Frame holds information about formal parameters and local vari- ables allocated in this frame. To make a new frame for a function f with k formal parameters, call newFrame( f , l) , where l is a list of k booleans: true for each parameter that escapes and false for each parameter that does not.

namespace frame {
	// The Access class describes formals and locals that may be in the frame or in registers. This is an abstract data type, so its implementation as a pair of subclasses is visible only inside the Frame module:
	class Access {
		public:
			virtual tree::Exp* exp(tree::Exp* framePtr) = 0;
			virtual tree::Exp* expFromStack(tree::Exp* stackPtr) = 0;
	};

	class AccessList {
		public:
			Access* m_head;
			AccessList* m_next;

			AccessList(Access* head, AccessList* next);
	};

	class Frame : public temp::TempMap {
		public:
			// these functions implements mips
			
			temp::Label* m_name; // Label of this frame: basically the name of the function
			AccessList* m_formals = nullptr; // arguments of this function

			// Allocate a new frame. label name - the name of the function, BoolList formals - a list of one Boolean per formal, stating whether it escapes. Example: main function needs a frame
			virtual Frame* newFrame(temp::Label* name, util::BoolList* formals) = 0;

			// To allocate a new local variable, call this function which returns a frame::Access. That makes Frame a Factory of Access.  If it escapes, then store it in the frame, otherwise it is stored in a register
			virtual Access* allocLocal(bool escape) = 0;

			// This function calls some external function written for example in C. func - the name of the external procedure, args - guments to be passed
			virtual tree::Exp* externalCall(const std::string& func, tree::ExpList* args) = 0;

			virtual temp::Temp* FP() = 0; // frame pointer
			virtual temp::Temp* SP() = 0; // stack pointer 
			virtual temp::Temp* RA() = 0; // return adress is created by the CALL instruction and tells where (within the calling function) control should return upon completion of the current function
			virtual temp::Temp* RV() = 0; // return value

			// for caller and callee save registers
			virtual std::set<temp::Temp*> registers() = 0;


			//  example
			// L4:
			// .word 6
			// .asciiz ""str2""
			virtual std::string string(temp::Label* label, const std::string& value) = 0;
			
			// Moving incoming formal parameters, and saving and restoring of callee-save registers
			virtual tree::Stm* procEntryExit1(tree::Stm* body) = 0;

			// assure that the temporaries zero, return-address, stack pointer, and all the callee-saves registers are still live at the end of the function
			virtual assem::InstrList* procEntryExit2(assem::InstrList* body) = 0;

			// pseudo-instructions, as needed in the particular assembly language, to an- nounce the beginning of a function;
			//an instruction to adjust the stack pointer (to allocate a new frame)
			//an instruction to reset the stack pointer (to deallocate the frame);
			//pseudo-instructions, as needed, to announce the end of a function.
			virtual assem::InstrList* procEntryExit3(assem::InstrList* body) = 0; 

			virtual assem::InstrList* codegen(tree::Stm* s) = 0;
	};

}; // end of namespace

#endif /* FRAME_HPP */
