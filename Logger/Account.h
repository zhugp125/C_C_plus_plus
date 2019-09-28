#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "LoggerImp.h"

class Account
{
public:
    Account(const CLoggerImpPtr& ptr_logger);

    bool saveMoney(const long long money);
    long long withdrawMoney();

private:
    CLoggerImpPtr ptr_logger_;
    long long money_ = 0;
};

#endif // ACCOUNT_H
