#include "./summator.h"
#include "godot_cpp/core/class_db.hpp"

void Summator::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("add", "value"), &Summator::add);
	ClassDB::bind_method(D_METHOD("reset"), &Summator::reset);
	ClassDB::bind_method(D_METHOD("get_total"), &Summator::get_total);
}

void Summator::add(const int &p_value)
{
	count = count + p_value;
}

void Summator::reset(void)
{
	count = 0;
}

int Summator::get_total(void)
{
	return (count);
}

Summator::Summator() : count(0)
{
}
