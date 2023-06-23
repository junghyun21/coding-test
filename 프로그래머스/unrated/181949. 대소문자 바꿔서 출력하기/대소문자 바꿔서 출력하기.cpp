#include <iostream>
#include <string>

using namespace std;

int main(void) {
    string str;
    cin >> str;
    
    // ' ' == 32
    for(int i = 0; i < str.length(); ++i)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] -= ' ';
        }
        else
        {
            str[i] += ' ';
        }
    }
    
    cout << str;
    
    return 0;
}