#include "user.h"
/*
 * 中介者模式，一个文件搞不定
 *
 * user.h
 * #include <iostream>
 * using namespace std;
 *
 * class User
 * {
 * public:
 *  User(const string& name) : m_name(name) {}
 *  void setName(const string& name) { m_name = name; }
 *  string getName() { return m_name; }
 *  void showMessage(const string& msg);
 * private:
 *  string m_name;
 * };
 *
 * user.cpp
 * #include "user.h"
 * #include "chatroom.h"
 *
 * void User::showMessage(const string &msg)
 * {
 *  ChatRoom::showMessage(this, msg);
 * }
 *
 * chatroom.h
 * #include <iostream>
 * using namespace std;
 *
 * class User;
 * class ChatRoom
 * {
 * public:
 *  static void showMessage(User* user, const string& msg);
 * };
 *
 * #include "chatroom.h"
 * #include "user.h"
 *
 * void ChatRoom::showMessage(User *user, const string &msg)
 * {
 *  cout << user->getName() << ": " << msg << endl;
 * }
 *
 * Mediator.cpp
 * int main()
 * {
 *  User hebe("hebe");
 *  hebe.showMessage("小情歌");
 *  return 0;
 * }
*/

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
