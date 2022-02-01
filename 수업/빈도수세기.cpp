#include <stdio.h>
#include <map>

using namespace std;

int main()
{
    int N; 
    scanf("%d", &N); //[입력] 주어질 정수들의 총 개수(20만 이하의 자연수)


    //각 <정수, 빈도수> 형태로 key-value를 저장할 Map 자료구조
    //frequencyMap := 이전에 입력된 정수들의 빈도수를 저장하고 있다
    map<int, int> frequencyMap;

    for(int i = 0; i < N; i++){
        int X;
        scanf("%d", &X); //[입력] 정수
        frequencyMap[X]++; //입력된 정수(key)의 빈도수(value)를 +1

        //[출력] 현재까지 입력으로 주어진 숫자의 종류와 해당 숫자(X)가 등장한 횟수
        printf("%lu %d\n", frequencyMap.size(), frequencyMap[X]);
    }

    return 0;
}
/*
map<int, int>::iterator it;

for(it = frequencyMap.begin(); it != frequencyMap.end(); it++)
    printf("%d %d\n", it->first, it->second); //key기준으로 오름차순
*/