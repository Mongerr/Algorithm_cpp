#include <cstdio>
#include <cmath>
#include <climits>
#include <iostream>

using namespace std;

class Point2D {
private:
    int x;
    int y;

public:
    Point2D(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }

    //2차원 평면 상에서 점 this부터 점 target까지 거리의 제곱을 계산하는 함수
    int getSquareDistanceTo(const Point2D &target) const{
        int dx = abs(this->x - target.x); //x좌표의 거리
        int dy = abs(this->y - target.y); //y좌표의 거리

        return dx*dx + dy*dy; //두 점의 거리 제곱 반환
    }

    //거리의 제곱에 루트를 씌워 거리를 반환하는 함수
    double getDistanceTo(const Point2D &target) const{
        double sqd = (double) this->getSquareDistanceTo(target);
        return sqrt(sqd);
    }
};

int main()
{
    int n;
    Point2D *points;

    scanf("%d", &n); //[입력] 천체의 수
    points = new Point2D[n]; //천체의 수만큼 객체 배열 생성

    for(int i = 0; i < n; i++){ //천체의 수만큼 반복
        int x, y;
        scanf("%d %d", &x, &y); //[입력] 천체의 위치를 나타내는 두 정수

        points[i] = Point2D(x, y); //좌표값 설정한 객체 생성
    }

    int min_sqd = INT_MAX; //최소 거리를 INT_MAX로 초기화
    int min_cnt = 0; //최소 거리만큼 떨어진 천체 쌍의 수 초기화

    //모든 쌍을 반복
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            // i와 j번째 천체의 거리(제곱) 구하기
            int sqd = points[i].getSquareDistanceTo(points[j]); 
            if(sqd < min_sqd){ //최소 거리보다 작으면
                min_sqd = sqd; //최소 거리 갱신
                min_cnt = 1; //최소 거리만큼 떨어진 천체 쌍의 수 = 1
            }else if(sqd == min_sqd){ //최소 거리와 같으면
                min_cnt++; //1 증가
            }
        }
    }

    double distance = sqrt(min_sqd); //거리의 제곱에 루트 씌워 거리 구하기
    printf("%.1f\n", distance); //[출력] 가장 가까운 두 천체의 거리(소수점 첫 번째 자리까지)
    printf("%d\n", min_cnt); //[출력] 그 거리만큼 떨어진 천체 쌍의 수

    delete[] points;
    return 0;
}
