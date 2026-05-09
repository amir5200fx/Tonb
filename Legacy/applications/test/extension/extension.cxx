#include <boost/filesystem.hpp>

#include <iostream>
#include <string>

int main()
{
	boost::filesystem::path p("C:\myFolder\myFile.xx");

	std::cout << p.extension() << std::endl;

	std::system("pause");
	return 0;
}