#include <cstdio>

using namespace std;

const int MAX_TABLE_LENGTH = 10000;

//data[0] ~ data[n-1]에 등장한 번호들에 대한 빈도수 테이블을 채우는 함수
void fillFrequencyTable(int data[], int n, int table[])
{
    for(int i = 0; i < MAX_TABLE_LENGTH; i++)
        table[i] = 0; //빈도수 테이블 초기화

    for(int i = 0; i < n; i++)
        table[data[i]] += 1; //등장한 번호에 대한 빈도수 값 1 증가

}

//data[0] ~ data[n-1] 사이에서 가장 많이 등장한 번호를 반환하는 함수
int getFrequentNumber(int data[], int n)
{
    int frequent_number = 0;
    int table[MAX_TABLE_LENGTH]; //0~9999까지 숫자의 횟수를 카운트하는 히스토그램
    
    fillFrequencyTable(data, n, table);

    for(int i = 0; i < MAX_TABLE_LENGTH; i++)
    {
        if(table[i] > table[frequent_number]) //횟수가 같은 번호가 두개 이상인 경우 사전순으로 빠른 숫자 선택
            frequent_number = i;
    }

    return frequent_number; //가장 많이 등장한 번호 반환, 여러개인 경우 사전순으로 가장 빠른 번호
}

int main()
{
    int n;

    scanf("%d", &n); //[입력] 전화번호의 수
    int* data = new int[n];

    for(int i = 0; i < n; ++i){
        scanf("%d", &data[i]); //[입력] 4개의 자연수로 구성 된 전화번호 뒷자리(0000~9999)
    }

    int answer = getFrequentNumber(data, n);

    printf("%04d", answer); //[출력] 전화번호 뒷자리들 중 가장 많이 등장한 번호(네 자리 숫자로 출력)
 
    delete[] data;

    return 0;
}