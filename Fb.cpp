#include <cstdio>
#include <vector>
#include <algorithm>

struct Edge {
   int x, y, weight;

   Edge(int a, int b,int  c)
      : x(a), y(b), weight(c) {}
};

bool cmp(Edge e1, Edge e2) { return e1.weight > e2.weight; }

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
   if (w[a] <= w[b]) {
      w[b] += w[a];
      parents[a] = b;
   } else {
      w[a] += w[b];
      parents[b] = a;
   }
}

int main() {
   int m, n, a, b, c, minimal;
   std::vector<Edge> v;
   scanf("%d %d", &m, &n);
   v.reserve(n);
   parents.reserve(n);
   w.reserve(n);
   
   for (int i = 0; i < n; i++) {
      parents.push_back(i);
      w.push_back(1);
      scanf("%d %d %d", &a, &b, &c);
      v.push_back(Edge(a-1, b-1, c));
   }

   std::sort(v.begin(), v.end(), cmp);
   for (int i = 0; i < v.size(); i++) {
      if (find(v[i].x) != find(v[i].y)) {
         minimal = v[i].weight;
         union_(v[i].x, v[i].y);
      }
   }
   printf("%d\n", minimal);
}