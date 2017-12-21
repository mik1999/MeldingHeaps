#pragma once
template <typename T>
class IHeap {
public:
virtual void insert(const T& key) = 0;
virtual const T& getMin() const = 0;
virtual void extractMin() = 0;
virtual void meld(IHeap <T>* heap) = 0;
virtual bool empty() const = 0;
virtual ~IHeap() {}
};

#include <stack>
#include <iostream>
template <typename T>
bool equalHeaps(IHeap<T>* heap1, IHeap<T>* heap2) {
	std::stack <T> s;
	while (!heap1->empty()) {
		if (heap1->getMin() != heap2->getMin())
			return false;
		s.push(heap1->getMin());
		heap1->extractMin();
		heap2->extractMin();
	}
	if (!heap2->empty())
		return false;
	while (!s.empty()) {
		heap1->insert(s.top());
		heap2->insert(s.top());
		s.pop();
	}
	return true;
}