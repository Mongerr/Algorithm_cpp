#include <time.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class food_time{
public:
	int t; //시간
	int index; //인덱스

	//생성자
	food_time(int index, int t){
		this->index = index;
		this->t = t;
	}

	bool operator < (const food_time& other) const{
		return this->t < other.t;
	}
};

int solution(vector<food_time> v2, long long k)
{
    sort(v2.begin(), v2.end());

    int time = 0;

    while(1)
    {   
        // for(int i = 0; i < v2.size(); i++)
        //     cout << v2[i].t << ','; 
        // cout << endl; 
        
        int min = v2.begin()->t;

        if(time + min * v2.size() > k) break;

        time += min * v2.size();

        for(vector<food_time>::iterator iter = v2.begin(); iter != v2.end(); iter++)
            iter->t -= min;
        
        while(v2.front().t == 0)
            v2.erase(v2.begin());
    }
    
    /*
    if(!v2.empty())
        cout << "안비었음" << endl;
    else
        cout << "비었음" << endl;
    */
    
    // cout << v2.empty() << endl;
    // cout << v2.size() << endl;

    vector<int> remain;
    for(int i = 0; i < v2.size(); i++)
    {
        // cout << v2[i].index << ':' <<v2[i].t << endl;
        remain.push_back(v2[i].index);
    }
    sort(remain.begin(), remain.end());

    return remain[(k-time) % remain.size()] + 1;
}

int main()
{  
    int n, t;
    long long k;
    long long sum = 0;

    cin >> n; //[입력] 음식의 개수 n(1이상 200,000이하)

    vector<food_time> times;

    for(int i = 0; i < n; i++)
    {   
            cin >> t;
            sum += t;
            times.push_back(food_time(i, t)); //[입력] 각 음식을 모두 먹는데 필요한 시간(1이상 100,000,000이하)
    }

    cin >> k; //[입력] 먹방을 시작한 후 방송이 중단된 시간 k(1이상 2*10^13이하의 자연수)

    clock_t start = clock(); //실행시간 측정 시작

    if( k >= sum)
        cout << -1 <<endl;
    else
        cout << solution(times, k) << endl;

    clock_t end = clock(); //실행시간 측정 종료

    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간
    
    return 0;
}