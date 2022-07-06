#pragma comment(linker, "/STACK:300000000")
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include "items.h"
#include "BinarySearchTree.h"
#include "HashTable.h"

using namespace std;

const int find(HashTable<WordItem>& Hashtable, const WordItem & x , const string & DocumentName){
	int collisionNum = 0;
	WordItem & v = Hashtable.getelement(x);
	if(!Hashtable.doesexist(x)){
		return -1;
	}
	for(unsigned int i = 0; i< v.list.size();i++){
		if(v.list[i].documentName == DocumentName){
			return v.list[i].count;
		}
	}
	return -1;
}

const int find(BinarySearchTree<WordItem>& BST, const WordItem & x , const string & DocumentName){
	BinaryNode<WordItem> * elem = BST.returnaddress(x);
	if(elem==NULL){
		return -1;
	}
	WordItem & v = BST.getelement(elem);
	for(unsigned int i = 0; i< v.list.size();i++){
		if(v.list[i].documentName == DocumentName){
			return v.list[i].count;
		}
	}
	return -1;
}

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

int main(){
	cout << "Enter number of input files: ";
	int inputamount;
	cin >> inputamount;
	vector<string> inputs;
	for (int i = 0; i < inputamount; i++){
		cout <<"Enter "<< to_string(i+1) <<". file name: ";
		string input;
		cin >> input;
		inputs.push_back(input);
	}
	WordItem temp = WordItem();
	HashTable<WordItem> Hashtable(temp,53);
	for (int i = 0; i < inputamount; i++){
		ifstream file = GetFile(inputs[i]);
		string line,word;
		while (getline(file,line)){ 
			for(unsigned int lettercount=0;lettercount<line.size();lettercount++){
				char letter = tolower(line.at(lettercount));
				if( ( (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') )){
					word += letter;
				}
				else{
					if(word !=""){
						WordItem item(word,inputs[i]);
						if(!Hashtable.doesexist(item)){
							Hashtable.insert(item);
						}
						else{
							WordItem & v = Hashtable.getelement(item);
							bool found=false;
							for(unsigned int f = 0; f< v.list.size();f++){
								if(v.list[f].documentName == inputs[i]){
									v.list[f].count = v.list[f].count+1;
									found=true;
								}
							}
							if(!found){
								v.list.push_back(DocumentItem(inputs[i],1));
							}
						}
						word = "";
					}
				}
			}
			if(word !=""){
				WordItem item(word,inputs[i]);
				if(!Hashtable.doesexist(item)){
					Hashtable.insert(item);
				}
				else{
					WordItem & v = Hashtable.getelement(item);
					bool found=false;
					for(unsigned int f = 0; f< v.list.size();f++){
						if(v.list[f].documentName == inputs[i]){
							v.list[f].count = v.list[f].count+1;
							found=true;
						}
					}
					if(!found){
						v.list.push_back(DocumentItem(inputs[i],1));
					}
				}
				word = "";
			}
		}
		file.close();
	}
	Hashtable.statistics();
	temp = WordItem();
	BinarySearchTree<WordItem> BST(temp);
	for (int i = 0; i < inputamount; i++){
		ifstream file = GetFile(inputs[i]);
		string line,word;
		int a=0;
		while (getline(file,line)){ 
			for(unsigned int lettercount=0;lettercount<line.size();lettercount++){
				char letter = tolower(line.at(lettercount));
				if( ( (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') )){
					word += letter;
				}
				else{
					if(word !=""){
						WordItem item(word,inputs[i]);
						BinaryNode<WordItem> * elem = BST.returnaddress(item);
						if(elem == NULL){
							BST.insert(item);
						}
						else{
							WordItem & v2 = BST.getelement(elem);
							bool found=false;
							for(unsigned int f = 0; f< v2.list.size();f++){
								if(v2.list[f].documentName == inputs[i]){
									v2.list[f].count++;
									found=true;
								}
							}
							if(!found){
								v2.list.push_back(DocumentItem(inputs[i],1));
							}
						}
						word = "";
					}
				}
			}
			if(word !=""){
				WordItem item(word,inputs[i]);
				BinaryNode<WordItem> * elem = BST.returnaddress(item);
				if(elem == NULL){
					BST.insert(item);
				}
				else{
					WordItem & v2 = BST.getelement(elem);
					bool found=false;
					int s2=v2.list.size();
					for(unsigned int f = 0; f< s2;f++){
						if(v2.list[f].documentName == inputs[i]){
							v2.list[f].count++;
							found=true;
						}
					}
					if(!found){
						v2.list.push_back(DocumentItem(inputs[i],1));
					}
				}
				word = "";
			}
		}
		file.close();
	}
	cout << "Enter queried words in one line: ";
	string input= getinput();
	int k =100;
	/////////////////////HASHTABLE PRINT/////////////////////////////////////
	string word;
	vector<vector<int>> outputHT(inputamount);
	vector<vector<bool>> Print(inputamount);
	vector<string> wordsHT;
	for (int i = 0; i < inputamount; i++){
		for(unsigned int lettercount=0;lettercount<input.size();lettercount++){
			char letter = tolower(input.at(lettercount));
			if( ( (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') )){
				word += letter;
			}
			else{
				WordItem Item(word,inputs[i]);
				int count = find(Hashtable,Item,inputs[i]);
				if(count==-1){
					Print[i].push_back(false);
				}
				else{
					outputHT[i].push_back(count);
					Print[i].push_back(true);
				}
				wordsHT.push_back(word);
				word = "";
			}
		}
		if(word !=""){
			WordItem Item(word,inputs[i]);
			int count = find(Hashtable,Item,inputs[i]);
			if(count==-1){
				Print[i].push_back(false);
			}
			else{
				outputHT[i].push_back(count);	
				Print[i].push_back(true);
			}
			wordsHT.push_back(word);
			word = "";
		}
	}
	vector<bool> foundall(inputamount);
	for (int x = 0; x < inputamount; x++){
		bool found =true;
		for (int i1 = 0; i1 < Print[x].size(); i1++){
			if(Print[x][i1] == false){
				found=false;
			}
		}
		foundall.push_back(found);
		if(found){
			cout << "in Document "<<inputs[x];
			for (int y=0;y< wordsHT.size()/inputamount;y++){
				cout <<", "<<wordsHT[y]<<" found "<<outputHT[x][y]<<" times";
			}
			cout <<"."<<endl;
		}
	}
	bool found =false;
	for (int i1 = 0; i1 < foundall.size(); i1++){
		if(foundall[i1] == true){
			found=true;
		}
	}
	if(!found){
		cout << "No document contains the given query"<<endl;
	}
	/////////////////////BINARYSEARCHTREE PRINT/////////////////////////////////////
	word="";
	vector<vector<int>> outputBST(inputamount);
	vector<vector<bool>> PrintBST(inputamount);
	vector<string> wordsBST;
	for (int i = 0; i < inputamount; i++){
		for(unsigned int lettercount=0;lettercount<input.size();lettercount++){
			char letter = tolower(input.at(lettercount));
			if( ( (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') )){
				word += letter;
			}
			else{
				WordItem Item(word,inputs[i]);
				int count = find(BST,Item,inputs[i]);
				if(count==-1){
					PrintBST[i].push_back(false);
				}
				else{
					outputBST[i].push_back(count);
					PrintBST[i].push_back(true);
				}
				wordsBST.push_back(word);
				word = "";
			}
		}
		if(word !=""){
			WordItem Item(word,inputs[i]);
			int count = find(BST,Item,inputs[i]);
			if(count==-1){
				PrintBST[i].push_back(false);
			}
			else{
				outputBST[i].push_back(count);	
				PrintBST[i].push_back(true);
			}
			wordsBST.push_back(word);
			word = "";
		}
	}
	foundall.clear();
	for (int x = 0; x < inputamount; x++){
		bool found =true;
		for (int i1 = 0; i1 < Print[x].size(); i1++){
			if(Print[x][i1] == false){
				found=false;
			}
		}
		foundall.push_back(found);
		if(found){
			cout << "in Document "<<inputs[x];
			for (int y=0;y< wordsBST.size()/inputamount;y++){
				cout <<", "<<wordsBST[y]<<" found "<<outputBST[x][y]<<" times";
			}
			cout <<"."<<endl;
		}
	}
	found =false;
	for (int i1 = 0; i1 < foundall.size(); i1++){
		if(foundall[i1] == true){
			found=true;
		}
	}
	if(!found){
		cout << "No document contains the given query"<<endl;
	}
	////////////HASHTABLE TIME////////////////////////////////////////////////////////////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	for (int j = 0; j < k; j++){
		string word;
		vector<vector<int>> outputHT(inputamount);
		vector<vector<bool>> Print(inputamount);
		vector<string> wordsHT;
		for (int i = 0; i < inputamount; i++){
			for(unsigned int lettercount=0;lettercount<input.size();lettercount++){
				char letter = tolower(input.at(lettercount));
				if( ( (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') )){
					word += letter;
				}
				else{
					WordItem Item(word,inputs[i]);
					int count = find(Hashtable,Item,inputs[i]);
					if(count==-1){
						Print[i].push_back(false);
					}
					else{
						outputHT[i].push_back(count);
						Print[i].push_back(true);
					}
					wordsHT.push_back(word);
					word = "";
				}
			}
			if(word !=""){
				WordItem Item(word,inputs[i]);
				int count = find(Hashtable,Item,inputs[i]);
				if(count==-1){
					Print[i].push_back(false);
				}
				else{
					outputHT[i].push_back(count);	
					Print[i].push_back(true);
				}
				wordsHT.push_back(word);
				word = "";
			}
		}
	}
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -start);
	///////////////////BINARYSEARCHTREE TIME/////////////////////////////////////////////////////////////////////////////
	start = std::chrono::high_resolution_clock::now();
	for (int j = 0; j < k; j++){
		word="";
		vector<vector<int>> outputBST(inputamount);
		vector<vector<bool>> Print(inputamount);
		vector<string> wordsBST;
		for (int i = 0; i < inputamount; i++){
			for(unsigned int lettercount=0;lettercount<input.size();lettercount++){
				char letter = tolower(input.at(lettercount));
				if( ( (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') )){
					word += letter;
				}
				else{
					WordItem Item(word,inputs[i]);
					int count = find(BST,Item,inputs[i]);
					if(count==-1){
						Print[i].push_back(false);
					}
					else{
						outputBST[i].push_back(count);
						Print[i].push_back(true);
					}
					wordsBST.push_back(word);
					word = "";
				}
			}
			if(word !=""){
				WordItem Item(word,inputs[i]);
				int count = find(BST,Item,inputs[i]);
				if(count==-1){
					Print[i].push_back(false);
				}
				else{
					outputBST[i].push_back(count);	
					Print[i].push_back(true);
				}
				wordsBST.push_back(word);
				word = "";
			}
		}
	}
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -start);
	//////////////////////////////////////////////////////////////////////
	cout << "\nTime: " << BSTTime.count() / k << "\n";
	cout << "\nTime: " << HTTime.count() / k << "\n";
	cout << "\nSpeed Up: "<<(double)(BSTTime.count()/k)/(HTTime.count() / k) << "\n";
	system("pause");
	return 0;
}