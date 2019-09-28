#include <iostream>
#include "client.hpp"
#include "Account.h"
#include "StandardOutputLogger.h"

using namespace std;

int main()
{
    // Signle
    Client client;
    client.login();
    client.searchFailed();
    client.logout();

    // Dependency injection
    CLoggerImpPtr ptr_logger = std::make_shared<StandardOutputLogger>();
    Account account(ptr_logger);
    account.saveMoney(1000);
    std::cout << account.withdrawMoney() << std::endl;

    cout << "Hello World!" << endl;
    return 0;
}
