#ifndef CONSUMIDOR_H
#define CONSUMIDOR_H

#include <string>
#include <vector>
#include <map>
#include <thread>
#include <datatypes.h>
#include <json.hpp>
#include <cppkafka/cppkafka.h>

using namespace cppkafka;
using namespace std;
using json = nlohmann::json;

class Consumidor{

  protected:

    string consumer_tag;
    long consumertimestamp;
    json messageBody;
    SVData data;
    string it;
    cppkafka::Consumer* consumer;

  public:
    Consumidor(cppkafka::Configuration config);
    //void dataConsumer();
    void from_json(const json& j, SVData& p);
    void consume();
    //void to_json(json& j, const SVData& p);

};

#endif
