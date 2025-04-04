#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// genres[i]: 고유번호가 i인 노래의 장르
// plays[i]: 고유번호가 i인 노래의 재생 횟수 
vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    unordered_map<string, int> total_play;
    unordered_map<string, vector<int>> music;
    
    // 해시 테이블 초기화
    for(int i = 0; i < genres.size(); ++i) {
        total_play[genres[i]] += plays[i]; // 특정 장르의 총 재생 횟수
        music[genres[i]].push_back(i); // 장르별로 노래 저장
    }
    
    // 모든 장르를 재생 횟수가 많은 순으로 정렬
    vector<pair<string, int>> vec(total_play.begin(), total_play.end());
    sort(vec.begin(), vec.end(), [](const auto &a, const auto &b){
       return a.second > b.second;
    });
    
    // 특정 장르 내 재생 횟수가 많은 순으로 정렬
    // 재생 횟수가 같은 경우는 고유 번호가 낮은 노래가 먼저 저장됨
    for(auto &e : vec) {
        sort(music[e.first].begin(), music[e.first].end(), [&plays](const int &a, const int &b){
            if(plays[a] == plays[b])
                return a < b;
            
            return plays[a] > plays[b];
        });

        for(int i = 0; i < music[e.first].size() && i < 2; ++i) {
            answer.push_back(music[e.first][i]);
        }
    }

    
    return answer;
}