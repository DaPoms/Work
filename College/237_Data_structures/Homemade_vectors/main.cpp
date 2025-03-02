/*
File:			myV.cpp
By:				Dr. Hussain
Adapted From:	zyBook - Chapter 5
Last Modified:	26-Feb-2025
Static sized array; a simplified version of std::vect
Simplifications:
	1. Fixed capacity (10 elements) always greater than size
	2. Static array to represent the vector
	3. Important functions to write: push_back(), pop_back(), operator[]
*/
#include <iostream>
using namespace std ;	// not given in the text

template <typename T>
class Vector {
  private:
	int cap{0}; // capacity of the array
	int sz{0}; // number of actual entries
	T* data{nullptr}; // Declare an array of 10 elements
 
  public:
    Vector(){}				// Constructs an empty vector
    int capacity() {return cap;}		// Returns current capacity of the array

	void updateSize()
	{
		cap = max(1, cap * 2);
		T* newPtr = new T[cap];
		for(int i{0}; i < sz; i++)
		{
			*(newPtr + i) = *(data + i); 
		}

		data = newPtr; 
		
	}
    int size() {return sz;}				 // Returns the number of elements stored
    T operator[](int i) {return *(data + i);}    // Returns reference to the element at index i; 
								// behavior is undefined if i is out of bounds

    void push_back(const T& elem) {
            // Insert an element at the end of the vector
			if(sz == cap)
				updateSize();
			sz++;
			*(data + (sz - 1)) = elem;
    }
    
    void pop_back() {
			// Remove an element from the end of the vector
			if(sz == cap)
			{
				updateSize();
				--sz;
			}
			else
				sz--;

			
	}

};

template <typename T>
void disp_vector (T& v) 
{
	cout << "Vector size: " << v.size() << ". Data: " ;
	for (int i=0 ; i<v.size(); i++) cout << v[i] << " " ;
	cout << endl ;
}


	
int main () 
{
	
	Vector<int> v{}; 

	disp_vector(v);	
	v.push_back(5) ;
	disp_vector (v) ;	v.push_back(3) ;
	disp_vector (v) ;	v.push_back(15) ;
	disp_vector (v) ;	v.push_back(31) ;
	disp_vector (v) ;	v.push_back(22) ;
	disp_vector (v) ;	v.push_back(18) ;
	disp_vector (v) ;	v.pop_back() ;
	disp_vector (v) ;	v.pop_back() ;
	disp_vector (v) ;	v.pop_back() ;
	disp_vector (v) ;
	return 0 ;
}
