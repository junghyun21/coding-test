#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<double> fail(N + 1);        // 각 스테이지의 실패율 -> 0으로 초기화
    vector<bool> isPush(N + 1);     // 각 stage 번호의 answer에 저장 여부 -> false로 초기화
    
    // 더미
    fail[0] = -1;
    isPush[0] = true;    
    
    // 실패율 = 스테이지에 도달했으나 아직 클리어하지 못한 플레이어의 수 / 스테이지에 도달한 플레이어 수
    double successPlayer;      // 도달함
    double failPlayer;         // 도달했으나 아직 클리어하지 못함
    for(int i = 1; i <= N; ++i) {
        successPlayer = count_if(stages.begin(), stages.end(), [i](int x) {return i < x;});      
        failPlayer = count(stages.begin(), stages.end(), i);
        
        if(successPlayer == 0 && failPlayer == 0) {
            fail[i] = 0;
            continue;
        }
        
        fail[i] = failPlayer / successPlayer;    
    }
    
    // 실패율이 높은 순서대로 내림차순 정렬
    while(find(isPush.begin(), isPush.end(), false) != isPush.end()) {
        double maxFail = *max_element(fail.begin(), fail.end());
        
        auto it = fail.begin();
        while((it = find(it, fail.end(), maxFail)) != fail.end()) {
            int idx = distance(fail.begin(), it);
            
            answer.push_back(idx);
            
            fail[idx] = -1;
            isPush[idx] = true;
        }
    }
    
    return answer;
}