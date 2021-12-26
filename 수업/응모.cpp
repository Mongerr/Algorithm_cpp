#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SERIAL_NUMBER = 100000;

void fillFrequencyTable(const vector<int> & data, int n, vector<int> & table)
{
    //빈도수 테이블 초기화
    table.clear();
    table.resize(MAX_SERIAL_NUMBER+1, 0);

    for(int i = 0; i < n; i++)
        table[data[i]] += 1; //data에 대한 빈도수 1 증가
}

vector<int> getUniqueElements(const vector<int> & data, int n)
{
    vector<int> ret; //유일한 원소들 배열
    vector<int> table; //data에 대한 빈도수 테이블

    fillFrequencyTable(data, n, table);

    //존재할 수 있는 모든 시리얼 넘버에 대해 차례로 조회
    for(int number = 1; number <= MAX_SERIAL_NUMBER; number++)
    {
        if(table[number] == 1) //한 번만 등장한 number를 차례로 정답 리스트에 추가
            ret.push_back(number);
    }

    //오름차순 순서로 추가했기 때문에 ret에 대한 정렬은 불필요
    return ret;
}

int main()
{
    int n;
    scanf("%d", &n); //[입력] 응모 번호 개수

    //벡터 컨테이너: 자동으로 메모리가 할당되는 배열
    vector<int> data = vector<int>(n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &data[i]); //[입력] 응모한 시리얼 번호(1 이상 10만 이하)
    }

    const vector<int> answer = getUniqueElements(data, n);

    for(int i = 0; i < answer.size(); ++i){
        if(i > 0){
            printf(" ");
        }
        printf("%d", answer[i]); //[출력] 두 번 이상 응모한 번호를 제외한 나머지 번호들(오름차순)
    }

    return 0;
}