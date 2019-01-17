#include <iostream>
#include <thread>
#include <functional>
#include "ringbuffer.hpp"

using namespace std;

RingBuffer<int> g_buffer;

void func()
{
    cout << "thread id : " << this_thread::get_id() << endl;
    cout << "" << g_buffer.take() << endl;
}

void push(int value)
{
    cout << "push " << value << endl;
    g_buffer.push(value);
}

int main()
{
    thread td(func);

    cout << "main   id : " << this_thread::get_id() << endl;
    push(2);

    td.join();

    cout << "Hello World!" << endl;
    return 0;
}
