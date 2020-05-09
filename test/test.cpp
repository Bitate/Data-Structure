#include <iostream>
#include "../Hash/hash.h"

using namespace std;

void printList(list<int> &lst)
{
	list<int>::iterator it;
	it = lst.begin();
	for (it; it != lst.end(); it++)
	{
		cout << *it << endl;
	}
}

void push_back(list<int>& lst, int ele)
{
	list<int>::iterator it = lst.end();
	lst.insert(it,ele);
}

int main()
{	//**************************************************************
	// Hash Table Test
	//**************************************************************
	HashMap<int, int, int> hashmap;
	int key = 1, value1 = 1, value2 = 2, value3 = 3;
	cout << "At the very beginning, the size of hashmap is : " << hashmap.size() << endl;
	cout << "Then, I insert an entry with the key is " << key << " and the value is " << value1 << endl;
	// if the key is same, then update its corresponding value
	hashmap.put(2, 2);
	cout << "Done" << endl;
	hashmap.put(2, 3);
	cout << "Then, I insert an entry with the key is " << key << " and the value is " << value2 << endl;
	hashmap.put(2, 4);
	cout << "Done" << endl;
	cout << "Then, I insert an entry with the key is " << key << " and the value is " << value3 << endl;
	int sz = hashmap.size();
	cout << "Done" << endl;
	cout << "Now, hash size is : " << sz << endl;
	HashMap<int,int,int>::Iterator iterator = hashmap.find(2);
	Entry<const int,int> value = *iterator;
	cout << " Begin to find entry info..." << endl;
	cout << "If key is 2, then value is : " << value.value() << endl;
	
	cout << "Deleting entry with the key is " << value.key() << endl;
	hashmap.erase(iterator);
	cout << "Done" << endl;

	cout << "Now the size of hashmap is : " << hashmap.size() << endl;


	//**************************************************************
	// xxxxxxxxx Test
	//**************************************************************

}