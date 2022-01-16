#include <iostream>
#include <cstdio>

using namespace std;

int get_area(int la, int ra, int ta, int ba, int lb, int rb, int tb, int bb)
{
    int l, r, t, b; //교차하는 영역의 점들

    l = max(la, lb); //왼쪽 x
    r = min(ra, rb); //오른쪽 x
    t = min(ta, tb); //위 y
    b = max(ba, bb); //아래 y

    if(r>=l && t>=b) //영역이 교차하는 경우에만
        return ((r-l)*(t-b)); //넓이  반환
    
    return 0;
}

void test_case()
{
    int ax, ay, bx, by;
    int px, py, qx, qy;
    scanf("%d %d %d %d", &ax, &ay, &bx, &by); //[입력] 첫번째 직사각형을 이루는 서로 대각선으로 마주보는 두 점의 좌표 
    scanf("%d %d %d %d", &px, &py, &qx, &qy); //[입력] 두번째 직사각형을 이루는 서로 대각선으로 마주보는 두 점의 좌표
 
    int la, ra, ba, ta; //직사각형 a
    la = min(ax, bx);
    ra = max(ax, bx);
    ta = max(ay, by);
    ba = min(ay, by);

    int lb, rb, bb, tb; //직사각형 b
    lb = min(px, qx);
    rb = max(px, qx);
    tb = max(py, qy);
    bb = min(py, qy);

    int answer = get_area(la, ra, ta, ba, lb, rb, tb, bb);

    printf("%d\n", answer); //[출력] 두 직사각형이 교차하는 영역의 넓이
}

int main()
{
    int t;
    scanf("%d", &t); //[입력] 테스트케이스의 수

    for(int i = 0; i < t; i++)
        test_case();
    
    return 0;
}