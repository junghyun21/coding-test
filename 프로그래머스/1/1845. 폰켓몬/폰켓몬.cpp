#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    unordered_map<int, int> pets; // <폰켓몬 번호, 해당 폰켓몬의 개수>
    
    for(const int &num : nums)
        ++pets[num];
    
    return (nums.size() / 2 < pets.size()) ? nums.size() / 2 : pets.size();
}