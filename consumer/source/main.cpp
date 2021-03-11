#include <consumidor.h>
#include <iostream>
#include <cppkafka/cppkafka.h>
#include "cppkafka/configuration.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <functional>
using namespace std;
using cppkafka::Consumer;
using cppkafka::Configuration;
using cppkafka::Message;
using cppkafka::TopicPartitionList;


int main(int argc, char** argv)
{

  // Create a configuration and set the group.id and broker list fields
  Configuration config = {
   { "metadata.broker.list", "kafka-server1:9092" },
   { "group.id", "foo" }
 };

  Consumidor c(config);
  c.consume();


} // end of main
