#!/usr/bin/env bash

# example of the run script for running the average_degree calculation

# I'll execute my programs, with the input directory tweet_input and output the files in the directory tweet_output
#python ./src/average_degree.py ./tweet_input/tweets.txt ./tweet_output/output.txt

g++ -g -Wall -c ./src/Tweet.cpp -o ./src/Tweet.o

g++ -g -Wall ./src/main.cpp ./src/Tweet.o -o main

./main ./tweet_input/tweets.txt ./tweet_output/output.txt



