#include <iostream>

using namespace std;

/**
  * 适配器模式
  * 如果可以进行系统重构，就不要选择适配器模式
*/

class MediaAdapter
{
public:
    void player(const string &mediaType, const string &mediaName)
    {
        if (mediaType == "mp4")
        {
            cout << "play mp4: " << mediaName << " ..." << endl;
        }
        else if (mediaType == "vlc")
        {
            cout << "play vlc: " << mediaName << " ..." << endl;
        }
    }
};

class MediaPlayer
{
public:
    MediaPlayer() :m_mediaAdapter(nullptr) {}

    void player(const string &mediaType, const string &mediaName)
    {
        if (mediaType == "mp3")
        {
            cout << "play mp3: " << mediaName << " ..." << endl;
        }
        else if(mediaType == "mp4" || mediaType == "vlc")
        {
            if (nullptr == m_mediaAdapter)
            {
                m_mediaAdapter = new MediaAdapter();
            }
            m_mediaAdapter->player(mediaType, mediaName);
        }
        else
        {
            cout << "unknow type: " << mediaName << " ..." << endl;
        }
    }

private:
    MediaAdapter* m_mediaAdapter;
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
