#include "calc.hpp"

#include <iostream>
#include <fstream>

int main()
{
	int choice{ -1 };

	std::cout << "select lab: ";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		first();
		break;
	case 2:
		second();
		break;
	case 3:
		third();
		break;
	default:
		break;
	}

	return 0;
}