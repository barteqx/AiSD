#include <vector>
#include <iostream>
#include <algorithm>

#define MAXTABLE 262144

struct Square {
   int x1, x2, y1, y2, val;
   Square(int a, int b, int c, int d, int v)
   : x1(a), y1(b), x2(c), y2(d), val(v) {} 
   Square() {}
};

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


bool cmp (Point p1, Point p2){
   return p1.y < p2.y;
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
   dfs(1, 0, 131071, a, b, val);
}

int main() {
   std::ios::sync_with_stdio(false);

   int n, max_val = 0;

   std::cin >> n;
   
   std::vector<Point> points;
   
   Square squares[n];

   for (int i = 0; i <= MAXTABLE; i++) {
      current[i] = 0;
      max[i] = 0;
   }

   for (int i = 0; i < n; i++) {
      int a, b, c, d, v;
      std::cin >> a >> b >> c >> d;
      points.push_back(Point(a, b, i, 1, false));
      points.push_back(Point(c, d, i, 1, true));
   }

   std::sort (points.begin(), points.end(), cmp);
   int last = points[0].y, curr = 0;
   for(int i = 0; i < points.size(); i++) {
      if(points[i].y > last) {
         last = points[i].y;
         curr++;
      }
      points[i].y = curr;
   }


   for (int i = 0; i < points.size(); i++) {
      Point sq = points[i];
      if (!sq.end) {
         squares[sq.sq].x1 = sq.x;
         squares[sq.sq].y1 = sq.y;
         squares[sq.sq].val = sq.val;
      }
      else {
         squares[sq.sq].x2 = sq.x;
         squares[sq.sq].y2 = sq.y;
         squares[sq.sq].val = sq.val;
      }
   }

   beginings.reserve(2*n);
   for(int i = 0; i < n; i++) {
      beginings.push_back(Section(squares[i].y1, squares[i].y2, squares[i].x1, squares[i].val));
      beginings.push_back(Section(squares[i].y1, squares[i].y2, squares[i].x2, squares[i].val*(-1)));
      //std::cout << squares[i].y1 << ' ' << squares[i].y2 << ' ' << squares[i].x1 << ' ' <<squares[i].x2 <<' ' << squares[i].val << std::endl;
   }

   std::sort(beginings.begin(), beginings.end(), cmp_sec);

   for(int i = 0; i < beginings.size(); i++) {
      insert(beginings[i].y1, beginings[i].y2, beginings[i].val);  
      if (max[1] > max_val) max_val = max[1];
   }
   std::cout << max_val << std::endl;
} 