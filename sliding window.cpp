#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WINDOW_SIZE 4
#define MAX_PACKETS 10

typedef struct {
    int seq_num;
    bool acked;
} Packet;

Packet window[MAX_WINDOW_SIZE];
int base = 0, next_seq_num = 0;

void send_packet(int seq_num) {
    printf("Sending packet %d\n", seq_num);
}

void slide_window() {
    while (base < next_seq_num && window[base % MAX_WINDOW_SIZE].acked) {
        printf("Acknowledgment received for packet %d\n", window[base % MAX_WINDOW_SIZE].seq_num);
        base++;
    }
}

void sender() {
    while (next_seq_num < MAX_PACKETS) {
        if (next_seq_num < base + MAX_WINDOW_SIZE) {
            window[next_seq_num % MAX_WINDOW_SIZE].seq_num = next_seq_num;
            window[next_seq_num % MAX_WINDOW_SIZE].acked = false;
            send_packet(next_seq_num);
            next_seq_num++;
        }
        slide_window();
    }
}

int main() {
    sender();
    return 0;
}

