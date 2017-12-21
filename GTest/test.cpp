#include "pch.h"
#include "Heaps/MeldingHeaps.h"
#include <fstream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

class Action {
private:
	friend istream & operator >>(istream& in, Action& num);
	friend ostream& operator <<(ostream& out, const Action& num);
	int key;
	size_t index1, index2;
public:
	enum Type {
		TaddHeap,
		Tinsert,
		TextractMin,
		Tmeld,
		TgetMin,
		Tsize
	};
	Type type;
	template <class MHeap>
	int operator ()(MHeap& heap) {
		switch (type) {
		case TaddHeap:
			heap.addHeap(key);
			return 0;
		case Tinsert:
			heap.insert(index1, key);
			return 0;
		case TextractMin:
			heap.extractMin(index1);
			return 0;
		case Tmeld:
			heap.meld(index1, index2);
			return 0;
		case TgetMin:
			return heap.getMin(index1);
		default:
			break;
		}
		return -1;
	}
	Action() {}
	Action(Type type, int key, size_t index1, size_t index2): type(type), key(key), index1(index1), index2(index2) {
	}
};

vector <Action> GenTest (int temps, int deep, int size, int maxSize){
	srand(time(NULL));
	vector <Action> ans;
	MeldingHeaps <STDHeap <int>, int> heap;
	for (int i = 0; i < size; i++) {
		int key = rand();
		heap.addHeap(key);
		ans.push_back(Action(Action::TaddHeap, key, 0, 0));
	}
	for (; (int)ans.size() < temps;) {
		if (rand() % 2) {
			if (rand() % 3) {
				int index1 = rand() % size, index2 = rand() % size;
				if (index1 == index2)
					continue;
				ans.push_back(Action(Action::Tmeld, 0, index1, index2));
			}
			else if (rand() % 2) {
				int index1 = rand() % size;
				if (heap.empty(index1))
					continue;
				ans.push_back(Action(Action::TgetMin, 0, index1, 0));
			}
			else {
				if (size == maxSize)
					continue;
				ans.push_back(Action(Action::TaddHeap, rand(), 0, 0));
				size++;
			}
		}
		else {
			if (ans.size() % (2 * deep) < deep) {
				if (rand() % 10) {
					int index = rand() % size;
					if (heap.empty(index))
						continue;
					ans.push_back(Action(Action::TextractMin, 0, index, 0));
				}
				else {
					ans.push_back(Action(Action::Tinsert, rand(), rand() % size, 0));
				}
			}
			else {
				if (rand() % 10) {
					ans.push_back(Action(Action::Tinsert, rand(), rand() % size, 0));
				}
				else {
					int index = rand() % size;
					if (heap.empty(index))
						continue;
					ans.push_back(Action(Action::TextractMin, 0, index, 0));
				}
			}
		}
		ans.back()(heap);
	}
	return ans;
}

istream& operator >>(istream& in, Action& num) {
	int type;
	in >> type >> num.key >> num.index1 >> num.index2;
	num.type = static_cast<Action::Type> (type);
	return in;
}

ostream& operator <<(ostream& out, const Action& num) {
	out << num.type << ' ' << num.key << ' ' << num.index1 << ' ' << num.index2 << '\n';
	return out;
}

const int CountOfTests = 40;
const string DirectName = "C:/mik/tests/";

void WriteTest(int numOfTest, int temps, int deep, int size, int maxSize) {
	std::ofstream out(DirectName + "Test" + to_string(numOfTest) + ".txt");
	out << temps + size << '\n';
	vector <Action> v = GenTest(temps, deep, size, maxSize);
	for (size_t k = 0; k < v.size(); k++)
		out << v[k];
	out.close();
}

void makeTests(){
	int i = 1;
	for (int j = 0; j < CountOfTests / 4; j++, i++)
		WriteTest(i, 10000, 10, 10, 20);
	for (int j = 0; j < CountOfTests / 4; j++, i++)
		WriteTest(i, 1000, 100, 100, 200);
	for (int j = 0; j < CountOfTests / 4; j++, i++)
		WriteTest(i, 10000, 100, 1000, 2000);
	for (int j = 0; j < CountOfTests / 4; j++, i++)
		WriteTest(i, i * 10000, 1000, 100, 200);
}

template <class MHeap>
void RunTest(int numOfTest) {
	std::ifstream in(DirectName + "Test" + to_string(numOfTest) + ".txt");
	int temps;
	in >> temps;
	MeldingHeaps <STDHeap <int>, int> heap1;
	MHeap heap2;
	for (int i = 0; i < temps; i++) {
		Action a;
		in >> a;
		ASSERT_EQ(a(heap1), a(heap2));
	}
}

template <class MHeap>
void TimeTest(int numOfTest, string MHeapName) {
	std::ifstream in(DirectName + "Test" + to_string(numOfTest) + ".txt");
	time_t begin = clock();
	int temps;
	in >> temps;
	MHeap heap2;
	for (int i = 0; i < temps; i++) {
		Action a;
		in >> a;
		a(heap2);
	}
	std::ofstream out(DirectName + "Test" + to_string(numOfTest) + ".txt", std::ios::in);
	out.seekp(0, std::ios::end);
	out << MHeapName << " testing: " << numOfTest << ' ' << temps << ' ' << (clock() - begin) * 1000 / CLOCKS_PER_SEC << '\n';
	out.close();
}

TEST(SkewTest, Test1) {
	for (int i = 1; i <= CountOfTests / 4; i++)
		RunTest<MeldingHeaps<SkewHeap<int>, int> >(i);
}

TEST(SkewTest, Test2) {
	for (int i = CountOfTests / 4 + 1; i <= CountOfTests / 2; i++)
		RunTest<MeldingHeaps<SkewHeap<int>, int> >(i);
}

TEST(SkewTest, Test3) {
	for (int i = CountOfTests / 2 + 1; i <= 3 * CountOfTests / 4; i++)
		RunTest<MeldingHeaps<SkewHeap<int>, int> >(i);
}

TEST(LeftistTest, Test1) {
	for (int i = 1; i <= CountOfTests / 4; i++)
		RunTest<MeldingHeaps<LeftistHeap<int>, int> >(i);
}

TEST(LeftistTest, Test2) {
	for (int i = CountOfTests / 4 + 1; i <= CountOfTests / 2; i++)
		RunTest<MeldingHeaps<LeftistHeap<int>, int> >(i);
}

TEST(LeftistTest, Test3) {
	for (int i = CountOfTests / 2 + 1; i <= 3 * CountOfTests / 4; i++)
		RunTest<MeldingHeaps<LeftistHeap<int>, int> >(i);
}

TEST(BinomialTest, Test1) {
	for (int i = 1; i <= CountOfTests / 4; i++)
		RunTest<MeldingHeaps<BinomialHeap<int>, int> >(i);
}

TEST(BinomialTest, Test2) {
	for (int i = CountOfTests / 4 + 1; i <= CountOfTests / 2; i++)
		RunTest<MeldingHeaps<BinomialHeap<int>, int> >(i);
}

TEST(BinomialTest, Test3) {
	for (int i = CountOfTests / 2 + 1; i <= 3 * CountOfTests / 4; i++)
		RunTest<MeldingHeaps<BinomialHeap<int>, int> >(i);
}

TEST(TimeTest, MainTest) {
	for (int i = 3 * CountOfTests / 4 + 1; i <= CountOfTests; i++)
		TimeTest<MeldingHeaps<BinomialHeap<int>, int> >(i, "BinomialHeap");
	for (int i = 3 * CountOfTests / 4 + 1; i <= CountOfTests; i++)
		TimeTest<MeldingHeaps<LeftistHeap<int>, int> >(i, "LeftistHeap");
	for (int i = 3 * CountOfTests / 4 + 1; i <= CountOfTests; i++)
		TimeTest<MeldingHeaps<SkewHeap<int>, int> >(i, "SkewHeap");
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	//makeTests();
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}