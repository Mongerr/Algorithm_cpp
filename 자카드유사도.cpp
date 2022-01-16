#include <time.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

double solution(string string1, string string2)
{
    vector<string> str1, str2; //두 글자씩 끊어서 만들 다중집합

    transform(string1.begin(), string1.end(), string1.begin(), ::toupper); //대문자 변환
	transform(string2.begin(), string2.end(), string2.begin(), ::toupper); //대문자 변환

    for(int i = 0; i < string1.size()-1; i++) //string1의 두 글자씩 끊어서 다중집합 str1 만들기
    {
        if((string1[i] >= 'A' && string1[i] <= 'Z') && (string1[i+1] >= 'A' && string1[i+1] <= 'Z')) //영문자로 된 글자 쌍만 유효
            str1.push_back(string1.substr(i,2));
    }
    for(int i = 0; i < string2.size()-1; i++) //string2의 두 글자씩 끊어서 다중집합 str2 만들기
    {
        if((string2[i] >= 'A' && string2[i] <= 'Z') && (string2[i+1] >= 'A' && string2[i+1] <= 'Z')) //영문자로 된 글자 쌍만 유효
            str2.push_back(string2.substr(i,2));
    }

    if(str1.size() == 0 && str2.size() == 0) return 1; //두 집합이 모두 공집할일 경우에는 자카드 유사도가 1

    double union_a = str1.size() + str2.size(); //합집합 원소의 개수 union_a
    double intersection = 0; //교집합 원소의 개수 intersection

    for(int i = 0; i < str1.size(); i++) //str1에 있는 원소가
    {
        for(int j = 0; j < str2.size(); j++)
        {
            if(str1[i] == str2[j]) //str2에 존재할 때
            {
                intersection ++; //교집합 1증가
                str2.erase(str2.begin()+j); //str2에서 해당 원소 지우기
                break; //str1의 다음 원소 검사
            }
        }
    }

    union_a -= intersection; //합집합 원소의 개수(str1.size() + str2.size() - 교집합)

    return intersection/union_a; //자카드 유사도 return
}

int main()
{  
    int time;
    string string1, string2;
    
    //[입력] 두 문자열
    getline(cin, string1);
    getline(cin, string2);
    
    clock_t start = clock(); //실행시간 측정 시작

    double answer = solution(string1, string2); //자카드 유사도 구하기
    cout << int(answer * 65536) << endl; //[출력] (자카드 유사도 * 65536)의 정수 부분

    clock_t end = clock(); //실행시간 측정 종료

    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간
    
    return 0;
}