#include <cstdio>
#include <vector>

using namespace std;

class TicketTable{
public:
    vector<bool> used;
    int length;

    TicketTable(int length){
        this->length = length; //행운권의 수
        this->used.assign(length, false); //행운권 번호 사용 여부(false로 초기화)
    }

    //사용자의 회원 번호로 지급받게 될 행운권 번호를 계산하는 메소드
    int findEmptyIndexByUserId(int userId){
        int index = userId % length;  //회원 번호를 행운권 개수(n)으로 나눈 나머지가 행운권 번호
        while(this->isEmpty(index) == true){ //사용 안 한 번호라면 건너 뛴다
            //해당 번호가 다른 사람에게 지급된 상황이라면 +1한 번호를 지급
            index = (index + 1) % length; //마지막 번호도 지급된 상태라면 0번부터 다시 조회(행운권 번호: 0 ~ n-1)
        }
        return index; //사용되지 않은 인덱스를 찾아서 반환
    }

    //해당 행운권 번호가 이미 사용 중인지 여부를 반환하는 메소드
    int isEmpty(int ticketIndex){
        return this->used[ticketIndex];
    }

    //티켓(번호) 사용 여부를 갱신하기 위한 메소드
    void setUsed(int index, bool status){
        this->used[index] = status;
    }
};

vector<int> getTicketNumbers(int n, int m, const vector<int> &ids){
    vector<int> tickets;
    TicketTable table = TicketTable(n);

    for(int i = 0; i < m; i++){
        int userId = ids[i]; //회원 번호
        int ticketIndex = table.findEmptyIndexByUserId(userId); //회원이 받을 행운권 번호
        tickets.push_back(ticketIndex); //tickets에 행운권 번호 추가
        table.setUsed(ticketIndex, true); //번호 사용 여부 갱신
    }

    return tickets; //입장한 회원들의 행운권 번호
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m); //[입력] 행운권의 수: n, 회원의 수: m

    vector<int> ids(m); 
    for(int i = 0; i < m; ++i){
        scanf("%d", &ids[i]); //[입력] 회원들의 회원번호
    }

    vector<int> tickets = getTicketNumbers(n, m, ids);
    for(int i = 0; i < tickets.size(); i++){
        printf("%d\n", tickets[i]); //[출력] 입장한 회원들의 순서대로 해당 회원이 지급받게 될 행운권 번호
    }
}