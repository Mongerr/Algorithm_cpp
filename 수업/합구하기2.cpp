#include <stdio.h>
#include <iostream>

using namespace std;

void solve(int data[], int n, int p, int q)
{   
    int cnt = 0, weight_sum = 0;
    for(int i = 0; i < n; i++) //전체 회원의 수 n만큼 반복
    {
        if (data[i] <= p) //체중 제한(p) 보다 몸무게가 적은 경우
        {   
            cnt ++; //체중 제한에 걸리지 않은 회원의 수 1 증가
            weight_sum += data[i]; //해당 회원의 몸무게를 몸무게의 총 합에 누적
        }
    }

    printf("%d %d\n", cnt, weight_sum); //[출력] 체중 제한에 걸리지 않은 회원의 수와 그들의 몸무게의 총 합
    
    //[출력] 그들 모두가 함께 놀이기구에 탑승할 수 있는지 여부 YES or NO
    if(weight_sum <= q) //몸무게의 총 합(weight_sum)이 놀이기구의 최대 하중(q)보다 작은 경우 YES
        printf("YES\n");
    else //반대의 경우 NO
        printf("NO\n");
}

int main()
{
    int n, p, q;
    int *data;

    scanf("%d %d %d", &n, &p, &q); //[입력] 동아리 회원의 수 N, 놀이기구 탑승 제한 체중 P, 놀이기구의 최대 하중 Q
    data = new int[n];
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &data[i]); //[입력] 각 회원의 몸무게
    }

    solve(data, n, p, q);

    delete[] data; //메모리 해제
    return 0;
}