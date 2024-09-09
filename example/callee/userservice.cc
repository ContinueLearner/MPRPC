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
        
    }
};