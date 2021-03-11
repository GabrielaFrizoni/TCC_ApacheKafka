FROM gcc:latest

RUN apt update && update-alternatives --install /usr/bin/gfortran gfortran /usr/local/bin/gfortran 999
RUN DEBIAN_FRONTEND=noninteractive apt-get install -yq cmake tshark libssl-dev libboost-all-dev
RUN wget https://github.com/edenhill/librdkafka/archive/master.zip
RUN unzip master.zip && cd librdkafka-master && ./configure --install-deps && make && make install
RUN wget https://github.com/mfontanini/cppkafka/archive/v0.3.1.tar.gz && tar -zxvf v0.3.1.tar.gz
RUN cd cppkafka-0.3.1 && mkdir build && cd build && cmake ..  && cmake --build . --target install && rm -rf cppkafka-0.3.1
RUN wget https://github.com/nlohmann/json/releases/download/v3.6.1/json.hpp
WORKDIR /acquisition_module
COPY ./entrypoint.sh /acquisition_module
RUN chmod +x /acquisition_module/entrypoint.sh
CMD  ./entrypoint.sh
