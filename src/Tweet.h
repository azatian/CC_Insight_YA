#ifndef TWEET_H
#define TWEET_H

#include <string>
#include <vector>

class Tweet
{
public:
	Tweet();
	Tweet(int, int, std::vector<std::string>);
	~Tweet();

	//int get_nodes() const;
	int get_ts() const;
	int get_order() const;
	int get_ts_sec() const;
	int get_ts_min() const;
	int get_ts_hour() const;
	std::vector<std::string> get_hashtags() const;
	bool operator<(const Tweet&) const;


private:

	int order;
	int ts;
	//int nodes;
	std::vector<std::string> the_hashtags;






};


#endif