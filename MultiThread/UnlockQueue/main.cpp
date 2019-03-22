#include <iostream>
#include <thread>
#include <chrono>

#include <stdio.h>

#include "UnlockQueue.hpp"

using namespace std;

struct Node
{
    int m_value;
};

void display(const Node* pNode)
{
    if (nullptr == pNode)
        return;

    printf("value = %d\n", pNode->m_value);
}

void consumer(UnlockQueue* queue)
{
    if (nullptr == queue)
        return;

    Node node;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        unsigned int len = queue->get((unsigned char*)&node, sizeof(Node));
        if (len > 0)
        {
            printf("---------------------------\n");
            printf("UnlockQueue length: %u\n", queue->length());
            display(&node);
            printf("---------------------------\n");
        }
    }
}

void producer(UnlockQueue* queue)
{
    if (nullptr == queue)
        return;

    while (true)
    {
        Node node;
        node.m_value = rand() % 1000;
        printf("---------------------------\n");
        printf("put a node to queue\n");
        queue->put((unsigned char*)&node, sizeof(Node));
        printf("UnlockQueue length: %u\n", queue->length());
        printf("---------------------------\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    UnlockQueue unlockQueue(1024);
    if (!unlockQueue.initialize())
    {
        return -1;
    }

    std::thread c_id(consumer, &unlockQueue);
    std::thread p_id(producer, &unlockQueue);
    c_id.join();
    p_id.join();

    cout << "Hello World!" << endl;
    return 0;
}
