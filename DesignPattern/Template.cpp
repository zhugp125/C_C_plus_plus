#include <iostream>
using namespace std;

class Game
{
public:
    virtual ~Game() {}
    void play()
    {
        // 初始化游戏
        initialize();
        // 开始游戏
        startPlay();
        // 结束游戏
        endPlay();
    }

protected:
    virtual void initialize() = 0;
    virtual void startPlay() = 0;
    virtual void endPlay() = 0;
};

class Basketball : public Game
{
protected:
    void initialize()
    {
        cout << "initialize basketball" << endl;
    }

    void startPlay()
    {
        cout << "start play basketball" << endl;
    }

    void endPlay()
    {
        cout << "end play basketball" << endl;
    }
};

class Football : public Game
{
protected:
    void initialize()
    {
        cout << "initialize football" << endl;
    }

    void startPlay()
    {
        cout << "start play football" << endl;
    }

    void endPlay()
    {
        cout << "end play football" << endl;
    }
};

int main()
{
    Game* basket = new Basketball;
    basket->play();
    delete basket;
    cout << endl;

    Game* foot = new Football;
    foot->play();
    delete foot;

    cout << "Hello World!" << endl;
    return 0;
}
