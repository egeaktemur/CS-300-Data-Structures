#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>

using namespace std;

ifstream GetFile(string filename){//Reading file
	ifstream file;
	file.open(filename.c_str());
	if (file.fail()){ // If could not open the file
		cout << "Cannot open file exiting program..."<<endl;
		file.close();
		exit(0);
	}
	return file;
}

string getinput(){
	string word;
	cin.clear();
	cin.sync();
	getline(cin,word);
	return word;
}

struct Contact {
	string name,number,city;
	Contact(string name1,string number1="",string city1="") :name(name1), number(number1),city(city1){};
	Contact(){name="";number="";city="";};
	const Contact & operator=(const Contact & rhs){
		this->name = rhs.name;this->number = rhs.number;
		this->city=rhs.city;return *this;}
	const bool operator<(Contact & rhs){
		if(this->name<rhs.name){return true;}return false;}
	const bool operator<(const Contact & rhs) const{
		if(this->name<rhs.name){return true;}return false;}
	const bool operator<=(Contact & rhs){
		if(this->name<rhs.name || this->name==rhs.name){return true;}return false;}
	const bool operator<=(const Contact & rhs) const{
		if(this->name<rhs.name || this->name==rhs.name){return true;}return false;}
	const bool operator>(Contact & rhs){
		if(this->name>rhs.name){return true;}return false;}
	const bool operator>(const Contact & rhs) const{
		if(this->name>rhs.name){return true;}return false;}
	const bool operator==(Contact& rhs){
		if(this->name.find(rhs.name)==0){return true;}return false;}
	const bool operator!=(Contact &rhs){return !(*this ==rhs);}

};


inline int leftChild( int i ){
	return 2*i+1;
}

ostream& operator<< (ostream& os,const Contact & rhs){
	os << rhs.name << ' ' << rhs.number << ' ' << rhs.city;
	return os;
}

template <class Comparable>
void insertionSort (vector <Comparable> & a){
	int j;
	for (int p = 1;  p < a.size(); p++){
		Comparable tmp = a[p];
		for (j = p; j > 0 &&  tmp < a[j - 1]; j --)
			a[j] = a[j -1];
		a[j] = tmp;
	}
}

template <class Comparable>  // for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
void percDown( vector<Comparable> & a, int i, int n ){
	int child;
	Comparable tmp;
	for (tmp=a[i] ; leftChild(i) < n; i = child ){
		child = leftChild(i);
		if ( child != n-1 && a[ child  ] < a[ child+1 ] ){
			child++;
		}
		if ( a[child ] > tmp ){
			a[i] = a[ child ];
		}
		else{
			break;
		}
	} 
	a[ i ] = tmp;
}



/**
* Mergesort algorithm (driver).
*/
template <class Comparable>
void mergeSort( vector<Comparable> & a ){
	mergeSort( a,0, a.size( ) - 1 );
}

/**
* Internal method that makes recursive calls.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void mergeSort( vector<Comparable> & a, int left, int right ){
	if ( left < right ){
		int center = ( left + right ) / 2;
		mergeSort( a, left, center );
		mergeSort( a, center + 1, right );
		merge( a, left, center + 1, right );
	}
}
/**
* Internal method that merges two sorted halves of a subarray.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* leftPos is the left-most index of the subarray.
* rightPos is the index of the start of the second half.
* rightEnd is the right-most index of the subarray.
*/
template <class Comparable>
void merge(  vector<Comparable> & a,int leftPos, int rightPos, int rightEnd ){
	int index = rightPos-1;
	if (a[index] <= a[rightPos]) {
		return;
	}
	while (leftPos <= index && rightPos <= rightEnd) {
		if (a[leftPos] <= a[rightPos]) {
			leftPos++;
		}
		else {
			Comparable value = a[rightPos];
			int i = rightPos;
			while (i != leftPos) {
				a[i] = a[i - 1];
				i--;
			}
			a[leftPos] = value;
			leftPos++;
			index++;
			rightPos++;
		}
	}
}

/**
* Quicksort algorithm (driver).
*/
template <class Comparable>
void quicksort( vector<Comparable> & a ){
	quicksort( a, 0, a.size( ) - 1 );
}

/**
* Internal quicksort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void quicksort( vector<Comparable> & a, int left, int right ){
	if ( left + 10 <= right ){
		Comparable pivot = median3( a, left, right );
		// Begin partitioning
		int i = left, j = right - 1;
		for ( ; ; ){
			while ( a[ ++i ] < pivot ) { }
			while ( pivot < a[ --j ] ) { }
			if ( i < j ){Swap( a[ i ], a[ j ] );}
			else{break;}
		}
		Swap( a[ i ], a[ right - 1 ] );   // Restore pivot
		quicksort( a, left, i - 1 );       // Sort small elements
		quicksort( a, i + 1, right );    // Sort large elements
	}
	else{  // Do an insertion sort on the subarray
		insertionSort( a, left, right );
	}
}

/**
* Internal insertion sort routine for subarrays
* that is used by quicksort.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right ){
	for ( int p = left + 1; p <= right; p++ ){
		Comparable tmp = a[ p ];
		int j;
		for ( j = p; j > left && tmp < a[ j - 1 ]; j-- ){
			a[ j ] = a[ j - 1 ];
		}
		a[ j ] = tmp;
	}
}

/**
* Standard Swap
*/
template <class Comparable>
inline void Swap( Comparable & obj1, Comparable & obj2 ){
	Comparable tmp = obj1;
	obj1 = obj2;
	obj2 = tmp;
}

/** Return median of left, center, and right.
*   Order these and hide the pivot.
*/
template <class Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right ){
	int center = ( left + right ) / 2;
	if ( a[ center ] < a[ left ] )
		Swap( a[ left ], a[ center ] );
	if ( a[ right ] < a[ left ] )
		Swap( a[ left ], a[ right ] );
	if ( a[ right ] < a[ center ] )
		Swap( a[ center ], a[ right ] );
	Swap( a[ center ], a[ right - 1 ] );// Place pivot at position right - 1
	return a[ right - 1 ];
}

template <class Comparable>
void heapsort(vector<Comparable> & a){
	for (int i = a.size()/2; i >=0; i--){// buildHeap
		percDown(a, i, a.size());
	}
	for (int j = a.size() -1; j >0; j--){// sort
		Swap(a[0], a[j]);    // Swap max to the last pos.
		percDown(a, 0, j); // re-form the heap
	}
}

template <class Comparable>
bool binarySearch(vector<Comparable> &  arr,Comparable x){
	int lbound = 0;
	int size =arr.size();
	int hbound = size - 1;
	bool found= false;
	while (lbound <= hbound){
		int middle = (lbound + hbound ) / 2;
		if (arr[middle]==x) {
			int i=-1;
			while(middle+i >= 0 && arr[middle+i]==x){
				i--;
			}
			i++;
			while(middle+i < size && arr[middle+i]==x){
				i++;
			}
			return true;
		}
		else if (x < arr[middle]) {
			hbound  = middle - 1;
		}
		else {
			lbound = middle + 1;
		}
	}
	return found;
}

template <class Comparable>
bool binarySearchP(vector<Comparable> &  arr,Comparable x){
	int lbound = 0;
	int size =arr.size();
	int hbound = size - 1;
	bool found= false;
	while (lbound <= hbound){
		int middle = (lbound + hbound ) / 2;
		if (arr[middle]==x) {
			int i=-1;
			while(middle+i >= 0 && arr[middle+i]==x){
				i--;
			}
			i++;
			while(middle+i < size && arr[middle+i]==x){
				cout<<arr[middle+i]<<endl;
				i++;
			}
			return true;
		}
		else if (x < arr[middle]) {
			hbound  = middle - 1;
		}
		else {
			lbound = middle + 1;
		}
	}
	return found;
}

template <class Comparable>
int sequantialSearch(vector<Comparable> &  arr,Comparable x){
	bool found= false;
	int size= arr.size();
	for(int i=0; i<size;i++){
		if(arr[i]==x){
			found=true;
		}
	}
	return found;
}

template <class Comparable>
int sequantialSearchP(vector<Comparable> &  arr,Comparable x){
	bool found= false;
	int size= arr.size();
	for(int i=0; i<size;i++){
		if(arr[i]==x){
			cout<<arr[i]<<endl;
			found=true;
		}
	}
	return found;
}


void ToUpper(string & x){
	int size= x.size();
	for (int i = 0;i<size; i++){
		x[i]=toupper(x[i]);
	}
}

int main(){
	cout <<"Please enter the contact file name: "<<endl;
	string filename,line,name, surname,number,city,search;
	cin >> filename;
	cout <<"Please enter the word to be queried :"<<endl;
	getline(cin >> ws,search);

	ToUpper(search);

	ifstream file = GetFile(filename);
	vector<Contact> original,ContactsIS,ContactsQS,ContactsMS,ContactsHS;

	while (getline(file,line)){ 
		istringstream info(line);
		info>>name>>surname>>number>>city;
		name=(name+" "+surname);
		ToUpper(name);
		Contact contact(name,number,city);
		original.push_back(contact);
	}
	
	int k=50;
	cout <<endl<<"Sorting the vector copies"<<endl;
	cout <<"======================================"<<endl;

	auto startQS = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++){
		ContactsQS= original;
		quicksort(ContactsQS);
	}
	auto endQS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -startQS);
	cout << "Quick Sort Time: " << endQS.count()/k << " Nanoseconds\n";
	
	auto startIS = std::chrono::high_resolution_clock::now();
	
	for (int i = 0; i < k; i++){
		ContactsIS= original;
		insertionSort(ContactsIS);
	}
	
	auto endIS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -startIS);
	cout << "Insertion Sort Time: " << endIS.count()/k  << " Nanoseconds\n";
	
	auto startMS = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++){
		ContactsMS= original;
		mergeSort(ContactsMS);
	}
	auto endMS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -startMS);
	cout << "Merge Sort Time: " << endMS.count()/k << " Nanoseconds\n";

	auto startHS = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++){
		ContactsHS= original;
		heapsort(ContactsHS);
	}
	auto endHS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -startHS);
	cout << "Heap Sort Time: " << endHS.count()/k  << " Nanoseconds\n";


	cout <<endl<< "Searching for "<<search<<endl;
	cout << "======================================"<<endl;
	bool found= false;
	Contact Search(search);
	auto startBS = std::chrono::high_resolution_clock::now();
	// Binary Search
	for (int i = 0; i < k; i++){
		found= binarySearch(ContactsIS,Search);
	}
	found= binarySearchP(ContactsIS,Search);
	if(!found){
		cout <<search<<" does NOT exist in the dataset"<<endl;
	}
	auto endBS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -startBS);
	cout << "Binary Search Time: "<<endBS.count()/k<<endl<<endl;
	cout << "Search results for Sequential Search:"<<endl;
	auto startSS = std::chrono::high_resolution_clock::now();
	//Sequantial search
	for (int i = 0; i < k; i++){
		found = sequantialSearch(ContactsIS,Search);
	}
	found = sequantialSearchP(ContactsIS,Search);
	if(!found){
		cout <<search<<" does NOT exist in the dataset"<<endl;
	}
	auto endSS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -startSS);
	cout << "Sequential Search Time: "<<endSS.count()/k<<endl<<endl;

	cout << "SpeedUp between Search Algorithms"<<endl;
	cout << "======================================"<<endl;
	cout << "(Sequential Search/ Binary Search) SpeedUp = "<<(double)((double)endSS.count()/(double)endBS.count())<<endl<<endl;


	cout << "SpeedUps between Sorting Algorithms"    << endl;
	cout << "======================================" << endl;
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = "<< (double)((double)endIS.count()/(double)endQS.count()) <<endl;
	cout << "(Merge Sort / Quick Sort) SpeedUp = "   << (double)((double)endMS.count()/(double)endQS.count()) <<endl;
	cout << "(Heap Sort / Quick Sort) SpeedUp = "    << (double)((double)endHS.count()/(double)endQS.count()) <<endl;
	file.close();
}