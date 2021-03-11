#include <sniffer.h>
#include <iostream>
#include <stdio.h>
#include <cppkafka/cppkafka.h>

using namespace std;
using namespace cppkafka;

int main(int argc, char** argv)
{
// Create the config
  Configuration config = {
      { "metadata.broker.list", "kafka-server1:9092" }
  };

  Sniffer s("SVRecording.pcap",true,config);
  s.start();
} // end of main
