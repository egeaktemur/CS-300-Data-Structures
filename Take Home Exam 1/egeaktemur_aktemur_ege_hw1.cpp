#include <iostream>
#include <string>
#include <vector>
#include "Stack.h"
#include "randgen.h"
#include "Doubly2dMatrix.h"
#include <fstream>  
#include <sstream>

using namespace std;
RandGen rnd;


/**
* Calculates ways that can be gone from a node
* Example output [0,1,3] where 0 is top 1 is right 2 is bottom 3 is left
* If it is used for maze generation it adds if the wall exists in the way
* If it is used for route generation it adds if the wall does not exists in the way
*/
vector<int> WaysCanGo(Stack<Node*> &visited, string application="findroute"){
	bool findroute = true;
	if ( application == "generate"){
		findroute = false;
	}
	vector<int>ways;
	Node *temp=visited.top();
	for (int i = 0; i < 4; i++){
		if(temp->data.edges[i]==false && temp->data.walls[i] == findroute){
			if(i==0 && temp->up->data.visited==false){
				ways.push_back(i);
			}
			else if(i==1 && temp->next->data.visited==false){
				ways.push_back(i);
			}
			else if(i==2 && temp->down->data.visited==false){
				ways.push_back(i);
			}
			else if(i==3 && temp->prev->data.visited==false){
				ways.push_back(i);
			}
		}
	}
	return ways;
}


/**
* If it is random it goes to random point in maze
* If it is not random it goes to given point in maze
*/
Node* MoveToStartPoint(Doubly2dMatrix Matrix,int x,int y,bool random){
	if (random){
		x = rnd.RandInt(0,x-1);
		y = rnd.RandInt(0,y-1);
	}
	Node*temp = Matrix.GetHead();
	int i=0;
	for (i=0; i < x; i++){
		temp = temp->next;
	}
	for (i=0; i < y; i++){
		temp = temp->up;
	}
	return temp;
}

void PrintToFile(Doubly2dMatrix Matrix,int mazecount,int x,int y){
	ofstream outfile ("maze_"+to_string(mazecount)+".txt");
	outfile << x <<" "<< y << endl;
	Node *temp=Matrix.GetHead();
	while(temp!=nullptr){
		Node* temp2=temp;
		while(temp2!=nullptr){
			cell data = temp2->data;
			outfile << "x="<< data.x <<" y="<< data.y <<" l="<< !data.walls[3] <<" r="<< !data.walls[1] <<" u="<< !data.walls[0] <<" d="<< !data.walls[2] << endl;
			temp2=temp2->next;
		}
		temp = temp->up;
	}
	outfile.close();
}


/**
* Moves in the given way and breaks wall accordingly if it is in Maze Generation step.
* Just moves in the given way if it is in Route Generation step.
*/
Node* MoveInWay(int way,Stack<Node*> &visited,bool Break){
	Node *temp=visited.top();
	if(way==0){
		temp->data.walls[way]=Break;
		temp->up->data.walls[2]=Break;
		temp=temp->up;
	}
	else if(way==1){
		temp->data.walls[way]=Break;
		temp->next->data.walls[3]=Break;
		temp=temp->next;
	}
	else if(way==2){
		temp->data.walls[way]=Break;
		temp->down->data.walls[0]=Break;
		temp=temp->down;
	}
	else if(way==3){
		temp->data.walls[way]=Break;
		temp->prev->data.walls[1]=Break;
		temp=temp->prev;
	}
	temp->data.visited=true;
	return temp;
}

void PrintStack(Stack<Node*> &visited,string mazeIndex,int entryX,int entryY,int exitX,int exitY){
	ofstream outfile("maze_" + mazeIndex + "_path_" +to_string(entryX) + "_" + to_string(entryY) + "_" + to_string(exitX) + "_" + to_string(exitY) + "_" + ".txt");
	Stack<Node*> visitedreverse;
	while(!visited.isEmpty()){
		visitedreverse.push(visited.topAndPop());
	}
	while(!visitedreverse.isEmpty()){
		cell data = visitedreverse.topAndPop()->data;
		outfile << data.x <<" "<< data.y << endl;
	}
	outfile.close();
}


/**
* Generates MxN maze with random walls
*/
Doubly2dMatrix CreateMaze(int mazecount,int x,int y){
	Stack<Node*> visited;
	Doubly2dMatrix Maze(x,y);
	Node*temp = MoveToStartPoint(Maze,x,y,true);// Move to random point in maze
	visited.push(temp);
	temp->data.visited = true;
	int visitedcount=1;
	while(visitedcount<x*y){// While all the nodes are not visited
		vector<int> ways = WaysCanGo(visited,"generate");// Calculate where we can go
		while(ways.size()==0){ // If we can not go anywhere backtrack until we can go somewhere
			temp = visited.topAndPop();
			ways=WaysCanGo(visited,"generate");
		}
		int way = ways[rnd.RandInt(0,ways.size()-1)]; // Calculate random way from where we can go
		temp = MoveInWay(way,visited,true); // Go to there and add
		visited.push(temp);
		visitedcount++;
	}
	PrintToFile(Maze,mazecount,x,y);
	return Maze;
}

void findPath(Doubly2dMatrix Maze,string mazeIndex,int entryX,int entryY,int exitX,int exitY){
	Stack<Node*> visited;
	Node*temp = MoveToStartPoint(Maze,entryX,entryY,false);
	visited.push(temp);
	temp->data.visited=true;
	while(temp->data.x != exitX || temp->data.y != exitY){// While not on the exit node
		vector<int> ways = WaysCanGo(visited);// Calculate where we can go
		while(ways.size() == 0){// If we can not go anywhere backtrack until we can go somewhere
			temp=visited.topAndPop();
			ways=WaysCanGo(visited);
		}
		int way = ways[rnd.RandInt(0,ways.size()-1)];// Calculate random way from where we can go
		temp = MoveInWay(way,visited,false);// Go to there and add to stack
		visited.push(temp);
	}
	PrintStack(visited,mazeIndex,entryX,entryY,exitX,exitY);
}

int main() {
	int mazeamount,x,y,i,z=0;
	cout << "Enter the number of mazes: ";
	cin >> mazeamount;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> x >> y;
	vector<Doubly2dMatrix> Mazes;
	for (int mazecount = 1; mazecount <= mazeamount; mazecount++){
		Mazes.push_back(CreateMaze(mazecount,x,y));
	}
	cout << "All mazes are generated."<<endl<<endl;
	string mazeIndex;
	int entryX,entryY,exitX,exitY;
	cout << "Enter a maze ID between 1 to "+to_string(mazeamount)+" inclusive to find a path: ";cin>>mazeIndex;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";cin>>entryX>>entryY;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";cin>>exitX>>exitY;
	Doubly2dMatrix Maze = Mazes[stoi(mazeIndex)-1]; // After all mazes are generated select the maze to start pathfind
	Maze.setallunvisited(); // Set that maze's all points unvisited
	findPath(Maze,mazeIndex,entryX,entryY,exitX,exitY);
	return 0;
}