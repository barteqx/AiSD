#include <iostream>
#include <cstdio>

#define MAXSIZE 4000

struct vertex {
	unsigned long long val;
	unsigned int x;
	unsigned int y;

	vertex() {};

	vertex (unsigned int x, unsigned int y) :
		x(x), y(y), val(static_cast<unsigned long long>(x) * static_cast<unsigned long long>(y)) {};
};

class Heap {

public:
	unsigned int current_size;	
	vertex tab[MAXSIZE];
	Heap() : current_size(0) {};

	void push(vertex val);

	const vertex pop_max();

	void operator = (Heap& val);

	unsigned int size() { return current_size; }

	void print();

	void heapify(int i);

private:
	void swap(unsigned int m, unsigned int n);
	
};

void Heap::print() {
	for(unsigned int i = 0; i < current_size; i++) {
		printf("%u %u\n", tab[i].x, tab[i].y);
	}
}

void Heap::push(vertex val) {
	int n = current_size++;
	tab[n] = val;
	while (n > 0 && tab[n].val > tab[n/2].val) {
		swap(n/2, n);
		n = (n)/2;
	}
}

void Heap::operator = (Heap& val) {
	for (unsigned int i = 0; i < val.size(); i++)
	   tab[i] = val.tab[i];
	 current_size = val.current_size;
}

const vertex Heap::pop_max() {
	vertex tmp = tab[0];
	tab[0] = tab[--current_size];
	heapify(0);
	return tmp;
}

void Heap::heapify(int n) {
	int m = n;
	while (true) {
		if (n * 2 <= current_size && tab[n*2].val > tab[m].val) m = n*2;
		if (n * 2 + 1 <= current_size && tab[n*2+1].val > tab[m].val) m = n*2+1;
		if (m == n) break;
		swap(m, n);
		n = m;
	}
}

void Heap::swap(unsigned int m, unsigned int n) {
	vertex tmp(tab[m].x, tab[m].y);
	tab[m] = tab[n];
	tab[n] = tmp;
}

Heap maxheap = Heap();

int main() {
	std::ios::sync_with_stdio(false);
	unsigned long long n = 0, max = 0, counter = 0;
	unsigned long long maxval;	

	scanf("%llu %llu", &n, &max);
	maxval = n*n+1;
	maxheap.push(vertex(n, n));
	
	while (counter < max) {
		vertex print_vertex = maxheap.pop_max();

		unsigned long long i = print_vertex.val;
		if (i < maxval) {
			printf("%llu\n",i);
			maxval = i;
			counter++;
		}
		if (print_vertex.x-1 == print_vertex.y) maxheap.push(vertex(print_vertex.x-1,print_vertex.y));
		if (print_vertex.y > 1) maxheap.push(vertex(print_vertex.x,print_vertex.y-1));
	}
	return 0;
}