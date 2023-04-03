#include "mbed.h"

CircularBuffer<CANMessage, 32> queue2;   // canメッセージ置き場

DigitalOut led1(LED1);
RawCAN can1(PA_11, PA_12, 1000000);
RawCAN can2( PB_5,  PB_6, 1000000);

char counter[8] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};
char RcvData[8];

CANMessage msg(0x456, counter, 8, CANData, CANStandard);

void canListen() {  // ISR
    // CANMessage msg;

    if (can1.read(msg)) {
        queue2.push(msg);
    }
}

void send() {
    if(counter[0] % 0x10 == 0) {
        msg.id = 0x456;
        for(uint8_t i=0; i<8; i++) {
            msg.data[i] = counter[i]++;
        }
    } else {
        msg.id = 0x500;
        for(uint8_t i=0; i<8; i++) {
            msg.data[i] = counter[i]++;
        }
    }
    if(can1.write(msg)) {
        led1 = !led1;
        printf("\033[1;1HCAN1 TRANSID: 0x%x", msg.id);
        printf("\033[2;1HCAN1 DATA[0]: 0x%x", msg.data[0]);
        printf("\033[3;1HCAN1 DATA[1]: 0x%x", msg.data[1]);
        printf("\033[4;1HCAN1 DATA[2]: 0x%x", msg.data[2]);
        printf("\033[5;1HCAN1 DATA[3]: 0x%x", msg.data[3]);
        printf("\033[6;1HCAN1 DATA[4]: 0x%x", msg.data[4]);
        printf("\033[7;1HCAN1 DATA[5]: 0x%x", msg.data[5]);
        printf("\033[8;1HCAN1 DATA[6]: 0x%x", msg.data[6]);
        printf("\033[9;1HCAN1 DATA[7]: 0x%x", msg.data[7]);
    }
    if(counter[0] >= 0xF0)
        printf("\033[2J");if(counter[0] % 0x10 == 0) {
        msg.id = 0x456;
        for(uint8_t i=0; i<8; i++) {
            msg.data[i] = counter[i]++;
        }
    } else {
        msg.id = 0x500;
        for(uint8_t i=0; i<8; i++) {
            msg.data[i] = counter[i]++;
        }
    }
    if(can1.write(msg)) {
        led1 = !led1;
        printf("\033[1;1HCAN1 TRANSID: 0x%x", msg.id);
        printf("\033[2;1HCAN1 DATA[0]: 0x%x", msg.data[0]);
        printf("\033[3;1HCAN1 DATA[1]: 0x%x", msg.data[1]);
        printf("\033[4;1HCAN1 DATA[2]: 0x%x", msg.data[2]);
        printf("\033[5;1HCAN1 DATA[3]: 0x%x", msg.data[3]);
        printf("\033[6;1HCAN1 DATA[4]: 0x%x", msg.data[4]);
        printf("\033[7;1HCAN1 DATA[5]: 0x%x", msg.data[5]);
        printf("\033[8;1HCAN1 DATA[6]: 0x%x", msg.data[6]);
        printf("\033[9;1HCAN1 DATA[7]: 0x%x", msg.data[7]);
    }
    if(counter[0] >= 0xF0)
        printf("\033[2J");
}

int main() {
    EventQueue *queue = mbed_event_queue();
    // t.start(callback(&queue, &EventQueue::dispatch_forever)); 
    queue->call_every(1s, send); 
    
    CANMessage msg;
    
    can2.attach(&canListen, CAN::RxIrq);

    while (1) {
        while (!queue2.empty()) {
            CANMessage msg;
            queue2.pop(msg);
            led1 = !led1;
            printf("\033[1;25HCAN RCVID: 0x%x", msg.id);
            for(uint8_t i=0; i<8; i++) {
                RcvData[i] = msg.data[i];
            }
            printf("\033[2;25HCAN DATA[0]: 0x%x", RcvData[0]);        
            printf("\033[3;25HCAN DATA[0]: 0x%x", RcvData[1]);
            printf("\033[4;25HCAN DATA[0]: 0x%x", RcvData[2]);
            printf("\033[5;25HCAN DATA[0]: 0x%x", RcvData[3]);
            printf("\033[6;25HCAN DATA[0]: 0x%x", RcvData[4]);
            printf("\033[7;25HCAN DATA[0]: 0x%x", RcvData[5]);
            printf("\033[8;25HCAN DATA[0]: 0x%x", RcvData[6]);
            printf("\033[9;25HCAN DATA[0]: 0x%x", RcvData[7]);
            // led1 = !led1;
        }
    }
}
