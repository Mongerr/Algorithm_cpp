#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 1000000;
vector<int> FIBONACCI_TABLE;

//피보나치 수열의 1 ~ n번째 항을 배열에 저장하여 반환해주는 힘수
//단, 항의 가장 뒤 8자리만을 저장
vector<int> makeFibonacciTable(int n)
{
    const int MOD = 100000000;

    vector<int> ret(n+1); //피보나치 배열 선언
    ret[1] = 0;
    ret[2] = 1;

    //f(n) = f(n-1) + f(n-2)
    for(int i = 3; i <= n; i++)
    {
        ret[i] = ret[i-1] + ret[i-2];

        //모듈러 값을 이용해 마지막 8자리만 남기도록 함
        //((A % MOD) + (B % MOD)) % MOD == (A + B) % MOD
        //위 식이 성립하기 때문에 피보나치의 값이 잘못될 일은 없다 
        ret[i] %= MOD;
    }

    return ret;
}

int getFibo(int n)
{
    int answer = FIBONACCI_TABLE[n];

    return answer;
}

int main()
{
    FIBONACCI_TABLE = makeFibonacciTable(MAX_N); //전처리를 통해 미리 계산

    int caseSize;
    scanf("%d", &caseSize); //[입력] 테스트케이스의 수

    for(int caseIndex = 1; caseIndex <= caseSize; ++caseIndex){
        int n;
        scanf("%d", &n); //[입력] 각 테스트케이스(1이상 100만 이하 자연수 N)

        int answer = getFibo(n);
        printf("%d\n", answer); //[출력] 각 테스트케이스의 정답(피보나치 수열의 N번째 숫자)
    }

    FIBONACCI_TABLE.clear();

    return 0;
}