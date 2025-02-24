#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) { 
    vector<int> ans1{1, 2, 3, 4, 5};
    vector<int> ans2{2, 1, 2, 3, 2, 4, 2, 5};
    vector<int> ans3{3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    
    vector<int> matchCnt(3);
    
    for(int i = 0; i < answers.size(); i++) {
        if(answers[i] == ans1[i % ans1.size()])
            ++matchCnt[0];
        
        if(answers[i] == ans2[i % ans2.size()])
            ++matchCnt[1];
        
        if(answers[i] == ans3[i % ans3.size()])
            ++matchCnt[2];
    }
    
    vector<int> answer;
    
    int max = *max_element(matchCnt.begin(), matchCnt.end());
    
    for(int i = 0; i < matchCnt.size(); i++) {
        if(matchCnt[i] == max)
            answer.push_back(i + 1);
    }
 
    return answer;
}