#include <iostream>

#ifndef ARC
#include "ARC.cpp"

#endif // !ARC

using namespace arc;

int main()
{
	ARC<int , int> *a = new ARC<int,int>();
	
	try {
		a->insert(1, 2);
		a->insert(3, 4);
		a->insert(5, 6);
		a->print();
		cout << a->fetch(5);
		a->fetch(6);

	}
	catch (std::exception e)
	{
		cout << "Exception !!!!!!!!!!!!! => ";
		cout << e.what() << endl;
	}
}