#include "Interval.h"
#include <sstream>

Interval::Interval(std::istream & is)
{
	is >> *this;
}

void Interval::save(std::ofstream & os) const
{
	print(os);
}

void Interval::print(std::ostream & os) const
{
	os << toString() << "\n";
}

std::string Interval::toString() const
{
	std::ostringstream oss;
	oss << "[ " << m_beg << ", " << m_end << " ]";
	return oss.str();
}

std::istream & operator>>(std::istream & is, Interval & interval)
{
	is >> interval.m_beg >> interval.m_end;
	if (is)
	{
		return is;
	}
	else
	{
		interval = Interval();
		return is;
	}
}

std::ostream & operator<<(std::ostream & os, const Interval & interval)
{
	return os << interval.toString();
}
