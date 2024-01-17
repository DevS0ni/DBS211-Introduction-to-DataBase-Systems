#include <iostream>
#include<iomanip>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

int main(void)
{
	Environment* env = nullptr;
	Connection* conn = nullptr;
    Statement* stmt = nullptr;

	string str;
	string usr = "dbs211_222j04";
	string pass = "12141168";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

    try
    {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(usr, pass, srv);
        stmt = conn->createStatement();


        ResultSet* rs = nullptr;
        rs = stmt->executeQuery("SELECT EMPLOYEENUMBER, FIRSTNAME, LASTNAME, PHONE, EXTENSION FROM RETAILEMPLOYEES INNER JOIN RETAILOFFICES ON RETAILEMPLOYEES.OFFICECODE = RETAILOFFICES.OFFICECODE WHERE RETAILOFFICES.CITY = 'San Francisco' ORDER BY EMPLOYEENUMBER");
        cout << "------------------------- Report 1 (Employee Report) ------------------------------" << endl;
        cout << "Employee ID   First Name           Last Name        Phone            Extension" << endl;
        cout << "------------  ------------------   ---------------  ---------------  ----------" << endl;
        
        if (!rs->next()) 
        {
            cout << "ResultSet is empty." << endl;
        }
        else 
        {
            do
            {
                cout << setw(14) << left << rs->getString(1) << setw(21) << left << rs->getString(2) << setw(16) << left << rs->getString(3) << setw(18) << left << rs->getString(4) << setw(16) << left << rs->getString(5) << endl;
            } while (rs->next());

        }
        
        ResultSet* sr = nullptr;
        sr = stmt->executeQuery("SELECT DISTINCT t2. EMPLOYEENUMBER, t2.FIRSTNAME,t2.LASTNAME, PHONE, t2.EXTENSION FROM RETAILEMPLOYEES t LEFT JOIN RETAILEMPLOYEES t2 ON t.REPORTSTO = t2.EMPLOYEENUMBER JOIN RETAILOFFICES t3 ON t2.OFFICECODE = t3.OFFICECODE WHERE t3.OFFICECODE IN (1,6,5,4) AND t.REPORTSTO IS NOT NULL ORDER BY EMPLOYEENUMBER");
        cout << endl << "------------------------- Report 2 (Manager Report) ------------------------------" << endl;
        cout << "Employee ID   First Name           Last Name        Phone            Extension" << endl;
        cout << "------------  ------------------   ---------------  ---------------  ----------" << endl;
        
        if (!sr->next()) 
        {
            cout << "ResultSet is empty." << endl;
        }
        else 
        {
            do
            {
                cout << setw(14) << left << sr->getString(1) << setw(21) << left << sr->getString(2) << setw(16) << left << sr->getString(3) << setw(18) << left << sr->getString(4) << setw(16) << left << sr->getString(5) << endl;
            } while (sr->next());

        }
        conn->terminateStatement(stmt);
        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }
        catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
    return 0;
}
