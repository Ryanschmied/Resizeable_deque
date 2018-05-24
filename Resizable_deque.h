/*****************************************
 * UW User ID:  rmschmie
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"

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

    //Private member variables
	private:
        Type *array;
        int ifront;
        int iback;
        int deque_size;
        int initial_array_capacity;
        int array_capacity;
    
		// Any private member functions
        void double_array_capacity();
        void halve_array_capacity();
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
// Your initalization list
array(nullptr),
ifront(n),
iback(-1),
deque_size(0),
initial_array_capacity(n),
array_capacity(n)
{
	//Check to see if size passed in is less than 16
    if(n < 16)
        n=16;
    //Assign member variables
    array = new Type[initial_array_capacity];
    ifront = n;
    iback = -1;
    deque_size = 0;
    initial_array_capacity = n;
    array_capacity = n;
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque ):
// Your initalization list
array(nullptr),
ifront(16),
iback(-1),
deque_size(0),
initial_array_capacity(0),
array_capacity(0)
{
    //Create new deque withe the same member variables as the deque passed in
    array = new Type[deque.array_capacity];
    ifront = deque.ifront;
    iback = deque.iback;
    deque_size = deque.deque_size;
    initial_array_capacity = deque.initial_array_capacity;
    array_capacity = deque.array_capacity;
    
    //Copy the contents of the array of the deque passed in to the new array
    for(int i = 0; i<array_capacity; i++){
        array[i] = deque.array[i];
    }
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque ):
// Your initalization list
array(new Type[16]),
ifront(16),
iback(-1),
deque_size(0),
initial_array_capacity(16),
array_capacity(16)
{
    //Create deque with default member variables
    array = new Type[16];
    ifront = 16;
    iback = -1;
    deque_size = 0;
    initial_array_capacity = 16;
    array_capacity = 16;
    
    //Call swap with
    swap(deque);
}
// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	// Delete the memory allocated for array in the deque
    delete []array;
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
    if(deque_size==0) //Check deque size
        return true;
	return false;
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
    if(empty())
        throw underflow();
    else
        return array[ifront];
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
    if(empty())
        throw underflow();
    else
        return array[iback];
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	//Swap the member variables
    std::swap(array, deque.array);
    std::swap(ifront, deque.ifront);
    std::swap(iback, deque.iback);
    std::swap(deque_size, deque.deque_size);
    std::swap(array_capacity, deque.array_capacity);
    std::swap(initial_array_capacity, deque.initial_array_capacity);
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
	//Check to see oif array capacity needs to be doubled
    if (deque_size == array_capacity){
        double_array_capacity();
        ifront = array_capacity -1;
        array[ifront] = obj;
    }
    else{ //Else do a normal push
        ifront--;
        if(ifront < 0) //Check if loop around is required
            ifront = array_capacity -1;
        
        array[ifront] = obj;
    }
    
    deque_size++;
    //If there is only one element in the deque, ifront and iback should both be the index of it
    if(deque_size == 1)
        iback = ifront;
}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// Enter your implementation heres
    if (deque_size == array_capacity){ //Check if the array capacity needs to be doubled
        double_array_capacity();
        iback++;
        array[iback] = obj;
    }
    else{ //Else do a normal push
        iback++;
        if(iback > array_capacity -1) //Check if Loop around is required
            iback = 0;
        
        array[iback] = obj;
    }
    
    deque_size++;
    if(deque_size == 1) //If there is only one element in the deque, ifront and iback should both be the index of it it
        ifront = iback;
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
    if(empty()){
        throw underflow();
    }
    else{
        ifront++; //Increment ifront to 'pop' the value at its previous index
        if(ifront > array_capacity - 1) //Check if loop around is required
            ifront = 0;
        
        deque_size--;
    
        //Check if array capacity needs to be halved
        if(deque_size == (array_capacity/4) && array_capacity > initial_array_capacity)
            halve_array_capacity();
    }
}
template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Enter your implementation here
    if(empty()){
        throw underflow();
    }
    else{
        iback--; //Decrement iback to 'pop' the value at its previous index
        if(iback < 0) //Check if loop around is required
            iback = array_capacity-1;
        
        deque_size--;
        
        //Check if array capacity needs to be halved
        if(deque_size == (array_capacity/4) && array_capacity > initial_array_capacity)
            halve_array_capacity();
    }
}
    

template <typename Type>
void Resizable_deque<Type>::clear() {
    //Delete the array,
    delete []array;
    //Reset all memeber variables other than initial_array capacity as that remains constant
    ifront = initial_array_capacity;
    iback = -1;
    deque_size  = 0;
    array_capacity = initial_array_capacity;
    //Create empty array
    array = new Type[initial_array_capacity];
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functios (helper functions) here
template <typename Type>
void Resizable_deque<Type>::double_array_capacity(){
    Type *newArr = new Type[array_capacity*2]; //Create new array with double the capacity of the full array
    int index = 0; //Create index variable to keep track of indecies in new array
    int i = ifront; //Iterate from front of deque to back of deque
    
    //use do while to handle case where ifront == iback + 1
    //Loop through array being copied and push values to new array from ifront to iback to maintain order
    do{
        if(i > array_capacity-1) //Check if loop around is required
            i = 0;
        newArr[index] = array[i];
        index++;
        i++;
    }while(i!=iback+1); //Loop until be go past iback
    
    //Adjust indexes of ifront and iback
    ifront = 0;
    iback = deque_size-1; //Since deque_size elements were copied to new array, deque_size -1 is the index
    
    //Delete memory of the old array
    Type *temp = array;
    array = newArr;
    delete []temp;
    
    //Double the array capacity
    array_capacity *= 2;
}

template <typename Type>
void Resizable_deque<Type>::halve_array_capacity(){
    Type *newArr = new Type[array_capacity/2]; //Create new array with 1/2 the capacity of the 1/4 full array
    int index = 0; //Index of array being copied to
      //Loop through array being copied and push values to new array from ifront to iback to maintain order
    for(int i = ifront; i!=iback+1; i++){
        if(i > array_capacity-1) //Check if loop around is required
            i = 0;
        newArr[index] = array[i];
        index++;
    }
    //Adjust indexes of ifront and iback
    ifront = 0;
    iback = deque_size-1; //Since deque_size elements were copied to new array, deque_size -1 is the index
    
    //Delete memory of the old array
    Type *temp = array;
    array = newArr;
    delete []temp;
    
    //Halve the array capacity
    array_capacity /= 2;
}


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
