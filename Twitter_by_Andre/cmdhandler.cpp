#include "cmdhandler.h"
#include "util.h"
#include <vector>
#include "tweet.h"
#include "datetime.h"
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
  : Handler(next)
{

}

//if the cmd is "AND", returns true
bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{
	vector<string> terms;
	string term;
	//pull in search terms with instr
	while(instr >> term)
	{
		terms.push_back(term);
	}
	//call search with the terms and with AND strategy and store in vector
	vector<Tweet*> results = eng->search(terms, 0);
	displayHits(results);
	return HANDLER_OK;
}

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{

}

//if the cmd is "OR", returns true
bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";
}


Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	vector<string> terms;
	string term;
	//pull in search terms with instr
	while(instr >> term)
	{
		terms.push_back(term);
	}
	//call search with the terms and OR strategy
	vector<Tweet*> results = eng->search(terms, 1);
	displayHits(results);
	return HANDLER_OK;
}

TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
  : Handler(next)
{

}

//if cmd is "TWEET", returns true
bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";
}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{
	string username, text;
	DateTime timestamp;
	//pull in username of tweet
	instr >> username;
	//check if username is valid user in system
	if (eng->validUser(username))
	{
		//get the text of the tweet
		getline(instr, text);
		trim(text);
		//use addtweet to enter tweet into system with appropriate information (current time)
		eng->addTweet(username, timestamp, text);
	}
	//if username isn't valid, don't add tweet and return error
	else
	{
		return HANDLER_ERROR;
	}
	return HANDLER_OK;

}



