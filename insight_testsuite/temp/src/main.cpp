#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <map>
#include <sstream>
#include <vector>
#include <list>
#include "Tweet.h"
#include "Graph.h"

using namespace std; 

//Global Variables
//Raw Version of Tweets before information extraction
map<int, vector<string> > raw_tweets;
//Collection of Tweets
vector<Tweet> collection_of_tweets;
//Final tally of all hashtags
int nodes = 0;
//Key for Hashtags
map<string, int> _key;

void RetrieveInput(char* argv2)
{
	ifstream myfile;
	//"../insight_testsuite/tests/test-2-tweets-all-distinct/tweet_input/tweets.txt"
	myfile.open(argv2);

	if(!myfile.is_open())
	{
		cout << "File not found: " << "Tweet Inputs" << endl;
		return;
	}

	string line;
	string comparator_one = "{created_at:";
	string comparator_two = "{hashtags:";

	bool extractor_switch = 0;
	bool _switch = 0; 
	int counter = 0; 
	
	while(getline(myfile, line))
	{
		counter++;

		string extractor_one;
		//string extractor_two;
		for(unsigned int i = 0; i < line.length(); i++)
		{
			
			if(extractor_switch == 0)
			{
			_switch = 0;
			char c = line[i];
			if(c != '"')
			{
				extractor_one.push_back(c);

				if(extractor_one.compare(comparator_one) == 0)
				{

					while(_switch == 0)
					{
						i++;
						c = line[i];
						if(c != ',')
						{

							extractor_one.push_back(c);


						}
						else
						{
							_switch = 1;
						}
					}
					
					vector<string> v;
					v.push_back(extractor_one);

					//Checker
					//cout << extractor_one << endl;

					raw_tweets.insert(make_pair(counter, v));
					//counter++; //need to change later
					extractor_switch = 1;
				}
			}
			}
			else
			{
				bool second_switch = 0;
				string extractor_two;

				char d = line[i];
				if(d == '{')
				{
					extractor_two.push_back(d);
					int next = 0;
					while(next < 9)
					{
						i++;
						d = line[i];
						if( d != '"')
						{
							extractor_two.push_back(d);
							next++;
						}

					}

					if(extractor_two.compare(comparator_two) == 0)
					{
						//cout << "Check" << endl;
						while(second_switch == 0)
						{
							i++;
							d = line[i];
							if(d != '"')
							{
								extractor_two.push_back(d);



							}
							else
							{
								char d_one = line[i+1];
								char d_two = line[i+2];
								char d_three = line[i+3];
								char d_four = line[i+4];
								char d_five = line[i+5];
								if(d_one == 'u' && d_two == 'r' && d_three == 'l' && d_four == 's' && d_five == '"')
								{
									//extractor_two.push_back(d);
									second_switch = 1;
								}
								else
								{
									extractor_two.push_back(d);
								}
								

							}
						}

						raw_tweets[counter].push_back(extractor_two);
						//cout << extractor_two << endl;
						extractor_switch = 0;

					}



				}


				//Make sure to increment counter here, this is where I will add the hashtags

			}



		}

		

	}

}

void Condensor()
{
	//Iterate through the map and double check
	map<int, vector<string> >::iterator it; 
	int _int_timestamp;
	int order_counter = 0;

	for(it = raw_tweets.begin(); it != raw_tweets.end(); ++it)
	{
		//cout << "Key is: " << it->first << endl;
		//cout << "Pair Information Timestamp: " << (it->second)[0] << endl;
		//cout << "Pair Information Hashtags: " << (it->second)[1] << endl;
		string temp_timestamp = (it->second)[0];
		//string temp_hashtags = (it->second)[1];

		string final_timestamp;

		//vector<string> final_hashtags;

		int checker = 0;

		for(unsigned int i = 0; i < temp_timestamp.length(); i++)
		{
			//int checker = 0;
			char c = temp_timestamp[i];
			if(c == ':')
			{
				checker++;
			}

			if(checker == 2)
			{
				//Timestamp Individual Pieces 
				char c_0 = temp_timestamp[i-2];
				char c_1 = temp_timestamp[i-1];
				char c_2 = temp_timestamp[i+1];
				char c_3 = temp_timestamp[i+2];
				char c_4 = temp_timestamp[i+4];
				char c_5 = temp_timestamp[i+5];

				final_timestamp.push_back(c_0);
				final_timestamp.push_back(c_1);
				final_timestamp.push_back(c_2);
				final_timestamp.push_back(c_3);
				final_timestamp.push_back(c_4);
				final_timestamp.push_back(c_5);

				//cout << final_timestamp << endl;
				//break;

				//Let's change final_timestamp to an integer

				
				_int_timestamp = atoi(final_timestamp.c_str());

				//cout << "Int Version: " << _int_timestamp << endl;


				break;
			}


		}

		string temp_hashtags = (it->second)[1];

		list<string> final_hashtags;
		vector<string> condensed_final_hashtags;

		istringstream ss(temp_hashtags);
		string token;

		while(getline(ss, token, '"'))
		{
			//cout << token << endl;
			final_hashtags.push_back(token);

		}

		//Probably will have to use an if statement here if there exists a condition where hashtags are empty
		final_hashtags.pop_front();
		final_hashtags.pop_front();
		final_hashtags.pop_front();

		//int total_elements = final_hashtags.size();

		list<string>::const_iterator _it;

		int list_counter = 1; 

		for(_it = final_hashtags.begin(); _it != final_hashtags.end(); ++_it)
		{
			int mod_answer = list_counter % 6;

			if(mod_answer == 1)
			{

				condensed_final_hashtags.push_back(*_it);
				//nodes++;

				//I will add to the map that maps string to int to identify the key of the hashtag
				//I have to make a conditional to check to see if the ndde is in the map
				if(_key.find(*_it) == _key.end())
				{
					_key.insert(make_pair(*_it, nodes));
					nodes++;
				}

			}

			list_counter++;
		}

		//Checking

		//for(unsigned int i = 0; i < condensed_final_hashtags.size(); i++)
		//{
			//cout << condensed_final_hashtags[i] << endl;
		//}



		//Create Classes For Each Tweet
		//Store them in some data structure
		order_counter++;

		Tweet my_tweet(order_counter, _int_timestamp, condensed_final_hashtags);
		collection_of_tweets.push_back(my_tweet);

		//Printing stuff to make sure
		//Iterate through the vector of Tweets

		//cout << collection_of_tweets.size() << endl;

		



	}
}

int main(int argc, char* argv[])
{

	if(argc != 3)
	{
		cout << "Please include the directory to take inputs and directory to place outputs" << endl;
		return -1;
	}



	
	RetrieveInput(argv[1]);
	Condensor();

	ofstream myfiley;
	//"../insight_testsuite/tests/test-2-tweets-all-distinct/tweet_output/output.txt"
	myfiley.open(argv[2]);


	//Checking to see if number of nodes match up 
	//cout << "Number of Nodes: " << nodes << endl;

	Graph Master_Graph(nodes);

	int max_ts = collection_of_tweets[0].get_ts();
	int max_hour = collection_of_tweets[0].get_ts_hour();
	int max_min = collection_of_tweets[0].get_ts_min();
	int max_sec = collection_of_tweets[0].get_ts_sec(); 

	//Printing Check
	/*for(unsigned int i = 0; i < collection_of_tweets.size(); i++)
	{
		cout << "Order: " << collection_of_tweets[i].get_order() << endl;
		cout << "TimeStamp: " << collection_of_tweets[i].get_ts() << endl;

		cout << "HASHTAGS" << endl;

		for(unsigned int j = 0; j < collection_of_tweets[i].get_hashtags().size(); j++)
		{
			cout << j << endl;
			cout << collection_of_tweets[i].get_hashtags()[j] << endl;
		}

	}
	*/

	list<Tweet> window;

	for(unsigned int i = 0; i < collection_of_tweets.size(); i++)
	{
		vector<Tweet> to_delete;
		//Need to also take into consideration of timestamps!!
		int ex_ts = collection_of_tweets[i].get_ts();
		int ex_hour = collection_of_tweets[i].get_ts_hour();
		int ex_min = collection_of_tweets[i].get_ts_min();
		int ex_sec = collection_of_tweets[i].get_ts_sec();

		//Exact same timestamp
		if(ex_ts == max_ts)
		{
			//Add the Tweet you are comparing to 60second window, no change in max
			window.push_back(collection_of_tweets[i]);

		}
		else
		{
			if(ex_hour == max_hour)
			{

				if(ex_min == max_min)
				{
					if(ex_sec > max_sec)
					{
						//Change in max
						max_ts = ex_ts;
						max_hour = ex_hour;
						max_min = ex_min;
						max_sec = ex_sec;
						//Add to window data structure, pop out tweets that fall out of range
						window.push_back(collection_of_tweets[i]);
						window.sort();

						list<Tweet>::const_iterator itx;
						int counter = 0;
						for(itx = window.begin(); itx != window.end(); ++itx)
						{
							int it_ts = (*itx).get_ts();
							int it_hour = (*itx).get_ts_hour();
							int it_min = (*itx).get_ts_min();

							if(it_hour == max_hour)
							{
								if(it_min == max_min)
								{
									break;
								}
								else if((it_min - max_min) == -1)
								{
									if((max_ts - it_ts) <= 100)
									{
										break;
									}
									else
									{
										to_delete.push_back(*itx);
										counter++;
										//window.pop_front();
									}
									
								}
								else
								{
									to_delete.push_back(*itx);
									counter++;
									//window.pop_front();

								}

							}
							else if(((it_hour - max_hour) == -1) && ((it_min - max_min) == 59) && ((max_ts - it_ts) <= 4100))
							{
								break;
							}
							else
							{
								to_delete.push_back(*itx);
								counter++;
								//window.pop_front();
							}

						}

						while(counter > 0)
						{
							window.pop_front();
							counter--;
						}




					}
					else
					{
						//Add to window data structure
						window.push_back(collection_of_tweets[i]);
					}
				}
				else
				{
					if((ex_min - max_min) == 1)
					{
						if((ex_ts - max_ts) <= 100)
						{
							//cout << "Check" << endl;
							//In the window, change in max
							max_ts = ex_ts;
							max_hour = ex_hour;
							max_min = ex_min;
							max_sec = ex_sec;
							//Add to window data structure, pop out tweets that fall out of range

							window.push_back(collection_of_tweets[i]);
							window.sort();

							//cout << "Check" << endl;

							list<Tweet>::const_iterator itx;
							int counter = 0;
							for(itx = window.begin(); itx != window.end(); ++itx)
							{

								int it_ts = (*itx).get_ts();
								//cout << it_ts << endl;
								int it_hour = (*itx).get_ts_hour();
								int it_min = (*itx).get_ts_min();

								if(it_hour == max_hour)
								{
									if(it_min == max_min)
									{
										break;
									}
									else if((it_min - max_min) == -1)
									{
										if((max_ts - it_ts) <= 100)
										{
											break;
										}
										else
										{
											//cout << "Check1" << endl;
											to_delete.push_back((*itx));
											counter++;
											//window.pop_front();
											//cout << "Check2" << endl;
										}
									
									}
									else
									{
										to_delete.push_back((*itx));
										//window.pop_front();
										counter++;

									}

								}
								else if(((it_hour - max_hour) == -1) && ((it_min - max_min) == 59) && ((max_ts - it_ts) <= 4100))
								{
									break;
								}
								else
								{
									to_delete.push_back((*itx));
									counter++;
								}

							}

							while(counter > 0)
							{
								//cout << "Check" << endl;
								window.pop_front();
								counter--;
							}


						}
					}
					else if((ex_min - max_min == -1))
					{
						if((max_ts - ex_ts <= 100))
						{
							//Add to window data structure
							window.push_back(collection_of_tweets[i]);
						}
					}
				}
			}
			else if(((ex_hour - max_hour) == 1) && ((ex_min - max_min) == -41) && ((ex_ts - max_ts) <= 4100))
			{
				//In range
				max_ts = ex_ts;
				max_hour = ex_hour;
				max_min = ex_min;
				max_sec = ex_sec;
				//Add to window data structure, pop out tweets that fall out of range

				window.push_back(collection_of_tweets[i]);
				window.sort();


				list<Tweet>::const_iterator itx;
				int counter = 0;
				for(itx = window.begin(); itx != window.end(); ++itx)
				{
					int it_ts = (*itx).get_ts();
					int it_hour = (*itx).get_ts_hour();
					int it_min = (*itx).get_ts_min();

					if(it_hour == max_hour)
					{
						if(it_min == max_min)
						{
							break;
						}
						else if((it_min - max_min) == -1)
						{
							if((max_ts - it_ts) <= 100)
							{
								break;
							}
							else
							{
								to_delete.push_back(*itx);
								//window.pop_front();
								counter++;
							}
									
						}
						else
						{
							to_delete.push_back(*itx);
							//window.pop_front();
							counter++;

						}

					}
					else if(((it_hour - max_hour) == -1) && ((it_min - max_min) == 59) && ((max_ts - it_ts) <= 4100))
					{
						break;
					}
					else
					{
						to_delete.push_back(*itx);
						//window.pop_front();
						counter++;
					}

				}

				while(counter > 0)
				{
					window.pop_front();
					counter--;
				}

			}
			else if(((ex_hour - max_hour) == -1) && ((ex_min - max_min) == 59) && ((max_ts - ex_ts) <= 4100))
			{
				//Add to window data structure
				window.push_back(collection_of_tweets[i]);
			}
		}


		//Continue with creating graph here 
		//Transfer list elements
		vector<Tweet> to_add;

		list<Tweet>::const_iterator itz;
		for(itz = window.begin(); itz != window.end(); ++itz)
		{
			to_add.push_back(*itz);
		}


		

		//Deleting Edges
		for(unsigned int i = 0; i < to_delete.size(); i++)
		{
			vector<int> index_holder;

			for(unsigned int j = 0; j < to_delete[i].get_hashtags().size(); j++)
			{
				index_holder.push_back(_key[to_delete[i].get_hashtags()[j]]);
			}

			int pair_first;
			int pair_second;

			//cout << index_holder.size() << endl;

			if(index_holder.size() > 1)
			{
				for(unsigned int x = 0; x < index_holder.size(); x++)
				{
					pair_first = index_holder[x];

					for(unsigned int y = x+1; y < index_holder.size(); y++)
					{
						pair_second = index_holder[y];
						//cout << "First Pair: " << pair_first << endl;
						//cout << "Second Pair: " << pair_second << endl;
						Master_Graph.removeEdge(pair_first, pair_second);
					}
				}

			}


		}


		//Adding Edges

		for(unsigned int i = 0; i < to_add.size(); i++)
		{
			vector<int> index_holder;

			for(unsigned int j = 0; j < to_add[i].get_hashtags().size(); j++)
			{
				index_holder.push_back(_key[to_add[i].get_hashtags()[j]]);
			}

			int pair_first;
			int pair_second;

			if(index_holder.size() > 1)
			{
				for(unsigned int x = 0; x < index_holder.size(); x++)
				{
					pair_first = index_holder[x];

					for(unsigned int y = x+1; y < index_holder.size(); y++)
					{
						pair_second = index_holder[y];
						//cout << "First Pair: " << pair_first << endl;
						//cout << "Second Pair: " << pair_second << endl;
						Master_Graph.addEdge(pair_first, pair_second);
					}
				}

			}

		}

		//After every tweet we will be printing out the average degree of the graph 

		myfiley << fixed << setprecision(2) << Master_Graph.findavgdegree() << endl;

		

		


		
	}




	

	


	return 0;
}