#include <iostream>
#include <set>

using namespace std;

int main()
{
    int N;
    cin >> N; //[입력] 정수들의 총 개수

    set<int> s; //세트 선언
    //C++ set의 find메소드는 찾는 수가 있다면 해당 iterator를, 없다면 end() iterator를 반환
    for(int i = 0; i < N; i++){
        int X;
        cin >> X; //[입력] 정수

        if(s.count(X) > 0) //찾는 수가 있다면 s.find(x) != s.end()
            cout << "DUPLICATED" << endl; //[출력] "DUPLICATED"
        else //찾는 수가 없다면(처음 등장한 숫자의 경우)
        {
            s.insert(X); //set에 수를 등록한다
            cout << "OK" << endl; //[출력] "OK"
        }
    }
    return 0;
}