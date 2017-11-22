#include "ColorInterval.h"
#include <algorithm>
#include <sstream>
#include <cstring>

std::allocator<char> ColorInterval::alloc;

ColorInterval::ColorInterval(double beg, double end, const char * color)
	: Interval(beg, end)
{
	allocateAndCopy(color, color + strlen(color));
}

ColorInterval::ColorInterval(const ColorInterval & other)
	: Interval(other)
{
	allocateAndCopy(other.m_color, other.m_colorEnd);
}

ColorInterval::ColorInterval(ColorInterval &&other) noexcept
	: Interval(std::move(other))
	, m_color(other.m_color)
	, m_colorEnd(other.m_colorEnd)
{
	other.m_color = other.m_colorEnd = nullptr;
}

ColorInterval & ColorInterval::operator=(const ColorInterval & rhs) &
{
	Interval::operator=(rhs);
	if (this != &rhs)
	{
		deallocate();
		allocateAndCopy(rhs.m_color, rhs.m_colorEnd);
	}
	return *this;
}

ColorInterval & ColorInterval::operator=(ColorInterval && rhs) & noexcept
{
	Interval::operator=(std::move(rhs));
	if (&rhs != this)
	{
		deallocate();
		m_color = rhs.m_color;
		m_colorEnd = rhs.m_colorEnd;
		rhs.m_color = rhs.m_colorEnd = nullptr;
	}
	return *this;
}

ColorInterval::~ColorInterval()
{
	deallocate();
}

void ColorInterval::deallocate()
{
	std::for_each(m_color, m_colorEnd, [](char element) { alloc.destroy(&element); });
	alloc.deallocate(m_color, m_colorEnd - m_color);
}

void ColorInterval::allocateAndCopy(const char * otherBeg, const char * otherEnd)
{
	m_color = alloc.allocate(otherEnd - otherBeg);
	m_colorEnd = std::uninitialized_copy(otherBeg, otherEnd, m_color);
}

std::string ColorInterval::toString() const
{
	std::ostringstream oss;
	oss << "[ " << m_beg << ", " << m_end << " ] (";
	std::for_each(m_color, m_colorEnd, [&oss](char c) { oss << c; });
	oss << ")";
	return oss.str();
}

std::istream & operator>> (std::istream & is, ColorInterval & interval)
{
	double beg, end;
	std::string color;
	is >> beg >> end >> color;
	if (is)
	{
		interval = ColorInterval(beg, end, color.c_str());
		return is;
	}
	else
	{
		interval = ColorInterval();
		return is;
	}
}