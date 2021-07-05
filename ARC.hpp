#include <list>
#include <map>
#include <iostream>
#include <algorithm>

#ifndef ARC_H
#define ARC_H

#define PAGE_SIZE 5

namespace arc {
	template<typename T1 , typename T2>
	class ARC {

	public:
		ARC();
		void print();
		T2 fetch(T1 key , T2 &value);
		bool load_master_data(T1 key, T2 value);
		void clear();
		
		std::list<std::pair<T1, T2>> t1, t2, b1, b2; // b1 and b2 should ideally be vectors as they are proposed to be just history , keeping as list for simplicity for now

	private:
		void replace(float& p , T1 key);
		void moveList(std::list<std::pair<T1, T2>> &from, std::list<std::pair<T1, T2>> &to, T1 key);
		void moveToTop(std::list<std::pair<T1, T2>>& list, T1 key , T2 value);
		void fetchMaster(T1  key , T2 & value , std::list<std::pair<T1, T2>>& to);
		void print(std::list<std::pair<T1, T2>>);
		bool hit(std::list<std::pair<T1, T2>>, T1 key, T2& value);
		float p;
		unsigned int c;
		std::map<T1, T2> masterData;
	};


}


#endif // !ARC_H
