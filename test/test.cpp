#include <iostream>
#include "../Hash/hash.h"

using namespace std;

int main()
{
	HashMap<int, int, int> hashmap;
	int sz = hashmap.size();
	cout << sz << endl;
}