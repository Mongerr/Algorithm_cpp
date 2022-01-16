#include <time.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{  
    int n;
    cin >> n; //[입력] n(n*n 행렬, 2<=n<=1024, n은 항상 2의 거듭제곱)

    int matrix[n][n]; //행렬 생성

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cin >> matrix[i][j]; //[입력] 각 행의 원소(-10,000 이상 10,000 이하의 정수) 
    }

    clock_t start = clock(); //실행시간 측정 시작

    for(int k = n; k >= 1; k /=2) //행렬 크기를 4분의 1로 줄여가면서 반복
    {
        for(int i = 0; i<k; i+=2) //2x2 행렬의 행(2행씩 묶음)
        { 
            for(int j = 0; j<k; j+=2) //2x2 행렬의 열(2열씩 묶음)
            {
                /*
                2x2 행렬의 인덱스는 다음과 같음
                [ i, j ] [ i, j+1 ]
                [i+1, j] [i+1, j+1]
                */
                
                vector<int> v = {matrix[i][j], matrix[i][j+1], matrix[i+1][j], matrix[i+1][j+1]};
                sort(v.begin(), v.end()); //2x2 정사각형 내에서 오름차순으로 정렬 후
                matrix[i/2][j/2] = v[2]; //2번째로 큰 수만 남김
                //(원래 인덱스를 2로 나눈 몫이 새롭게 들어갈 자리 -> 행렬이 남은 수들로 채워짐)
            }
        }

        //확인용 출력
        // cout << '\n';
        // for(int i = 0; i < k/2; i++)
        // {
        //     for(int j = 0; j < k/2; j++)
        //         cout << matrix[i][j] << ' ';
        //     cout << '\n';
        // }
    }
    
    clock_t end = clock(); //실행시간 측정 종료

    cout << matrix[0][0] <<endl;; //[출력] 222-풀링 반복 후 마지막에 남은 숫자
    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간
    
    return 0;
}