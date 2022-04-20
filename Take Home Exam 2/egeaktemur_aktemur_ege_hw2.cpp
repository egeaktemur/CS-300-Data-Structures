#pragma comment(linker, "/STACK:300000000")
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include "AvlTree.h"
#include "BinarySearchTree.h"

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

template <class Comparable>
void ConstructNotebooks(AvlTree<AvlTree<Comparable>> &AVL,BinarySearchTree<BinarySearchTree<Comparable>> &BST){
	ifstream fileAVL = GetFile("data.txt");
	string lineAVL,titleOfSectionAVL,titleOfItemAVL,itemAVL;
	ifstream fileBST = GetFile("data.txt");
	string lineBST,titleOfSectionBST,titleOfItemBST,itemBST;
	bool firsttime = true;
	while (getline(fileAVL,lineAVL)&&getline(fileBST,lineBST)){ 
		if(firsttime){
			titleOfSectionAVL=lineAVL;
			titleOfSectionBST=lineBST;
			firsttime = false;
		}

		AvlTree<string> AVL2 = AvlTree<string>(titleOfSectionAVL,"");
		auto begin = std::chrono::high_resolution_clock::now();
		while(getline(fileAVL,lineAVL) && lineAVL.substr(0,1) == "-"){
			lineAVL=lineAVL.substr(1,-1);
			titleOfItemAVL=lineAVL.substr(0,lineAVL.find("-"));
			itemAVL=lineAVL.substr(lineAVL.find("-")+1,-1);
			(AVL2).insert(titleOfItemAVL,itemAVL);
		}

		AVL.insert(titleOfSectionAVL,AVL2);
		auto end = std::chrono::high_resolution_clock::now();
		long long timer = (end-begin).count()/1000.0;
		cout << "Section \""<<titleOfSectionAVL<<"\" has been inserted into the AVL notebook."<<endl;
		cout << "[AVL] Elapsed time: "<<timer<<" microseconds"<<endl;;
		titleOfSectionAVL=lineAVL;
		BinarySearchTree<string> BST2 = BinarySearchTree<string>(titleOfSectionBST,"");
		begin = std::chrono::high_resolution_clock::now();
		while(getline(fileBST,lineBST) && lineBST.substr(0,1) == "-"){
			lineBST=lineBST.substr(1,-1);
			titleOfItemBST=lineBST.substr(0,lineBST.find("-"));
			itemBST=lineBST.substr(lineBST.find("-")+1,-1);
			(BST2).insert(titleOfItemBST,itemBST);
		}
		BST.insert(titleOfSectionBST,BST2);
		end = std::chrono::high_resolution_clock::now();
		timer = (end-begin).count()/1000.0;
		cout << "Section \""<<titleOfSectionBST<<"\" has been inserted into the BST notebook."<<endl;
		cout << "[BST] Elapsed time: "<<timer<<" microseconds"<<endl;;
		titleOfSectionBST=lineBST;
		cout << endl;
	}
	fileAVL.close();
	fileBST.close();
}

int main(){

	AvlTree<string> DummyAVL("","");
	AvlTree<AvlTree<string>> AVL("Notebook",DummyAVL);

	BinarySearchTree<string> DummyBST("","");
	BinarySearchTree<BinarySearchTree<string>> BST("Notebook",DummyBST);
	ConstructNotebooks(AVL,BST);
	auto begin = std::chrono::high_resolution_clock::now();
	auto endtime = std::chrono::high_resolution_clock::now();
	long long timer;

	

	string section;
	int option=0; 
	while (option!=6){ 
		option=0; 
		cout<<"MENU"<<endl 
			<<"Please enter an input between [1 - 6]:"<<endl 
			<<"1- Display the sections [AVL]"<<endl 
			<<"2- Display the sections [BST]"<<endl 
			<<"3- Select a section"<<endl 
			<<"4- Add new section"<<endl 
			<<"5- Delete a section"<<endl 
			<<"6- Exit"<<endl << endl; 
		cout << "Input: "; 
		cin >> option; 
		if (option == 1){
			AVL.AVLdisplaySections();
		}
		else if (option == 2){
			BST.BSTdisplaySections();
		}

		else if (option == 3){
			cout<<"Enter the title of the section: ";
			section = getinput();
			bool found = false;
			int option2=0; 
			if (AVL.DoesExist(section)) {
				found = true;
				cout<<"Selected section -> "<<section<<endl;
				cout<<"Please enter an input between [1 - 7]:"<<endl 
					<<"1- Display the items [AVL]"<<endl 
					<<"2- Display the items [BST]"<<endl
					<<"3- Display the information of a item"<<endl
					<<"4- Add new item"<<endl
					<<"5- Update the information of a item"<<endl
					<<"6- Delete an item"<<endl
					<<"7- Return to main menu"<<endl;
				AvlTree<string> & AVL2 = AVL.findtitle(section);
				BinarySearchTree<string> & BST2 = BST.findtitle(section);
				bool end = false;
				while(option2!=7){
					cout << "Input: "; 
					cin >>option2;
					if(option2==1){
						AVL2.AVLdisplaySections();
					}
					else if(option2==2){
						BST2.BSTdisplaySections();
					}
					else if(option2==3){
						cout << "Enter the title of the item: ";
						string item = getinput();
						begin = std::chrono::high_resolution_clock::now();
						bool exist =false;
						if(AVL2.DoesExist(item)) {
							item=AVL2.findtitle(item);
							exist=true;
						}
						endtime = std::chrono::high_resolution_clock::now();
						timer = (endtime-begin).count()/1000.0;
						cout << "[AVL] Elapsed time: "<<timer<<" microseconds"<<endl;
						begin = std::chrono::high_resolution_clock::now();
						if(BST2.DoesExist(item)) {
							item = BST2.findtitle(item);
							exist=true;
						}
						endtime = std::chrono::high_resolution_clock::now();
						timer = (endtime-begin).count()/1000.0;
						cout << "[BST] Elapsed time: "<<timer<<" microseconds"<<endl;
						if(!exist){
							cout << "Invalid title!"<<endl;
						}
						else{
							cout << item <<endl;
						}
					}
					else if(option2==4){
						cout << "Enter a title for the item: ";
						string titleOfItem = getinput();

						if (AVL2.DoesExist(titleOfItem)) {
							cout << "Item \""<<titleOfItem<<"\" already exists in the \""<<section<<"\"."<<endl;
						}
						else{
							cout << "Enter a description for the item: ";
							string descriptionOfTitle = getinput();

							begin = std::chrono::high_resolution_clock::now();
							AVL2.insert(titleOfItem,descriptionOfTitle);
							endtime = std::chrono::high_resolution_clock::now();
							timer = (endtime-begin).count()/1000.0;
							cout << "[AVL] Elapsed time: "<<timer<<" microseconds"<<endl;

							begin = std::chrono::high_resolution_clock::now();
							BST2.insert(titleOfItem,descriptionOfTitle);
							endtime = std::chrono::high_resolution_clock::now();
							timer = (endtime-begin).count()/1000.0;
							cout << "[BST] Elapsed time: "<<timer<<" microseconds"<<endl;

							cout << "The new item \""<<titleOfItem<<"\" has been inserted."<<endl;
						}
					}
					else if(option2==5){
						cout << "Enter the title of the item: ";
						string oldelement = getinput();
						bool exist=true;
						begin = std::chrono::high_resolution_clock::now();
						if (!AVL2.DoesExist(oldelement)) {
							exist=false;
						}
						endtime = std::chrono::high_resolution_clock::now();
						timer = (endtime-begin).count()/1000.0;
						cout << "[AVL] Elapsed time: "<<timer<<" microseconds"<<endl;

						begin = std::chrono::high_resolution_clock::now();
						if (!BST2.DoesExist(oldelement)) {
							exist=false;
						}
						endtime = std::chrono::high_resolution_clock::now();
						timer = (endtime-begin).count()/1000.0;
						cout << "[BST] Elapsed time: "<<timer<<" microseconds"<<endl;

						if(exist){
							cout << "Enter the new information: ";
							string newelement = getinput();
							AVL2.update(newelement,oldelement);
							BST2.update(newelement,oldelement);
							cout << "The content "<<oldelement<<" has been updated."<<endl;
						}
						else{
							cout << "Item \""<<oldelement<<"\" does not exist in the \""<<section<<"\"."<<endl;
						}
					}
					else if(option2==6){
						cout << "Enter a title for the item: ";
						string element= getinput();
						if (!AVL2.DoesExist(element)) {
							cout << "Item \""<<element<<"\" does not exist in the \""<<section<<"\"."<<endl;
						}
						else{
							begin = std::chrono::high_resolution_clock::now();
							AVL2.remove(element,AVL2.findtitle(element));
							endtime = std::chrono::high_resolution_clock::now();
							timer = (endtime-begin).count()/1000.0;
							cout << "[AVL] Elapsed time: "<<timer<<" microseconds"<<endl;

							begin = std::chrono::high_resolution_clock::now();
							BST2.remove(element,BST2.findtitle(element));
							endtime = std::chrono::high_resolution_clock::now();
							timer = (endtime-begin).count()/1000.0;
							cout << "[BST] Elapsed time: "<<timer<<" microseconds"<<endl;

							cout << "The item \""<<element<<"\" has been deleted."<<endl;
						}
					}
					else if(option2!=7){
						cout << "Invalid option"<<endl;
					}
					cout<<endl;
				}
			}
			if(!found){
				cout << "Invalid title!"<<endl;
			}
		}
		else if (option == 4){
			cout << "Enter a title for the section: ";
			string titleOfSection = getinput();
			if (!AVL.DoesExist(titleOfSection)) {
				begin = std::chrono::high_resolution_clock::now();
				AvlTree<string> AVL2 = AvlTree<string>(titleOfSection,"");
				AVL.insert(titleOfSection,AVL2);
				BinarySearchTree<string> BST2 = BinarySearchTree<string>(titleOfSection,"");
				endtime = std::chrono::high_resolution_clock::now();
				timer = (endtime-begin).count()/1000.0;
				cout << "[AVL] Elapsed time: "<<timer<<" microseconds"<<endl;

				begin = std::chrono::high_resolution_clock::now();
				BST.insert(titleOfSection,BST2);
				endtime = std::chrono::high_resolution_clock::now();
				timer = (endtime-begin).count()/1000.0;
				cout << "[BST] Elapsed time: "<<timer<<" microseconds"<<endl;
				cout << "The new section \""<<titleOfSection<<"\" has been inserted."<<endl;
			}
			else{
				cout << "Section \""<<titleOfSection<<"\" already exists."<<endl;
			}
		}

		else if (option == 5){
			cout << "Enter a title for the item: ";
			string element = getinput();
			if (AVL.DoesExist(element)) {
				begin = std::chrono::high_resolution_clock::now();
				AVL.remove(element,AVL.findtitle(element));
				endtime = std::chrono::high_resolution_clock::now();
				timer = (endtime-begin).count()/1000.0;
				cout << "[AVL] Elapsed time: "<<timer<<" microseconds"<<endl;

				begin = std::chrono::high_resolution_clock::now();
				BST.remove(element,BST.findtitle(element));
				endtime = std::chrono::high_resolution_clock::now();
				timer = (endtime-begin).count()/1000.0;
				cout << "[BST] Elapsed time: "<<timer<<" microseconds"<<endl;
				cout << "The section has been deleted."<<endl;
			}
			else{
				cout << "Section \""<<element<<"\" does not exist."<<endl;
			}
		}
		cout<<endl;
	}
	system("pause");
	return 0;
}