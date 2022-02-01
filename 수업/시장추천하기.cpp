#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    int N;
    cin >> N; //[입력] 투표용지의 수(10만 이하의 자연수)

    //각 후보 이름과 득표 수를 저장하는 key-value Map
    map<string, int> frequencyMap;

    int maxFrequency = 0; //가장 많은 득표수

    //각 이름이 하나 추가될 때마다 현재까지의 최다 득표 값 갱신, 최다 득표 후보 리스트를 갱신해간다
    for(int i = 0; i < N; i++){
        string st;
        cin >> st; //[입력] 후보자의 이름(1~10글자의 알파벳 대문자로 구성된 문자열)
        
        frequencyMap[st]++; //해당 후보(key)의 득표수(value)를 +1
        int k = frequencyMap[st];
        if(k > maxFrequency) //득표수가 maxFrequency보다 크다면
            maxFrequency = k; //maxFrequency 갱신
    }

    cout << maxFrequency << endl; //[출력] 가장 많은 표를 획득한 후보자의 표수

    map<string, int>::iterator it;
    for(it = frequencyMap.begin(); it != frequencyMap.end(); it++)
    {
        if(it->second == maxFrequency)
            printf("%s ", it->first.c_str()); //[출력] 해당 표수만큼 표를 획득한 후보들의 이름을 사전순-오름차순으로 출력
            //key값을 출력하기 위해 it->first, Key값이 문자열이므로 .c_str()
    }

    return 0;
}