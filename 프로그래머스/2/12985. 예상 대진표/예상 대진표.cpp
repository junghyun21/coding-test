int solution(int n, int a, int b)
{
    int answer = 0;
    
    do {
        a = (a + 1) / 2;
        b = (b + 1) / 2;
        ++answer;
    } while(a != b);

    return answer;
}