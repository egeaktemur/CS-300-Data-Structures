#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode{
	Comparable element;
	BinaryNode*right;
	BinaryNode*left;
	int height;
	BinaryNode(const Comparable & theElement,BinaryNode<Comparable> *lt, BinaryNode<Comparable> *rt, int h = 0 )
		: element( theElement ), left( lt ), right( rt ), height( h ) { }
	friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree{
public:
	explicit BinarySearchTree(const Comparable & notFound );
	BinarySearchTree( const BinarySearchTree<Comparable> & rhs );
	~BinarySearchTree( );
	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	Comparable & find( const Comparable & x ) const;
	const int findamount(  const string & x,const string & DocumentName ) const;
	Comparable & getelement( BinaryNode<Comparable> * t) const{return t->element;};
	bool isEmpty( ) const;
	void makeEmpty( );
	void insert(const Comparable & x );
	void insert( std::string DocumentName,BinaryNode<Comparable> * & t );
	BinaryNode<Comparable> * returnaddress(const Comparable &x) const;
	void remove( std::string DocumentName,const Comparable & x );
	const BinarySearchTree<Comparable> & operator=( const BinarySearchTree & rhs );
	bool operator<(const BinarySearchTree &rhs) const;
	bool operator>(const BinarySearchTree &rhs) const;
	void BSTdisplaySections();
private:
	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
	void insert(const Comparable & x, BinaryNode<Comparable> * & t ) const;
	void remove( std::string DocumentName, const Comparable & x, BinaryNode<Comparable> * & t ) const;
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * find( const Comparable & x,BinaryNode<Comparable> *t ) const;
	const int findamount( const string & x,const string & DocumentName, BinaryNode<Comparable> *t ) const;
	void makeEmpty( BinaryNode<Comparable> * & t ) const;
	int height( BinaryNode<Comparable> *t ) const;
	int max( int lhs, int rhs ) const;
	void printTree( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable>* deepcopy(BinaryNode<Comparable>* node)const;
	void BSTdisplaynode(BinaryNode<Comparable>*& t);
};

/**
* Construct the tree.
*/
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable & notFound ) :ITEM_NOT_FOUND( notFound ), root( NULL ){}

/**
* Copy constructor.
*/
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ){
	*this=rhs;
}

/**
* Destructor for the tree.
*/
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( ){
	makeEmpty( );
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin( ) const{
	return elementAt( findMin( root ) );
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
	return elementAt( findMax( root ) );
}

/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
Comparable & BinarySearchTree<Comparable>::find( const Comparable & x ) const{
	return find( x, root )->element;
}

template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::returnaddress( const Comparable & x ) const{
	return find( x, root );
}

/**
* Check if given tree is empty
*/
template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty( ) const{
	if( root != NULL ){
		return true;
	}
	return false;
}

/**
* Make the tree logically empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( ){
	makeEmpty(root );
}

/**
* Insert x into the tree; duplicates are ignored.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x ){
	insert(x, root );
}

/**
* Remove x from the tree. Nothing is done if x is not found.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( std::string DocumentName,const Comparable & x ){
	remove(DocumentName,x, root );
}

//const AvlTree & operator=( const AvlTree & rhs );
template <class Comparable>
const BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=( const BinarySearchTree<Comparable> & rhs ){
	this->root=deepcopy(rhs.root);
	return *this;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::operator<(const BinarySearchTree<Comparable> &rhs) const{
	return this->root->element < rhs.root->element;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::operator>(const BinarySearchTree<Comparable> &rhs) const{
	return this->root->element > rhs.root->element;
}
template <class Comparable>
void BinarySearchTree<Comparable>::BSTdisplaySections(){
	cout <<endl<<"*****"<<endl;
	BSTdisplaynode(root);
	cout <<"*****"<<endl;
}

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::elementAt( BinaryNode<Comparable> *t ) const{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode<Comparable> * & t ) const{
	if( t == NULL ){ // create a new node at the right place
		t = new BinaryNode<Comparable>(	x, NULL, NULL );
	}
	else if(x< t->element){
		insert(x,t->left ); // insert at the left or
	}
	else if( t->element < x){
		insert(x,t->right ); // right subtree
	}
	//t->height = max( height( t->left ), height( t->right ) ) + 1;
}

/**
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( std::string DocumentName,const Comparable & x, BinaryNode<Comparable> * & t )const{
	if( t == NULL )
		return; // Item not found; do nothing
	if( x < t->element)
		remove( x, x, t->left );
	else if( t->element < x)
		remove( x, x, t->right );
	else if( t->left != NULL && t->right != NULL ){ // Two children
		t->element = findMin( t->right )->element;
		t->element = findMin( t->right )->element;
		remove(t->element, t->element, t->right );
	}
	else{ // one or no children
		BinaryNode<Comparable> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}
	t->height = max( height( t->left ), height( t->right ) ) + 1;
}

/**
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const {
	if(t==NULL)
		return NULL;
	if(t->left==NULL)
		return t;
	return findMin(t->left);
}

/**
* Internal method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t )const{
	if(t==NULL)
		return NULL;
	if(t->right==NULL)
		return t;
	return findMax(t->left);
}
/**
* Internal method to find an item in a subtree.
* x is item to search for.
* t is the node that roots the tree.
* Return node containing the matched item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> *t ) const{
	while( t != NULL ){
		if( x < t->element ){
			t = t->left;
		}
		else if( t->element < x ){
			t = t->right;
		}
		else{
			return t; // Match
		}
	}
	return NULL; // No match
}

/**
* Internal method to make subtree empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( BinaryNode<Comparable> * & t ) const{
	if( t != NULL ){
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	t = NULL;
}

/**
* Return the height of node t, or -1, if NULL.
*/
template <class Comparable>
int BinarySearchTree<Comparable>::height( BinaryNode<Comparable> *t )const{
	if (t == NULL)
		return -1;
	return t->height;
}

/**
* Return maximum of lhs and rhs.
*/
template <class Comparable>
int BinarySearchTree<Comparable>::max( int lhs, int rhs )const{
	if (lhs > rhs)
		return lhs;
	return rhs;
}

template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::deepcopy(BinaryNode<Comparable>* node)const{
	if (node == NULL){
		return NULL;
	}
	return new BinaryNode<Comparable>(node->element, deepcopy(node->left), deepcopy(node->right) ,node->height);
}

template <class Comparable>
void BinarySearchTree<Comparable>::BSTdisplaynode(BinaryNode<Comparable>*& t){
	if( t != NULL ){
		BSTdisplaynode( t->left );
		cout<<t->element<<endl;
		BSTdisplaynode( t->right );
	}
}


#endif