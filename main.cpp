#include <cstdio>
#include <vector>

#include "BinaryHeapExt.h"
#include <functional>
using namespace std;

typedef std::pair<size_t, size_t> SzPair;

struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const {
		auto hash1 = hash<T1>{}(p.first);
		auto hash2 = hash<T2>{}(p.second);
		return hash1 ^ hash2;
	}
};

int main() {

	//vector<int> v{ 4, 9, 11, 7, 5, 3 };
	//BinaryHeapExt<int, std::less<>> heap (v);

	//const auto minItem = heap.getExtremum();
	//printf("%d\n", minItem);

	//auto str = heap.toString();
	//printf("%s\n", str.c_str());
	//
	//heap.addKey(2);
	//str = heap.toString();
	//printf("%s\n", str.c_str());

	std::function<size_t> a;

	vector<pair<size_t, size_t>> v{ {4, 0}, {1, 4}, {4, 2}, {3, 1}, {9, 3} };
	const auto hashFun = std::function<pair<bool, size_t, size_t>&>([](const pair<size_t, size_t>& p)
		{ return (bool)(hash<size_t>{}(p.first) ^ hash<size_t>{}(p.second)); });

	BinaryHeapExt<SzPair, std::less<>, hash_pair> heap(v);
	const auto minItem = heap.getExtremum();

	printf("%zu - %zu\n", minItem.first, minItem.second);

	return 0;
}
