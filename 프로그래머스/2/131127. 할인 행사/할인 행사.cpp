#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    
    unordered_map<string, int> umap; // <물품 이름(want[i]), 물품 개수(number[i])>
    
    for(int i = 0; i < want.size(); ++i)
        umap[want[i]] = number[i];
   
    for(int i = 0; i < discount.size() - 9; ++i) {
        // i일에 회원가입 시에 할인받을 수 있는 품목
        unordered_map<string, int> discount_umap;
        
        for(int j = i; j < 10 + i; ++j)
            ++discount_umap[discount[j]];
        
        if(umap == discount_umap) 
            ++answer;
    }
    
    return answer;
}