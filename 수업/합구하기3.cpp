#include <cstdio>
#include <iostream>

using namespace std;

// 1부터 i까지의 자연수의 합을 계산하는 함수
int getRangeSumFromOne(int i)
{   
    int sum = 0;

    for(int j = 1; j <= i; j++) //j를 1에서 i까지 변경하며 반복
        sum += j;

    return sum; //1부터 i까지의 자연수의 합
}

long long getAnswer(int N)
{
    long answer = 0;

    for(int i = 1; i <= N; i++) //i를 1에서 N까지 변경하며 반복
    {   
        int rangeSum = getRangeSumFromOne(i); //1부터 i까지의 자연수의 합
        answer += rangeSum; //모든 합을 누적
    }
    return answer;
}

int main()
{
    int n;

    scanf("%d", &n); //[입력] 자연수 n

    //(1이상 1이하 모든 자연수의 합)+(1이상 2이하 모든 자연수의 합)...+(1이상 n이하의 모든 자연수의 합)
    long long answer = getAnswer(n);

    printf("%lld\n", answer); //[출력] 입력값 n에 대하여 계산한 결과

    return 0;
}