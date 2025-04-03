#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    
    unordered_map<string, int> umap; // <물품 이름(want[i]), 물품 개수(number[i])>
    
    for(int i = 0; i < want.size(); ++i) {
        umap.insert({want[i], number[i]});
    }
    
    queue<string> items;
   
    for(int i = 0; i < discount.size(); ++i) {
        // 현재 물품이 구매할 항목에 포함되지 않는 경우: 장바구니 목록 모두 삭제
        if(umap.find(discount[i]) == umap.end()) {
            while(!items.empty()) {
                ++umap[items.front()];
                items.pop();
            }
            
            continue;
        }
        
        // 장바구니가 가득 차지 않은 경우
        if(items.size() < 10) {
            items.push(discount[i]);
            --umap[discount[i]];
        }
        // 장바구니가 가득 찬 경우
        else{
            ++umap[items.front()];
            items.pop();
            
            items.push(discount[i]);
            --umap[discount[i]];
        }
        
        // 초과구매한 물품이 있는지 확인
        if(items.size() == 10) {
            bool hasNegative = false;
            for (const auto& [key, value] : umap) {
                if (value < 0) {
                    hasNegative = true;
                    break;
                }
            }
            
            if(!hasNegative) ++answer;
        }
    }
    
    return answer;
}