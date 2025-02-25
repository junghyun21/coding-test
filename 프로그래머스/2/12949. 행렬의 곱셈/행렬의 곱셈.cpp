#include <string>
#include <vector>

using namespace std;

    
// arr2의 행(row) 개수
// arr1 * arr2 행렬곱: arr1의 열(col) 개수와 arr2의 행(row) 개수가 동일해야 가능
vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
    vector<vector<int>> answer;
    
    // 행렬곱 크기
    // arr1의 행(row) 크기 * arr2의 열(col) 크기
    // 0으로 초기화
    answer.assign(arr1.size(), vector<int>(arr2[0].size(), 0));

    for(int i = 0; i < arr1.size(); ++i)            // arr1의 행(row)
        for(int j = 0; j < arr2[0].size(); ++j)     // arr2의 열(col)
            for(int k = 0; k < arr2.size(); ++k)    // arr1의 열(col) 및 arr2의 행(row) 
                answer[i][j] += arr1[i][k] * arr2[k][j];
                     
    return answer;
}