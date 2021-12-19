#include <cstdio>
#include <iostream>

using namespace std;

int getElementTyoeCount(int data[], int n)
{
    int countType = 1; //화보의 종류는 무조건 1종류 이상

    for(int i = 1; i < n; i++)
    {
        if(data[i-1] != data[i]) //배열의 앞 뒤 요소가 다르면
            countType++; //화보 종류의 수 증가
            
    }

    return countType;
}

int main()
{
    int n;
    int *data;

    scanf("%d", &n); //[입력] 화보의 수
    data = new int[n];

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]); //[입력] 각 화보의 고유번호(오름차순)
    }

    int answer = getElementTyoeCount(data, n);

    printf("%d\n", answer); //[출력] 중복을 제외한 화보의 종류의 수

    delete[] data;

    return 0;
}