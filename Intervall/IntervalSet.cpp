#include "IntervalSet.h"
#include <algorithm>


std::allocator<Interval *> IntervalSet::alloc;

IntervalSet::IntervalSet(size_t capacity)
{
	m_beg = m_firstFree = alloc.allocate(capacity);
	m_end = m_beg + capacity;
}

IntervalSet::IntervalSet(const IntervalSet &other)
{
	allocateAndCopy(other.begin(), other.end());
}

IntervalSet::IntervalSet(IntervalSet && other) noexcept
	: m_beg(other.m_beg)
	, m_end(other.m_end)
	, m_firstFree(other.m_firstFree)
{
	other.m_beg = other.m_end = other.m_firstFree = nullptr;
}

IntervalSet & IntervalSet::operator=(const IntervalSet & rhs) &
{
	if (&rhs != this)
	{
		deallocate();
		allocateAndCopy(rhs.begin(), rhs.end());
	}
	return *this;
}

IntervalSet & IntervalSet::operator=(IntervalSet && rhs) & noexcept
{
	if (&rhs != this)
	{
		m_beg = rhs.m_beg;
		m_end = rhs.m_end;
		m_firstFree = rhs.m_firstFree;
		rhs.m_beg = rhs.m_end = rhs.m_firstFree = nullptr;
	}
	return *this;
}

IntervalSet::~IntervalSet()
{
	deallocate();
}

IntervalSet & IntervalSet::operator+=(const Interval & interval) &
{
	if (m_firstFree != m_end)
	{
		alloc.construct(m_firstFree++, interval.clone());
	}
	else
	{
		std::cerr << "not enough space" << std::endl;
	}
	return *this;
}

IntervalSet & IntervalSet::operator+=(Interval && interval) &
{
	if (m_firstFree != m_end)
	{
		alloc.construct(m_firstFree++, std::move(interval).clone());
	}
	else
	{
		std::cerr << "not enough space" << std::endl;
	}
	return *this;
}

IntervalSet IntervalSet::operator--(int) &
{
	IntervalSet is = *this;
	if (m_firstFree != m_beg)
	{
		alloc.destroy(--m_firstFree);
	}
	return is;
}

void IntervalSet::allocateAndCopy(Interval ** beg, Interval ** end)
{
	m_beg = m_end = alloc.allocate(end - beg);
	std::for_each(beg, end, [this](Interval * curr) { alloc.construct(m_end++, curr->clone()); });
	m_firstFree = m_end;
}

void IntervalSet::deallocate()
{
	std::for_each(m_beg, m_firstFree, [](Interval * current) {
		alloc.destroy(current);
	});
	alloc.deallocate(m_beg, size());
}

std::ostream & operator<<(std::ostream &os, const IntervalSet & intervalSet)
{
	std::for_each(intervalSet.begin(), intervalSet.end(), [&os](const Interval * interval) { interval->print(os); });
	return os;
}