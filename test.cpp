#include <iostream>
#include <list>
#include <string>

int main()
{
	std::string str = "lol";
	str += std::to_string(3);
	
	std::cout << str << std::endl;
}
