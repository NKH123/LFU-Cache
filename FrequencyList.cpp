#include "FrequencyList.h"

// Constructors
template <typename T>
FrequencyList<T>::FrequencyList() {

}

template <typename T>
FrequencyList<T>::FrequencyList(int count) {
	this->count = count;
}

template <typename T>
FrequencyList<T>::FrequencyList(int count, FrequencyList *left, FrequencyList *right) {
	this->count = count;
	this->left = left;
	this->right = right;
}

// Destructors
template <typename T>
FrequencyList<T>::~FrequencyList() {
	delete(this->right);
	delete(this->left);
	this->nodelist.clear();
}


// Support functions
template <typename T>
void FrequencyList<T>::Add(T node) {
	this->nodelist[node] = 1;
}

template <typename T>
void FrequencyList<T>::Delete(T node) {
	if (IsPresent(node)) {
		// node present.
		this->nodelist.erase(node);
	}
}

template <typename T>
void FrequencyList<T>::PrintNodeList() {
	std::unordered_map<int, int>::const_iterator iter = this->nodelist.begin();
	while (iter != this->nodelist.end()) {
		std::cout << iter->first << " ";
		iter++;
	}
}

template <typename T>
bool FrequencyList<T>::IsPresent(T node) {
	std::unordered_map<int, int>::const_iterator iter = this->nodelist.find(node);
	return !(iter == this->nodelist.end());
}

template <typename T>
int FrequencyList<T>::GetCount() {
	return this->count;
}

template <typename T>
void FrequencyList<T>::SetNext(FrequencyList *right) {
	this->right = right;
}

template <typename T>
void FrequencyList<T>::SetPrevious(FrequencyList *left) {
	this->left = left;
}

template <typename T>
FrequencyList<T>* FrequencyList<T>::GetNext() {
	return this->right;
}

template <typename T>
FrequencyList<T>* FrequencyList<T>::GetPrevious() {
	return this->left;
}

template <typename T>
bool FrequencyList<T>::IsEmpty() {
	return this->nodelist.empty();
}

template class FrequencyList<int>;