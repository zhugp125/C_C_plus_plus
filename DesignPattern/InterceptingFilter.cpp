#include <iostream>
#include <vector>
using namespace std;

class Filter
{
public:
    virtual ~Filter() {}
    virtual void execute(const string& request) = 0;
};

class AuthenicationFilter : public Filter
{
public:
    void execute(const string& request)
    {
        cout << "[authenication] request: " << request << endl;
    }
};

class DebugFilter : public Filter
{
public:
    void execute(const string& request)
    {
        cout << "[debug] request: " << request << endl;
    }
};

class Target
{
public:
    void execute(const string& request)
    {
        cout << "[target] execute request: " << request << endl;
    }
};

class FilterChain
{
public:
    FilterChain() : m_target(nullptr) {}

    void addFilter(Filter* filter) { m_filters.push_back(filter); }
    void setTarget(Target* target) { m_target = target; }
    void execute(const string& request)
    {
        for(Filter* filter : m_filters)
        {
            filter->execute(request);
        }
        m_target->execute(request);
    }

private:
    Target* m_target;
    vector<Filter*> m_filters;
};

class FilterManager
{
public:
    FilterManager(Target* target)
    {
        m_filterChain.setTarget(target);
    }

    void setFilter(Filter* filter)
    {
        m_filterChain.addFilter(filter);
    }

    void filterRequest(const string& request)
    {
        m_filterChain.execute(request);
    }

private:
    FilterChain m_filterChain;
};

class Client
{
public:
    Client() : m_filterManager(nullptr) {}
    void setFilterManager(FilterManager* filterManager) { m_filterManager = filterManager; }
    void sendRequest(const string& request) { m_filterManager->filterRequest(request); }

private:
    FilterManager* m_filterManager;
};

int main()
{
    Target target;
    FilterManager filterManager(&target);

    Filter* authenFilter = new AuthenicationFilter;
    Filter* debugFilter = new DebugFilter;
    filterManager.setFilter(authenFilter);
    filterManager.setFilter(debugFilter);

    Client client;
    client.setFilterManager(&filterManager);
    client.sendRequest("HOME");

    delete authenFilter;
    delete debugFilter;

    cout << "Hello World!" << endl;
    return 0;
}
