// #include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
using namespace std;

const int header_length = 12;

int insert_header(unsigned char *packet, /* int *length, */ unsigned char *full_packet/* , int *full_length */)
{
    if (packet == nullptr)
    {
        return -1;
    }

    int packet_length = sizeof(packet)/sizeof(unsigned char);
    unsigned char header[header_length] = {0x80, 0x52, 0x66, 0x61, 0x77, 0x52};
    int full_packet_length = sizeof(full_packet)/sizeof(unsigned char);

    memcpy(full_packet, header, header_length*sizeof(unsigned char));
    memcpy(&full_packet[header_length], packet, (packet_length)*sizeof(unsigned char));
    
    return 0;
}

int main() {
    // To run the program, let only one of the following tests (1, 2, 3) uncommented
    // test packet 1:
    unsigned char packet[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    
    // test packet 2:
    // unsigned char packet[]={};
    
    // test packet 3:
    // unsigned char *packet;
    
    int packet_length = sizeof(packet) / sizeof(unsigned char);
    unsigned char full_packet[packet_length + header_length];


    int res = insert_header(packet, full_packet);
    if (res < 0) {
        printf("failed adding header to an unallocated packet");
        return res;
    }

    printf("original packet: ");
    for (int i = 0; i<packet_length; i++)
        printf("%d ", packet[i]);
    printf(" | length: %d\n", packet_length);

    int full_packet_length = sizeof(full_packet) / sizeof(unsigned char);

    printf("full packet: ");
    for (int i = 0; i<full_packet_length; i++)
        printf("%d ", full_packet[i]);
    printf(" | length: %d\n", full_packet_length);

    return res;
}