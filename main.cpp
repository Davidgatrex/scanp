#include "clases.h"

using namespace std;

int main(int argc, char **argv){
    if(argc < 2){
        cout << "Usage: scanp <target-ip> [options]" << endl;
        return -1;
    }
    char* ip = argv[1];
    int startP = 0;
    int endP = 300;

    struct sockaddr_in addr;
    struct sockaddr_in target_addr;
    int sock = 0;

    memset(&target_addr, '0', sizeof(target_addr));

    target_addr.sin_family = AF_INET;

    if(inet_pton(AF_INET, ip, &target_addr.sin_addr) <= 0){
        cout << "Error processing binary-form of address" << endl;
        return -2;
    }

    for(int i = startP; i < endP; i++){
        target_addr.sin_port = htons(i);
        if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            cout << "Error creating socket" << endl;
            return -3;
        }

        if(connect(sock, (struct sockaddr*)&target_addr, sizeof(target_addr)) < 0){
            //
            cout << "Port " << i << "closed." << endl;
        }
        else{
            cout << "Port " << i << "open." << endl;
        }
        close(sock);
    }
    return 0;
}