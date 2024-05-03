#include "connector/include/mysql/jdbc.h"

int main()
{
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;


    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "1");

    con->setSchema("dataBaze");
    
    sql::Statement *stmt;
    sql::ResultSet *res;

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM Ana");

    while (res->next())
    {
        std::cout << "ID: " << res->getInt("id") << ", Name: " << res->getInt("price") << ' ' << res->getString("numeProdus") <<'\n';
    }

    delete res;
    delete stmt;
    delete con;
}