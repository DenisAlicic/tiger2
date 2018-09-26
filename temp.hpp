#ifndef TEMP_HPP
#define TEMP_HPP 

#include <string>
#include "symbol.hpp"

namespace temp {

	// use the temporary to mean a value that is temporarily held in a register
	//Temp s are abstract names for local variables 
	class Temp {
	private:
		static int s_count;
		int m_num;

	public:
		Temp(int i);
		// returns a new temporary from an infinite set of temps
		Temp();
		std::string toString() const;
	};

	// some machine-language location whose exact address is yet to be determined – just like a label in assembly language
	// Label s are abstract names for static memory addresses 
	// We need labels for jumps, for functions, strings etc
	class Label {
		private:
			static int s_count;
			std::string m_name;

		public:
			// returns a new label from an infinite set of labels, or returns a new label whose assembly-language name is given string
			Label(std::string name = "");
			Label(symbol::Symbol* s);
			std::string toString() const;
	};

	class LabelList {
		private:
			Label* m_head;
			LabelList* m_tail;

		public:
			LabelList(Label* head, LabelList* tail);
			~LabelList();

			Label* head() const;
			LabelList* tail() const;
	};

	class TempList {
		private:
			Temp* m_head;
			TempList* m_tail;

		public:
			TempList(Temp* head, TempList* tail);
			~TempList();

			Temp* head() const;
			TempList* tail() const;
	};

	class TempMap {
		public:
			virtual std::string tempMap(Temp* temp) const = 0;
			virtual ~TempMap(){}
	};

	// page 198
	class DefaultMap : public TempMap {
		public:
			std::string tempMap(Temp* temp) const override;
	};

}; // end of namespace

#endif /* TEMP_HPP */
