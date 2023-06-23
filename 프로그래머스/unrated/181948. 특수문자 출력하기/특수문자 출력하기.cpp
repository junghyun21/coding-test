#include <iostream>

using namespace std;

int main(void) {
    // C++11부터 원시문자리터럴(Raw String Litaral) 사용 가능
    // 이스케이프 문자 사용 없이 문자열 만들 수 있음
    cout << R"(!@#$%^&*(\'"<>?:;)";
    return 0;
}