#pragma once
#include "typewise-alert.h"

class TypewiseAlertSender {
public:
    static void sendToController(BreachType breachType);
    static void sendToEmail(BreachType breachType);
};
