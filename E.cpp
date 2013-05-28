#include <vector>
#include <iostream>
#include <algorithm>

#define MAXTABLE 524288

struct Point {
   int x, y, sq, val;
   bool end;
   Point(int a, int b, int c, int d, bool e)
   : x(a), y(b), sq(c), val(d), end(e) {}
};

struct Section {
   int y1, y2, x, val;
   Section(int a, int b, int c, int v)
   : y1(a), y2(b), x(c), val(v) {}
};


bool cmp (Point p1, Point p2) {
   return p1.y < p2.y;
}

bool cmp2 (Point p1, Point p2){
   if (p1.sq == p2.sq && !p1.end && p2.end) return true;
   if (p1.sq < p2.sq) return true;
   return false;
}

bool cmp_sec (Section s1, Section s2) {
   if (s1.x == s2.x && s1.val > s2.val) return true;
   if (s1.x < s2.x) return true;
   return false;
}

int current[MAXTABLE], max[MAXTABLE];
std::vector<Section> beginings;

void dfs(int k, int a, int b, int x, int y, int val) {
   if ( a >= x && b <= y ) {current[k] += val; max[k] += val; return;}
   int m = (a+b)/2;
   if ( x <= m ) dfs(2*k, a, m, x, y, val);
   if ( y > m  ) dfs(2*k+1, m+1, b, x, y, val);
   max[k] = std::max(max[2*k], max[2*k+1]) + current[k];
}

void insert(int a, int b, int val) {
   dfs(1, 0, 262143, a, b, val);
}

int main() {
   std::ios::sync_with_stdio(false);

   int n, max_val = 0;

   std::cin >> n;
   std::vector<Point> points;

   for (int i = 0; i <= MAXTABLE; i++) {
      current[i] = 0;
      max[i] = 0;
   }

   for (int i = 0; i < n; i++) {
      int a, b, c, d, v;
      std::cin >> a >> b >> c >> d >> v;
      points.push_back(Point(a, b, i, v, false));
      points.push_back(Point(c, d, i, v, true));
   }

   std::sort(points.begin(), points.end(), cmp);
   int last = 0, curr = 0;
   for(int i = 0; i < points.size(); i++) {
      if(points[i].y > last) {
         last = points[i].y;
         curr++;
      }
      points[i].y = curr;
   }

   std::sort(points.begin(), points.end(), cmp2);
   beginings.reserve(2*n);
   for(int i = 0; i < n; i++) {
      beginings.push_back(Section(points[2*i].y, points[2*i+1].y, points[2*i].x, points[2*i].val));
      beginings.push_back(Section(points[2*i].y, points[2*i+1].y, points[2*i+1].x, points[2*i].val*(-1)));
   }
   std::sort(beginings.begin(), beginings.end(), cmp_sec);
   for(int i = 0; i < beginings.size(); i++) {
      insert(beginings[i].y1, beginings[i].y2, beginings[i].val);  
      if (max[1] > max_val) max_val = max[1];
   }
   std::cout << max_val << std::endl;
} 