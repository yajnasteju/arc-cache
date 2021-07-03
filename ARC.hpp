#include <unordered_map>
#include <iostream>

#ifndef ARC_H
#define ARC_H

#define PAGE_SIZE 1024

namespace arc {
	template<typename T1 , typename T2>
	class ARC {

	public:
		ARC();
		void print();
		void print(std::unordered_map<T1, T2>);
		bool insert(T1 key, T2 value);
		T2 fetch(T1 key);
		
		std::unordered_map<T1, T2> t1, t2, b1, b2; // b1 and b2 should ideally be vectors as they are proposed to be just history , keeping as map for simplicity for now

	private:
		void replace(int p);
		int p;
		int c;
	};


}


#endif // !ARC_H
