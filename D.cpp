#include <iostream>
#include <string>
#include <vector>

using namespace std;

void check(string production);

unsigned char translate(char letter);

struct Rule1 {
	unsigned char in;
	unsigned char out1;
	unsigned char out2;

	Rule1(unsigned char x, unsigned char y, unsigned char z) 
		: in(translate(x)), out1(translate(y)), out2(translate(z)) {}
};

struct Rule2 {
	unsigned char in;
	char out;

	Rule2(unsigned char x, char y) 
		: in(translate(x)), out(y) {}
};

std::vector<Rule1> rules1;
std::vector<Rule2> rules2;

unsigned char table[256][256];

void check(string production) {
	int size = production.size();
	unsigned char tab[size+1][size+1];

	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++) {
			tab[i][j] = 0;
		}
	}

	for (int i = 1; i <= size; i++) {
		for (int j = 0; j < rules2.size(); j++) {
			if (production[i-1] == rules2[j].out) {
				tab[i][1] |= rules2[j].in;
			}
		}
	}

	for (int i = 2; i <= size; i++) {
		for (int j = 1; j <= size - i + 1; j++) {
			tab[j][i] = 0;
			for (int k = 1; k <= i-1; k++) {
				tab[j][i] |= table[tab[j][k]][tab[j+k][i-k]];
			}
		}
	}
	if (tab[1][size] & 1) cout << "TAK" << endl;
	else cout << "NIE" << endl;

}

unsigned char translate(char letter) {
	return 1 << (letter - 'A');
}

void preprocessing() {
	for (unsigned short int i = 0; i < 256; i++) {
		for (unsigned short int j = 0; j < 256; j++) {
			table[i][j] = 0;
			for (int n = 0; n < rules1.size(); n++) {
				if((i & rules1[n].out1) && (j & rules1[n].out2)) {
						table[i][j] |= rules1[n].in;
				}
			}
		}
	}
}

int main() {
	int D, x, y;
	char A, B, C;
	string production;

	cin >> D;
	for (int i = 0; i < D; i++) {
		rules1 = std::vector<Rule1>();
		rules2 = std::vector<Rule2>();
		cin >> x >> y;
		
		rules1.reserve(x);
		rules2.reserve(y);

		for (int i = 0; i < x; i++) {
			cin >> A >> B >> C;
			rules1.push_back(Rule1(A,B,C));
		}

		for (int i = 0; i < y; i++) {
			cin >> A >> B;
			rules2.push_back(Rule2(A,B));
		}
		preprocessing();

		cin >> production;
		check(production);
	}
	return 0;
}