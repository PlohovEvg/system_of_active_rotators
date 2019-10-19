#include <stdlib.h>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
	srand(time(NULL));
	cout << (rand() % 6 + 2)*-1 << endl;
	cout << (rand() % 6 + 2)*-1 << endl;
	cout << (rand() % 6 + 2)*-1 << endl;
	cout << (rand() % 6 + 2)*-1 << endl;
	cout << (rand() % 6 + 2)*-1 << endl;
	cout << (rand() % 6 + 2)*-1 << endl;
	cout << (rand() % 6 + 2)*-1 << endl;
	cout << (rand() % 6 + 2)*-1 << endl;
	return 0;
}