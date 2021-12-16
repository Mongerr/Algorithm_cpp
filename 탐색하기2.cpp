#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

void printIndexes(string school[], int n)
{
    int first = -1; //배열에서 소속이 "AJOU"인 첫 원소의 인덱스, 존재하지 않으면 -1
    int last = -1; //배열에서 소속이 "AJOU"인 마지막 원소의 인덱스, 존재하지 않으면 -1

    for(int i = 0; i < n; i++) //사람들의 수 n만큼 반복
    {
        if(school[i] == "AJOU") //소속학교가 "AJOU"와 일치하는 경우
        {
            if(first == -1) //소속이 "AJOU"인 첫 원소의 인덱스(first)가 아직 존재하지 않는 경우
                first = i+1; //배열의 인덱스는 0부터 시작하므로 1을 더함
            last = i+1; //소속이 "AJOU"인 마지막 원소의 인덱스(last) 갱신, 배열의 인덱스는 0부터 시작하므로 1을 더함
        }
    }
    printf("%d %d\n", first, last); //[출력] 소속이 "AJOU"인 첫 원소와 마지막 원소
}

int main()
{
    int n;
    char buff[11];
    string *school;

    scanf("%d", &n); //[입력] 데이터의 수 n(사람들의 수)
    school = new string[n]; //각 사람들의 소속학교 정보 배열

    for(int i = 0; i < n; i++)
    {
        scanf("%s", buff); //[입력] 각 사람들의 소속학교 입력
        school[i] = buff; //배열에 저장
    }

    printIndexes(school, n);

    delete[] school;
    return 0;
}