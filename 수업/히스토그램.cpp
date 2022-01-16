#include <iostream>
#include <stack>
#include <cmath>
#include <vector>

using namespace std;

class Histogram{
public:
    int height; //히스토그램의 높이
    int leftX; //인덱스 혹은 히스토그램의 왼쪽 변의 x좌표
    int rightX; //히스토그램의 오른쪽 변의 x좌표
    
    //기본 생성자
    Histogram() {}

    //생성자(index와 height를 매개변수로 받음)
    Histogram(int index, int height){
        this->leftX = index;
        this->rightX = this->leftX + 1; //각 히스토그램은 너비가 1이므로
        this->height = height;
    }
};

//왼쪽에서 오른쪽으로 차례로 세워진 히스토그램들 내부에 만들 수 있는
//최대의 직사각형 넓이를 계산하는 함수
long long getLargestRectangleArea(const vector<Histogram>& histograms){
    long long answer = 0; //최대 직사각형의 넓이

    //현재 우측으로 확장 가능성이 있는 히스토그램들
    stack<Histogram> stk;

    //구현상 편의를 위해 가장 왼쪽에 가상의 히스토그램 추가
    stk.push(Histogram(-1, 0));

    //왼쪽부터 오른쪽 히스토그램까지 차례로
    for(int i = 0; i < histograms.size() + 1; i++){    
        Histogram h;
        if(i < histograms.size()){
            h = histograms[i];
        }else{
            //if(i == n)
            //구현상 편의를 위해 가장 오른쪽에 가상의 히스토그램 추가
            h = Histogram(histograms.size(), 0);
        }

        //이전에 확장중이던 히스토그램들 중, h보다 높이가 높은 히스토그램들은
        //더 이상 확장될 수 없다 => 최대 넓이가 결정된다
        while(stk.size() > 1 && stk.top().height > h.height){ //높이가 오름차순이 아닌동안!
            //확장중이던 히스토그램
            Histogram lh = stk.top(); //삭제하기 전의 top을 나중에 사용하기 위함
            stk.pop();

            //그 이전의 히스토그램(왼쪽 확장의 끝)
            Histogram bh = stk.top();

            //현재 추가된 h의 바로 왼쪽까지 확장중이었다
            long long width = abs(h.leftX - bh.rightX); //폭 = 현재h의 왼쪽 - 왼쪽 확장 끝의 오른쪽
            long long height = lh.height; //높이 = 확장 중이던 히스토그램의 높이
            long long area = width * height; //면적
            // cout << width << '*' << height << endl;

            //최대 값 갱신
            answer = max(answer, area);
        }

        //h를 새로 추가한다
        stk.push(h);
    }

    return answer; //최대 넓이 반환
}

void process(int caseIndex){
    int n;
    cin >> n; //[입력] 히스토그램을 구성하는 직사각형 모양 기둥의 수(10만 이하의 자연수)

    vector<Histogram> histograms; //벡터 선언

    for(int i = 0; i < n; i++){
        int height;
        cin >> height; //[입력] 각 직사각형 모양 기둥의 높이(10만 이하의 자연수)
        histograms.push_back(Histogram(i, height)); //벡터의 맨 끝에 삽입
    }

    //직사각형의 최대 넓이 구하기
    long long answer = getLargestRectangleArea(histograms);
    cout << answer << endl; //[출력] 히스토그램 내부에 존재할 수 있는 직사각형의 최대 넓이
}

int main()
{
    int caseSize;
    cin >> caseSize; //[입력] 테스트케이스의 수

    //caseSize만큼 반복하면서 process함수 실행
    for(int caseIndex = 1; caseIndex <= caseSize; caseIndex += 1){
        process(caseIndex);
    }
}