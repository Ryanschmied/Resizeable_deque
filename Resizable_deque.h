/*****************************************
 * UW User ID:  n4mahaja
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"
#include <iostream>
template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
    Type *array ;
    int ifront;
    int iback;
    int deque_size;
    int initial_array_capacity;
    int array_capacity;


		// Your member variables

		// Any private member functions
		//   - helper functions for resizing your array?

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n ):
array (nullptr), // changes the array size to 16 if the initial array is less than 16
ifront(0),
iback(0),
deque_size (0),
initial_array_capacity (0),
array_capacity(0)
{
    if (n<16)
        n=16;
    array = new Type [n];
    ifront = 0;
    iback = n-1;
    deque_size = 0;
    initial_array_capacity = n;
    array_capacity = n;
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque ):
        array (nullptr),
        ifront(0),
        iback(0),
        deque_size(0),
        initial_array_capacity(0),
        array_capacity (0)

{
    for (int i= 0; i < deque.array_capacity ; i++)
    array [i] = deque.array[i];
}


template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque ):

array (nullptr),
ifront(0),
iback(0),
deque_size(0),
initial_array_capacity(0),
array_capacity (0)


{
}


template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	// Enter your implementation here
    delete[] array;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
    return deque_size;

}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
    return (deque_size ==0);
    }


template <typename  Type>
Type Resizable_deque<Type>::front() const {
    if (empty()) {
        throw underflow();
    }
    else
    {
        return array[ifront];
    }
}


template <typename  Type>
Type Resizable_deque<Type>::back() const {
    if (empty()) {
        throw underflow();
    }
else
    {
        return array[iback];
    }
}
template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
    //std::swap (array,deque.array);
    //std::swap(ifront, deque.ifront);
    //std::swap (iback,deque.iback);
    //std::swap(initial_array_capacity,deque.initial_array_capacity);
    //std::swap(array_capacity,deque.array_capacity);





    // Swap the member variables
	//     std::swap( variable, deque.variable );

	// Enter your implementation here
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
    if (ifront == 0) {
        ifront = array_capacity - 1;
    } else {
        ifront = ifront - 1;
    }
    int new_array_capacity;
    array[ifront] = obj;
    deque_size +=1;
    if (size()==1)
    iback=ifront;
    if (size()==array_capacity) {
        new_array_capacity = array_capacity * 2;
    }

        Type *double_array = new Type[new_array_capacity];
        int data = 0;
        int i = ifront;

        while (i != iback) {
        double_array[data] = array[i];
            i = (i+1)%array_capacity;

        }
        delete[] array;
        array = double_array;
        array_capacity = new_array_capacity;
        ifront = 0;
        iback = i;
            }

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
//    if (iback==0){
//        iback = array_capacity -1;}
//    else {
//        iback =  iback - 1;
//    }
//    array[iback] = obj;
//
//    int new_array_capacity;
//    if (size() == new_array_capacity )
//    {
//        new_array_capacity = array_capacity * 2;
//    }
//    else
//    {
//        return;
//    }
//    Type *double_array = new Type [new_array_capacity];
//    int data =0;
//    int data_trail = iback;
//
//    while (data_trail!= ifront ){
//        double_array[data] = array[data_trail];
//        data_trail = (data_trail+1)%array_capacity;
//        data++;
//    }
//    delete[] array;
//    array = double_array;
//    array_capacity = new_array_capacity;
//    iback = 0 ;
//    ifront =  data;
//    deque_size +=1;
//   }
//    // Enter your implementation here
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
    if (size()==0) {
        throw underflow();
    }
    ifront = (ifront+1)%array_capacity;
    if (size()>0){
        deque_size = deque_size -1;
    }
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
    if (size()==0) {
        throw underflow();
    }
    if (size() > 0 ){
        deque_size = deque_size - 1;
    }
    if (iback ==0 ){
        iback = array_capacity - 1;
    }
    else{
        iback = iback -1;

    }

    // Enter your implementation here
}

template <typename Type>
void Resizable_deque<Type>::clear() {
        array_capacity = initial_array_capacity ;
        delete [] array;
        array = new Type[initial_array_capacity];
        ifront=0;
        iback=0;
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functios (helper functions) here


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
