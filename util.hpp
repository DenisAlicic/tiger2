#ifndef UTIL_HPP
#define UTIL_HPP 

namespace util {
	class BoolList {
		public:
			bool m_head;
			BoolList* m_tail;

			BoolList(bool head, BoolList* tail);
			~BoolList();
	};

}; // end of namespace

#endif /* UTIL_HPP */
