#include <cstdio>
#include <iostream>

using namespace std;

bool isInside(long long x, long long y, long long R)
{   
    //원의 부등식 (x^2 + y^2 < r^2)을 만족하면 좌표가 원의 내부에 있음
    return (x*x + y*y < R*R);

}

void testcase(int caseIndex){
    long long R;
    scanf("%lld", &R); //[입력] 계산하고자 하는 원의 반지름의 픽셀 수 R

    long long sum = 0; //1사분면에 존재하는 총 픽셀의 수
    long long y = R;
    for(long x = 0; x <= R; x++){ //x값을 반지름의 픽셀수까지 증가하면서
        long long height = 0;
        for(; y >=0; y--){ //위에서 부터 내려오다가
            if(isInside(x,y,R)){ //가장 최초로 원 안에 포함덴 픽셀(x,y)
                height = (y+1); //이 그룹의 높이는 (y+1)이 된다 -> x축에 대한 픽셀 수
                break;
            }
        }
        sum += height; //모든 x의 height값을 누적
    }

    printf("#%d\n", caseIndex); //[출력] 테스트케이스의 번호
    printf("%lld\n", sum*4); //[출력] 원이 포함하는 픽셀의 수
}

int main()
{
    int caseSize;
    scanf("%d", &caseSize); //[입력] 테스트케이스의 수
    for(int caseIndex = 1; caseIndex <= caseSize; caseIndex += 1)
    {
        testcase(caseIndex); //테스트케이스 수행
    }
    return 0;
}