#include <string>
#include <vector>

using namespace std;

// progresses: 배포되어야 하는 순서대로 작업의 진도가 적힌 정수 배열
// speeds: 각 작업의 개발 속도가 적힌 정수 배열 
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer; // 각 배포마다 배포되는 기능의 개수

    int currIdx = 0;
    while(currIdx < progresses.size()) {
        // 각 작업의 작업 진도를 갱신
        for(int i = currIdx; i < progresses.size(); ++i) {
            progresses[i] += (progresses[i] < 100) ? speeds[i] : 0;
        }
        
        // 한 번에 배포된 기능의 개수 카운트
        int cnt = 0;
        while(currIdx < progresses.size() && progresses[currIdx] >= 100) {
            ++cnt;
            ++currIdx;
        }
        
        // 개수를 answer에 저장
        if(cnt > 0) {
            answer.push_back(cnt);
        }
    }
    
    return answer;
}