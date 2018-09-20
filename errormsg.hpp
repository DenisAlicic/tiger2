#ifndef TIGER_HPP
#define TIGER_HPP 

#include <string>

namespace tiger {
	namespace errormsg {

		class LineList {
			public:
				int m_head;
				LineList* m_tail;

				LineList(int head, LineList* tail);
		};

		class ErrorMsg {
			public:
				LineList* m_linePos;
				int m_lineNum;
				std::string m_filename;
				static bool anyErrors;

				ErrorMsg(const std::string& f);
				void newline(int pos);
				void error(int pos, const std::string& msg);
		};

	}; // end of error namespace
}; // end of tiger namespace

#endif /* TIGER_HPP */
