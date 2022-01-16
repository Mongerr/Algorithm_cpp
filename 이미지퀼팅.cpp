#include <time.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main() //백준 정답 아님!!
{  
    int h, w;
    cin >> h >> w; //[입력] 포개어진 두 이미지의 높이 h(1<=h<=100)와 포개어진 영역의 넓이 w(1<=w<=100)

    int image_B1[h][w], image_B2[h][w]; //두 이미지 B1과 B2

    //아래 두 행렬은 이미지의 폭+2 (오른쪽과 왼쪽에 1열씩 더 있음)
    int difference[h][w+2]; //밝기 값의 차를 구해놓은 행렬
    int matrix[h][w+2]; //알고리즘 구현을 위한 행렬(이후에 difference와 같은 값으로 시작)

    for(int i = 0; i < h; i++) //이미지의 행 h개
    {
        for(int j = 0; j < w; j++) //w개의 픽셀
            cin >> image_B1[i][j]; //[입력] B1 이미지의 밝기(0~255)
    }

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
            cin >> image_B2[i][j]; //[입력] B2 이미지의 밝기(0~255)
    }

    clock_t start = clock(); //실행시간 측정 시작

    /*
    < 이미지 퀼팅 알고리즘 >
    https://ooz.co.kr/236
    최소 경계값을 찾는 방법 참고
    */

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w+2; j++)
            //밝기 값의 차를 저장할 행렬에 밝기의 최대값(255)보다 큰 정수를 미리 저장
            difference[i][j] = 256;
    }

    for(int i = 0; i < h; i++)
    {
        for(int j = 1; j < w+1; j++)
            //가장 왼쪽과 오른쪽 열을 남겨놓고 밝기 값의 차를 계산해서 저장
            difference[i][j] = abs(image_B1[i][j-1] - image_B2[i][j-1]);
        /*
            ex) 다음과 같은 모양이 됨
            [0]  [1]   ...   [w] [w+1]
            256   ?   ?   ?   ?   256
            256   ?   ?   ?   ?   256
            256   ?   ?   ?   ?   256
            256   ?   ?   ?   ?   256
        */
    }

    //matrix 행렬은 difference 행렬의 내용을 복사해서 시작
    memcpy(matrix, difference, sizeof(difference));
    
    for(int i = 0; i < h-1; i++) //마지막 행을 제외하고 반복
    {   
        //위에서 아래로 내려오면서(행)
        //각 열의 아래 행의 인접한 픽셀(-1, 0, 1열 차이) 중에 최소값 찾기 
        for(int j = 1; j < w+1; j++)
        {   
            int min = matrix[i][j]; //최소값을 찾기 위해 초기화
            //(인접한 픽셀들을 비교하며 최소값 갱신)
            if(matrix[i][j-1] < min)
                min = matrix[i][j-1];
            if(matrix[i][j+1] < min)
                min = matrix[i][j+1];

            //최소값을 찾아 바로 밑 픽셀에 더함
            matrix[i+1][j] += min;
        }
    } //matrix행렬 계산 끝

    // //확인용 출력
    // cout << '\n';
    // for(int i = 0; i < h; i++)
    // {
    //     for(int j = 0; j < w+2; j++)
    //         cout << matrix[i][j] << ' ';
    //     cout << '\n';
    // }

    int ssd = 0; //sum of squared distance
    
    //matrix행렬의 끝행에서 가장 작은 값이 마지막 경계선 픽셀임
    //(여기서는 아래서 위로 올라가면서 경계선을 찾으므로 시작으로 표현)
    int start_min = matrix[h-1][1]; //최소값을 찾기 위해 초기화(끝행의 첫번째 열)

    int col; //column값을 임시로 저장할 변수

    for(int j = 2; j < w+1; j++)
    {   
        //가장 마지막행에서 제일 작은 값을 찾고
        if(matrix[h-1][j] < start_min)
            col = j; //col 갱신
    }
    //인덱스를 통해 difference(밝기 값의 차를 미리 계산한 행렬)에서 찾은 값을 제곱해서 누적
    ssd += difference[h-1][col] * difference[h-1][col];

    for(int i = h-2; i >= 0; i--) //아래에서 위로 올라가면서 경계값 픽셀을 찾음
    {   
        int new_col; //임시 변수

        //직전 행에서 선택한 열(픽셀)의 위로 인접한 세 픽셀 중에서 최소값을 찾는 과정
        int min = matrix[i][col]; //최소값을 찾기 위해 초기화

        if(matrix[i][col-1] < min) //왼쪽 비교
        {
            min = matrix[i][col-1];
            new_col = col-1;
        }
        if(matrix[i][col+1] < min) //오른쪽 비교
        {
            min = matrix[i][col+1];
            new_col = col+1;
        }
        col = new_col; //col 갱신

        //인덱스를 통해 difference(밝기 값의 차를 미리 계산한 행렬)에서 찾은 값을 제곱해서 누적
        ssd += difference[i][col] * difference[i][col];
    }
    cout << ssd << endl; //[출력] 이미지에서 선택할 수 있는 경계선이 가지는 최소의 부자연스러운 정도(SSD)

    clock_t end = clock(); //실행시간 측정 종료

    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간
    
    return 0;
}