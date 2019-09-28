#include "Account.h"

Account::Account(const CLoggerImpPtr& ptr_logger)
    : ptr_logger_(ptr_logger)
{
}

bool Account::saveMoney(const long long money)
{
    if (money > 0)
    {
        money_ += money;
        ptr_logger_->writeInfoMsg(std::to_string(money));
        return true;
    }
    else
    {
        ptr_logger_->writeErrorMsg(std::to_string(money));
        return false;
    }
}

long long Account::withdrawMoney()
{
    if (money_ > 0)
    {
        ptr_logger_->writeInfoMsg(std::to_string(money_));
        return money_;
    }
    else
    {
        ptr_logger_->writeWarnMsg("no money");
        return -1;
    }
}
