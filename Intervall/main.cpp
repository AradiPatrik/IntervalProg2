#include <iostream>
#include "Interval.h"
#include "ColorInterval.h"
#include "IntervalSet.h"
#include <string>

void firstAssignment()
{
	std::ifstream in("in.txt");
	std::ofstream out("out.txt");
	Interval i1(3, 5);
	i1.print(std::cout);
	Interval i2(std::cin);
	i2.print(std::cout);
	Interval i3(in);
	i3.print(std::cout);
	i3.save(out);
	std::cout << "length is: " << i3.length() << std::endl;
	ColorInterval ci1(5, 10, "green");
	ci1.print(std::cout);
	ColorInterval ci2;
	std::cin >> ci2;
	ColorInterval ci3(5, 6);
	ci3 = ci2;
	ColorInterval ci4(ci2);
	std::cout << ci3;
	std::cout << ci4;
}

void secondAssignment()
{
	IntervalSet set(10);
	set += Interval(10, 20);
	set += Interval(10, 40);
	set += Interval(20, 30);
	set += ColorInterval(10, 20);
	set += ColorInterval(5, 10, "black");
	set += ColorInterval(6, 8, "purple");
	std::cout << set;
}

int main(int argc, char **argv)
{
	secondAssignment();
	return 0;
}
