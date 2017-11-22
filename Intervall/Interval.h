#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Interval {
public:
	friend std::istream & operator>> (std::istream & is, Interval & interval);
	friend std::ostream & operator<< (std::ostream & os, const Interval & interval);
	Interval() = default;
	Interval(double beg, double end) : m_beg(beg), m_end(end) { }
	Interval(std::istream & is);
	Interval(const Interval &) = default;
	Interval(Interval &&) = default;
	Interval & operator=(const Interval &) = default;
	Interval & operator= (Interval &&) = default;
	virtual ~Interval() = default;

	virtual Interval * clone() const & { return new Interval(*this); }
	virtual Interval * clone() const && { return new Interval(std::move(*this)); }

	// redundant we could simply pass a file stream to the print function
	void save(std::ofstream & os) const;
	// use polimporphism of the toString method instead of overriding print function
	void print(std::ostream & os) const;
	double length() const { return m_end - m_beg; }
	virtual std::string toString() const;

protected:
	double m_beg = 0.0;
	double m_end = 0.0;
};

std::istream & operator>>(std::istream & is, Interval & interval);
std::ostream & operator<<(std::ostream & os, const Interval & interval);