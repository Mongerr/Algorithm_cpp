#include <cstdio>
#include <iostream>

using namespace std;

bool isOrdered(int data[], int n)
{
    int count = 0;

    for(int i = 0; i < n-1; i++) //끝까지 비교하기 위해 n-1로 설정
    {
        if(data[i] > data[i+1]) //배열의 앞 뒤 요소를 비교
        {   
            count++; //앞에 서있는 학생의 키가 더 큰 경우
            break; //반복문 탈출
        }
    }

    //오름차순으로 정렬되어 있는지 여부 return
    if(count > 0)
        return false;
    else
        return true;
}

int main()
{
    int n;
    int *data;

    scanf("%d", &n); //[입력] 학생의 수 
    data = new int[n];

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]); //[입력] 학생들의 키
    }

    bool result = isOrdered(data, n);

    //[출력] 학생들의 키가 오름차순으로 정렬되어 있는지 여부
    if(result){
        printf("YES");
    }
    else{
        printf("NO");
    }

    delete[] data;

    return 0;
}