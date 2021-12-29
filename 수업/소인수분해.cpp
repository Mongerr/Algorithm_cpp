#include <cstdio>
#include <vector>

using namespace std;

//자연수 n을 구성하는 모든 소인수를 반환하는 함수
vector<long long> factorize(long n){
    vector<long long> factors;

    //약수 후보 div(초기값 2)가 루트n 이하일 동안 반복
    for(int div = 2; div * div <= n; div += 1){
        while(n % div == 0){
            //div이 n의 약수라면?
            //이 때, div보다 작은 약수는 모두 처리되었으므로 div는 소인수임이 보장된다
            
            factors.push_back(div); //소인수 목록에 div 추가

            //n을 div로 나눔
            //이후에는 div를 제외한 소인수를 찾게 된다
            n /= div;
        }
    }
    if(n > 1){
        //소인수를 찾지 못하고 남아있는 n이 존재한다면, 소수일 수 밖에 없다
        factors.push_back(n); //이를 소인수에 추가
    }

    return factors; //소인수 목록 반환
}

void process(int caseIndex){
    long long n;
    scanf("%lld", &n); //[입력] 소인수 분해를 할 자연수(2억 이상 10억 이하)

    vector<long long> factors = factorize(n);

    printf("#%d:\n", caseIndex); //[출력] 테스트케이스의 번호
    for(int i = 0; i < factors.size(); ++i){
        if(i > 0){
            printf(" ");
        }
        printf("%lld", factors[i]); //[출력] 소인수들(오름차순)
    }
    printf("\n");
}

int main()
{
    int caseSize;
    scanf("%d", &caseSize); //[입력] 테스트케이스의 수

    for(int caseIndex = 1; caseIndex <= caseSize; ++caseIndex){
        process(caseIndex);
    }
}