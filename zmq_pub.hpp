#include <zmq.hpp>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <iterator>
#include <Eigen/Dense>
#include <string>

zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_PUB);
std::ostringstream stream;

void init_publisher() {
    socket.connect("tcp://127.0.0.1:98765");
}

template <typename T>
void send_message(T message)
{
    std::string pub_msg;
    std::copy(message.begin(), message.end(), std::ostream_iterator<double>(stream,", "));
    pub_msg = stream.str();
    std::cout<<"pub_msg:"<<pub_msg<<"\n";
    zmq::message_t message_to_send(pub_msg.size());
    memcpy(message_to_send.data(), pub_msg.c_str(), strlen(pub_msg.c_str()));
    socket.send(message_to_send, zmq::send_flags::dontwait);
}
