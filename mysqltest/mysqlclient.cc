#include<iostream>
#include<string>
#include<cstdlib>
#include<mysql/mysql.h>

using namespace std;

string host = "127.0.0.1";
string user = "root";
string pass = "tzx131359";
string db = "douyin";
unsigned int port = 3306;


int main()
{
    MYSQL *msql = mysql_init(nullptr);
    if(msql == nullptr)
    {
        cerr << "init error" << endl;
        exit(1); 
    }

    if(mysql_real_connect(msql,host.c_str(),user.c_str(),pass.c_str(),db.c_str(),
    port,nullptr,0) == nullptr)
    {
        cerr << "connect error" << endl;
        exit(1);
    }

    cout << "connect success" << endl;
    mysql_close(msql);
    
    return 0;

}