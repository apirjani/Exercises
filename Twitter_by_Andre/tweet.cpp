#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "datetime.h"
#include "user.h"
#include "tweet.h"
#include "util.h"

using namespace std;


Tweet::Tweet()
{
    _user = NULL;
    DateTime timestamp;
}

Tweet::Tweet(User* user, const DateTime& time, const string& text)
: _user(user), _timestamp(time), _text(text)
{
}

//return timestamp of tweet
DateTime const& Tweet::time() const
{
    return _timestamp;
}

//return text of tweet
string const& Tweet::text() const
{
    return _text;
}

set<string> Tweet::hashTags() const
{
    
    set<string> hashtag_set;
    //iterate through the text of the tweet
    for (unsigned int i = 0; i < _text.size(); i++)
    {
        //when reach pound sign
        if (_text[i] == '#')
        {
            //start with next character
            int j = i+1;
            string hash_temp = "";
            //continue to store each character after pound sign
            //until reach end of word or end of text
            while (_text[j] != ' ' && _text[j] != '\0')
            {
                hash_temp += _text[j];
                j++;
            }
            convLower(hash_temp);
            hashtag_set.insert(hash_temp);
        }
    }

    return hashtag_set;
}

//return true if tweet came before other tweet
bool Tweet::operator<(const Tweet& other) const
{
    return _timestamp < other.time();
}

//return user of tweet
User* Tweet::user() const
{
    return _user;
}

//overload insertion operator to print tweet with timestamp and username
ostream& operator<<(ostream& os, const Tweet& t)
{
    os << t.time() << ' ' << (t.user())->name() << ' ' << t.text();
    return os;
}

