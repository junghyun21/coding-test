#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<char> str1, str2;
    char c;

    str1.push_back('\0'); // dummy
    while((c = cin.get()) != '\n') {
        str1.push_back(c);
    }

    str2.push_back('\0'); // dummy
    while((c = cin.get()) != '\n') {
        str2.push_back(c);
    }

    // DP[i][j]: str1[0...i]와 str2[0...j] 간 LCS의 최대 길이 
    vector<vector<int>> DP(str1.size(), vector<int>(str2.size()));
    for(int i = 1; i < str1.size(); ++i) {
        for(int j = 1; j < str2.size(); ++j) {
            if(str1[i] == str2[j]) {
                DP[i][j] = DP[i - 1][j - 1] + 1;
            }
            else {
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            }

        }
    }

    cout << DP[str1.size() - 1][str2.size() - 1] << endl;

    return 0;
}