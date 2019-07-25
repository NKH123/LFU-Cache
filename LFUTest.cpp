#include "LFU.h"

//Testing LFU
int main(){
	LFU lfu;
	lfu.Retrieve(1);
	lfu.Retrieve(2);
	lfu.Retrieve(1);
	lfu.Retrieve(3);
	lfu.Retrieve(1);
	lfu.Evict(3);
	lfu.Retrieve(1);
	lfu.Retrieve(4);
	lfu.PrintLFU();
	return 0;
}