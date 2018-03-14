#pragma once
#include <iostream>
#include <string>

inline void print(char c)
{
	std::cout << c;
}

inline void print(std::string s)
{
	std::cout << s;
}

inline void println(std::string s)
{
	std::cout << s << std::endl;
}