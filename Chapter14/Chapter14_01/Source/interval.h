#pragma once

#include "common.h"

class interval
{
public:
	interval() : _min(+infinity), _max(-infinity) {}
	interval(double min, double max) : _min(min), _max(max) {}

	double size() const
	{
		return _max - _min;
	}

	bool contains(double x) const
	{
		return _min <= x && x <= _max;
	}

	bool surrounds(double x) const
	{
		return _min < x && x < _max;
	}

	double clamp(double x) const
	{
		if (x < _min) return _min;
		if (x > _max) return _max;
		return x;
	}

	double min() const { return _min; }
	double max() const { return _max; }

	static const interval empty;
	static const interval universe;

private:
	double _min;
	double _max;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);