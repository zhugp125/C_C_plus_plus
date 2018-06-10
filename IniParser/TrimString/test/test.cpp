#include <gtest/gtest.h>
#include "../TrimString.h"

TEST(TrimLeft, LEFT)
{
    using namespace std;

    EXPECT_EQ("", trimleft(""));
    EXPECT_EQ("hello", trimleft("hello"));
    EXPECT_EQ("hello", trimleft("   hello"));
    EXPECT_EQ("hello  ", trimleft("hello  "));
    EXPECT_EQ("#  hello", trimleft("#  hello"));
    EXPECT_EQ("hello  ", trimleft("  hello  "));
}

TEST(TrimRight, RIGHT)
{
    using namespace std;

    EXPECT_EQ("", trimright(""));
    EXPECT_EQ("hello", trimright("hello"));
    EXPECT_EQ("hello", trimright("hello  "));
    EXPECT_EQ("  hello", trimright("  hello"));
    EXPECT_EQ("hello  #", trimright("hello  #"));
    EXPECT_EQ("  hello", trimright("  hello  "));
}

TEST(Trim, TRIM)
{
    using namespace std;

    EXPECT_EQ("", trim(""));
    EXPECT_EQ("hello", trim("hello"));
    EXPECT_EQ("hello", trim("hello  "));
    EXPECT_EQ("hello", trim("  hello"));
    EXPECT_EQ("#  hello  #", trim("#  hello  #"));
    EXPECT_EQ("hello", trim("  hello  "));
}

TEST(Section, parserSection)
{
    using namespace std;

    string section;
    bool ok = parserSection("", section);
    EXPECT_FALSE(ok);

    ok = parserSection("first]", section);
    EXPECT_FALSE(ok);

    ok = parserSection("[first", section);
    EXPECT_FALSE(ok);

    ok = parserSection("[first]", section);
    EXPECT_TRUE(ok);
    if (ok)
    {
        EXPECT_EQ("first", section);
    }

    ok = parserSection("  [first]", section);
    EXPECT_TRUE(ok);
    if (ok)
    {
        EXPECT_EQ("first", section);
    }

    ok = parserSection("[first]   ", section);
    EXPECT_TRUE(ok);
    if (ok)
    {
        EXPECT_EQ("first", section);
    }

    ok = parserSection("  [first]  ", section);
    EXPECT_TRUE(ok);
    if (ok)
    {
        EXPECT_EQ("first", section);
    }
}

TEST(IsComment, comment)
{
    EXPECT_FALSE(isComment(""));
    EXPECT_FALSE(isComment("hello"));
    EXPECT_TRUE(isComment("#hello"));
    EXPECT_TRUE(isComment(";hello"));
}

TEST(ParserKeyValue, KeyValue)
{
    using namespace std;
    string key, value;

    bool ok = parserKeyValue("", key, value);
    EXPECT_FALSE(ok);

    ok = parserKeyValue("hello", key, value);
    EXPECT_FALSE(ok);

    ok = parserKeyValue("key=value", key, value);
    EXPECT_TRUE(ok);
    EXPECT_EQ("key", key);
    EXPECT_EQ("value", value);

    ok = parserKeyValue("key=value  ", key, value);
    EXPECT_TRUE(ok);
    EXPECT_EQ("key", key);
    EXPECT_EQ("value", value);

    ok = parserKeyValue(" key=value", key, value);
    EXPECT_TRUE(ok);
    EXPECT_EQ("key", key);
    EXPECT_EQ("value", value);
}

