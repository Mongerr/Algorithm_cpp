#include <time.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//sort()의 인자로 comp 정의하기
bool comp(pair<int, int> a, pair<int, int> b){
    return a.second < b.second; //시간의 오름차순
}

int solution(vector<pair<int, int>> v2, long long k)
{
    sort(v2.begin(), v2.end(), comp); //시간의 오름차순으로 정렬

    int time = 0; //한꺼번에 지울 수 있는 시간

    while(1)
    {   
        int min = v2.begin()->second; //현재 가장 조금 남아있는 음식의 시간(개수)

        if(time + min * v2.size() > k) break; //입력한 k보다 한꺼번에 지울 시간이 커진 경우 break
        
        time += min * v2.size(); //한꺼번에 지울 수 있는 시간 누적

        for(vector<pair<int, int>>::iterator iter = v2.begin(); iter != v2.end(); iter++)
            iter->second -= min; //각각의 음식의 시간(개수)을 지움
        
        while(v2.front().second == 0) //더 이상 남아있지 않은 음식 제거
            v2.erase(v2.begin());
    }

    vector<int> remain; //남은 음식

    for(int i = 0; i < v2.size(); i++)
        remain.push_back(v2[i].first); //남은 음식들의 index 저장

    sort(remain.begin(), remain.end()); //남은 음식들의 index를 오름차순으로 정렬

    return remain[(k-time) % remain.size()] + 1; //남은 음식 중 이어서 먹어야 할 음식의 번호
}

int main()
{  
    int n, t;
    long long k;
    long long sum = 0;

    cin >> n; //[입력] 음식의 개수 n(1이상 200,000이하)

    vector<pair<int, int>> times;

    for(int i = 0; i < n; i++)
    {   
            cin >> t; //[입력] 각 음식을 모두 먹는데 필요한 시간(1이상 100,000,000이하)
            times.push_back(make_pair(i, t)); //인덱스와 시간(음식 개수)을 쌍으로 저장
    }

    cin >> k; //[입력] 먹방을 시작한 후 방송이 중단된 시간 k(1이상 2*10^13이하의 자연수)

    clock_t start = clock(); //실행시간 측정 시작

    //모든 음식을 먹는데 필요한 시간
    for(vector<pair<int, int>>::iterator i= times.begin(); i != times.end(); i++){
        sum += i->second;
    }

    if( k >= sum) //더 섭취해야 할 음식이 없다면
        cout << -1 <<endl; //[출력] -1을 출력
    else
        cout << solution(times, k) << endl; //[출력] 네트워크 정상화 후, 이어서 먹어야 할 음식 번호

    clock_t end = clock(); //실행시간 측정 종료

    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간
    
    return 0;
}