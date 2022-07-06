#ifndef HASHTABLE
#define HASHTABLE

#include <vector>
#include <string>
using namespace std;

int hashword (const WordItem & key1, int tableSize){ 
	string key=key1.word;
	int sum = 0;
	for (unsigned int i = 0; i < key.length(); i++) // add all bytes in a loop
		sum = sum + key[ i ];
	return (sum % tableSize);
}

/**
* Internal method to test if a positive number is prime.
* Not an efficient algorithm.
*/
bool isPrime( int n ){
	if ( n == 2 || n == 3 )
		return true;
	if ( n == 1 || n % 2 == 0 )
		return false;
	for ( int i = 3; i * i <= n; i += 2 )
		if ( n % i == 0 )
			return false;
	return true;
}

/**
* Internal method to return a prime number 
* at least as large as n.  Assumes n > 0.
*/
int nextPrime( int n ){
	if ( n % 2 == 0 )
		n++;
	for ( ; ! isPrime( n ); n += 2 );
	return n;
}

template <class Comparable>
class HashTable{
public:
	explicit HashTable( const Comparable & notFound = Comparable(), int size=0 )
		: ITEM_NOT_FOUND( notFound ),currentSize(0){
			HashEntry temp=HashEntry(notFound);
			vector<HashEntry> Array2;
			Array2.push_back(temp);
			for(int i =0; i<size-1;i++){
				Array2.push_back(temp);
			}
			Array=Array2;
	}
	HashTable( const HashTable & rhs ): ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),Array( rhs.Array ), currentSize( rhs.currentSize ) { }
	bool doesexist(const Comparable & x)const;
	void makeEmpty( );
	void insert( const Comparable & x );
	void remove( const Comparable & x );
	void statistics();
	Comparable & getelement(const Comparable & e){return Array[findPos(e)].element;}
	const HashTable & operator=( const HashTable & rhs );
	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry{
		Comparable element;
		EntryType info;
		HashEntry( const Comparable & e = Comparable( ), EntryType i = EMPTY )
			: element( e ), info( i ) { }
	};
	vector<HashEntry> Array;
	int currentSize;
	const Comparable ITEM_NOT_FOUND;
	int findPos( const Comparable & x ) const;
	bool isActive( int currentPos ) const;
	void rehash( );
};


/**
* Make the hash table logically empty.
*/
template <class Comparable>
void HashTable<Comparable>::makeEmpty( ){
	HashTable<Comparable> HashTable<Comparable>(Comparable(),1);
	*this = HashTable<Comparable>;
	// destroy the lists but not the vector!
}

/**
* Method that performs quadratic probing resolution.
* Return the position where the search for x terminates.
*/
template <class Comparable>
int HashTable<Comparable>::findPos( const Comparable & x ) const{
	int collisionNum = 0;
	unsigned int currentPos = hashword( x, Array.size());
	while ( currentPos<0 || currentPos>= Array.size() || (Array[ currentPos ].info != EMPTY && Array[ currentPos ].element != x) ){
		currentPos += pow(++collisionNum, 2) ;  //add the difference
		if ( currentPos >= Array.size( ) )              // perform the mod
			currentPos -= Array.size( );                // if necessary
	}
	return currentPos;
}

template <class Comparable>
bool HashTable<Comparable>::doesexist( const Comparable & x ) const{
	return isActive(findPos(x));
}

/**
* Return true if currentPos exists and is active.
*/
template <class Comparable>
bool HashTable<Comparable>::isActive( int currentPos ) const{
	return Array[ currentPos ].info == ACTIVE;
}

/**
* Remove item x from the hash table.
*  x has to be in the table
*/
template <class Comparable>
void HashTable<Comparable>::remove( const Comparable & x ){
	int currentPos = findPos( x );
	if ( isActive( currentPos ) )
		Array[ currentPos ].info = DELETED;
}

template <class Comparable>
void HashTable<Comparable>::insert( const Comparable & x){
	int currentPos = findPos( x );
	if ( isActive( currentPos ) )
		return;
	Array[ currentPos ] = HashEntry( x, ACTIVE );
	// enlarge the hash table if necessary 
	if ( ++currentSize >= (double)Array.size( ) *6/10 )
		rehash( );
}
/**
* Expand the hash table.
*/
template <class Comparable>
void HashTable<Comparable>::rehash( ){
	vector<HashEntry> oldArray = Array;
	cout << "rehashed..."<<endl;
	int new_size= nextPrime( 2 * oldArray.size( ) );
	cout << "previous table size: "<< oldArray.size( ) 
		 << ", new table size: "<< new_size
		 << ", current unique word count "<< currentSize
		 << ", current load factor: "<< (double)currentSize/(double)new_size<< endl;
	// Create new double-sized, empty table
	Array.resize( new_size );
	for (unsigned int j = 0; j < Array.size( ); j++ )
		Array[ j ].info = EMPTY;
	// Copy table over
	currentSize = 0;
	for (unsigned int i = 0; i < oldArray.size( ); i++ )
		if ( oldArray[ i ].info == ACTIVE )
			insert( oldArray[ i ].element);
}

template <class Comparable>
void HashTable<Comparable>::statistics( ){
	cout << "After preprocessing, the unique word count is "
		<<	currentSize<<". Current load ratio is "<< (double)currentSize/(double)Array.size()<< endl;
}

template <class Comparable>
const HashTable<Comparable> & HashTable<Comparable>::operator=( const HashTable<Comparable> & rhs ){
	this->Array= rhs.Array;
	this->currentSize=rhs.currentSize;
	return *this;
}

#endif