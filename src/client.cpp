//
// Created by zhihui on 12/31/19.
//

#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcchat.grpc.pb.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using grpcchat::GrpcChat;
using grpcchat::Msg;

class ChatClient{
public:
    ChatClient(std::shared_ptr<Channel> channel):stub(GrpcChat::NewStub(channel)){}

    void yell(const std::string &input){
        ClientContext context;
        Msg request, response;
        request.set_content(input);
        Status status = stub->yellEcho(&context, request, &response);
        std::cout << "Server reply: "<< response.content() << std::endl;
    }

    void yellEchoing(const std::string &input){
        ClientContext context;
        Msg request, response;
        request.set_content(input);
        std::unique_ptr<ClientReader<Msg>> reader(stub->yellEchoing(&context,request));
        while(reader->Read(&response)){
            std::cout << "Server reply: " << response.content() <<std::endl;
        }
        Status status = reader->Finish();
        if (status.ok()) {
            std::cout << "yellEchoing rpc succeeded." << std::endl;
        } else {
            std::cout << "yellEchoing rpc failed." << std::endl;
        }
    }

    void yellingEcho()

private:
    std::unique_ptr<GrpcChat::Stub> stub;
};

int main(int argc, char *argv[]){

    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " host_address:port" << std::endl;
        return -1;
    }

    int choice = 0;

    ChatClient client(grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials()));
    std::cout << "Select mode: 1)1-1 2)1-many 3)many-1 4)many-many" <<std::endl;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    char buffer[1024];
    switch(choice){
        case 1:
            while(true){
                std::cout <<"Enter message: "<<std::endl;
                std::cin.getline(buffer,sizeof(buffer));
                client.yell(buffer);
            }
        case 2:
            while(true){
                std::cout <<"Enter message: "<<std::endl;
                std::cin.getline(buffer,sizeof(buffer));
                client.yellEchoing(buffer);
            }
    }


}