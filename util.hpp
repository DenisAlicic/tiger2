#ifndef UTIL_HPP
#define UTIL_HPP 

namespace util {
	class BoolList {
		private:
			bool m_head;
			BoolList* m_tail;

		public:
			BoolList(bool head, BoolList* tail);
			~BoolList();

			bool head() const;
			BoolList* tail() const;
	};

	template<typename Base, typename T>
	inline bool instanceof(const T *ptr) 
	{
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}
}; // end of namespace

#endif /* UTIL_HPP */
