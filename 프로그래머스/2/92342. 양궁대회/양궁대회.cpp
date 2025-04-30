#include <vector>

using namespace std;

vector<int> answer(11);
int max_diff;

void dfs(const vector<int> &Apeach_info, 
         vector<int> Ryan_info,
         int Ryan, 
         int Apeach, 
         int arrow_cnt,
         int score)
{
    if(arrow_cnt > 0 && score > 0) {
        // 라이언 win
        int idx = 10 - score;
        if(arrow_cnt > Apeach_info[idx]) {
            int temp = Apeach;
            
            Ryan_info[idx] += (Apeach_info[idx] + 1);
            if(Apeach_info[idx] > 0) {
                temp -= score;
            }
            
            dfs(Apeach_info,
                Ryan_info,
                Ryan + score,
                temp,
                arrow_cnt - (Apeach_info[idx] + 1), 
                score - 1);
            Ryan_info[idx] -= (Apeach_info[idx] + 1);
        }
        
        // 어피치 win || 아무도 점수 획득 x
        dfs(Apeach_info,
                Ryan_info,
                Ryan,
                Apeach,
                arrow_cnt, 
                score - 1);
    }
    else {
        if(arrow_cnt > 0) {
            Ryan_info[10 - score] += arrow_cnt;
        }
        
        int diff = Ryan > Apeach ? Ryan - Apeach : 0;
        
        if(max_diff < diff) {
            max_diff = diff;
            answer = Ryan_info;
        }
        else if(max_diff > 0 && max_diff == diff) {
            for(int i = 10; i >= 0; --i) {
                if(answer[i] == Ryan_info[i])
                    continue;
                
                if(answer[i] < Ryan_info[i])
                    answer = Ryan_info;
                
                break;
            }
        }
    }
    
    return;
}

vector<int> solution(int n, vector<int> info) {
    vector<int> Ryan_info(info.size(), 0);
    
    int Apeach = 0;
    for(int i = 0; i < 11; ++i) {
        if(info[i] > 0)
            Apeach += (10 - i);
    }
    
    dfs(info, Ryan_info, 0, Apeach, n, 10);
    
    if(max_diff == 0) {
        answer.assign(1, -1);
    }
    
    return answer;
}