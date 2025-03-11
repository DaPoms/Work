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

	void updateCap(int newSize)
	{
		cap = newSize;
		T* newPtr = new T[cap];
		for(int i{0}; i < sz; i++)
		{
			//Lesson learned!: both these do the same thing, operator[] 
		    //opens up to the start array address and whatever is inside of operator[] adds to the address by the passed value
			//*(newPtr + i) = *(data + i); 
			newPtr[i] = data[i];
		}

		data = newPtr; 
		
	}
    int size() {return sz;}				 // Returns the number of elements stored
    T operator[](int i) {return data[i];}    // Returns reference to the element at index i; 
								// behavior is undefined if i is out of bounds

    void push_back(const T& elem) {
            // Insert an element at the end of the vector
			if(sz == cap)
				updateCap(max( 1,2 * cap ));
			sz++;
			data[sz - 1] = elem;
    }
    
    void pop_back() {
			// Remove an element from the end of the vector
			if(sz == cap)
			{
				updateCap(-1);
				--sz;
			}
			else
				sz--;

			
	}

	
	void insert(int i, const T& elem)
	{
		if (sz == cap)
			updateCap(max( 1,2 * cap ) );
		for(int k = sz - 1; k >=i; k--)
			data[k + 1] = move(data[k]); //Teacher showed us move(), removes the need of a placeholder var for data swapping
		data[i] = elem;
		sz++;
	}

	void erase(int i) //Do we need to change size in erase?
	{
		for(int k{i}; k < sz - 1; k++)
		{
			data[k] = move(data[k + 1]);
		}
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
	v.insert(2, 69);
	disp_vector (v) ;
	v.erase(1);
	disp_vector (v) ;
	return 0 ;
}
