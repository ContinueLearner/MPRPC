#include "mprpcconfig.h"
#include <iostream>

//从配置文件中加载信息
void MprpcConfig::LoadConfigFile(const char* configFile)
{
    FILE *pf = fopen(configFile,"r");
    if(pf == nullptr)
    {
        cout << configFile << " is note exist!" << endl;
        exit(EXIT_FAILURE);
    }

    while(!feof(pf))
    {
        char buf[512] = {0};
        fgets(buf,512,pf);

        string read_buf(buf);
        Trim(read_buf);

        if(read_buf[0] == '#' || read_buf.empty())continue;

        int idx = read_buf.find('=');
        if(idx == -1)continue;

        string key;
        string value;
        key = read_buf.substr(0,idx);
        Trim(key);

        int endidx = read_buf.find('\n');
        value = read_buf.substr(idx+1,endidx-idx - 1);
        Trim(value);

        m_configMap.insert({key,value});
    }
}
//根据某个key返回对应的value
string MprpcConfig::Load(const string& key)
{
    auto it = m_configMap.find(key);
    if(it != m_configMap.end())return it->second;
    else return "";
}
void MprpcConfig::Trim(string& src_buf)
{
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串前面有空格
        src_buf = src_buf.substr(idx, src_buf.size()-idx);
    }
    // 去掉字符串后面多余的空格
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串后面有空格
        src_buf = src_buf.substr(0, idx+1);
    }
}