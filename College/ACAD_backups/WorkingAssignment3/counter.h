#ifndef COUNTER_H
#define COUNTER_H

class Counter
{

protected:
    int value{0};    		// a simple integer instance variable

public:
    Counter() {};    		// Constructs a new Counter with value zero.
    Counter(int initial) : value{initial} {}   // Constructs a new Counter with given initial value.
    int get_value() const { return value; }    	// Returns the current value.
    void increment(int delta) { value += delta; }    // Increments the value by the specified delta.
    void reset() { value = 0; }    				// Resets the value to zero.
    void decrement(int delta) {value -= delta;} //Put into subclass
};


#endif
