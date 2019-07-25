#ifndef LFU_LFU_H
#define LFU_LFU_H

#include "FrequencyList.h"

class LFU {
private:
	std::unordered_map<int, FrequencyList<int>* > NodeFrequencyListMap;
	std::unordered_map<int, FrequencyList<int>* > CountFrequencyListMap;
	FrequencyList<int> *head;

	void Set(int value);
	bool NodePresent(int node);
	bool FrequencyNodePresent(int count);
	bool IsNodeEmpty(FrequencyList<int> *frequencyList);
public:
	LFU();
	~LFU();

	void Retrieve(int value);
	void Evict(int value);
	void PrintLFU();
};


#endif //LFU_LFU_H