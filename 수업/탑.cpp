#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Tower{
public:
    int index; //타워의 인덱스
    int height; //타워의 높이
    int targetTowerIndex; //이 타워에 레이저를 수신하는 대상 타워
    
    //생성자(매개변수는 타워의 인덱스와 높이)
    Tower(int index, int height){
        this->index = index;
        this->height = height;
        this->targetTowerIndex = 0;
    }

    //타겟 타워의 인덱스를 설정하는 함수
    void setTargetTowerIndex(int targetTowerIndex){
        this->targetTowerIndex = targetTowerIndex;
    }

    //타겟 타워의 인덱스를 반환하는 함수
    int getTargetTowerIndex(){
        return this->targetTowerIndex;
    }
};

//파라미터로 주어지는 각 타워들에 대해 타겟 타워를 계산하는 함수
void findTargetTowers(vector<Tower>& towers){
    //현재 다른 타워의 신호를 수신할 가능성이 있는 타워들
    stack<Tower> stk; //스택으로 선언

    //시간복잡도 O(N)
    for(int i = 0; i < towers.size(); i++){ //(모든 타워를 반복)
        Tower& t = towers[i]; //각 타워 t에 대해 차례로 고려
        int targetTowerIndex = 0; //타워 t의 신호를 수신할 후보(초기값 null)

        //스택이 비어있지 않고, top에 있는 타워의 높이가 t보다 작은 경우 동안
        while(stk.empty() == false && stk.top().height < t.height){
            //t보다 높이가 낮은 타워들은 이후에도 수신 가능성이 없으므로 제거
            stk.pop();
        }

        //t 이상의 높이를 가진 타워가 남아있다면?
        if(stk.size() > 0){
            //t는 해당 타워를 타겟으로 정하게 된다
            targetTowerIndex = stk.top().index;
        }

        //계산한 타겟 정보를 저장한다
        t.setTargetTowerIndex(targetTowerIndex);

        //t는 마지막에 등장했으므로 다른 타워의 신호를 수신할 수 있다
        stk.push(t); //t를 스택에 추가
    }
}

int main()
{
    int n;
    cin >> n; //[입력] 탑의 수(1 이상 500,000 이하)

    vector<Tower> towers; //벡터 선언
    
    //탑의 개수만큼 반복
    for(int i = 0; i < n; ++i){
        int hi;
        cin >> hi; //[입력] 탑들의 높이(직선상에 놓인 순서대로)
        towers.push_back(Tower(i + 1, hi)); //벡터의 맨 끝에 삽입(인덱스 1부터 저장)
    }

    //각 타워가 송신하는 레이저에 대해 타겟을 모두 계산
    findTargetTowers(towers);

    //모든 타워 n개 반복
    for(int i = 0; i < n; i++){
        if(i > 0){
            cout << " "; //빈칸
        }

        Tower t = towers[i]; //각 타워
        int targetIndex = t.getTargetTowerIndex(); //타겟 타워의 인덱스 가져오기
        cout << targetIndex; //[출력] 주어진 탑들의 순서대로 각각의 탑들에서 발사한 레이저 신호를 수신한 탑들의 번호를 출력
        //만약 레이저 신호를 수신하는 탑이 존재하지 않으면 0을 출력
    }
}