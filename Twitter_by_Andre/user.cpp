#include <string>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include "tweet.h"
#include "user.h"

using namespace std;

User::User(string name)
: _name(name)
{
}

User::~User()
{
    list<Tweet*>::iterator it;
    for (it = _tweets.begin(); it != _tweets.end(); ++it)
    {
        delete *it;
    }

}

//returns user's name
string User::name() const
{
    return _name;
}

//returns set of pointers to user's followers
set<User*> User::followers() const
{
    return _followers;
}

//returns set of pointers to users that current user is following
set<User*> User::following() const
{
    return _following;
}

//returns list of tweets from current user
list<Tweet*> User::tweets() const
{
    return _tweets;
}

//adds user to followers set
void User::addFollower(User* u)
{
    _followers.insert(u);
}

//adds user to following set
void User::addFollowing(User* u)
{
    _following.insert(u);
}

//adds tweet to tweet list
void User::addTweet(Tweet* t)
{
    _tweets.push_back(t);
}

//gets the feed of the user, including the current users tweets and
//from the users he/she is following
vector<Tweet*> User::getFeed()
{
    vector<Tweet*> feed_tweets;
    list<Tweet*>::iterator it;
    //first collect all of the user's current tweets
    for (it = _tweets.begin(); it != _tweets.end(); ++it)
    {
        feed_tweets.push_back(*it);
    }

    set<User*>::iterator it2;
    //iterate through list of users being followed by current user
    for (it2 = _following.begin(); it2 != _following.end(); ++it2)
    {
        //store each user's tweets
        list<Tweet*> following_tweets = (*it2)->tweets();
        list<Tweet*>::iterator it3;
        //store all of them in the vector that will be returned
        for (it3 = following_tweets.begin(); it3 != following_tweets.end(); ++it3)
        {
            feed_tweets.push_back(*it3);
        }
    }

    //sort them all by timestamp
    sort(feed_tweets.begin(), feed_tweets.end(), TweetComp());

    return feed_tweets;

}


