#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N; // 칠판에 적을 자연수 개수 (1 <= S <= E <= N)
    int M; // 질문 개수
    int S, E; // 팰린드롬 수의 시작 점과 끝 점

    cin >> N;
    
    vector<int> num(N + 1);
    for(int i = 1; i <= N; ++i)
        cin >> num[i];

    cin >> M;

    vector<pair<int, int>> idx(M);
    for(int i = 0; i < M; ++i)
        cin >> idx[i].first >> idx[i].second;

    // --------------------------------------
    // 팰린드롬일 때 양 옆의 수를 보며, 그 다음도 팰린드롬인지 확인
    // 행: S, 열: E
    vector<vector<bool>> is_palindrome(N + 1, vector<bool>(N + 1));
    for(int i = 1; i <= N; ++i) {
        // 홀수인 경우
        int s = i;
        int e = i;

        while(s >= 1 && e <= N) {
            if(num[s] != num[e])
                break;

            is_palindrome[s--][e++] = true;
        }

        // 짝수인 경우
        s = i;
        e = s + 1;

        while(s >= 1 && e <= N) {
            if(num[s] != num[e])
                break;

            is_palindrome[s--][e++] = true;
        }
    }

    // ---------------------------------------
    vector<bool> res;
    for(auto i : idx) {
        int start = i.first;
        int end = i.second;

        cout << is_palindrome[start][end] << '\n';
    }
    
    return 0;
}