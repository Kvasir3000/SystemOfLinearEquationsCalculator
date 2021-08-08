#include <iostream>
#include <cstdlib>
#include "SLE.h"
#include "array"
int main()
{
	int n;
	std::cout << "Type how many equations you have in your system: \n";
	std::cin >> n;
	SLE system1(n);

	std::string* arr = new std::string[n];
	for (int i = 0; i < n; i++) {
		std::cout << "Type equation number " << i + 1 << ":\n";
		std::cin >> arr[i];;
	}
	std::cout << '\n';
	auto results =  system1 << arr;
	for (auto element : results)
		std::cout << element << '\n';

	std::cout << '\n';

	system("pause");
	return 0;
}