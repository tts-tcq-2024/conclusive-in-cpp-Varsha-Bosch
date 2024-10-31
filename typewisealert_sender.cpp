#include "typewisealert_sender.h"
#include <stdio.h>

void TypewiseAlertSender::sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void TypewiseAlertSender::sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    switch (breachType) {
        case TOO_LOW:
            printf("To: %s\nHi, the temperature is too low\n", recipient);
            break;
        case TOO_HIGH:
            printf("To: %s\nHi, the temperature is too high\n", recipient);
            break;
        case NORMAL:
            break;
    }
}
