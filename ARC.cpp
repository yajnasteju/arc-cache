#include "ARC.hpp"

using namespace std;


template<typename T1, typename T2>
arc::ARC<T1, T2>::ARC() {
	this->c = PAGE_SIZE;
	this->p = 0;
}



template<typename T1, typename T2>
void arc::ARC<T1, T2>::print() {
	cout << "T1 Cache : " << endl;
	this->print(t1);
	cout << "======================================" << endl;
	cout << "B1 Cache : " << endl;
	this->print(b1);
	cout << "======================================" << endl;
	cout << "T2 Cache : " << endl;
	this->print(t2);
	cout << "======================================" << endl;
	cout << "B2 Cache : " << endl;
	this->print(b2);
	cout << "======================================" << endl;

}

template<typename T1, typename T2>
void arc::ARC<T1,T2>::print(std::unordered_map<T1, T2> m) {

	auto it = m.begin();
	while (it != m.end()) {
		cout << (*it).first << " => " << (*it).second << endl;
		it++;
	}

}

template<typename T1, typename T2>
bool arc::ARC<T1, T2>::insert(T1 key , T2 value) {
	
	this->t1.insert(make_pair(key,value));
	return true;
}


template<typename T1, typename T2>
T2 arc::ARC<T1, T2>::fetch(T1 key) {
	
	if (t1.find(key) != t1.end())
		return t1[key];
	throw std::exception("Miss");
}
