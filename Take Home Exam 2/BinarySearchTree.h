#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode{
	std::string titleOfNode;
	Comparable element;
	BinaryNode *right;
	BinaryNode *left;
	int height;
	BinaryNode(std::string title1, const Comparable & theElement,BinaryNode *lt, BinaryNode *rt, int h = 0 )
		: titleOfNode(title1),element( theElement ), left( lt ), right( rt ), height( h ) { }
	friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree{
public:
	explicit BinarySearchTree( std::string title1,const Comparable & notFound );
	BinarySearchTree( const BinarySearchTree & rhs );
	~BinarySearchTree( );
	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	const Comparable & find( const Comparable & x ) const;
	Comparable & findtitle(std::string x );
	bool DoesExist(std::string x );
	bool isEmpty( ) const;
	void makeEmpty( );
	void insert( std::string title1,const Comparable & x );
	void update(const Comparable & newelement , const Comparable & oldelement ) const;
	void remove( std::string title1,const Comparable & x );
	const BinarySearchTree & operator=( const BinarySearchTree & rhs );
	bool operator<(const BinarySearchTree &rhs) const;
	bool operator>(const BinarySearchTree &rhs) const;
	void BSTdisplaySections();
private:
	std::string titleOfTree;
	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
	void insert( std::string title1, const Comparable & x, BinaryNode<Comparable> * & t ) const;
	void update(const Comparable & newelement , const Comparable & oldelement, BinaryNode<Comparable> * t) const;
	void remove(std::string title1, const Comparable & x, BinaryNode<Comparable> * & t ) const;
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * find( const Comparable & x,BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * findtitle(std::string x, BinaryNode<Comparable> *t );
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
BinarySearchTree<Comparable>::BinarySearchTree(std::string title1,const Comparable & notFound ) :titleOfTree(title1),ITEM_NOT_FOUND( notFound ), root( NULL ){}

/**
* Copy constructor.
*/
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ){
	*this=rhs;
	titleOfTree=rhs.titleOfTree;
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
const Comparable & BinarySearchTree<Comparable>::find( const Comparable & x ) const{
	return elementAt( find( x, root ) );
}

/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
Comparable & BinarySearchTree<Comparable>::findtitle(std::string x ){
	return (findtitle( x, root ))->element;
}

/**
* Check if given item exists
*/
template <class Comparable>
bool BinarySearchTree<Comparable>::DoesExist(std::string x ){
	bool result = findtitle( x, root ) != NULL;
	return result;
}

/**
* Check if given tree is empty
*/
template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty( ) const{
	if( root != NULL ){
		return true
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
void BinarySearchTree<Comparable>::insert(std::string title1, const Comparable & x ){
	insert(title1, x, root );
}

template <class Comparable>
void BinarySearchTree<Comparable>:: update(const Comparable & newelement, const Comparable & oldelement) const{
	update(newelement,oldelement,root);
}

/**
* Remove x from the tree. Nothing is done if x is not found.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( std::string title1,const Comparable & x ){
	remove(title1,x, root );
}

//const AvlTree & operator=( const AvlTree & rhs );
template <class Comparable>
const BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=( const BinarySearchTree<Comparable> & rhs ){
	this->root=deepcopy(rhs.root);
	this->titleOfTree=rhs.titleOfTree;
	return *this;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::operator<(const BinarySearchTree<Comparable> &rhs) const{
	return this->root->titleOfNode < rhs.root->titleOfNode;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::operator>(const BinarySearchTree<Comparable> &rhs) const{
	return this->root->titleOfNode > rhs.root->titleOfNode;
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
void BinarySearchTree<Comparable>::insert(std::string title1, const Comparable & x, BinaryNode<Comparable> * & t ) const{
	if( t == NULL ){ // create a new node at the right place
		t = new BinaryNode<Comparable>(	title1, x, NULL, NULL );
	}
	if(title1 < t->titleOfNode){
		insert( title1, x, t->left ); // insert at the left or
	}
	else if( t->titleOfNode < title1 ){
		insert( title1, x, t->right ); // right subtree
	}
	
	t->height = max( height( t->left ), height( t->right ) ) + 1;
	
	/*
	if(y==NULL){
	y = new BinaryNode<Comparable>(title1, x, NULL, NULL );
	return;
	}
	BinaryNode<Comparable> * t=y;
	BinaryNode<Comparable> * prev=t;
	bool putleft=false;
	bool putright=false;
	while( t != NULL ){
	putleft=false;
	putright=false;
	if(title1 < t->titleOfNode){
	prev=t;
	t= t->left; // insert at the left or
	putleft=true;
	}
	else if( title1 > t->titleOfNode ){
	prev=t;
	t= t->right; // right subtree
	putright=true;
	}
	else if( title1 == t->titleOfNode ){
	if(x>t->element){
	t = new BinaryNode<Comparable>(title1, x, NULL, NULL );
	t->height = max( height( t->left ), height( t->right ) ) + 1;
	prev->left=t;
	return;
	}
	else if(x<t->element){
	t = new BinaryNode<Comparable>(title1, x, NULL, NULL );
	t->height = max( height( t->left ), height( t->right ) ) + 1;
	prev->right=t;
	return;
	}
	else{

	}
	}
	}
	t = new BinaryNode<Comparable>(title1, x, NULL, NULL );
	t->height = max( height( t->left ), height( t->right ) ) + 1;
	if(putleft){
	prev->left=t;
	return;
	}
	else if(putright){
	prev->right=t;
	return;
	}
	return;

	*/
}

template <class Comparable>
void BinarySearchTree<Comparable>:: update(const Comparable & newelement, const Comparable & oldelement, BinaryNode<Comparable> * t ) const{

	while( t != NULL ){
		if( oldelement < t->titleOfNode){
			t = t->left;
		}
		else if( t->titleOfNode < oldelement) {
			t = t->right;
		}
		else if( t->titleOfNode == oldelement ){
			t->element=newelement;
			return;
		}
	}
	return;
}

/**
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( std::string title1,const Comparable & x, BinaryNode<Comparable> * & t )const{
	if( t == NULL )
		return; // Item not found; do nothing
	if( title1 < t->titleOfNode)
		remove( title1, x, t->left );
	else if( t->titleOfNode < title1)
		remove( title1, x, t->right );
	else if( t->left != NULL && t->right != NULL ){ // Two children
		t->element = findMin( t->right )->element;
		t->titleOfNode = findMin( t->right )->titleOfNode;
		remove(t->titleOfNode, t->element, t->right );
	}
	else{ // one or no children
		BinaryNode<Comparable> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}

	/*
	if( y == NULL )
	return; // Item not found; do nothing
	BinaryNode<Comparable> * t=y;
	BinaryNode<Comparable> * prev=t;
	bool delleft=false;
	bool delright=false;
	while( t != NULL && t->titleOfNode != x ){
	delleft=false;
	delright=false;
	if( x < t->titleOfNode){
	prev=t;
	t= t->left; // insert at the left or
	delleft=true;
	}
	else if( x > t->titleOfNode ){
	prev=t;
	t= t->right; // right subtree
	delright=true;
	}
	}
	if( t == NULL )
	return; // Item not found; do nothing
	else if( t->left != NULL && t->right != NULL ) // Two children
	{
	t->element = findMin( t->right )->titleOfNode;
	remove( t->titleOfNode, t->right );
	return;
	}
	else // one or no children
	{
	BinaryNode<Comparable> *oldNode = t;
	if( t->left == NULL && t->right == NULL ){
	delete oldNode;
	if(delleft){
	prev->left=NULL;
	return;
	}
	else if(delright){
	prev->right=NULL;
	return;
	}
	return;
	}
	t = ( t->left != NULL ) ? t->left : t->right;
	delete oldNode;
	return;
	}
	*/
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
	while( t != NULL )
		if( x < t->element )
			t = t->left;
		else if( t->element < x )
			t = t->right;
		else
			return t; // Match

		return NULL; // No match
}

/**
* Internal method to find an item in a subtree.
* x is item to search for.
* t is the node that roots the tree.
* Return node containing the matched item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findtitle( std::string x, BinaryNode<Comparable> *t ){
	while( t != NULL ){
		if( x < t->titleOfNode ){
			t = t->left;
		}
		else if( t->titleOfNode < x ){
			t = t->right;
		}
		else {
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
	return new BinaryNode<Comparable>(node->titleOfNode, node->element, deepcopy(node->left), deepcopy(node->right) ,node->height);
}

template <class Comparable>
void BinarySearchTree<Comparable>::BSTdisplaynode(BinaryNode<Comparable>*& t){
	if( t != NULL ){
		BSTdisplaynode( t->left );
		cout<<t->titleOfNode<<endl;
		BSTdisplaynode( t->right );
	}
}


#endif