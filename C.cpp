#include <iostream>
#include <vector>


int main() {
	std::vector<long long> Max;
	std::vector<long long> Min;
	std::vector<int> val;
	std::vector<int> weight;

	int F, c;
	std::cin >> F;
	std::cin >> c;
	Max.reserve(F+1);
	Min.reserve(F+1);
	val.reserve(F+1);
	weight.reserve(F+1);

	short int maxV[F];
	short int minV[F];

	for (int i = 0; i < c; i++) {
		int a, b;
		std::cin >> a >> b;
		val.push_back(a);
		weight.push_back(b);
	}

	Max.push_back(0);
	Min.push_back(0);
	for (int i = 1; i <= F; i++) {	
		Min.push_back(9223372036854775807);
		Max.push_back(-1);
		for (int j = 0; j < c; j++) {
			if (weight[j] <= i) {
				if (Max[i - weight[j]] >= 0) {
					if (val[j] + Max[i-weight[j]] > Max[i]) {
						Max[i] = val[j] + Max[i-weight[j]];
						maxV[i] = j;
					}
					if (val[j] + Min[i-weight[j]] < Min[i]) {
						Min[i] = val[j] + Min[i-weight[j]];
						minV[i] = j;
					}
				}
			}
		}
	}
	if (Max[F] > -1 && Min[F] < 9223372036854775807) {
		
		long long valueMax = 0;
		long long valueMin = 0;
		int pointerMin = F;
		int pointerMax = F;
		int countMax[c], countMin[c];
		for (int i = 0; i < c; i++) {
			countMax[i] = 0;
			countMin[i] = 0;
		}
		while (pointerMax > 0) {
			int x = static_cast<int>(maxV[pointerMax]);
			valueMax += val[x];
			countMax[x]++;
			pointerMax -= weight[x];
		}
		while (pointerMin > 0) {
			int x = static_cast<int>(minV[pointerMin]);
			valueMin += val[x];
			countMin[x]++;
			pointerMin -= weight[x];
		} 
		std::cout << "TAK" << std::endl;
		std::cout << valueMin << std::endl;
		for (int i = 0; i < c; i++) std::cout<< countMin[i] << ' ';
		std::cout << std::endl;
		std::cout << valueMax << std::endl;
		for (int i = 0; i < c; i++) std::cout << countMax[i] << ' ';
		std::cout << std::endl;
	}
	else std::cout << "NIE" << std::endl;
}