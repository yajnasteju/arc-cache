#include <iostream>

#ifndef ARC
#include "ARC.cpp"

#endif // !ARC

using namespace arc;

/*

Test cases list:

1. (4.3) Test cache miss - L1 size should go upto PAGE_SIZE and remain constant.

2. (4.1) Test cache miss when T1 = PAGE_SIZE 

3. (4.2) Test cache miss when L1  < PAGE_SIZE 

4. (1) Test frequent hit - T2 should go upto PAGE_SIZE and T1 should simultaneously go down

5. (2) requested page in B1 - This should ultimately adjust p to increase the T1 capacity ( recency)

6. (3) requested page in B2 - This should ultimately adjust p to increase the T2 capacity ( frequency)

*/
int main()
{
	ARC<int , int> *a = new ARC<int,int>();
	
	for (int i = 1; i < 10000; i++) 
		a->load_master_data(i, i * 1000);
	
	cout << " ARU Cache implementation: PAGE_SIZE is defined to be 5 - Select test case from below " << endl;
	while (1)
	{

		cout << "	1. (4.3) Test cache miss - L1 size should go upto PAGE_SIZE and remain constant. " << endl;
		cout << "	2. (4.1) Test cache miss when L1 = PAGE_SIZE & T1 < c implies that there is a key in B1" << endl;
		cout << "	3. (4.2) Test cache miss when L1  < PAGE_SIZE " << endl;
		cout << "	4. (1) Test frequent hit - T2 should go upto PAGE_SIZE and T1 should simultaneously go down " << endl;
		cout << "	5. (2) requested page in B1 - This should ultimately increase p to increase the T1 capacity ( recency) " << endl;
		cout << "	6. (3) requested page in B2 - This should ultimately decrease p to increase the T2 capacity ( frequency) " << endl;
		cout << "	7. Custom Inputs : Press 99 to print " << endl;

		int id = 0;
		int value = 0;
		cin >> id;
		switch (id)
		{
		case 1:
			cout << "Input keys : 1,2,3,4,5 " << endl;
			cout << "Expected op : T1 should contain 5 to 1 " << endl;

			for (int i = 1; i <= 5; i++)
				a->fetch(i, value);
			a->print();
			a->clear();
			break;

		case 2:
			cout << "Input keys : 1,2,3,4,5, 1,2,3,4, 6, " << endl;
			cout << "Expected op : T1 should contain 6, B1 should contain 5, and T2 should contain 4 to 1" << endl;

			for (int i = 1; i <= 5; i++)
				a->fetch(i, value);
			for (int i = 1; i <= 4; i++)
				a->fetch(i, value);

			a->fetch(6, value);

			a->print();
			a->clear();
			break;

		case 3:				
			cout << "Input keys : 1,2,3,4,5,	1,2,3,4,5,	6 " << endl;
			cout << "Expected op : T1 should contain 6 , T2 should contain 5 to 2 , and B2 should contain 1" << endl;
				
			for (int i = 1; i <= 5; i++)
				a->fetch(i, value);
			for (int i = 1; i <= 6; i++)
				a->fetch(i, value);

			a->print();
			a->clear();
			break;

		case 4:
			cout << "Input keys : 1,2,3,4,5,	1,2,3,4,5 " << endl;
			cout << "Expected op : T2 should contain 5 to 1 , T1 should be empty" << endl;

			for (int i = 1; i <= 5; i++)
				a->fetch(i, value);
			for (int i = 1; i <= 5; i++)
				a->fetch(i, value);

			a->print();
			a->clear();
			break;

		case 5:
			cout << "Input keys : 1,2,3,4,5,	1,2,3,4, 	6,5 " << endl;
			cout << "Expected op : 5 thats in B1 moves to T2 BUT P value increases from 0 to 1 => T1 capacity increased" << endl;

			for (int i = 1; i <= 5; i++)
				a->fetch(i, value);
			for (int i = 1; i <= 4; i++)
				a->fetch(i, value);

			a->fetch(6, value);
			a->print();
			a->fetch(5, value);
				
			a->print();
			a->clear();
			break;
			
		case 6:
			cout << "Input keys : 1,2,3,4,5,	1,2,3,4, 	6,5 ,1" << endl;
			cout << "Expected op : 1 thats in B2 moves to T2 BUT P value goes from 1 to 0 => T2 capacity increased" << endl;

			for (int i = 1; i <= 5; i++)
				a->fetch(i, value);
			for (int i = 1; i <= 4; i++)
				a->fetch(i, value);

			a->fetch(6, value);
				
			a->fetch(5, value);
			a->print();
			a->fetch(1, value);

			a->print();
			a->clear();
			break;

		case 7:
			while (1)
			{
				int key, value;
				cin >> key;
				if (key == 99)
					a->print();
				else
					a->fetch(key, value);
				a->print();
				cout << endl << endl;

			}
		default:
			cout << " Select 1-7 as below" << endl;
			break;
		}

	}
	delete a;
	return 1;
}