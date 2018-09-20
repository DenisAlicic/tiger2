#ifndef TEMP_HPP
#define TEMP_HPP 

#include <string>
#include "symbol.hpp"

namespace temp {
	class Temp {
	private:
		static int m_count;
		int m_num;
	public:
		Temp(int i);
		Temp();
		std::string toString() const;
	};

	class Label {
		public:
		static int m_count;
		std::string m_name;
		Label(std::string name = "");
		Label(symbol::Symbol* s);
		std::string toString() const;
	};

	class LabelList {
	public:
		Label* m_head;
		LabelList* m_tail;
		LabelList(Label* head, LabelList* tail);
		// TODO free
	};

	class TempMap {
	public:
		virtual std::string tempMap(Temp* temp) const= 0;
	};

	class DefaultMap : public TempMap {
	public:
		std::string tempMap(Temp* temp) const override;
	};

	class CombineMap : public TempMap {
	public:
		TempMap* m_tmap1, *m_tmap2;
		CombineMap(TempMap* tmap1, TempMap* tmap2);
		std::string tempMap(Temp* temp) const override;
	};

	class TempList {
	public:
		Temp* m_head;
		TempList* m_tail;
		TempList(Temp* head, TempList* tail);
	};
}; // end of namespace

#endif /* TEMP_HPP */
