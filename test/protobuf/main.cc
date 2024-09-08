#include "test.pb.h"
#include <iostream>
using namespace fixbug;
using namespace std;

int main()
{
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("123456");

    //序列化
    string send_str;
    if(req.SerializeToString(&send_str))
    {
        cout<<send_str.c_str()<<endl;
    }
    //反序列化
    LoginRequest reqB;
    if(reqB.ParseFromString(send_str))
    {
        cout<<reqB.name()<<endl;
        cout<<reqB.pwd()<<endl;
    }

    return 0;
}