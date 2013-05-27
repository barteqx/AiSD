#include <iostream>
#include <cstdio>
#include <queue>

bool table[2002][2002];

struct pair {
	unsigned short int x,y;
	unsigned int distance;

	pair(int m, int n, int d):
		x(m), y(n), distance(d) { }
};

int main() {
	
	unsigned short int a,b,c;
	unsigned short int Sx, Sy;
	char line[2001];
	std::queue<pair> Q;

	c = scanf("%hu %hu", &a, &b);
	for(int i = 0; i <= a+1; i++) {
		table[i][0] = false;
		table[i][b+1] = false;
	}
	for(int i = 0; i <= b+1; i++) {
		table[0][i] = false;
		table[a+1][i] = false;
	}

	for (int i = 0; i < b; i++) {
		std::cin >> line;
		for (int j = 0; j < a; j++) {
			if (line[j] == '.') table[i+1][j+1] = true;
			else if (line[j] == 'x') table[i+1][j+1] = false;
			else if (line[j] == 'P') { table[i+1][j+1] = true; Q.push(pair(i+1, j+1, 0)); }
			else if (line[j] == 'S') {
				table[i+1][j+1] = true;
				Sx = i+1;
				Sy = j+1;
			}
		}
	}

	while (!Q.empty()) {
		pair current = Q.front();
		Q.pop();
		unsigned short int x = current.x;
		unsigned short int y = current.y;
		unsigned int dist = current.distance;
		if (x == Sx && y == Sy) { std::cout << dist; return 0; }
		if (table[x+1][y]) { Q.push(pair(x+1, y, dist+1)); table[x+1][y] = false; }
		if (table[x-1][y]) { Q.push(pair(x-1, y, dist+1)); table[x-1][y] = false; }
		if (table[x][y+1]) { Q.push(pair(x, y+1, dist+1)); table[x][y+1] = false; }
		if (table[x][y-1]) { Q.push(pair(x, y-1, dist+1)); table[x][y-1] = false; }
	}
	std::cout << "NIE";
	return 0;
}