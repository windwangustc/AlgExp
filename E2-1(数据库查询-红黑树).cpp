#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    string OPCODE,NUMBER;
    std:map<int, int> db;

    while(cin>>OPCODE){
        if(OPCODE=="EXIT")   exit(0);
        else
        {
            cin>>NUMBER;
            int digit = atoi(NUMBER.c_str());
            if(OPCODE == "INSERT")  db[digit]=digit;
            if(OPCODE == "FIND" && !db.empty()){
                auto iter = db.find(digit);
                if(iter != db.end()) {                   //如果找到了这个NUMBER 输出
                    cout << digit << endl;
                }
                else {                                    //否则输出比他小的最大的数字
                    iter = db.lower_bound(digit);
                    if(iter!=db.begin())
                        iter--;
                    int d = iter->second;
                    if(d< digit)
                        cout << d << endl;
                }
            }
        }
    }
    return 0;
}