#include "ARC.hpp"

using namespace std;

template<typename T1, typename T2>
arc::ARC<T1, T2>::ARC() {
	this->c = PAGE_SIZE;
	this->p = 0;
}


template<typename T1, typename T2>
T2 arc::ARC<T1, T2>::fetch(T1 key ,T2 &value) {
	
	//Case 1 Begin => key in either t1 or t2
	if (hit(t2, key, value)) {		// Check T2 before T1 to avoid duplicates in cache
		moveToTop(t2, key, value);
		return value;

	}else if (hit(t1, key, value)) {
		moveList(t1, t2, key);
		return value;
	}
	
	//Case 1 End

	//Case 2 Begin => Key in b1
	else if (hit(b1, key, value)) {

		p = (float)min((float)c, (float)(p + max((b2.size() * 1.0) / b1.size(), 1.0)));
		replace(p , key);
		moveList(b1, t2 , key );

		return value;
	}
	//Case 2 End

	//Case 3 Begin => key in b2 
	else if (hit(b2, key, value)) {
		p = (float)max((float)0.0, (float)(p - max((b1.size() * 1.0) / b2.size(), 1.0)));
		replace(p , key);
		moveList(b2, t2 , key);
		return value;
	}
	//Case 3 End

	// Case 4 Begin 
		
	else 
	{
		//Case 4.1 - L1 has c pages
		if (t1.size() + b1.size() == c)
		{
			if (t1.size() < c)
			{
				if( b1.size() > 0)
					b1.pop_back();
				replace(p , key);
			
			}
			else {
				if(t1.size() > 0)
					t1.pop_back();
			}
	
		}
		// Case 4.2 - L1 has less than c and L1+L2 >= c
		else if ((t1.size() + b1.size() < c) &&
			(t1.size() + t2.size() + b1.size() + b2.size() >= c))
		{
			if (t1.size() + t2.size() + b1.size() + b2.size() == 2 * c)
			{
				if(b2.size()>0)
					b2.pop_back();
			}
			replace(p , key);
		}

		// Case 4.3 - default for cache miss - add to top of T1 
		fetchMaster(key , value , t1);
		
	}

	return value;

}

template<typename T1, typename T2>
bool arc::ARC<T1, T2>::hit(std::list<std::pair<T1, T2>> cache , T1 key , T2  &value)
{
	auto it = cache.begin();
	while (it != cache.end())
	{
		if ((*it).first == key)
		{
			value = (*it).second;
			return true;

		}
		it++;
	}
	return false;
}

template<typename T1, typename T2>
void arc::ARC<T1, T2>::clear()
{
	t1.clear();
	t2.clear();
	b1.clear();
	b2.clear();
}

template<typename T1, typename T2>
void arc::ARC<T1, T2>::replace(int &p , T1 key)
{
	T2 value;
	if ((t1.size() >= 1) &&
		((hit(b2, key , value) && (t1.size() == p)) || t1.size() > p))
	{
		moveList(t1, b1,t1.back().first);
	}
	else
	{
		moveList(t2, b2 ,t2.back().first);
	}
}

template<typename T1, typename T2>
void arc::ARC<T1, T2>::moveList(std::list<std::pair<T1, T2>> &from, std::list<std::pair<T1, T2>> &to, T1 key)
{
	T2 value;
	auto it = from.begin();
	while (it != from.end())
	{
		if ((*it).first == key) {
			to.push_front(make_pair(key, (*it).second));
			value = (*it).second;
			break;
		}
		it++;
	}
	from.remove(make_pair(key, value));
}

template<typename T1, typename T2>
void arc::ARC<T1, T2>::moveToTop(std::list<std::pair<T1, T2>>& list, T1 key , T2 value)
{
	list.remove(make_pair(key, value));
	list.push_front(make_pair(key, value));
}


template<typename T1, typename T2>
void arc::ARC<T1, T2>::fetchMaster(T1  key , T2  &value , std::list<std::pair<T1, T2>>& to)
{
	//cout << " **********************Master data Accessed *********************" << " for  key ==> " << key << endl;
	to.push_front(make_pair(key, value = masterData[key]));
}


template<typename T1, typename T2>
void arc::ARC<T1, T2>::print() {
	cout << "T1 Cache : size =>" << t1.size() << endl;
	this->print(t1);
	cout << "======================================" << endl;
	cout << "B1 Cache : size =>" << b1.size() << endl;
	this->print(b1);
	cout << "======================================" << endl;
	cout << "T2 Cache : size =>" << t2.size() << endl;
	this->print(t2);
	cout << "======================================" << endl;
	cout << "B2 Cache : size =>" << b2.size() << endl;
	this->print(b2);
	cout << "======================================" << endl;
	cout << " Value of P => " << p << endl;
}

template<typename T1, typename T2>
void arc::ARC<T1, T2>::print(std::list<std::pair<T1, T2>> m) {

	auto it = m.begin();
	while (it != m.end()) {
		cout << (*it).first << " => " << (*it).second << endl;
		it++;
	}

}

template<typename T1, typename T2>
bool arc::ARC<T1, T2>::load_master_data(T1 key, T2 value) {

	this->masterData.insert(make_pair(key, value));
	return true;
}

