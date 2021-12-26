#include <cstdio>
#include <vector>

using namespace std;

const int MAX_SEAT_NUMBER = 1000;
const int MAX_COLOR_NUMBER = 100;

class Painting{
public:
    int left;
    int right;
    int color;

    Painting() { }

    Painting(int left, int right, int color){
        this->left = left;
        this->right = right;
        this->color = color;
    }
};

void fillFrequencyTable(int data[], int n, int table[])
{
    for(int i = 0; i < MAX_COLOR_NUMBER; i++)
        table[i] = 0; //빈도수 테이블 초기화

    for(int i = 0; i < n; i++)
        table[data[i]] += 1; //색에 대한 빈도수 1 증가
}

//좌석의 수 n, 좌석을 칠한 횟수 m, 좌석들을 색칠한 이벤트들의 정보 Paintings
void solve(int n, int m, const Painting* paintings)
{
    int* seats = new int[n];
    for(int i = 0; i < n; i++)
    {
        seats[i] = 0; //좌석을 흰색(0)으로 초기화
    }

    for(int i = 0; i < m; i++) //모든 색칠정보 p에 대하여 차례로
    {
        const Painting &p = paintings[i];

        for(int j = p.left; j <= p.right; j++)
            seats[j] = p.color; //각 페인팅 정보마다 좌석의 색을 업데이트 해줌
    }

    //모든 색칠을 완료한 이후의 색상 정보를 사용하여 모든 색상에 대한 빈도수 테이블 계산
    int* table = new int[MAX_COLOR_NUMBER];
    fillFrequencyTable(seats, n, table);

    int minColor = seats[0]; //가장 적게 등장한 색깔
    int maxColor = seats[0]; //가장 많이 등장한 색깔

    for(int color = 0; color < MAX_COLOR_NUMBER; color++)
    {
        if(table[color] == 0) //한번도 등장하지 않은 색깔
            continue;

        //한 번 이상 등장한 모든 색깔 color에 대하여
        if(table[minColor] > table[color]) //현재 minColor보다 적게 등장한 경우
            minColor = color; //갱신

        if(table[maxColor] < table[color]) //현재 maxColor보다 많이 등장한 경우
            maxColor = color; //갱신
    }

    printf("%d\n", maxColor); //[출력] 가장 많은 좌석이 칠해진 색의 번호
    printf("%d\n", minColor); //[출력] 가장 적은 좌석이 칠해진 색의 번호

    delete[] seats;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m); //[입력] 좌석의 수 N, 색칠을 할 방법의 수 M

    //paintings[i] := i번째에 일어난 색칠 이벤트의 정보
    Painting* paintings = new Painting[n];

    for(int i = 0; i < m; i++){
        scanf("%d", &paintings[i].left); //[입력] 색칠할 가장 왼쪽(번호가 작은) 좌석의 번호
        scanf("%d", &paintings[i].right); //[입력] 색칠할 가장 오른쪽(번호가 큰) 좌석의 번호
        scanf("%d", &paintings[i].color); //[입력] 좌석에 칠할 색깔의 번호(0~99)

        //좌석의 번호는 1번부터 시작하므로, 0 ~ (n-1)범위로 맞추기 위하여 1씩 빼줌
        paintings[i].left -= 1;
        paintings[i].right -= 1;
    }

    solve(n, m, paintings);

    return 0;
}