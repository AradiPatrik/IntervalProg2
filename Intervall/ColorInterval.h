#pragma once
#include <memory>
#include "Interval.h"

class ColorInterval : public Interval {
public:
	friend std::istream & operator>> (std::istream & is, ColorInterval & interval);
	ColorInterval() = default;
	ColorInterval(double beg, double end, const char * color = "white");
	// if one of the copy control members is defined, than most of the time
	// all of them should be defined
	ColorInterval(const ColorInterval &other);
	ColorInterval(ColorInterval &&other) noexcept;
	ColorInterval & operator=(const ColorInterval & rhs) &;
	ColorInterval & operator=(ColorInterval && rhs) & noexcept;
	~ColorInterval();

	ColorInterval * clone() const & override { return new ColorInterval(*this); }
	ColorInterval * clone() const && override { return new ColorInterval(std::move(*this)); }

	std::string toString() const override;

private:
	// logic concerning memory management logic for string should be in separate class
	// this is really bad practice
	void deallocate();
	void allocateAndCopy(const char * otherBeg, const char * otherEnd);

	char * m_color = nullptr;
	char * m_colorEnd = nullptr;
	static std::allocator<char> alloc;
};

std::istream & operator>> (std::istream & is, ColorInterval & interval);