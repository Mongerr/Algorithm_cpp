#include <cstdio>
#include <iostream>

using namespace std;

int getMaxmumHeight(int Height[], int month[], int n, int m)
{
    int maxHeight = -1; //생일에 해당 달에 속한 도토리가 없는 경우 -1을 출력
    for(int i = n; i >= 0; i--) //도토리들은 현재 키에 대해 오름차순으로 서 있으므로 뒤에서부터 확인
    {
        if(m == month[i]) //현재 달과 도토리의 생일이 속한 달이 일치하는 경우
        {
            maxHeight = Height[i]; //가장 큰 키
            break; //반복문 탈출
        }    
    }
    
    return maxHeight;
}

int main()
{
    int n, m;
    int *height;
    int *month;

    scanf("%d", &n); //[입력] 도토리의 수
    height = new int[n];
    month = new int[n];
    
    for(int i = 0; i < n; i++)
    {   
        scanf("%d", &height[i]); //[입력] n개의 도토리의 키
    }
    for(int i = 0; i < n; i++)
    {   
        scanf("%d", &month[i]); //[입력] n개의 도토리들의 생일이 속한 달
    }
    scanf("%d", &m); //[입력] 현재 달

    int answer = getMaxmumHeight(height, month, n, m);

    printf("%d\n", answer); //[출력] 이번 달에 생일이 있는 도토리들 중 가장 큰 도토리의 키

    delete[] height;
    delete[] month;

    return 0;
}