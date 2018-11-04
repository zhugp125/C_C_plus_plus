#include <iostream>
using namespace std;

class HomeView
{
public:
    void display()
    {
        cout << "display HomeView" << endl;
    }
};

class StudentView
{
public:
    void display()
    {
        cout << "display StudentView" << endl;
    }
};

class Dispatcher
{
public:
    void dispatch(const string& request)
    {
        if (request == "student")
        {
            m_studentView.display();
        }
        else
        {
            m_homeView.display();
        }
    }

private:
    HomeView m_homeView;
    StudentView m_studentView;
};

class FrontController
{
private:
    bool isAuthenticUser()
    {
        cout << "user is authenticated successfully" << endl;
        return true;
    }

    void trackRequest(const string& request)
    {
        cout << "[Page] requested: " << request << endl;
    }

public:
    void dispatchRequest(const string& request)
    {
        trackRequest(request);

        if (isAuthenticUser())
        {
            m_dispatcher.dispatch(request);
        }
    }

private:
    Dispatcher m_dispatcher;
};

int main()
{
    FrontController frontController;
    frontController.dispatchRequest("student");
    cout << endl;
    frontController.dispatchRequest("home");
    cout << "Hello World!" << endl;
    return 0;
}
