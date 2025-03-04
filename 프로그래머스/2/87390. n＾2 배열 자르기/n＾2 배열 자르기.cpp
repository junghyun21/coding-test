#include <vector>

using namespace std;

// n*n 크기의 1차원 배열 생성 및 초기화 시, 메모리/시간 초과 발생!!
// 처음부터 push_back()을 통해 right - left + 1 크기의 답안(answer)을 생성하자
vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;
    vector<int> x;
    
    // {1, ..., n}의 배열 생성
    for(int i = 1; i <= n; ++i) 
        x.push_back(i);
    
    // n*n 크기의 1차원 배열(arr) 중, arr[left] ... arr[right] 값만 저장
    for(long long i = left; i <= right; ++i) {
        int row = i / n;
        int col = i % n;
        int data = (row < col) ? x[row] + (col - row) : x[row];
        
        answer.push_back(data);
    }
    
    return answer;
}