#include <cstdio>
#include <vector>

using namespace std;

class Sieve{
public:
    int maximumValue; //에라토스테네스의 체에서 다룰 가장 큰 범위의 값
    vector<bool> isPrime; //각 숫자별 소수 여부
    Sieve(int maximumValue){
        this->maximumValue = maximumValue;
        this->isPrime.assign(maximumValue + 1, false);
        this->fillSieve();
    }

    bool isPrimeNumber(int num) const{
        return this->isPrime[num];
    }

    //isPrime 배열의 값을 채우는 함수
    void fillSieve(){
        isPrime.assign(this->maximumValue, true); //모두 소수라고 초기화
        isPrime[0] = isPrime[1] = false; //0과 1은 소수가 아님

        for(int num = 2; num < maximumValue; num++){ //[2, maximumVale]사이의 모든 자연수 num에 대해
            if(isPrime[num] == false) //이미 소수가 아니라고 체크되어 있다면 건너 뛴다
                continue;
            
            //이 때 num은 소수임, num * num ~ maximumValue 범위에 있는 num의 배수들을 모두 소수가 아니라고 체크
            //num보다 작은 k에 대해 mul = num * num으로 표현되는 모든 자연수는 이미 처리되었다
            //그러므로 mul = num * num 부터만 처리하면 된다. 최대 100만의 제곱까지 --> long long 타입 
            for(long long mul = (long long) num * num; mul <= maximumValue; mul += num) //mul은 num의 배수!
            {   
                //이 때 mul에 대해서, mul을 나누는 '최초의 소인수 num'이 등장한다
                //이 정보를 저장해 두면 소인수 분해를 할 때 유용하다
                int index = (int) mul;
                isPrime[index] = false;
            }
        }
    }
};

vector<int> getAllPrimeNumbers(int from, int to, const Sieve& sieve){
    vector<int> primes;

    //주어진 범위 안에 존재하는 소수 찾아서 추가
    for(int num = from; num <= to; num++){ 
        if(sieve.isPrimeNumber(num)){
            primes.push_back(num);
        }
    }
    return primes; //from과 to to사이의 소수들
}

void process(int caseIndex, const Sieve& sieve){
    int L, R;
    scanf("%d %d", &L, &R); //[입력] 1이상 100만이하의 두 자연수

    //L이상 R이하의 소수
    vector<int> allPrimeNumbers = getAllPrimeNumbers(L, R, sieve);
    
    printf("Case #%d:\n", caseIndex); //[출력] 테스트케이스의 번호
    printf("%d\n", (int)allPrimeNumbers.size()); //[출력] L이상 R이하의 소수의 갯수
}

int main()
{
    const int MAX_VALUE = 1000000; //전처리
    Sieve sieve = Sieve(MAX_VALUE); //전처리

    int caseSize;
    scanf("%d", &caseSize); //[입력] 테스트케이스의 수

    for(int caseIndex = 1; caseIndex <= caseSize; ++caseSize){
        process(caseIndex, sieve);
    }
}