#include "Doubly2dMatrix.h"
#include <vector>
#include <string>

vector<bool> CreateVector(bool arr[]){
	vector<bool> arr2;
	for(int i=0; i<4; i++){
		arr2.push_back(arr[i]);
	}
	return arr2;
}


/**
* Creates MxN doubly 2d linked list
*/
Doubly2dMatrix::Doubly2dMatrix(int y, int x){
	Node* temp = nullptr;
	Node* row  = nullptr;
	bool allfalse4a[4] = {0,0,0,0}; vector<bool> allfalse4 = CreateVector(allfalse4a); 
	bool fortopa[4]    = {1,0,0,0}; vector<bool> fortop    = CreateVector(fortopa);
	bool forrighta[4]  = {0,1,0,0}; vector<bool> forright  = CreateVector(forrighta);
	bool forbottoma[4] = {0,0,1,0}; vector<bool> forbottom = CreateVector(forbottoma);
	bool forlefta[4]   = {0,0,0,1}; vector<bool> forleft   = CreateVector(forlefta); // Creating needed vectors
	bool forltopa[4]   = {1,0,0,1}; vector<bool> forltop   = CreateVector(forltopa);
	bool forrtopa[4]   = {1,1,0,0}; vector<bool> forrtop   = CreateVector(forrtopa);
	bool forrbota[4]   = {0,1,1,0}; vector<bool> forrbot   = CreateVector(forrbota);
	bool forlbota[4]   = {0,0,1,1}; vector<bool> forlbot   = CreateVector(forlbota);
	cell current(0,0,allfalse4,forltop);
	for (int i = 0; i < y; i++){
		int j = 0;
		if( i > 0){ // If in left edge but not head (left bottom)
			current = cell(0,i,allfalse4,forleft);
			if(i == y-1){ // If in left top
				current = cell(0,i,allfalse4,forltop);
			}
			row->up = new Node(current,nullptr,nullptr,nullptr,row);
			temp = row->up;
			row  = row->up;
			j++;
		}
		for (;j < x; j++){
			if(i == 0 && j == 0){// create head
				current = cell(j,i,allfalse4,forlbot);
				head = new Node(current);
				row = head;
				temp = head;
			}
			else {
				if(i == y-1){// top edge
					if(j == x-1){ current = cell(j,i,allfalse4,forrtop);}// right top
					else { current = cell(j,i,allfalse4,fortop);}
					temp->next = new Node(current,nullptr,temp,nullptr,nullptr);
					temp->down->next->up = temp->next;
					temp->next->down = temp->down->next;
				}
				else if(i == 0){// bottom edge
					if(j == x-1){current = cell(j,i,allfalse4,forrbot);} // right bottom
					else{ current = cell(j,i,allfalse4,forbottom);}
					temp->next = new Node(current,nullptr,temp,nullptr,nullptr);
				}
				else {// not edge or right edge
					if(j == x-1) {current = cell(j,i,allfalse4,forright);}// right edge
					else {current = cell(j,i,allfalse4,allfalse4);}
					temp->next = new Node(current,nullptr,temp,nullptr,nullptr);
					temp->down->next->up = temp->next;
					temp->next->down = temp->down->next;
				}
				temp = temp->next;
			}
		}

	}
}

/**
* Reset the maze for pathfind
*/
void Doubly2dMatrix::setallunvisited(){ 
	Node* temp=head;
	int count=0;
	while(temp!=nullptr){
		Node* temp2=temp;
		while(temp2!=nullptr){
			temp2->data.visited=false;
			temp2=temp2->next;
		}
		temp=temp->up;
	}
}
