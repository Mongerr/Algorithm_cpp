#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getPossibleTargets(int n, int m, int* cards, int* targets){
    vector<int> possibleTargets; //만들 수 있는 당첨 번호들

    sort(cards, cards + n); //모든 카드를 오름차순으로 정렬, 바이너리 서치를 하기 위한 조건
    
    for(int i = 0; i < m; i++)
    {
        int k = targets[i]; //모든 타겟 k에 대하여
        bool possible = false;

        for(int j = 0; j < n; ++j)
        {
            int x = cards[j]; //모든 카드 중 하나인 x에 대하여
            for(int p = 0; p <= j; p += 1) //숫자조합의 중복 없애기
            {
                int y = cards[p]; //카드 중 하나 y를 선택한다
                int z = k - (x + y); // k = (x + y) + z가 되는 z를 계산한다

                //z가 cards[]에 존재한다면?
                if(binary_search(cards, cards + n, z) == true) //시작위치, 끝 위치, 찾을 값
                {
                    possible = true; //k = x + y + z 가 가능한 <x, y, z>가 존재한다
                    break;
                }
            }
            if(possible){ //이미 찾았다면 탈출한다
                break;
            }
        }

        if(possible){ //세 카드의 합으로 k를 만들 수 있다면, 추가한다
            possibleTargets.push_back(k);
        }
    }

    sort(possibleTargets.begin(), possibleTargets.end()); //오름차순 정렬
    return possibleTargets;
}

int main()
{
    int n;
    int m;
    scanf("%d %d", &n, &m); //[입력] 사용할 카드의 수 n(1~1000), 당첨 번호의 숫자 m(1~100)

    int* cards = new int[n];
    int* targets = new int[n];
    
    for(int i = 0; i < n; i++){
        scanf("%d", &cards[i]); //[입력] n개의 카드에 적힌 숫자들(1이상 1억 이하)
    }

    for(int i = 0; i < m; i++){
        scanf("%d", &targets[i]); //[입력] m개의 사용 될 당첨 번호들(서로 다른 1이상 3억 이하)
    }

    vector<int> answer = getPossibleTargets(n, m, cards, targets);

    //[출력] m개의 당첨번호들 중 실제로 세 카드에 적힌 숫자의 합으로 표현될 수 있는 당첨번호들을 모두 출력
    if(answer.size() == 0)
        printf("NO"); //실제로 만들 수 있는 당첨번호가 존재하지 않는다면
    else{
        for(int i = 0; i < answer.size(); i++)
        {
            if(i > 0)
                printf(" ");
            printf("%d", answer[i]); //실제로 만들 수 있는 당첨번호가 여러개라면, 공백으로 구분하여 한줄에 출력(오름차순)
        }
    }

    delete[] cards;
    delete[] targets;

    return 0;
}