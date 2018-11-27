#ifndef COUNTER_HPP 
#define COUNTER_HPP
class Counter
{
protected:
	size_t& Count() { static size_t counter = 0; return counter; }

public:
	Counter() { ++Count(); }
	~Counter() { --Count(); }
};
#endif
