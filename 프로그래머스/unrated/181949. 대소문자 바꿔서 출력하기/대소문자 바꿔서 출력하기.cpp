#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(void) {
    string str;
    cin >> str;
    
    // // ' ' == 32
    // for(int i = 0; i < str.length(); ++i)
    // {
    //     if(str[i] >= 'a' && str[i] <= 'z')
    //     {
    //         str[i] -= ' ';
    //     }
    //     else
    //     {
    //         str[i] += ' ';
    //     }
    // }
    //
    // cout << str;
    
    for(char s: str)
    {
        if(s >= 'a' && s <= 'z')
        {
            cout << (char)toupper(s);
        }
        else
        {
            cout << (char)tolower(s);
        }
    }
    
    return 0;
}