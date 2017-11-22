#pragma once
#include <memory>
#include "Interval.h"
#include "ColorInterval.h"

// Represents an array, not a set
class IntervalSet {
public:
	friend std::ostream & operator<<(std::ostream &os, const IntervalSet & intervalSet);

	IntervalSet() = default;
	IntervalSet(size_t capacity);
	IntervalSet(const IntervalSet &other);
	IntervalSet(IntervalSet &&other) noexcept;
	IntervalSet & operator=(const IntervalSet &rhs) &;
	IntervalSet & operator=(IntervalSet &&rhs) & noexcept;
	~IntervalSet();

	// surprising behaviour should be push_back, or subscript operator
	IntervalSet & operator+=(const Interval &interval) &;
	IntervalSet & operator+=(Interval && interval) &;
	// again surprising behaviour should be pop_back
	IntervalSet operator--(int) &;

	size_t size() const { return m_end - m_beg; }
	Interval ** begin() const { return m_beg; }
	Interval ** end() const { return m_firstFree; }
private:
	void allocateAndCopy(Interval ** beg, Interval ** end);
	void deallocate();

	static std::allocator<Interval *> alloc;
	Interval ** m_beg = nullptr;
	Interval ** m_end = nullptr;
	Interval ** m_firstFree = nullptr;
};

std::ostream & operator<<(std::ostream &os, const IntervalSet & intervalSet);
