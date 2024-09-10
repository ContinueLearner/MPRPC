#pragma once
#include<string>
#include<unordered_map>
using namespace std;

class MprpcConfig
{
public:
    //从配置文件中加载信息
    void LoadConfigFile(const char* configFile);
    //根据某个key返回对应的value
    string Load(const string& key);
private:
    unordered_map<string,string> m_configMap;
    void Trim(string& src_buf);
};