#pragma once
#include <vector>
using namespace std;

template <typename T>
class Comp {
public:
	bool operator ()(const T& a, const T& b) const{
		return a > b;
	}
};

template <typename T>
class STDHeap: public IHeap <T> {
private:
	vector <T> elements_;
public:
	STDHeap();
	STDHeap(const T& key);
	virtual void insert(const T& key);
	virtual const T& getMin() const;
	virtual void extractMin();
	virtual void meld(IHeap <T>* heap);
	virtual bool empty() const;
	~STDHeap();
};

template <typename T>
STDHeap<T>::STDHeap() {
}

template <typename T>
STDHeap<T>::~STDHeap() {
}

template <typename T>
STDHeap<T>::STDHeap(const T& key) {
	elements_.push_back(key);
}

template <typename T>
void STDHeap<T>::insert(const T& key) {
	elements_.push_back(key);
	Comp <T> comp;
	make_heap(elements_.begin(), elements_.begin() + elements_.size(), comp);
}

template <typename T>
const T& STDHeap<T>::getMin() const {
	return elements_[0];
}

template <typename T>
void STDHeap<T>::extractMin() {
	Comp <T> comp;
	pop_heap(elements_.begin(), elements_.begin() + elements_.size(), comp);
	elements_.pop_back();
}

template <typename T>
bool STDHeap<T>::empty() const{
	return elements_.empty();
}

template <typename T>
void STDHeap<T>::meld(IHeap <T>* heap) {
	STDHeap <T>* pheap = static_cast <STDHeap <T>*> (heap);
	size_t oldSize = elements_.size();
	elements_.resize(elements_.size() + pheap->elements_.size());
	copy(pheap->elements_.begin(), pheap->elements_.end(), elements_.begin() + oldSize);
	pheap->elements_.clear();
	Comp <T> comp;
	make_heap(elements_.begin(), elements_.begin() + elements_.size(), comp);
}

