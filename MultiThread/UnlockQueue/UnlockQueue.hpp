#ifndef UNLOCKQUEUE_H
#define UNLOCKQUEUE_H

/**
 * 适用于单消费者/单读写者的环境
*/
class UnlockQueue
{
public:
    UnlockQueue(unsigned int size);
    virtual ~UnlockQueue();

    bool initialize();

    unsigned int put(const unsigned char* buffer, unsigned int len);
    unsigned int get(unsigned char* buffer, unsigned int len);

    inline void clear() { m_in = m_out = 0; }
    inline unsigned int length() const { return m_in - m_out; }

private:
    inline bool isPowerOfTwo(unsigned long n) { return (n != 0 && (n & (n - 1)) == 0); }
    inline unsigned long roundupPowerOfTwo(unsigned long n);

private:
    unsigned char* m_buffer;
    unsigned int   m_size;
    unsigned int   m_in;
    unsigned int   m_out;
};

UnlockQueue::UnlockQueue(unsigned int size)
    : m_buffer(nullptr)
    , m_size(size)
    , m_in(0)
    , m_out(0)
{
    if (!isPowerOfTwo(size))
    {
        m_size = roundupPowerOfTwo(size);
    }
}

UnlockQueue::~UnlockQueue()
{
    if (m_buffer != nullptr)
    {
        delete[] m_buffer;
        m_buffer = nullptr;
    }
}

bool UnlockQueue::initialize()
{
    m_buffer = new unsigned char[m_size];
    if (nullptr == m_buffer)
    {
        return false;
    }

    clear();
    return true;
}

unsigned int UnlockQueue::put(const unsigned char *buffer, unsigned int len)
{
    unsigned int ul;
    len = std::min(len, m_size - length());

    __sync_synchronize();

    ul = std::min(len, m_size - (m_in & (m_size - 1)));
    memcpy(m_buffer + (m_in & (m_size - 1)), buffer, ul);

    memcpy(m_buffer, buffer + ul, len - ul);

    __sync_synchronize();

    m_in += len;
    return len;
}

unsigned int UnlockQueue::get(unsigned char *buffer, unsigned int len)
{
    unsigned int ul;
    len = std::min(len, length());

    __sync_synchronize();

    ul = std::min(len, m_size - (m_out & (m_size - 1)));
    memcpy(buffer, m_buffer + (m_out & (m_size - 1)), ul);

    memcpy(buffer + ul, m_buffer, len - ul);

    __sync_synchronize();

    m_out += len;
    return len;
}

unsigned long UnlockQueue::roundupPowerOfTwo(unsigned long n)
{
    if (isPowerOfTwo(n))
        return n;

    unsigned long maxulong = (unsigned long)((unsigned long)~0);
    unsigned long andv = ~(maxulong & (maxulong >> 1));
    while ((andv & n) == 0)
        andv = andv >> 1;

    return andv << 1;
}

#endif // UNLOCKQUEUE_H
