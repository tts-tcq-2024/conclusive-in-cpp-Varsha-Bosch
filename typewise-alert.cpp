#include "typewise-alert.h"
#include "typewisealert_sender.h"

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    return (value < lowerLimit) ? TOO_LOW : (value > upperLimit ? TOO_HIGH : NORMAL);
}

Limits getCoolingTypeLimits(CoolingType coolingType) {
    switch (coolingType) {
        case PASSIVE_COOLING:
            return {0, 35};
        case HI_ACTIVE_COOLING:
            return {0, 45};
        case MED_ACTIVE_COOLING:
            return {0, 40};
        default:
            return {0, 0};
    }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    Limits limits = getCoolingTypeLimits(coolingType);
    return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    sendAlert(alertTarget, breachType);
}

void sendAlert(AlertTarget alertTarget, BreachType breachType) {
    switch (alertTarget) {
        case TO_CONTROLLER:
            TypewiseAlertSender::sendToController(breachType);
            break;
        case TO_EMAIL:
            TypewiseAlertSender::sendToEmail(breachType);
            break;
    }
}
