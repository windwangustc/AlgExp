#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    string OPCODE,ID,NAME;
    std:map<string , int> db;

    while(cin>>OPCODE){
        if(OPCODE=="EXIT")   exit(0);
        else
        {
            if(OPCODE == "INSERT")  {
                cin >> ID;
                cin >> NAME;
                int digit_id = atoi(ID.c_str());
                db[NAME]=digit_id;
            }
            if(OPCODE == "FIND" && !db.empty()){
                cin>>NAME;
                auto iter = db.find(NAME);
                if(iter != db.end()) {                   //如果找到了这个NAME 输出ID
                    cout << iter->second << endl;
                }
                else {                                    //否则输出-1
                    cout << -1 << endl;
                }
            }
        }
    }
    return 0;
}