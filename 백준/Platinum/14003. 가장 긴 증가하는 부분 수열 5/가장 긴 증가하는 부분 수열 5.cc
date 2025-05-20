#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;
    
    vector<int> A(N);
    for(int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    vector<int> lis;
    vector<int> index(N, -1);

    lis.push_back(A[0]);
    index[0] = 0;

    for(int i = 1; i < N; ++i) {
        if(lis.back() < A[i]) {
            index[i] = lis.size();
            lis.push_back(A[i]);
        }
        else {
            int low = 0;
            int high = lis.size() - 1;

            while(low <= high) {
                int mid = (low + high) / 2;

                if(lis[mid] == A[i]) {
                    low = mid;
                    break;
                }
                else if(lis[mid] < A[i]) {
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }

            lis[low] = A[i];
            index[i] = low; 
        }
    }

    vector<int> answer(lis.size());
    for(int i = index.size() - 1, j = lis.size() - 1; i >= 0 && j >= 0; --i) {
        if(index[i] == j) {
            answer[j--] = A[i];
        }
    }

    cout << answer.size() << endl;
    for(const int &a : answer) {
        cout << a << " ";
    }
    cout << endl;

    return 0;
}