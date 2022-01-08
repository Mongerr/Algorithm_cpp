#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Parenthesis{
public:
    bool type; //열린 괄호면 true, 닫힌 괄호면 false
    int index; //해당 괄호의 인덱스

    Parenthesis(int index, bool type){
        this->index = index;
        this->type = type;
    }

    //생성자(index와 괄호문자 c를 매개변수로 받음)
    Parenthesis(int index, char c){
        this->index = index;
        if(c == '('){
            this->type = true; //열린 괄호
        }else{
            this->type = false; //닫힌 괄호
        }
    }
};

//괄호들의 정보가 차례로 주어질 때, 올바른 괄호 문자열인지 판단하는 함수
bool isValidParenthess(const vector<Parenthesis>& parentheses){
    //현재 짝을 찾지 못한 열린 괄호들만 저장
    //닫힌 괄호가 나오면 탑에 저장된 열린 괄호를 삭제해 나감
    //탑 원소 삭제만 이루어짐 -> 스택변수로 선언
    stack<Parenthesis> st; //스택 선언

    for(int i = 0; i < parentheses.size(); i++){
        //왼쪽부터 오른쪽의 괄호를 차례로 조회한다
        //벡터 변수이므로 모든 원소 접근 가능
        Parenthesis p = parentheses[i];

        if(p.type == true){
            //열린 괄호라면 짝을 찾을 때 까지 스택에 보관한다
            st.push(p);
        }
        else if(p.type == false){
            //닫힌 괄호 p에 대하여

            if(st.size() > 0){
                //가장 마지막에 추가된 열린 괄호와 짝을 맞출 수 있으므로 제거한다
                st.pop();
            }else{
                //짝을 맞출 수 있는 열린 괄호가 없다면 올바르지 않은 괄호 문자열이다
                return false;
            }
        }
    }
    //모든 짝을 맞춘 후
    if(st.size() > 0){ //혹은 st.empty() == 0
        //아직 스택에 짝을 찾지 못한 열린 괄호가 남아있다면
        return false; //올바르지 않은 괄호 문자열
    }

    return true; //그 외의 경우 올바른 문자열임
}

void process(int caseIndex){
    string str;
    cin >> str; //[입력] 괄호 문자열

    vector<Parenthesis> parentheses; //벡터 선언
    //벡터는 (front~back)모든 위치의 원소 접근 가능 (동적 배열로 사용)
    //스택은 탑 위치의 원소만 접근 가능

    for(int i = 0; i < str.length(); ++i){
        //입력 받은 문자열의 길이만큼 반복하면서 벡터의 맨 끝에 문자 한 개(Parenthesis) 삽입
        parentheses.push_back(Parenthesis(i, str[i]));
    }

    //유효한 괄호 문자열인지 판단하는 함수에 벡터 전달
    bool isValid = isValidParenthess(parentheses);

    //[출력] 올바른 괄호 문자열이면 YES, 아니면 NO
    if(isValid){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
}

int main()
{
    int caseSize;
    cin >> caseSize; //[입력] 입력데이터의 수

    //caseSize만큼 반복하면서 process함수 실행
    for(int caseIndex = 1; caseIndex <= caseSize; caseIndex += 1){
        process(caseIndex);
    }
}