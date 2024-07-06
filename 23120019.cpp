#include <iostream>
using namespace std;

string Sum(string s, string t);
string Minus(string s, string t);

string Sum(string s, string t){
    if(s[0] == '-' && t[0] == '-'){
        s = s.substr(1,s.size() - 1);
        t = t.substr(1,t.size() - 1);
        string a = Sum(s,t);
        a = '-' + a;
        return a;
    }
    if(s[0] == '-'){
        s = s.substr(1,s.size() - 1);
        return Minus(t, s);
    }
    if(t[0] == '-'){
        t = t.substr(1, t.size() - 1);
        return Minus(s, t);
    }
    if(s.size() < t.size()){
        swap(s, t);
    }
    while(s.size() > t.size()){
        t = '0' + t;
    }
    string sum;
    int n = s.size();
    int borrow = 0;
    for(int i = n - 1; i >= 0; --i){
        int num1 = s[i] - '0';
        int num2 = t[i] - '0';
        int k  = num1 + num2;
        if(borrow){
            k++;
            borrow = 0;
        }
        if(k <= 9){
            sum = ((char) ('0' + k)) + sum;
        } else {
            borrow = k / 10;
            sum = ((char) ('0' + (k % 10))) + sum;
        }
    }
    if(borrow){
        sum = ((char) ('0' + borrow)) + sum;
    }
    return sum;
}
string Subtract(string s, string t){
    while(t.size() < s.size()){
        t = '0' + t;
    }
    int n = s.size();
    string ans;
    for(int i = n-1; i >= 0; --i){
        int num1 = s[i] - '0';
        int num2 = t[i] - '0';
        if(num1 < num2){
            num1 += 10;
            s[i-1]--;
        }
        ans = ((char) ('0' + (num1 - num2))) + ans;
    }
    return ans;
}
int SoSanh(string s, string t){
    if(s.size() < t.size()) return -1;
    else if(s.size() > t.size()) return 1;
    else {
        int n = s.size();
        for(int i = 0; i < n; ++i){
            int n1 = s[i]-'0';
            int n2 = t[i]-'0';
            if(n1 > n2) return 1;
            else if(n1 < n2) return -1;
        }
        return 0;
    }
}
void DeleteZero(string &s){
    int i;
    if(s[0] == '-') i = 1;
    else i = 0;
    while(s[i] == '0'){
        for(int j = i + 1; j < s.size(); ++j){
            s[j-1] = s[j];
        }
        s.erase(s.size() - 1);
    }
}
string Minus(string s, string t){
    if(s[0] == '-' && t[0] == '-'){
        s = s.substr(1,s.size() - 1);
        t = t.substr(1,t.size() - 1);
        return Minus(t, s);
    }
    if(t[0] == '-') {
        t = t.substr(1,t.size() - 1);
        return Sum(s, t);
    }
    if(s[0] == '-'){
        s = s.substr(1,s.size() - 1);
        string a = Sum(s,t);
        a = '-' + a;
        return a;
    }
    string ans;
    if(SoSanh(s, t) < 0){ // s < t
        ans = Subtract(t,s);
        ans = '-' + ans;
        DeleteZero(ans);
    } else if(SoSanh(s, t) > 0){ // s > t
        ans = Subtract(s,t);
        DeleteZero(ans);
    } else {
        ans = "0";
    }
    return ans;
}
string Pow10(int n){
    string s = "10";
    for(int i = 1; i < n; ++i){
        s = s + '0';
    }
    return s;
}
string Multiply(string s, string t){
    if(s[0] == '-' && t[0] == '-'){
        s = s.substr(1,s.size() - 1);
        t = t.substr(1,t.size() - 1);
        return Multiply(s, t);
    }
    if(t[0] == '-') {
        t = t.substr(1,t.size() - 1);
        string a = Multiply(s, t);
        a = '-' + a;
        return a;
    }
    if(s[0] == '-'){
        s = s.substr(1,s.size() - 1);
        string a = Multiply(s,t);
        a = '-' + a;
        return a;
    }
    int n = s.size(), m = t.size();
    if(n == 0 && m == 0) return "0";
    int nn,mm;
    if(n % 2 == 0) nn = n/2;
    else nn = n/2 + 1;
    if(m % 2 == 0) mm = m/2;
    else mm = m/2 + 1;
    if(n == 1) {
        string ans = t;
        int s_value = (s[0] - '0');
        if(s_value == 0) return "0";
        for(int i = 2; i <= s_value; ++i){
            ans = Sum(ans, t);
        }
        return ans;
    }
    if(m == 1) {
        string ans = s;
        int t_value = (t[0] - '0');
        if(t_value == 0) return "0";
        for(int i = 2; i <= t_value; ++i){
            ans = Sum(ans, s);
        }
        return ans;
    }
    string s1 = "", s2 = "", t1 = "", t2 = "";
    for(int i = 0; i < s.size(); ++i){
        if(i < n/2) s1 += s[i];
        else s2 += s[i];

    }
    for(int i = 0; i < t.size(); ++i){
        if(i < m/2) t1 += t[i];
        else t2 += t[i]; 
    }
    DeleteZero(s1);
    DeleteZero(t1);
    DeleteZero(s2);
    DeleteZero(t2);
    // cout << s1 << " " << s2 << " " << t1 << " " << t2 << endl;
    string A = Multiply(s1, t1);
    string B = Multiply(s1, t2);
    string C = Multiply(s2, t1);
    string D = Multiply(s2, t2);
    // cout << A << " " << B << " " << C << " " << D << endl;
    for(int i = 0; i < nn + mm; i++)
        A += '0';
    for(int i = 0; i < nn; i++) {
        B += '0';
    }
    for(int i = 0; i < mm; i++) {
        C += '0';
    }
    // cout << A << " " << B << " " << C << " " << D << endl;
    string ans = Sum(Sum(Sum(A,B),C),D);
    return ans;
}
string Divide(string s, string t){
    if(s[0] == '-' && t[0] == '-'){
        s = s.substr(1,s.size() - 1);
        t = t.substr(1,t.size() - 1);
        return Divide(s, t);
    }
    if(t[0] == '-') {
        t = t.substr(1,t.size() - 1);
        string a = Divide(s, t);
        a = '-' + a;
        return a;
    }
    if(s[0] == '-'){
        s = s.substr(1,s.size() - 1);
        string a = Divide(s,t);
        a = '-' + a;
        return a;
    }

    int n = s.size(), m = t.size();
    if(n < m) return "0";
    
    string ans = "";
    string remainder = s.substr(0, m);
    for(int i = m; i <= n; i++){
        int digit = 0;
        while(SoSanh(remainder, t) >= 0){
            remainder = Minus(remainder, t);
            digit++;
        }
        ans += to_string(digit);
        DeleteZero(remainder);
        if(i < n){
            remainder += s[i];
        }
        
    }
    
    DeleteZero(ans);
    
    return ans;
}

struct Node{
    string value;
    Node *pNext;
};
struct Stack{
    Node *pHead;
    Node *pTail;
};
Stack* Init(){
    Stack* s = new Stack;
    s->pHead = NULL;
    s->pTail = NULL;
    return s;
}
Node* CreateNode(string s){
    Node* p = new Node;
    p->value = s;
    p->pNext = NULL;
    return p;
}
void AddNode(Stack*&s, string ss){
    Node *p = CreateNode(ss);
    if(s->pHead == NULL){
        s->pHead = p;
        s->pTail = p;
    } else {
        p->pNext = s->pHead;
        s->pHead = p;
    }
}
void DeleteStack(Stack*s){
    Node* current = s->pHead;
    while(current != NULL){
        Node* temp = current;
        current = current->pNext;
        delete temp;
    }
    s->pHead = NULL;
    s->pTail = NULL;
    delete s;
}
void PopNode(Stack*s){
    if(s->pHead == s->pTail){
        delete s->pHead;
        s->pHead = NULL;
        s->pTail = NULL;
    } else {
        Node* tmp = s->pHead->pNext;
        delete s->pHead;
        s->pHead = tmp;
    }
}
void Print(Stack*s){
    Node* p = s->pHead;
    while(p != NULL){
        cout << p->value << endl;
        p = p->pNext;
    }
}
void Reverse(Stack* s){
    Node* p = s->pHead;
    Node* prev = NULL;
    Node* next = NULL;
    while(p != NULL){
        next = p->pNext;
        p->pNext = prev;
        prev = p;
        p = next;
    }
    s->pHead = prev;
    s->pTail = s->pHead;
}
int Size(Stack* s){
    int cnt = 0;
    Node* p = s->pHead;
    while(p != NULL){
        cnt++;
        p = p->pNext;
    }
    return cnt;
}
string Calculate(string eq){
    Stack* s = Init();
    Stack* op = Init();
    string ele = "";
    for(int i = 0; i < eq.size(); ++i){
        
        if(eq[i] != ' '){
            ele += eq[i];
        } else {
            if(ele.size() != 1 || (ele[0] - '0' <= 9 && ele[0] - '0' >= 0)){
                AddNode(s, ele);
            } else if(ele[0] == '+' || ele[0] == '-'){
                while(op->pHead != NULL && (op->pHead->value[0] == '*' || op->pHead->value[0] == ':' || op->pHead->value[0] == '+' || op->pHead->value[0] == '-')){
                    AddNode(s, op->pHead->value);
                    PopNode(op);
                }           
                AddNode(op, ele);         
            } else if(ele[0] == '*' || ele[0] == ':'){
                while(op->pHead != NULL && (op->pHead->value[0] == '*' || op->pHead->value[0] == ':')){
                    AddNode(s, op->pHead->value);
                    PopNode(op);
                }           
                AddNode(op, ele);        
            } else if(ele[0] == '('){
                AddNode(op, ele);
            } else if(ele[0] == ')'){
                while(op->pHead != NULL && op->pHead->value[0] != '('){
                    AddNode(s, op->pHead->value);
                    PopNode(op);
                }
                PopNode(op);
            }
            ele = "";
        }
    }
    
    while(op->pHead != NULL){
        AddNode(s, op->pHead->value);
        PopNode(op);
    }
    DeleteStack(op);
    // cout << Size(s) << endl;
    Reverse(s);
    // Print(s);
    Stack* math = Init();
    Node* curr = s->pHead;
    while(curr != NULL){
        string n = curr->value;
        // PopNode(s);
        curr = curr->pNext;
        
        if(n.size() != 1 || (n[0] - '0' <= 9 && n[0] - '0' >= 0)){
            AddNode(math, n);
        } else {
            int size = Size(math);
            if(size < 2){
                DeleteStack(s);
                DeleteStack(math);
                return "Invalid Expression";
            } else {
                string num1 = math->pHead->value;
                PopNode(math);
                string num2 = math->pHead->value;
                PopNode(math);
                if(n[0] == '+') AddNode(math, Sum(num1, num2));
                if(n[0] == '-') AddNode(math, Minus(num2, num1));
                if(n[0] == '*') AddNode(math, Multiply(num1, num2));
                if(n[0] == ':') {
                    if(num1.size() == 1 && num1[0] == '0'){
                        DeleteStack(s);
                        DeleteStack(math);
                        return "Invalid Expression";
                    } else
                        AddNode(math, Divide(num2, num1));
                }
            }
        }
    }
    string ans = math->pHead->value;
    DeleteStack(s);
    DeleteStack(math);
    return ans;
}
string Trim(string s){
    string res = "";
    for(int i = 0; i < s.size(); ++i){
        if(s[i] != ' ') res += s[i];
    }
    return res;
}
string Refactor(string eq){
    string res = "";
    for(int i = 0; i < eq.size(); ++i){
        char c = eq[i];
        if(c == '+' || c == '*' || c == ':' || c == '(' || c == ')'){
            if(c == '('){
                res += c;
                res += ' ';
            } else
            if(c == ')'){
                res += ' ';
                res += c;
            } else {
                res += ' ';
                res += c;
                res += ' ';
            }
        } else if(c == '-' && (i >= 1 && ((eq[i-1] - '0' >= 0 && eq[i-1] - '0' <= 9) || eq[i-1] == ')') && (eq[i+1] - '0' >= 0 && eq[i+1] - '0' <= 9) || eq[i+1] == '(')){
            res += ' ';
            res += c;
            res += ' ';
        } else if(c == '-'){
            res += c;
        } else {
            res += c;
        }
    }
    res += ' ';
    // cout << res << endl;
    return res;
}
bool IsValid(string expression) {
    Stack* s = Init();
    for (char c : expression) {
        if (c == '(') {
            AddNode(s, string(1, c));
        } else if (c == ')') {
            if (s->pHead == NULL) {
                DeleteStack(s);
                return false;
            }
            PopNode(s);
        }
    }
    bool isValid = (s->pHead == NULL);
    DeleteStack(s);
    bool isValid2 = true;
    for(int i = 0; i < expression.size() - 1; ++i){
        if((expression[i] == '+' || expression[i] == '-') && (expression[i+1] == '*' || expression[i+1] == ':')){
            isValid2 = false;
            break;
        }
        if(expression[i] == ':' && expression[i+1] == '0'){
            isValid2 = false;
            break;
        }
    }
    return (isValid && isValid2);
}

int main() {
    FILE* inp = fopen("input.txt","r");
    FILE* out = fopen("output.txt","w");
    while(!feof(inp)){
        char eq_c[256];
        fscanf(inp,"%[^\n]\n",eq_c);
        string eq = eq_c;
        eq = Trim(eq);
        string ans;
        if(IsValid(eq)){
            eq = Refactor(eq);
            ans = Calculate(eq);
        } else
            ans = "Invalid Expression";
        fprintf(out,"%s\n",ans.c_str());
    }
    fclose(inp);
    fclose(out);
    return 0;
}