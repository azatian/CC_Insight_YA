#include "Tweet.h"

using namespace std;

Tweet::Tweet()
{

}
Tweet::Tweet(int _order, int _ts, vector<string> _the_hashtags)
{
	order = _order;
	ts = _ts;
	//nodes = 0;

	//Probably need to change, shallow copy or deep copy?
	//the_hashtags = _the_hashtags;
	for(unsigned int i = 0; i < _the_hashtags.size(); i++)
	{
		the_hashtags.push_back(_the_hashtags[i]);
		//nodes++;
	}

}

Tweet::~Tweet()
{

}

//int Tweet::get_nodes() const
//{
//	return nodes;
//}

int Tweet::get_order() const
{
	return order;
}

int Tweet::get_ts() const
{
	return ts;
}

int Tweet::get_ts_sec() const
{
	int seconds = ts % 100;
	return seconds;
}

int Tweet::get_ts_min() const
{
	int min = ( ts % 10000 ) / 100;
	return min;
}

int Tweet::get_ts_hour() const
{
	int hour = ( ts % 1000000 ) / 10000;
	return hour;
}

vector<string> Tweet::get_hashtags() const
{
	return the_hashtags;
}

bool Tweet::operator<(const Tweet& t) const
{
	return (ts < t.get_ts());
}