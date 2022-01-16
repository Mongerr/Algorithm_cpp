#include <cstdio>

using namespace std;

const int MAX_ROW = 9; //9행
const int MAX_COL = 9; //9열

class SudokuBoard{
public:
    //칸의 번호로 행의 번호를 계산하는 메소드
    int getRowByIndex(int index){
        //칸의 번호에 대해 마디를 가지고 증가하므로 몫으로 계산할 수 있다
        return (index - 1) / 9 + 1; //칸의 번호를 9로 나눈 몫(시작을 0으로 맞추기 위해 1을 빼고 더함)
    }

    //칸의 번호로 열의 번호를 계산하는 메소드
    int getColByIndex(int index){
        //칸의 번호에 대해 규칙적으로 순환하므로 나머지로 계산할 수 있다
        return (index - 1) % 9 + 1; //칸의 번호를 9로 나눈 나머지
    }

    //칸의 번호로 그룹 번호를 계산하는 메소드
    int getGroupByIndex(int index){
        int r = getRowByIndex(index);
        int c = getColByIndex(index);
        return getGroupByPosition(r, c);
    }

    //칸의 위치 (행, 열)로 그룹 번호를 계산하는 메소드
    int getGroupByPosition(int row, int column){
        //해당 행에 존재하는 그룹들 중 가장 왼쪽 그룹의 번호
        //1~3행 = 1, 4~6행 = 4, 7~9행 = 7
        int left = ((row - 1) / 3) * 3 + 1; //(1 or 4 or 7)

        //해당 행에 존재하는 그룹들 중 몇 번째 그룹에 속하는지
        //1~3열 = 0, 4~6열 = 1, 7~9열 = 2
        int offset = ((column - 1) / 3); //(0 or 1 or 2)

        return left + offset; //해당 칸이 속한 그룹의 번호
    }

    //칸의 위치 (행, 열)로 칸의 번호를 계산하는 메소드
    int getIndexByPosition(int row, int column){
        // 행의 위치(0~8)*9 + 열의 위치(1~9)
        return (row - 1) * 9 + (column - 1) % 9 + 1;
    }
};

void process(int caseIndex)
{
    int index;
    scanf("%d", &index); //[입력] 칸의 번호(1~81)

    SudokuBoard board = SudokuBoard();

    //칸의 번호로 행, 열, 그룹 번호를 계산
    int row = board.getRowByIndex(index);
    int col = board.getColByIndex(index);
    int group = board.getGroupByIndex(index);

    printf("Case #%d:\n", caseIndex); //[출력] 테스트케이스의 번호
    printf("%d %d %d\n", row, col, group); //[출력] 칸의 행, 열, 그룹 번호
}

int main()
{
    int caseSize;
    scanf("%d", &caseSize); //[입력] 테스트케이스의 수

    for(int caseIndex = 1; caseIndex <= caseSize; ++caseIndex){
        process(caseIndex);
    }
}

