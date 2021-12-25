#include <cstdio>
#include <iostream>

using namespace std;

bool isPrime(int N) //N이 소수인지 판별하는 함수
{
    if(N == 1) return false; //1은 소수가 아님
    for(int i = 2; i*i <= N; i++) // i = 2부터 루트N까지 반복
    {
        if(N % i == 0) //N이 i로 나누어 떨어진다면
            return false; //N은 소수가 아님
    }
    
    return true; //N은 소수
}

void testcase(int caseIndex)
{
    int n;
    scanf("%d", &n); //[입력] 판별할 자연수 (1이상 10억 이하)

    bool result = isPrime(n); //소수인지 판별한 결과

    printf("Case #%d\n", caseIndex); //[출력] 테스트 케이스 번호
    if(result) //[출력] 판별 결과
    {
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
}

int main()
{
    int caseSize;
    scanf("%d", &caseSize); //[입력] 테스트 케이스의 숫자
    for(int caseIndex = 1; caseIndex <= caseSize; caseIndex += 1)
    {
        testcase(caseIndex); //테스트 케이스의 수만큼 반복
    }
    return 0;
}