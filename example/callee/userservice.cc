#include <iostream>
#include <string>
#include "user.pb.h"
using namespace std;

class UserService : public fixbug::UserService
{
public:
    bool Login(string name, string pwd)
    {
        cout << "doing local service:Login" << endl;
        cout << name << " " << pwd << endl;
    }

    void Login(::google::protobuf::RpcController *controller,
               const ::fixbug::LoginRequest *request,
               ::fixbug::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        string name = request->name();
        string pwd = request->pwd();

        bool Login_result = Login(name,pwd);

        //写response返回值
        fixbug::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(Login_result);
    }
};

int main()
{

    return 0;
}