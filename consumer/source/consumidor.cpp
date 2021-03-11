
#include <consumidor.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <cstring>
#include <chrono>
#include <string>
#include <json.hpp>

#define NAMOSTRAS 1000

//colocar número de pacotes -1
#define BATCHSIZE 49

using namespace std;
//using namespace AmqpClient;
using json = nlohmann::json;

Consumidor::Consumidor(cppkafka::Configuration config)
{

   this->consumer= new Consumer(config);

}

void Consumidor::consume(){

  // Set the assignment callback
   this->consumer->set_assignment_callback([&](TopicPartitionList& topic_partitions) {
      // Here you could fetch offsets and do something, altering the offsets on the
      // topic_partitions vector if needed
      cout << "Got assigned " << topic_partitions.size() << " partitions!" << endl;
  });

   // Set the revocation callback
  this->consumer->set_revocation_callback([&](const TopicPartitionList& topic_partitions) {
     cout << topic_partitions.size() << " partitions revoked!" << endl;
  });



  // Subscribe
  this->consumer->subscribe({ "my_topic" });

  ofstream myfile;

  int h=0;
  string amostras[NAMOSTRAS];
  int temposcamada2[NAMOSTRAS];
  int consumertimestampvector[NAMOSTRAS];
  int times1layer[NAMOSTRAS];

  do {
      // Poll. This will optionally return a message. It's necessary to check if it's a valid
      // one before using it
    Message msg = this->consumer->poll();
    consumertimestampvector[h]= std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if (msg) {
        if (!msg.get_error()) {
            // It's an actual message. Get the payload and print it to stdout

             amostras[h]=msg.get_payload();
             h++;}

         else if (!msg.is_eof()) {
            // Is it an error notification, handle it.
           // This is explicitly skipping EOF notifications as they're not actually errors,
            // but that's how rdkafka provides them
          }
      }
   }
   while(h<NAMOSTRAS);


   for(int z=0;z<NAMOSTRAS;z++){

             this->messageBody= json::parse(amostras[z]);

             from_json(this->messageBody,this->data);
             long diff1= (consumertimestampvector[z] - data.timedataSenderlast);

             long diff2= (data.timedataSenderlast-data.arrivetimestampfirst);

             //times1layer[h]= data.time1layer;
             times1layer[z]= diff2;
             temposcamada2[z]=diff1;
       }



   myfile.open("cpukafka.txt");
   for(int p=0;p<NAMOSTRAS;p++){
         myfile<<temposcamada2[p]<<" "<<times1layer[p]<<endl;}


   cout<<endl<<"FIM"<<endl;
   myfile.close();}



//pegar informações json e transformar para a struct
void Consumidor::from_json(const json& j, SVData& p) {
      j[0].at("arrivetimestamp").get_to(p.arrivetimestampfirst);
      j[BATCHSIZE].at("arrivetimestamp").get_to(p.arrivetimestamplast);

      //j[2].at("time1layer").get_to(p.time1layer);

      j[0].at("timedataSender").get_to(p.timedataSenderfirst);
      j[BATCHSIZE].at("timedataSender").get_to(p.timedataSenderlast);

    }
