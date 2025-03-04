#include <vector>

using namespace std;

vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;
    vector<int> x;
    
    for(int i = 1; i <= n; ++i) 
        x.push_back(i);
    
    for(long long i = left; i <= right; ++i) {
        int row = i / n;
        int col = i % n;
        int data = (row < col) ? x[row] + (col - row) : x[row];
        
        answer.push_back(data);
    }
    
    return answer;
}