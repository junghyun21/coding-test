#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

bool solution(vector<string> phone_book) {
    vector<unordered_set<string>> numbers(21); // 길이 1 ~ 20
    
    // numbers[번호의 길이]
    for(const auto &p : phone_book)
        numbers[p.size()].insert(p);
    
    // phone_book의 요소들 하나씩 검사
    for(int i = 0; i < phone_book.size(); ++i) {  
        // 앞부터 한글자, 두글자, ... 가 다른 번호와 동일한지 확인
        for(int j = 1; j < phone_book[i].size(); ++j) {
            string temp = phone_book[i].substr(0, j);
            if(numbers[j].find(temp) != numbers[j].end())
                return false;
        }
    }
    
    return true;
}