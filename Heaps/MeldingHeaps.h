#pragma once
#include <vector>
#include <queue>
#include "LeftistHeap.h"
#include "STDHeap.h"
#include "SkewHeap.h"
#include "BinomialHeap.h"

template <class MHeap, typename T>
class MeldingHeaps
{
private:
	std::vector <MHeap> heaps_;
	template <class MHeap1, class MHeap2, typename T>
	friend bool operator ==(MeldingHeaps<MHeap1, T> mh1, MeldingHeaps<MHeap2, T> mh2);
public:
	MeldingHeaps();
	void addHeap(const T& key);
	void insert(size_t index, const T& key);
	const T& getMin(size_t index) const;
	void extractMin(size_t index);
	void meld(size_t index1, size_t index2);
	bool empty(size_t index) const;
	~MeldingHeaps();
};

template <class MHeap, typename T>
MeldingHeaps<MHeap, T>::MeldingHeaps()
{
}

template <class MHeap, typename T>
MeldingHeaps<MHeap, T>::~MeldingHeaps()
{
}

template <class MHeap, typename T>
void MeldingHeaps<MHeap, T>::addHeap(const T& key) {
	heaps_.push_back(MHeap(key));
}

template <class MHeap, typename T>
void MeldingHeaps<MHeap, T>::insert(size_t index, const T& key) {
	heaps_[index].insert(key);
}

template <class MHeap, typename T>
const T& MeldingHeaps<MHeap, T>::getMin(size_t index) const{
	return heaps_[index].getMin();
}

template <class MHeap, typename T>
void MeldingHeaps<MHeap, T>::extractMin(size_t index) {
	heaps_[index].extractMin();
}

template <class MHeap, typename T>
void MeldingHeaps<MHeap, T>::meld(size_t index1, size_t index2) {
	heaps_[index1].meld(&heaps_[index2]);
}

template <class MHeap, typename T>
bool  MeldingHeaps<MHeap, T>::empty(size_t index) const {
	return heaps_[index].empty();
}

template <class MHeap1, class MHeap2, typename T>
bool operator ==(MeldingHeaps<MHeap1, T> mh1, MeldingHeaps<MHeap2, T> mh2) {
	if (mh1.heaps_.size() != mh2.heaps_.size())
		return false;
	for (size_t i = 0; i < mh1.heaps_.size(); i++)
		if (!equalHeaps(&mh1.heaps_[i], &mh2.heaps_[i]))
			return false;
	return true;
}