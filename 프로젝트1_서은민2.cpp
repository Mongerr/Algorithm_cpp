#include <time.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{   
    /*
    R < P < S < R < P < S
    2   1   0
        2   1   0
            2   1   0
    */

    map<char,int> dic;
    dic['R'] = 2;
    //dic.insert(make_pair('r',2));
    //dic.insert(pair<char,int>('r',2));
    dic['P'] = 1;
    dic['S'] = 0;

    int R, N;
    string jn;
    string *friends;

    cin >> R; //[입력] 라운드 수 (1 <= R <= 20) 
    cin >> jn; //[입력] 전남이가 각 라운드에 낸 모양
    cin >> N; //[입력] 친구의 수 (1 <= N <= 20)

    friends = new string[N]; //친구의 수만큼 배열 생성
    for(int i = 0; i < N; i++)
        cin >> friends[i]; //[입력] 친구들이 각 라운드에 낸 모양

    clock_t start = clock(); //실행시간 측정 시작

    int score = 0;
    int best_score = 0;

    for(int i = 0; i < R; i++) //각 라운드마다 반복
    {   
        char game[3] = {'S', 'P', 'R'};
        int game_score[3] = {0,};

        for(int j = 0; j < N; j++)
        {
            if(jn[i] == friends[j][i])
                score += 1;
            else if(((dic.find(jn[i])->second)+1)%3 == dic.find(friends[j][i])->second)
            {
                score += 2;
                //cout << friends[j][i]<< "이김" <<endl;
            }

            for(int k = 0; k < 3; k++)
            {   
                if(game[k] == friends[j][i])
                    game_score[k] += 1;
                else if((k+1)%3 == dic.find(friends[j][i])->second)
                    game_score[k] += 2;
            }
        }
        // cout << game_score[0] << ' ' << game_score[1] << ' ' << game_score[2] <<endl;
        best_score += *max_element(game_score, game_score+3);
    }

    cout << score << endl;
    cout << best_score << endl;

    clock_t end = clock(); //실행시간 측정 종료
    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC));
    
    delete[] friends;

    return 0;
}