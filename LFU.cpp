#include "LFU.h"

//Constructor
LFU::LFU() {
	this->head = new FrequencyList<int>(0, NULL, NULL);
	this->CountFrequencyListMap[0] = this->head;
}

//Destructor
LFU::~LFU() {
	delete(this->head);
	this->NodeFrequencyListMap.clear();
	this->CountFrequencyListMap.clear();
}

//Adds an item to the cache
void LFU::Set(int value) {
	int node = value;
	if (NodePresent(node)) {
		std::unordered_map<int, FrequencyList<int> *>::const_iterator iter1 = this->NodeFrequencyListMap.find(node);
		FrequencyList<int> *frequencyList = iter1->second;
		int freq = frequencyList->GetCount();

		frequencyList->Delete(node);

		freq = freq + 1;

		if (FrequencyNodePresent(freq)) {
			FrequencyList<int> *frequencyList1 = this->CountFrequencyListMap.find(freq)->second;
			frequencyList1->Add(node);
			this->NodeFrequencyListMap[node] = frequencyList1;
		}
		else {
			FrequencyList<int> *newFrequencyNode = new FrequencyList<int>(freq);
			newFrequencyNode->SetPrevious(frequencyList);
			newFrequencyNode->SetNext(frequencyList->GetNext());
			this->CountFrequencyListMap[freq] = newFrequencyNode;
			frequencyList->SetNext(newFrequencyNode);

			frequencyList->GetNext()->SetPrevious(newFrequencyNode);
			frequencyList->SetNext(newFrequencyNode);

			newFrequencyNode->Add(node);
			this->NodeFrequencyListMap[node] = newFrequencyNode;
		}

		if (IsNodeEmpty(frequencyList)) {
			frequencyList->GetNext()->SetPrevious(frequencyList->GetPrevious());
			frequencyList->GetPrevious()->SetNext(frequencyList->GetNext());
			this->CountFrequencyListMap.erase(frequencyList->GetCount());
			free(frequencyList);
		}
	}
	else {
		int freq = 1;
		if (FrequencyNodePresent(freq)) {
			FrequencyList<int> *frequencyList1 = this->CountFrequencyListMap.find(freq)->second;
			frequencyList1->Add(node);
			this->NodeFrequencyListMap[node] = frequencyList1;
		}
		else {
			FrequencyList<int> *newFrequencyNode = new FrequencyList<int>(freq);
			this->CountFrequencyListMap[freq] = newFrequencyNode;
			newFrequencyNode->SetPrevious(this->head);
			newFrequencyNode->SetNext(this->head->GetNext());
			newFrequencyNode->Add(node);

			this->head->SetNext(newFrequencyNode);
			if (newFrequencyNode->GetNext() != NULL)
				newFrequencyNode->GetNext()->SetPrevious(newFrequencyNode);
			this->NodeFrequencyListMap[node] = newFrequencyNode;
		}
	}
}

//Retrieve a value from the cache
void LFU::Retrieve(int node) {
		Set(node);
}

//Remove node present in cache
void LFU::Evict(int value) {
	int node = value;
	if (NodePresent(node)) {
		FrequencyList<int> *presentFrequencyNode = this->NodeFrequencyListMap[node];
		presentFrequencyNode->Delete(node);

		if (IsNodeEmpty(presentFrequencyNode)) {
			if (presentFrequencyNode->GetNext() != NULL)
				presentFrequencyNode->GetNext()->SetPrevious(presentFrequencyNode->GetPrevious());
			if (presentFrequencyNode->GetPrevious() != NULL)
				presentFrequencyNode->GetPrevious()->SetNext(presentFrequencyNode->GetNext());
			this->CountFrequencyListMap.erase(presentFrequencyNode->GetCount());
			free(presentFrequencyNode);
		}
	}
}

bool LFU::NodePresent(int node) {
	std::unordered_map<int, FrequencyList<int> *>::const_iterator iter1 = this->NodeFrequencyListMap.find(node);
	return !(iter1 == this->NodeFrequencyListMap.end());
}

bool LFU::FrequencyNodePresent(int count) {
	std::unordered_map<int, FrequencyList<int> *>::const_iterator iter1 = this->CountFrequencyListMap.find(count);
	return !(iter1 == this->CountFrequencyListMap.end());
}

bool LFU::IsNodeEmpty(FrequencyList<int> *frequencyList) {
	return frequencyList->IsEmpty();
}

void LFU::PrintLFU() {
	FrequencyList<int> *Node = this->head;
	while (Node != NULL) {
		Node->PrintNodeList();
		Node = Node->GetNext();
	}
}