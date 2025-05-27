#include <iostream>
#include <map>
#include <cmath>
#include <math.h>
using namespace std;
struct stacke {
    char info;
    long double chisl;
    stacke* nxt;
};
map<char, int> pr;
map<char, int> pro;
void pushe(stacke* &top, char t, long double u) {
    stacke* p;
    p = (stacke*)malloc(sizeof(stacke));
    if (t != '#') {
        (*p).info = t;
    }
    (*p).nxt = top;
    if (u != -100000000000) {
        (*p).chisl = u;
    }
    top = p;
}
stacke pop(stacke* &top) {
    stacke l;
    l = (*top);
    top = (*top).nxt;
    return l;
}
bool oper(stacke x, stacke* &top) {
    long double x1 = pop(top).chisl;
    if (pro[x.info] != 1 && top == nullptr) {
        return false;
    }
    if (x.info == '^') {
        pushe(top, '#', pow(pop(top).chisl, x1));
        return true;
    }
    if (x.info == 's') {
        pushe(top, '#', sin(x1));
        return true;
    }
    if (x.info == 'c') {
        pushe(top, '#', cos(x1));
        return true;
    }
    if (x.info == 't') {
        pushe(top, '#', tan(x1));
        return true;
    }
    if (x.info == 'l') {
        if (x1 < 0) {
            return false;
        }
        pushe(top, '#', log(x1));
        return true;
    }
    if (x.info == 'q') {
        if (x1 < 0) {
            return false;
        }
        pushe(top, '#', sqrt(x1));
        return true;
    }
    if (x.info == '+') {
        pushe(top, '#', x1 + pop(top).chisl);
        return true;
    }
    if (x.info == '-') {
        pushe(top, '#', pop(top).chisl - x1);
        return true;
    }
    if (x.info == '*') {
        pushe(top, '#', x1 * pop(top).chisl);
        return true;
    }
    if (x.info == '/') {
        if (x1 == 0) {
            return false;
        }
        pushe(top, '#', pop(top).chisl / x1);
        return true;
    }
}
bool er(string s) {
    int nume = 0;
    int num = 0;
    bool a = true;
    for (int i = 0; i < s.size(); i ++) {



        if (s[i] >= '0' && s[i] <= '9') {
            nume ++;
        }
        if (i == 0) {
            if (s[i] == '*' || s[i] == '/' || s[i] == '^' || s[i] == '+') {
                a = false;
            }
        }

        if( i!= 0){
            if(s[i] == '.'){
                continue;
            }
        }

        if (i > 0) {
            if (pro[s[i - 1]] == 1) {
                if (s[i] != '(') {
                    a = false;
                }
            }
            if (s[i - 1] == '^' && s[i] == '-') {
                a = false;
            }
            if (s[i - 1] == '(' && (s[i] == '*' || s[i] == '/' || s[i] == '^' || s[i] == '+')) {
                a = false;
            }
        }
        if (pr[s[i]] > 0 && i < s.size() - 1 && s[i + 1] == ')') {
            a = false;
        }
        if (i == s.size() - 1 && pr[s[i]] > 0) {
            a = false;
        }
        if (s[i] == '(') {
            num ++;
        }
        else if (s[i] == ')') {
            num --;
        }
        if (num < 0) {
            a = false;
        }
        if (pr[s[i]] > 0 || (s[i] >= '0' && s[i] <= '9') || s[i] == ')') {
            continue;
        }
        else {
            a = false;
        }
    }
    if (nume == 0) {
        a = false;
    }
    return a;
}

bool calc(string q, float&ans)
{
    stacke* top = nullptr;
    stacke* top2 = nullptr;
    pr['+'] = 2;
    pr['*'] = 3;
    pr['-'] = 2;
    pr['/'] = 3;
    pr['('] = 1;
    pr['s'] = 5;
    pr['c'] = 5;
    pr['t'] = 5;
    pr['l'] = 5;
    pr['q'] = 4;
    pr['^'] = 4;
    pro['l'] = 1;
    pro['q'] = 1;
    pro['t'] = 1;
    pro['c'] = 1;
    pro['s'] = 1;
    string s = "";
    string o = "";
    for (int i = 0; i < q.size(); i ++) {
        if (q[i] == 's' && q[i + 1] == 'i') {
            s += 's';
            i += 2;
        }
        else if (q[i] == 'c') {
            s += 'c';
            i += 2;
        }
        else if (q[i] == 't') {
            s += 't';
            i += 1;
        }
        else if (q[i] == 's' && q[i + 1] == 'q') {
            s += 'q';
            i += 3;
        }
        else if (q[i] == 'l') {
            s += 'l';
            i += 1;
        }

        else {
            s += q[i];
        }
    }
    for (int i = 0; i < s.size(); i ++) {
        if (i == 0 && s[i] == '-') {
            o += '0';
        }
        if (i > 0 && s[i - 1] == '(' && s[i] == '-') {
            o += '0';
        }
        o += s[i];
    }
    s = o;
    int j = 0;
    if(er(s) == false){
        return false;
    }
    while (j < s.size()) {
        char i = s[j];
        if ((i == '-' || i == '+' || i == '*' || i == '/' || i == '(' || pro[i] == 1 || i == '^') && (top2 == nullptr || pr[(*top2).info] < pr[i]  || i == '(')) {
            pushe(top2, i, -100000000000);
        }
        else if (i == ')') {
            stacke x = pop(top2);

                while (x.info != '(') {
                    bool fla = oper(x, top);
                    if (fla ==  false){
                        return false;
                    }
                    x = pop(top2);

                }


        }
        else if ((i == '-' || i == '+' || i == '*' || i == '/' || pro[i] == 1 || i == '^')) {
            while (top2 != nullptr && pr[(*top2).info] >= pr[i]) {
                stacke x = pop(top2);
                bool fla = oper(x, top);
                    if (fla ==  false){
                        return false;
                    }

            }
            pushe(top2, i, -100000000000);
        }

        else {
            long double qe = 0;
            while (i >= '0' && i <= '9') {
                qe = qe * 10 + (i - '0');
                j ++;
                i = s[j];
            }
            if (i == '.'){
                j++;
                i = s[j];
                long double st = 1;
                while (i >= '0' && i <= '9') {
                    st *= 10;
                    qe = qe + (long double)(i - '0') / st;
                    j ++;
                    i = s[j];
                }
                if(i =='.'){
                    return false;
                }
            }
            j --;
            pushe(top, '#', qe);
        }
        j ++;
        }
        if ((top2) != nullptr) {
            stacke x = pop(top2);
            while (top2 != nullptr) {
                bool fla = oper(x, top);
                if (fla ==  false){
                    return false;
                }
                x = pop(top2);

            }
            bool fla = oper(x, top);
            if (fla ==  false){
                return false;
             }


        }
        ans = pop(top).chisl;
        return true;

}
/*int main () {
    float ans;
    string q, x;
    cin >> q >> x;
    if (calc(q, x, ans) == false){
            return 0;
    }
    calc(q, x, ans);
    cout << ans;
}*/
