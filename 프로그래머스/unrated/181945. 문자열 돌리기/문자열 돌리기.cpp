#include <iostream>
#include <string>

using namespace std;

int main(void) {
    string str;
    cin >> str;
    
    for(char s: str)
    {
        cout << s << endl;
    }
    
    return 0;
}