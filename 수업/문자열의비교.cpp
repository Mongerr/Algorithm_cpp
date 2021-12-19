#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_LENGTH = 100000;

class MyString{
private:
    char *characters;
    int length;

public:
    MyString(const char *str)
    {
        this->length = strnlen(str, MAX_LENGTH);
        this->characters = new char[this->length];
        for(int i = 0; i < this->length; i += 1)
        {
            this->characters[i] = str[i];
        }
    }

    MyString(const string &original)
    {
        this->length = original.length();
        this->characters = new char[this->length];
        for(int i = 0; i < this->length; i += 1)
        {
            this->characters[i] = original[i];
        }
    }

    ~MyString()
    {
        delete[] characters;
    }

    //비교 연산자 오버로딩
    //param o는 비교할 문자열(오른쪽 항)
    bool operator < (const MyString &o) const{
        int n = min(this->length, o.length);
        for(int i = 0; i < n; i++) //두 문자열 중 짧은 문자열의 길이만큼 반복하면서 문자 비교
        {
            if(this->characters[i] < o.characters[i]) //this가 o보다 사전순으로 앞선다면 true
                return true;
            else if(this->characters[i] > o.characters[i]) //반대라면
                return false;
        }

        //위에서 비교가 끝났고 오른쪽 항 문자열의 길이가 더 긴 경우
        //ex) algo < algorithm
        if(this->length < o.length) //왼쪽 항의 문자열이 사전순으로 앞섬
            return true; 
        else //오른쪽 항의 문자열이 사전순으로 앞섬
            return false;
    }

    //위에서 오버로딩한 연산자와 반대
    //o가 this보다 사전순으로 앞선다면 true
    bool operator > (const MyString &o) const{
        int n = min(this->length, o.length);
        for(int i = 0; i < n; i++)
        {
            if(this->characters[i] < o.characters[i])
                return false;
            else if(this->characters[i] > o.characters[i])
                return true;
        }

        //ex) algo > algorithm
        if(this->length > o.length) //오른쪽 항의 문자열이 사전순으로 앞섬
            return true;
        else //왼쪽 항의 문자열이 사전순으로 앞섬
            return false;
    }

    bool operator == (const MyString &o) const{
        if(this->length != o.length) //두 문자열의 길이가 다르다면 false
            return false;

        //두 문자열의 길이가 같은 경우
        for(int i = 0; i < this->length; i++)
        {
            if(this->characters[i] != o.characters[i]){ //문자 비교 중 서로 다르다면
                return false; //두 문자열이 다름
            }
        }
        
        return true; //두 문자열이 같음
    }
};

int main()
{
    string s1;
    string s2;
    cin >> s1 >> s2; //[입력] 영어 소문자로 구성된 문자열 두 개

    //MyString 객체 생성
    MyString mys1(s1);
    MyString mys2(s2);

    /*
    [출력]
    mys1이 mys2보다 사전순으로 앞서는 문자열이라면 -1을 출력
    mys2이 mys1보다 사전순으로 앞서는 문자열이라면 1을 출력
    두 문자열이 일치한다면 0을 출력
    */
    if(mys1 < mys2){
        printf("-1"); //cout << "-1" << endl;
    }
    else if(mys1 > mys2){
        printf("1");
    }
    else{
        printf("0");
    }

    return 0;
}