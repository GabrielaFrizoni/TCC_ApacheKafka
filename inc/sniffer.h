#ifndef SNIFFER_H
#define SNIFFER_H

#include <string>
#include <vector>
#include <map>
#include <datatypes.h>
#include <parameters.h>
#include <thread>
#include <cppkafka/cppkafka.h>


using namespace cppkafka;
using namespace std;

class Sniffer{
protected:
  string base_cmd = "tshark ";
  map<string, vector<string>> params;
  string cmd();
  std::thread t;
  bool syncing = true;
  SVData parser(char* cLine);
  void dispatch(SVData);
  bool infiniteloop=false;
  long timeseg;
  long long timeparser;
  long long timedataSender;
  long int message;


  cppkafka::Producer* producer;

public:

  Sniffer(string dst_mac);
  Sniffer(string filepath, bool il, cppkafka::Configuration config);
  void start();
  void method();
  void initTimestamp(int);
  long updateTimestamp(int);
  void dataSender(SVData);
  void createProducerKafka(Configuration config);

};


#endif
