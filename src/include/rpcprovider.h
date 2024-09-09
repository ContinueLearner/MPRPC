#include <google/protobuf/service.h>

class RpcProvider
{
public:
    void NotifyService(google::protobuf::Service *service);
    void run();
private:
};