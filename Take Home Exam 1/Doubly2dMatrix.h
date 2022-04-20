#ifndef DOUBLY2DMATRIX_H
#define DOUBLY2DMATRIX_H
#include <vector>
using namespace std;
struct cell{
	int x;
	int y;
	vector<bool> walls;
	vector<bool> edges;
	bool visited;
	cell::cell (int x1,int y1,vector<bool> walls1,vector<bool> edges1,bool v =false): 
		x(x1),y(y1),visited(v){
			for(int i=0; i<4; i++){
				walls.push_back(walls1[i]);
				edges.push_back(edges1[i]);
			}
	}
};

struct Node {
	cell data;
	Node* next;
	Node* prev;
	Node* up;
	Node* down;
	Node( cell data, Node* next = nullptr,Node* prev=nullptr,Node* up=nullptr,Node* down=nullptr )
		: data( data ), next( next ),prev(prev),up(up),down(down) { }
};

class Doubly2dMatrix{
public:
	Doubly2dMatrix(){ head=nullptr;}
	Node * GetHead(){ return head;}
	void setallunvisited();
	Doubly2dMatrix(int x,int y);
private:
	Node * head;
};

#endif

