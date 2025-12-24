#include <iostream>
#include <vector>
#include <deque>

void invalidDeque() {
	std::deque<int> deq = { 2, 5, 1, 5, 6 };

	auto it = deq.begin();

	while (it != deq.end()) {
		if ((*it % 2) == 0) {
			// puede invalidar iterador
			deq.push_back(0);
		}
	}

}

void invalidVector() {
	std::vector<int> vec = { 2, 5, 1, 5, 6 };

	auto it = vec.begin();

	while (it != vec.end()) {
		if ((*it % 2) == 0) {
			it = vec.erase(it);
		}
		else {
			++it;
		}
	}
}

void testInvalidIterator() {

}