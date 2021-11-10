#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "twiteng.h"
// Add other header files
#include <string>
#include <map>
#include <set>
#include "tweet.h"
#include <algorithm>
#include "util.h"

using namespace std;


// Update as needed
TwitEng::TwitEng()
{
}

// Update as needed
TwitEng::~TwitEng()
{
  map<string, User*>::iterator it;
  //delete all the users in the system
  for (it = _users.begin(); it != _users.end(); ++it)
  {
    delete it->second;
  }
}

bool TwitEng::parse(char* filename)
{
  ifstream ifile(filename);
  if (ifile.fail()) {
    cerr << "Unable to open " << filename << endl;
    return true;
  }
  int numUsers;
  ifile >> numUsers;
  if (ifile.fail()) {
    cerr << "Unable to read number of users " << endl;
    ifile.close();
    return true;
  }
  // Finish the parsing of the input file. Return false if successful,
  // true otherwise.

  //create all the users profiles, populating their follower and following sets
  for (int i = 0; i < numUsers; i++)
  {
    string user_name;
    //read in user
    ifile >> user_name;
    if (ifile.fail())
    {
      cerr << "Unable to read name of user" << endl;
      return true;
    }
    //if user hasn't already been created, create it
    if (!validUser(user_name))
    {
      _users.insert(make_pair(user_name, new User(user_name)));
    }
    //get the rest of the line which is the users that the current user is following
    string following;
    getline(ifile, following);
    if (ifile.fail())
    {
      cerr << "Unable to read name of following" << endl;
      return true;
    }
    stringstream ss(following);
    //use stringstream to parse each user
    while (ss >> following) //!ss.str().empty()
    {
      if (ss.fail())
      {
        cerr << "Unable to read name of following" << endl;
        return true;
      }
      //if the user doesn't exist yet, create the user
      if (!validUser(following))
      {
        _users.insert(make_pair(following, new User(following)));
      }
      //update the following and follower sets of the appropriate users
      _users[user_name]->addFollowing(_users[following]);
      _users[following]->addFollower(_users[user_name]);
    }
  }

    string temp_tweet;
    while (getline(ifile, temp_tweet))
    {
      if (ifile.fail())
      {
        cerr << "Unable to read tweet" << endl;
        return true;
      }
      //create stringstream that contains entire tweet (including timestamp and user)
      stringstream ss(temp_tweet);
      DateTime timestamp;
      //pull in timestamp from stringstream 
      ss >> timestamp;
      if (ss.fail())
      {
        cerr << "Unable to read tweet" << endl;
        return true;
      }
      string tweeter;
      //pull in username of the tweet
      ss >> tweeter;
      if (ss.fail())
      {
        cerr << "Unable to read tweet" << endl;
        return true;
      }
      if (!validUser(tweeter))
      {
        cerr << "Invalid user in tweet" << endl;
        return true;
      }
      string text;
      getline(ss, text);
      ltrim(text);
      //add tweet in appropriate user's tweets set with proper timestamp and text
      _users[tweeter]->addTweet(new Tweet(_users[tweeter], timestamp, text));
    }

    //return false if parsing successful
    return false;

}



void TwitEng::addTweet(const string& username, const DateTime& time, const string& text)
{
  //adds tweet to appropriate user's tweets set with appropriate information
  _users[username]->addTweet(new Tweet(_users[username], time, text));
}

//private helper function that I created to populate hashtag_map
void TwitEng::hashTags()
{
  
  set<string> hashtags;
  map<string, User*>::iterator it;
  //iterate through each user in system
  for (it = _users.begin(); it != _users.end(); ++it)
  {
    list<Tweet*> temp_tweetlist;
    //store their list of tweets
    temp_tweetlist = (it->second)->tweets();
    list<Tweet*>::iterator it2;
    //iterate through their tweets
    for (it2 = temp_tweetlist.begin(); it2 != temp_tweetlist.end(); ++it2)
    {
      set<string> hashtags_temp;
      //store the hashtags used in their tweets
      hashtags_temp = (*it2)->hashTags();
      set<string>::iterator it3;
      //iterate through set of hashtags and store them
      for (it3 = hashtags_temp.begin(); it3 != hashtags_temp.end(); ++it3)
      {
        hashtags.insert(*it3);
      }
    }

  }

  set<string>::iterator it4;
  //iterate through all the hashtags
  for (it4 = hashtags.begin(); it4 != hashtags.end(); ++it4)
  {
    //cout << *it4 << endl;
    set<Tweet*> temp_tweet_set;
    //store hashtag as key with an empy set of tweet pointers as value
    hashtag_map.insert(make_pair(*it4, temp_tweet_set));
    map<string, User*>::iterator it5;
    //iterate through the users
    for (it5 = _users.begin(); it5 != _users.end(); ++it5)
    {
      list<Tweet*> temp_tweetlist;
      //store the list of their tweets
      temp_tweetlist = (it5->second)->tweets();
      list<Tweet*>::iterator it6;
      //iterate through list of their tweets
      for (it6 = temp_tweetlist.begin(); it6 != temp_tweetlist.end(); ++it6)
      {
        set<string> hashtags_temp;
        //store the set of hashtags used in the current tweet
        hashtags_temp = (*it6)->hashTags();
        //if the hashtag is used in the tweet, insert the tweet in the set of tweet pointers
        //that correlate with the hashtag in hashtag_map
        if (hashtags_temp.find(*it4) != hashtags_temp.end())
        {
          hashtag_map[*it4].insert(*it6);
        }
        
      }
    }
  }

}

//private helper function for AND search
set<Tweet*> TwitEng::set_intersection(const set<Tweet*>& set1, const set<Tweet*>& set2)
{
  set<Tweet*> intersection;
  set<Tweet*>::iterator it;
  //iterate through set2
  for (it = set2.begin(); it != set2.end(); ++it)
  {
    //if tweet from set2 is found in set1, add to intersection set
    if (set1.find(*it) != set1.end())
    {
      intersection.insert(*it);
    }
  }

  return intersection;
}

set<Tweet*> TwitEng::set_union(const set<Tweet*>& set1, const set<Tweet*>& set2)
{
  set<Tweet*> union_set;
  //copy set 1 into union_set
  union_set = set1;
  set<Tweet*>::iterator it;
  //iterate through set 2
  for (it = set2.begin(); it != set2.end(); ++it)
  {
    //if tweet isn't already in set 1, add it to union_set
    if (set1.find(*it) == set1.end())
    {
      union_set.insert(*it);
    }
  }

  return union_set;
}


vector<Tweet*> TwitEng::search(vector<string>& terms, int strategy)
{
  //call private helper function hashtags to populate map of hashtags to tweets with hashtag
  hashTags();
  vector<Tweet*> hits;
  set<Tweet*> found;
  vector<string>::iterator it = terms.begin();
  //check to make sure terms were passed in
  if (!terms.empty())
  {
    convLower(*it);
    found = hashtag_map[*it];
  }
  //iterate through search terms
  for (; it != terms.end(); ++it)
  {
    //AND search
    if (strategy == 0)
    {
      //convlower to allow for case insensitivity 
      convLower(*it);
      //set the found set to intersection between previous found set and tweets with next hashtag
      found = set_intersection(found, hashtag_map[*it]);
    }

    else
    {
      //same thing but with set union
      convLower(*it);
      found = set_union(found, hashtag_map[*it]);
    }
  }

  set<Tweet*>::iterator it2;
  //iterate through the found set and populate vector that will be returned
  for (it2 = found.begin(); it2 != found.end(); ++it2)
  {
    hits.push_back(*it2);
  }

  return hits;
}


bool TwitEng::validUser(const string& name) const
{

  //if the user exists, return true
  if (_users.find(name) != _users.end())
  {
    return true;
  }

  return false;
}

void TwitEng::dumpFeeds()
{
  map<string, User*>::iterator it;
  //iterate through the users in the system
  for (it = _users.begin(); it != _users.end(); ++it)
  {
    //use their name to name their feed file
    string filename = it->first + ".feed";
    ofstream ofile(filename);
    //print out their name at top of file
    ofile << it->first << endl;
    //get their feed which is vector of their tweets
    vector<Tweet*> feed = (it->second)->getFeed();
    vector<Tweet*>::iterator it2;
    //iterate through feed vector
    for (it2 = feed.begin(); it2 != feed.end(); ++it2)
    {
      //print it out with overloaded insertion operator
      ofile << **it2 << endl;
    }
    ofile.close();
  }
}


