#include <time.h>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int A, B;
    cin >> A >> B; //[입력] 정수 A와 B

    clock_t start = clock(); //실행시간 측정 시작
    
    int cnt = 1; //연산 횟수
    // cout << stoi(to_string(A)+"1");

    if (A == B) //A와 B가 같으면 연산 횟수는 0
        return cnt; //cnt = A를 B로 바꾸는 데 필요한 연산의 최소값 + 1

    /*
    A -> B에서 가능한 연산이 두 가지
    B -> A에서 가능한 연산도 두 가지

    B가 1로 끝나는 경우 그 1을 없애기
    B가 짝수인 경우 2로 나누기
    
    A가 B와 같아질 때까지 두 연산을 반복
    */
    while(A!=B) //A와 B가 같지 않은 동안 반복
    {   
        if(A > B) //A가 B보다 커졌다면 A를 B로 바꿀 수 없는 것
        {
            cnt = -1;
            break;
        }

        if(to_string(B).back() == '1') //B가 1로 끝나는 경우(B%10 == 1)
        {
            B /= 10; //마지막 자릿수 없애기
            cnt ++; //연산 횟수 증가
            // cout << B << endl;
        } 
        else if(B%2 == 0) //B가 짝수인 경우
        {
            B /= 2; //2로 나누기
            cnt ++; //연산 횟수 증가
            // cout << B << endl;
        }
        else{ //두 경우에 해당하지 않으면 A를 B로 바꿀 수 없는 것
            cnt = -1;
            break;
        }
    }

    cout << cnt << endl; //[출력] A를 B로 바꾸는 데 필요한 연산의 최소값 + 1, 바꿀 수 없는 경우에는 -1
    
    clock_t end = clock();
    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간

    return 0;
}