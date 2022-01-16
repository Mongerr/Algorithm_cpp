#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Player{
public:
    int index; //플레이어의 인덱스

    Player(int index){
        this->index = index;
    }
};

//조세퍼스 게임을 수행하여 각 플레이어가 제거된 순서를 리스트로 반환하는 함수
//n: 플레이어의 수, m: 매 턴마다 건너 뛸 사람의 수, players: 좌석에 앉아있는 순서대로 주어지는 플레이어 정보
vector<Player> getDeadPlayersList(int n, int m, const vector<Player>& players){
    vector<Player> deadPlayers; //현재 게임에서 제외된 플레이어들의 리스트

    queue<Player> que; //아직 게임에서 제외되지 않은 플레이어들의 리스트

    for(int i = 0; i < n; i++){
        que.push(players[i]); // 1 2 3 4 5 6 7
    }

    for(int i = 0; i < n; i++){
        //(m-1)명의 사람을 건너뛴다
        int jump = 1 + (m-1) % que.size();
        
        //제외할 사람 바로 앞까지
        for(int j = 0; j < jump-1; j+=1){ 
            Player p = que.front(); //맨 앞 데이터를 임시 저장
            que.pop(); //맨 앞 데이터를 삭제
            que.push(p); //맨 앞 데이터를 뒤에 삽입
            //2 3 4 5 6 7 1 -> 3 4 5 6 7 1 2
        }
        
        //m번째 사람은 게임에서 제외한다
        Player dead = que.front();
        que.pop(); //4 5 6 7 1 2

        //제외 리스트에 추가한다
        deadPlayers.push_back(dead);
    }
    return deadPlayers;
}

void process(int caseIndex){
    int n, m;
    cin >> n >> m; //[입력] 사람의 수 n, 사람을 제외해 나갈 간격 m(5000이하 자연수)

    vector<Player> players; //좌석에 앉아있는 순서대로 주어지는 플레이어 정보
    for(int i = 0; i < n; i++){
        players.push_back(Player(i + 1)); //인덱스는 1부터 시작
    }

    //제외된 사람의 리스트
    vector<Player> deadPlayers = getDeadPlayersList(n, m, players);

    for(int i = 0; i < n; i++){
        if(i > 0){
            cout << " "; //공백으로 구분
        }

        Player p = deadPlayers[i]; //제외된 사람
        cout << p.index; //[출력] n명의 사람들의 번호를 제외된 순서대로 출력
    }
    cout << endl;
}

int main()
{
    int caseSize;
    cin >> caseSize; //[입력] 테스트케이스의 수(10이하)
    
    for(int caseIndex = 1; caseIndex <= caseSize; caseIndex += 1){ //테스트케이스의 수 만큼 반복
        process(caseIndex); 
    }
}