#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

int main()
{
    int n, k, x, y;
    
    cin >> n >> k; // n: 집의 개수, k: 대피소 개수
    
    vector<pair<int, int>> houses;
    for(int i = 0; i < n; ++i) {
        cin >> x >> y;
        houses.emplace_back(x, y);
    }
    
    // 인접 행렬 생성
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    for(int i = 0; i < n; ++i) {
        int x1 = houses[i].first;
        int y1 = houses[i].second;
        
        for(int j = i + 1; j < n; ++j) {
            int x2 = houses[j].first;
            int y2 = houses[j].second;
            
            adjMatrix[i][j] = adjMatrix[j][i] = abs(x1 - x2) + abs(y1 - y2);
        }
    }
    
    int answer = INF;
    if(k == 1) {
        for(int i = 0; i < n; ++i) {
            int maxDistance = 0;

            for(int j = 0; j < n; ++j) {
                maxDistance = max(maxDistance, adjMatrix[i][j]);
            }
        
            answer = min(answer, maxDistance);
        }
    }
    else if(k == 2) {
        for(int i = 0; i < n; ++i) {            
            for(int j = i + 1; j < n; ++j) {
                int maxDistance = 0;

                for(int k = 0; k < n; ++k) {
                    maxDistance = max(maxDistance, min(adjMatrix[i][k], adjMatrix[j][k]));
                }

                answer = min(answer, maxDistance);
            }
        }
    }
    else {
        for(int i = 0; i < n; ++i) {            
            for(int j = i + 1; j < n; ++j) {
                for(int k = j + 1; k < n; ++k) {
                    int maxDistance = 0;

                    for(int l = 0; l < n; ++l) {
                        maxDistance = max(maxDistance, min(adjMatrix[i][l], min(adjMatrix[j][l], adjMatrix[k][l])));
                    }
                    
                    answer = min(answer, maxDistance);
                }
                
            }
        }
    }

    cout << answer << endl;

    return 0;
}