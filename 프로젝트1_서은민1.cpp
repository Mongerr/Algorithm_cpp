#include <time.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{   /*
    R > S > P > R

            상  대   방
            R   S   P
    전   R   1   2   0
    남   S   0   1   2
    이   P   2   0   1
    */

    int score[3][3] = {{1,2,0},{0,1,2},{2,0,1}}; //모든 경우의 점수

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

    int final_score = 0; //총 점수
    int best_score = 0; //최고 점수
    int *jn_score;

    for(int i = 0; i < R; i++) //각 라운드마다 반복
    {   
      
        switch(jn[i]){ //전남이가 낸 모양에 따라 점수 설정
            case 'R': jn_score = score[0]; break;
            case 'S': jn_score = score[1]; break;
            default: jn_score = score[2];
        }

        // cout << *jn_score << *(jn_score+1) << *(jn_score+2) <<endl;

        char game[3] = {'R', 'S', 'P'}; //최고 점수 계산을 위해 낼 모든 모양
        int game_score[3] = {0,}; //각 모양을 냈을 때 얻는 점수

        for(int j = 0; j < N; j++) //모든 친구 반복
        {   
            if(friends[j][i] == 'R') //친구가 R을 낸 경우
                final_score += jn_score[0];
            else if(friends[j][i] == 'S') //친구가 S를 낸 경우
                final_score += jn_score[1];
            else //친구가 P를 낸 경우
                final_score+= jn_score[2];
            
            //친구들이 무엇을 낼지 미리 알고 있을 때
            for(int k = 0; k < 3; k++) //모든 모양을 내면서 반복
            {   
                if(game[k] == friends[j][i]) //비김
                    game_score[k] += 1;
                else if(game[(k+1)%3] == friends[j][i])
                    //친구가 낸 모양의 index가 전남이가 낸 모양의 index에 1을 더하고 3으로 나눈 값과 같으면 전남이가 이김
                    //[모양]    R > S > P > R > S > P
                    //[index]  0   1   2   0   1   2
                    game_score[k] += 2;
            }
        }
        best_score += *max_element(game_score, game_score+3); //모든 모양 중 가장 높은 점수를 best_score에 누적
    }

    cout << final_score << endl; //[출력] 전남이의 총 점수
    cout << best_score << endl; //[출력] 전남이가 얻을 수 있는 최고 점수

    clock_t end = clock(); //실행시간 측정 종료
    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간
    
    delete[] friends;

    return 0;
}