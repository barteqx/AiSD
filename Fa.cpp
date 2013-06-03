#include <cstdio>
#include <vector>
#include <queue>

struct Edge {
   int x, y, weight;

   Edge(int a, int b,int  c)
      : x(a), y(b), weight(c) {}
};

bool operator < (const Edge& e1, const Edge& e2) { return e1.weight < e2.weight; }

std::vector<int> parents, w;

int find(int x) {
   if (parents[x] == x) return x; 
   int fx = find(parents[x]);
   parents[x] = fx;
   return fx;
}

void union_(int x, int y) {
   int a = find(x);
   int b = find(y);
 
   if (a==b) return;
   if (w[a] < w[b]) {
      w[b] += w[a];
      parents[a] = b;
   } else if (w[a] < w[b]) {
      w[a] += w[b];
      parents[b] = a;
   } else {
      parents[b] = a;
      w[a] = w[b]+1;
   }
}

class resHeap : public std::priority_queue<Edge> {
public:
   resHeap (const unsigned int x) { this -> c.reserve(x); }
};

int main() {
   unsigned int m, n, a, b, c;
   int minimal;
   scanf("%d %d", &m, &n);
   resHeap v(n);
   parents.reserve(m);
   w.reserve(m);
   

   for (int i = 0; i < n; i++) {
      scanf("%d %d %d", &a, &b, &c);
      parents.push_back(i);
      w.push_back(1);
      v.push(Edge(a-1, b-1, c));
   }

   while (!v.empty()) {
      Edge e = v.top();
      v.pop();
      if (find(e.x) != find(e.y)) {
         minimal = e.weight;
         union_(e.x, e.y);
      }
   }
   printf("%d\n", minimal);
}