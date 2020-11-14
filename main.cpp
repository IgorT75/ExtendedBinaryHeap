#include <cstdio>
#include <vector>

#include "BinaryHeapExt.h"
using namespace std;

int main() {

	vector<int> v{ 4, 9, 11, 7, 5, 3 };
	BinaryHeapExt<int, std::less<>> heap (v);

	const auto minItem = heap.getExtremum();
	printf("%d\n", minItem);

	auto str = heap.toString();
	printf("%s\n", str.c_str());
	
	heap.addKey(2);
	str = heap.toString();
	printf("%s\n", str.c_str());
}
