#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class City{
public:
    int index; //도시의 인덱스
    int income; //해당 도시의 소득

    City(int index, int income){
        this->index = index;
        this->income = income;
    }

    //대소 관계 추가(income을 기준으로 비교)
    bool operator < (const City& o) const{
        return this->income < o.income;
    }
    bool operator > (const City& o) const{
        return this->income > o.income;
    }
};

int getMaximumRangeDifference(int n, int k, const vector<City>& cities){
    int answer = 0;

    //소득이 가장 작은 도시부터 pop되는 우선순위 큐
    priority_queue<City, vector<City>, greater<City>> rangeMinimum;

    //소득이 가장 높은 도시부터 pop되는 우선순위 큐
    priority_queue<City> rangeMaximum;
    // priority_queue<City, vector<City>, less<City>> rangeMaximum;

    for(int i = 0; i < k-1; i++){ //각 큐에 우선순위대로 push
        rangeMaximum.push(cities[i]); //top에 최대 income
        rangeMinimum.push(cities[i]); //top에 최소 income
    }

    for(int i = k-1; i < n; i++){
        rangeMaximum.push(cities[i]); 
        rangeMinimum.push(cities[i]);

        //범위에 포함되지 않은 index의 소득값 삭제
        while(rangeMaximum.top().index < i - k + 1) rangeMaximum.pop();
        while(rangeMinimum.top().index < i - k + 1) rangeMinimum.pop();

        //삭제 후 각각의 우선순의 큐에는 범위에 포함되는 도시의 소득만 남아있음(각각의 top에 최대, 최소값이 포함)
        //최고 소득차 갱신
        answer = max(answer, rangeMaximum.top().income - rangeMinimum.top().income);
    }
    return answer; //가장 큰 소득차를 가지는 영역의 소득차
}

void process(){
    int n, k;
    cin >> n >> k; //[입력] 도시의 수 n, 한 조사 영역이 포함하는 연속한 도시의 수 k
    vector<City> cities;

    for(int i = 0; i < n; i += 1){
        int income;
        cin >> income; //[입력] 각 도시의 소득 수준
        cities.push_back(City(i, income));
    }

    //가장 큰 소득차를 가지는 영역의 소득차
    int answer = getMaximumRangeDifference(n, k, cities);

    cout << answer << endl; //[출력] 연속한 k개의 도시로 이루어진 영역들 중 가장 큰 소득차를 가지는 영역의 소득차
}

int main()
{
    int caseSize;
    cin >> caseSize; //[입력] 테스트케이스의 수(10이하)

    for(int caseIndex = 1; caseIndex <= caseSize; caseSize += 1){ //테스트케이스의 수 만큼 반복
        process();
    }
}
