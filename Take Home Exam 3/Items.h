

#include <vector>
#include <string>
using namespace std;

struct DocumentItem {
	string documentName;
	int count;
	const bool DocumentItem::operator==(DocumentItem rhs);
	const bool DocumentItem::operator!=(DocumentItem rhs);
	const bool DocumentItem::operator==(const DocumentItem rhs) const;
	const bool DocumentItem::operator!=(const DocumentItem rhs) const;
	DocumentItem( const string & documentName1,int count1 = 1)
		: documentName(documentName1),count(count1){ }
};

struct WordItem {
	string word;
	vector<DocumentItem> list;
	const WordItem & operator=(const WordItem & rhs);
	const bool operator<(WordItem & rhs);
	const bool operator<(const WordItem & rhs) const;
	const bool operator==(WordItem rhs);
	
	const bool operator!=(WordItem rhs);
	const bool operator==(const WordItem rhs) const;
	const bool operator!=(const WordItem rhs) const;
	WordItem( const string & word1,const vector<DocumentItem> & list1)
		: word(word1){ list=list1;}
	WordItem( const string & word1,const string & DocumentName)
		: word(word1){
			DocumentItem temp(DocumentName);
			vector<DocumentItem> list1;
			list1.push_back(temp);
			list=list1;
	}
	WordItem( const WordItem & rhs)
	{
		*this=rhs;
	}
	WordItem()
		: word(""){const vector<DocumentItem> list1; }
};

const bool DocumentItem::operator==(DocumentItem rhs){
	if(this->count == rhs.count && this->documentName == rhs.documentName){
		return true;
	}
	return false;
}

const bool DocumentItem::operator!=(DocumentItem rhs){
	return !(*this == rhs);
}

const bool DocumentItem::operator==(const DocumentItem rhs) const {
	if(this->count == rhs.count && this->documentName == rhs.documentName){
		return true;
	}
	return false;
}

const bool DocumentItem::operator!=(const DocumentItem rhs) const{
	return !(*this == rhs);
}




const WordItem & WordItem::operator=(const WordItem & rhs){
	this->list = rhs.list;
	this->word = rhs.word;
	return *this;
}

const bool WordItem::operator<(WordItem & rhs){
	if(this->word<rhs.word){
		return true;
	}
	return false;
}

const bool WordItem::operator<(const WordItem & rhs) const{
	if(this->word<rhs.word){
		return true;
	}
	return false;
}

const bool WordItem::operator==(WordItem rhs){
	if((this->list.size() != rhs.list.size()) || (this->word != rhs.word) || (this->list !=rhs.list)){
		return false;
	}
	return true;
}

const bool WordItem::operator!=(WordItem rhs){
	if((this->word != rhs.word)){
		return true;
	}
	return false;
}

const bool WordItem::operator==(const WordItem rhs) const {
	if((this->word != rhs.word)){
		return false;
	}
	return true;
}

const bool WordItem::operator!=(const WordItem rhs) const{
	return !(*this == rhs);
}