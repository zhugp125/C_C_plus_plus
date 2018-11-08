#include <iostream>
#include <map>
using namespace std;

class Service
{
public:
    virtual ~Service() {}
    virtual string getName() = 0;
    virtual void execute() = 0;
};

class LocalService : public Service
{
public:
    string getName()
    {
        return "LocalService";
    }

    void execute()
    {
        cout << "LocalService start" << endl;
    }
};

class NetworkService : public Service
{
public:
    string getName()
    {
        return "NetworkService";
    }

    void execute()
    {
        cout << "NetworkService start" << endl;
    }
};

class Cache
{
public:
    ~Cache()
    {
        for(auto it = m_services.begin(); it != m_services.end(); ++it)
        {
            delete it->second;
        }
    }

    Service* getService(const string& serviceName)
    {
        auto it = m_services.find(serviceName);
        if (it != m_services.end())
        {
            return it->second;
        }
        return nullptr;
    }

    void addService(const string& serviceName)
    {
        auto it = m_services.find(serviceName);
        if (it != m_services.end())
        {
            return;
        }

        Service* service = nullptr;
        if ("LocalService" == serviceName)
        {
            service = new LocalService;
        }
        else if ("NetworkService" == serviceName)
        {
            service = new NetworkService;
        }

        if (service != nullptr)
        {
            cout << "add service: " << serviceName << endl;
            m_services[serviceName] = service;
        }
    }

private:
    map<string, Service*> m_services;
};

class ServiceLoactor
{
public:
    Service* getService(const string& serviceName)
    {
        Service* service = m_cache.getService(serviceName);
        if (service != nullptr)
        {
            return service;
        }

        m_cache.addService(serviceName);
        return m_cache.getService(serviceName);
    }

private:
    Cache m_cache;
};

int main()
{
    ServiceLoactor locactor;
    Service* service = locactor.getService("LocalService");
    service->execute();
    service = locactor.getService("NetworkService");
    service->execute();
    service = locactor.getService("LocalService");
    service->execute();
    service = locactor.getService("NetworkService");
    service->execute();

    cout << "Hello World!" << endl;
    return 0;
}
