#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Item { 
    int w;
    int v;
};

int main() {
	// 물건의 개수, 배낭의 용량
	int N, K; 
	cin >> N >> K;

    vector<Item> items(N + 1);
	for(int i = 1; i <= N; i++){ 
		cin >> items[i].w >> items[i].v; 
	}

	// 물건의 번호 * 무게 한도
    vector<vector<int>> bag(N + 1, vector<int>(K + 1));
	for(int i = 1; i <= N; i++){ // 물건 1~i까지 고려 
		for(int j = 1; j <= K; j++){ // 배낭의 용량 1~K 
			int weight = items[i].w; 
			int value = items[i].v; 

			// i번째 물건의 무게가 현재 배낭 용량보다 큰 경우: i-1)번째 물건까지만 담음
			if(weight > j) {
				bag[i][j] = bag[i - 1][j];
			}
            // i번째 물건을 담거나 vs 안담거나
            else{
				bag[i][j] = max(bag[i - 1][j - weight] + value, bag[i - 1][j]); 
			}
		}
	}

	// 배낭에 넣을 수 있는 물건 가치의 최댓값 
	cout << bag[N][K]; 
    
    return 0;
}