#include <compare>
#include <functional>
#include <limits>
#include <vector>
#include <cassert>

using namespace std;

template <typename T, class Compare = less<typename T::value_type>> // min or max depending on Compare, default max heap
class Heap {
public:
	// zero indexed versions of access
	static constexpr T MINVAL = numeric_limits<T>::has_infinity ? numeric_limits<T>::infinity() : numeric_limits<T>::lowest();
	static int parent(const int i) {return (i+1)/2-1;} // (i+1)/2-1
	static int left(const int i) {return 2*i+1;} // 2*(i+1)-1
	static int right(const int i) {return 2*i+2;} // 2*(i+1)+1-1

	static void increase_key(vector<T> &A, int i, T key) {
		A[i] = key;
		while (i>0 and Compare{}(A[parent(i)],A[i])) { // if out of bounds or parent < original
			swap(A[i],A[parent(i)]);
			i = parent(i); // recurse
		}
	}
	static void insert(vector<T> &A, T key) {
		A.push_back(MINVAL); // add a min key
		increase_key(A, A.size()-1, key); // push it up to where it belongs
	}
	static void heapify(vector<T> &A, int i) {
		const int n = A.size();
		const int l = left(i);
		const int r = right(i);
		int largest;
		if (l < n and Compare{}(A[i],A[l])) largest = l; // check against left
		else largest = i;
		if (r < n and Compare{}(A[largest],A[r])) largest = r; // check against right
		if (largest != i) { // if heap property false
			swap(A[i],A[largest]); // make it so
			return heapify(A,largest); // fix the rest
		}
	}
	static void build_heap(vector<T> &A) {
		for (int i = parent(A.size());i>=0;i--)
			heapify(A,i);
	}
	static T& top(vector<T> &A) {return A[0];} // peek at min or max
	static T extract(vector<T> &A) { // min or max depending on Compare
		T val = A[0];
		A[0] = A.back();
		A.pop_back();
		heapify(A, 0);
		return val;
	}

	static int find(vector<T> &A, T key) {
		const int n = A.size();
		int i = 0;
		while (i<n) switch (A[i]<=>key) {
				case strong_ordering::equal	: return i	;break;
				case strong_ordering::less	: i=right(i)	;break;
				case strong_ordering::greater	: i=left(i)	;break;
		}
		return -1;
	}
};

template <typename T>
using MaxHeap = Heap<T,less<T> >; // the MaxHeap

template <typename T>
using MinHeap = Heap<T,greater<T> >; // the MinHeap
