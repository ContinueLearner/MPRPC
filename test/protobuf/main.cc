#include "test.pb.h"
#include <iostream>
using namespace fixbug;
using namespace std;

int main()
{
    GetFriendListResponse rsp;
    ResultCode* result = rsp.mutable_resultcode();
    result->set_errcode(1);
    result->set_errmsg("出错啦");

    User* user = rsp.add_userlist();
    user->set_age(18);
    user->set_name("张三");
    user->set_sex(User::MAN);

    User* user1 = rsp.add_userlist();
    user1->set_age(18);
    user1->set_name("李四");
    user1->set_sex(User::MAN);

    cout<<rsp.userlist_size()<<endl;

    int cnt = rsp.userlist_size();
    for(int i = 0;i<cnt;i++)
    {
        User user = rsp.userlist(i);
        cout<<user.age()<<" "<<user.name()<<" "<<user.sex()<<endl;
    }
    return 0;
}
int main1()
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