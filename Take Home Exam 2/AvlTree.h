#ifndef AVLTREE
#define AVLTREE

template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode{
	std::string titleOfNode;
	Comparable element;
	AvlNode *left;
	AvlNode *right;
	int height;
	AvlNode(std::string title1, const Comparable & theElement,AvlNode *lt, AvlNode *rt, int h = 0 )
		: titleOfNode(title1),element( theElement ), left( lt ), right( rt ), height( h ) { }
	friend class AvlTree<Comparable>;

};

template <class Comparable>
class AvlTree{
public:
	explicit AvlTree(std::string, const Comparable & notFound );
	AvlTree( const AvlTree & rhs );
	~AvlTree( );
	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	const Comparable & find( const Comparable & x ) const;
	Comparable & findtitle(std::string x );
	bool DoesExist(std::string x );
	bool isEmpty( ) const;
	void makeEmpty( );
	void insert(std::string title1, const Comparable & x );
	void update(const Comparable & newelement , const Comparable & oldelement ) const;
	void remove(std::string title1, const Comparable & x );
	const AvlTree & operator=( const AvlTree & rhs );
	bool operator<(const AvlTree &rhs) const;
	void AVLdisplaySections();

private:
	AvlNode<Comparable> *root;
	std::string titleOfTree;
	const Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( AvlNode<Comparable> *t ) const;
	void insert( std::string title1,const Comparable & x, AvlNode<Comparable> * & t ) const;
	void update(const Comparable & newelement , const Comparable & oldelement, AvlNode<Comparable> * t) const;
	void remove(std::string title1,const Comparable & x, AvlNode<Comparable> * & t ) const;
	AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
	AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
	AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> *t )const;
	AvlNode<Comparable> * findtitle(std::string x, AvlNode<Comparable> *t );
	void makeEmpty( AvlNode<Comparable> * & t ) const;
	int height( AvlNode<Comparable> *t ) const;
	int max( int lhs, int rhs ) const;
	void rotateWithleft( AvlNode<Comparable> * & k2 ) const;
	void rotateWithright( AvlNode<Comparable> * & k1 ) const;
	void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
	void doubleWithright( AvlNode<Comparable> * & k1 ) const;
	AvlNode<Comparable>* deepcopy(AvlNode<Comparable>* node)const;
	void AVLdisplaynode(AvlNode<Comparable>*& t);
};

/**
* Construct the tree.
*/
template <class Comparable>
AvlTree<Comparable>::AvlTree(std::string title1,const Comparable & notFound ) :titleOfTree(title1),ITEM_NOT_FOUND( notFound ), root( NULL ){}

/**
* Copy constructor.
*/
template <class Comparable>
AvlTree<Comparable>::AvlTree( const AvlTree<Comparable> & rhs ) :root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ){
	*this=rhs;
	this->titleOfTree=rhs.titleOfTree;
}

/**
* Destructor for the tree.
*/
template <class Comparable>
AvlTree<Comparable>::~AvlTree( ){
	makeEmpty( );
}

/**
* Find the smallest item in the tree.
*/
template <class Comparable>
const Comparable & AvlTree<Comparable>::findMin( ) const{
	if(root==NULL){
		return ITEM_NOT_FOUND;
	}
	return elementAt( findMin( root ) );
}

/**
* Find the smallest item in the tree.
*/
template <class Comparable>
const Comparable & AvlTree<Comparable>::findMax( ) const{
	if(root==NULL){
		return ITEM_NOT_FOUND;
	}
	return elementAt( findMax( root ) );
} 

/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
const Comparable & AvlTree<Comparable>::find( const Comparable & x ) const{
	if(root==NULL){
		return ITEM_NOT_FOUND;
	}
	return elementAt( find( x, root ) );
}

/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
Comparable & AvlTree<Comparable>::findtitle(std::string x ){
	return (findtitle( x, root ))->element;
}

/**
* Check if given item exists
*/
template <class Comparable>
bool AvlTree<Comparable>::DoesExist(std::string x ){
	bool result = findtitle( x, root ) != NULL;
	return result;
}

/**
* Check if given tree is empty
*/
template <class Comparable>
bool AvlTree<Comparable>::isEmpty( ) const{
	if( root != NULL ){
		return true
	}
	return false;
}

/**
* Make the tree logically empty.
*/
template <class Comparable>
void AvlTree<Comparable>::makeEmpty( ){
	makeEmpty(root );
}

/**
* Insert given item to tree.
*/
template <class Comparable>
void AvlTree<Comparable>::insert(std::string title1, const Comparable & x) {
	insert( title1,x, root);
}

template <class Comparable>
void AvlTree<Comparable>::remove(std::string title1, const Comparable & x) {
	remove( title1,x, root);
}

template <class Comparable>
void AvlTree<Comparable>:: update(const Comparable & newelement, const Comparable & oldelement) const{
	update(newelement,oldelement,root);
}

//const AvlTree & operator=( const AvlTree & rhs );
template <class Comparable>
const AvlTree<Comparable> & AvlTree<Comparable>::operator=( const AvlTree<Comparable> & rhs ){
	root = deepcopy(rhs.root);
	titleOfTree = rhs.titleOfTree;
	return *this;
}

template <class Comparable>
bool AvlTree<Comparable>::operator<(const AvlTree<Comparable> &rhs) const{
	return this->root->element < rhs.root->element;
}


template <class Comparable>
void AvlTree<Comparable>::AVLdisplaySections(){
	cout <<endl<<"*****"<<endl;
	AVLdisplaynode(root);
	cout <<"*****"<<endl;
}

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
const Comparable & AvlTree<Comparable>::elementAt( AvlNode<Comparable> *t ) const{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
void AvlTree<Comparable>::insert(std::string title1, const Comparable & x, AvlNode<Comparable> * & t ) const{
	if ( t == NULL )
		t = new AvlNode<Comparable>( title1,x, NULL, NULL );
	else if ( title1 < t->titleOfNode ) {
		// X should be inserted to the left tree!
		insert( title1,x, t->left );
		// Check if the left tree is out of balance (left subtree grew in height!)
		if ( height( t->left ) - height( t->right ) == 2 )
			if ( title1 < t->left->titleOfNode ) // X was inserted to the left-left subtree!
				rotateWithleft( t );
			else // X was inserted to the left-right subtree!
				doubleWithLeftChild( t );
	}
	else if( t->titleOfNode < title1 ){ // Otherwise X is inserted to the right subtree
		insert( title1,x, t->right );
		if ( height( t->right ) - height( t->left ) == 2 )
			// height of the right subtree increased
				if ( t->right->titleOfNode < title1 )
					// X was inserted to right-right subtree
						rotateWithright( t );
				else // X was inserted to right-left subtree
					doubleWithright( t );
	}
	
	// update the height the node
	t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <class Comparable>
void AvlTree<Comparable>::remove(std::string title1, const Comparable & x, AvlNode<Comparable> * & t ) const{
	if( t == NULL )
		return; // Item not found; do nothing
	if( title1 < t->titleOfNode){
		remove(title1,x,t->left);
	}
	else if( title1 > t->titleOfNode ){
		remove(title1,x,t->right);
	}
	else if( title1 == t->titleOfNode ){
		AvlNode<Comparable> *temp;
		if( t->right == NULL && t->left == NULL){
			t = NULL;
			return;
		}
		else if( (t->right != NULL && t->left == NULL)){
			temp=t;
			t=t->right;
			free(temp);
		}
		else if( (t->right == NULL && t->left != NULL)){
			temp=t;
			t=t->left;
			free(temp);
		}
		else if( (t->right != NULL && t->left != NULL)){
			AvlNode<Comparable> * temp = findMin(root->right);
			t->titleOfNode = temp->titleOfNode;
			t->element = temp->element;
			remove(temp->titleOfNode,temp->element,t->right);
		}
	}
	t->height = max( height( t->left ), height( t->right ) ) + 1;

	if (height(t->left)-height(t->right) > 1 && height(t->left->left)-height(t->left->right)>=0){
		rotateWithleft(t);
	}

    else if (height(t->left)-height(t->right) > 1 && height(t->left->left)-height(t->left->right) < 0){
		doubleWithLeftChild( t );
    }

    else if (height(t->left)-height(t->right) < -1 && height(t->right->left)-height(t->right->right) <= 0) {
		rotateWithright(t);
	}

    else if (height(t->left)-height(t->right) < -1 && height(t->right->left)-height(t->right->right) > 0) {
		doubleWithright( t );
    }
}

template <class Comparable>
void AvlTree<Comparable>:: update(const Comparable & newelement, const Comparable & oldelement, AvlNode<Comparable> *t ) const{
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
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::findMin( AvlNode<Comparable> *t ) const {
	if( t == NULL )
		return NULL;
	if( t->left == NULL )
		return t;
	return findMin( t->left );
}

/**
* Internal method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::findMax( AvlNode<Comparable> *t )const{
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
AvlNode<Comparable> * AvlTree<Comparable>:: find( const Comparable & x, AvlNode<Comparable> *t ) const{
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
AvlNode<Comparable> * AvlTree<Comparable>:: findtitle( std::string x, AvlNode<Comparable> *t ){
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
void AvlTree<Comparable>::makeEmpty( AvlNode<Comparable> * & t ) const{
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
int AvlTree<Comparable>::height( AvlNode<Comparable> *t )const{
	if (t == NULL)
		return -1;
	return t->height;
}

/**
* Return maximum of lhs and rhs.
*/
template <class Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs )const{
	if (lhs > rhs)
		return lhs;
	return rhs;
}

/**
* Rotate binary tree node with left child.
* For AVL trees, this is a single rotation for case 1.
* Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::rotateWithleft(AvlNode<Comparable> * & k2 ) const{
	AvlNode<Comparable> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}

/**
* Rotate binary tree node with right child.
* For AVL trees, this is a single rotation for case 4.
* Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::rotateWithright( AvlNode<Comparable> * & k1 ) const{
	AvlNode<Comparable> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
	k2->height = max( height( k2->right ), k1->height ) + 1;
	k1 = k2;
}

/**
* Double rotate binary tree node: first left child.
* with its right child; then node k3 with new left child.
* For AVL trees, this is a double rotation for case 2.
* Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const{
	rotateWithright( k3->left );
	rotateWithleft( k3 );

}

/**
* Double rotate binary tree node: first right child.
* with its left child; then node k1 with new right child.
* For AVL trees, this is a double rotation for case 3.
* Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::doubleWithright( AvlNode<Comparable> * & k1 )const{
	rotateWithleft( k1->right );
	rotateWithright( k1 );
}



template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::deepcopy(AvlNode<Comparable>* node)const{
	if (node == NULL){
		return NULL;
	}
	return new AvlNode<Comparable>(node->titleOfNode, node->element, deepcopy(node->left), deepcopy(node->right) ,node->height);
}

template <class Comparable>
void AvlTree<Comparable>::AVLdisplaynode(AvlNode<Comparable>*& t){
	if( t != NULL ){
		AVLdisplaynode( t->left );
		cout<<t->titleOfNode<<endl;
		AVLdisplaynode( t->right );
	}
}

#endif
/*
template <class Comparable>
void AvlTree<Comparable>::insert(std::string title1, const Comparable & x, AvlNode<Comparable> * & t ) const{
if ( t == NULL )
t = new AvlNode<Comparable>( title1,x, NULL, NULL );
else if ( x < t->element ) {
// X should be inserted to the left tree!
insert( title1,x, t->left );
// Check if the left tree is out of balance (left subtree grew in height!)
if ( height( t->left ) - height( t->right ) == 2 )
if ( x < t->left->element ) // X was inserted to the left-left subtree!
rotateWithLeftChild( t );
else // X was inserted to the left-right subtree!
doubleWithLeftChild( t );
}
else if( t->element < x ){ // Otherwise X is inserted to the right subtree
insert( title1,x, t->right );
if ( height( t->right ) - height( t->left ) == 2 )
// height of the right subtree increased
if ( t->right->element < x )
// X was inserted to right-right subtree
rotateWithright( t );
else // X was inserted to right-left subtree
doubleWithright( t );
}
else; // Duplicate; do nothing
// update the height the node
t->height = max( height( t->left ), height( t->right ) ) + 1;
}
*/
/*
template <class Comparable>
void AvlTree<Comparable>::insertTree(std::string title1, const Comparable & x, AvlNode<AvlTree<Comparable>> * & t ) const{
if ( t == NULL )
t = new AvlNode<Comparable>( x, NULL, NULL );
else if ( title1 < t->element.title) {
// X should be inserted to the left tree!
insert( x, t->left );
// Check if the left tree is out of balance (left subtree grew in height!)
if ( height( t->left ) - height( t->right ) == 2 )
if ( title1, < t->left->element.title ) // X was inserted to the left-left subtree!
rotateWithLeftChild( t );
else // X was inserted to the left-right subtree!
doubleWithLeftChild( t );
}
else if( t->element.title < title1 ){ // Otherwise X is inserted to the right subtree
insert( x, t->right );
if ( height( t->right ) - height( t->left ) == 2 )
// height of the right subtree increased
if ( t->right->element.title < title1)
// X was inserted to right-right subtree
rotateWithright( t );
else // X was inserted to right-left subtree
doubleWithright( t );
}
else; // Duplicate; do nothing
// update the height the node
t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <class Comparable>
void AvlTree<Comparable>::insertTree(std::string title1, const Comparable & x) {
insertTree(title1, x, root);
}
*/