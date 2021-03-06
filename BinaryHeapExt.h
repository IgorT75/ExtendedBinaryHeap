#pragma once
#include <unordered_map>
#include <type_traits>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T, class Pred = std::less<T>, class Hash = std::hash<T>, class KeyEqual = std::equal_to<T>>
class BinaryHeapExt {
	/*static_assert(std::is_arithmetic<T>::value, "Not numeric!!");*/
private:
	std::unordered_map<T, size_t, Hash, KeyEqual> _map;
	std::vector<T> _heap;

	static size_t getLeftChildPos(size_t pos) { return 2 * pos + 1; }
	static size_t getRightChildPos(size_t pos) { return 2 * pos + 2; }
	static size_t getParentPos(size_t pos) { return (pos - 1) / 2; }

	bool containsKey(T key) const { return _map.find(key) != _map.end(); }
	size_t size() const { return _heap.size(); }

	void heapify(size_t i) {
		Pred pred;
		size_t left = getLeftChildPos(i), right = getRightChildPos(i);
		size_t lesser = i;
		if (left < _heap.size() && pred(_heap[left], _heap[lesser]))
			lesser = left;
		if (right < _heap.size() && pred(_heap[right], _heap[lesser]))
			lesser = right;
		if (lesser != i) {
			std::swap(_heap[lesser], _heap[i]);
			_map[_heap[lesser]] = lesser;
			_map[_heap[i]] = i;
			heapify(lesser);
		}
	}

	void init() {
		for (size_t i = 0; i < _heap.size(); ++i)
			_map[_heap[i]] = i;

		if (_heap.size() < 2) return;
		for (size_t i = (_heap.size() + 1) / 2; i-- > 0;) {
			heapify(i);
		}
	}

public:
	BinaryHeapExt(vector<T>& vec) : _heap(vec) {
		init();
	}

	BinaryHeapExt(vector<T>&& vec) : _heap(std::move(vec)) {
		init();
	}

	T extractExtremum() {
		T val = _heap.front();
		auto it = _map.find(val);
		if (it != _map.end())
			_map.erase(it);

		_heap.front() = _heap.back();
		_heap.pop_back();

		heapify(0);
		return val;
	}

	T getExtremum() const { return _heap.front(); }

	void changeKey(size_t pos, T value) {
		if (pos >= _heap.size()) throw std::exception("out of range");
		if (_heap[pos] == value) return;

		Pred cmp;
		if (cmp(_heap[pos], value)) throw std::exception("not extreming");

		auto it = _map.find(_heap[pos]);
		if (it != _map.end())
			_map.erase(it);

		_heap[pos] = value;
		_map[_heap[pos]] = pos;

		size_t par = getParentPos(pos);
		while (par >= 0 && cmp(_heap[pos], _heap[par])) {
			std::swap(_heap[pos], _heap[par]);

			_map[_heap[par]] = par;
			_map[_heap[pos]] = pos;

			if (par == 0) break;
			pos = par;
			par = getParentPos(par);
			//(pos, par) = (par, getParentPos(par));
		}
	}

	void addKey(T key) {
		if (_map.find(key) != _map.end())
			throw std::exception("key is already present");

		T max;
		if (_heap.size() == 1)
			max = std::numeric_limits<T>::max();
		else {
			max = _heap[0] < _heap[1] ? std::numeric_limits<T>::max()
				: std::numeric_limits<T>::min();
		}

		_heap.push_back(max);
		_map[max] = _heap.size() - 1;
		changeKey(_heap.size() - 1, key);
	}

	string toString() const {
		string s = std::accumulate(_heap.begin(), _heap.end(), ""s,
			[](string& a, const T& b) { return a.append(" ").append(std::to_string(b)); });
		return std::string(++s.begin(), s.end());
	}
};