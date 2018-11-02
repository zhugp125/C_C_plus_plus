#include <iostream>
#include <map>
using namespace std;

enum EBusinessServiceType
{
    EBST_UNVALID = -1,
    EBST_EJB = 0,
    EBST_JMS,
};

class BusinessService
{
public:
    virtual ~BusinessService() {}
    virtual void doProcessing() = 0;
};

class EJBService : public BusinessService
{
public:
    void doProcessing()
    {
        cout << "display EJBService" << endl;
    }
};

class JMSService : public BusinessService
{
public:
    void doProcessing()
    {
        cout << "display JMSService" << endl;
    }
};

class BusinessLookup
{
public:
    ~BusinessLookup()
    {
        for(auto it = m_businessServices.begin(); it != m_businessServices.end(); ++it)
        {
            delete it->second;
        }
    }

    BusinessService* getBusinessService(EBusinessServiceType eType)
    {
        auto it = m_businessServices.find(eType);
        if (it != m_businessServices.end())
        {
            return it->second;
        }

        BusinessService* service = nullptr;
        if (EBST_EJB == eType)
        {
            service = new EJBService;
        }
        else if (EBST_JMS == eType)
        {
            service = new JMSService;
        }
        m_businessServices[eType] = service;

        return service;
    }

private:
    map<EBusinessServiceType, BusinessService*> m_businessServices;
};

class BusinessDelegate
{
public:
    BusinessDelegate() : m_eType(EBST_UNVALID) {}

    void setBusinessServiceType(EBusinessServiceType eType) { m_eType = eType; }
    void doTask()
    {
        BusinessService* service = m_lookup.getBusinessService(m_eType);
        if (service != nullptr)
        {
            service->doProcessing();
        }
        else
        {
            cout << "unvalid type : " << m_eType << endl;
        }
    }

private:
    BusinessLookup m_lookup;
    EBusinessServiceType m_eType;
};

class Client
{
public:
    Client(BusinessDelegate* businessDelegate) : m_businessDelegate(businessDelegate) {}

    void doTask()
    {
        if (m_businessDelegate != nullptr)
        {
            m_businessDelegate->doTask();
        }
        else
        {
            cout << "unvalid business delegate " << endl;
        }
    }

private:
    BusinessDelegate* m_businessDelegate;
};

int main()
{
    BusinessDelegate delegate;
    Client client(&delegate);
    client.doTask();

    delegate.setBusinessServiceType(EBST_EJB);
    client.doTask();

    delegate.setBusinessServiceType(EBST_JMS);
    client.doTask();

    cout << "Hello World!" << endl;
    return 0;
}
