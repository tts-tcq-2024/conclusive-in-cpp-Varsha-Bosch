#include <gtest/gtest.h>
#include "typewise-alert.h"
#include "typewisealert_sender.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    EXPECT_EQ(inferBreach(12.0, 0.0, 20.0), NORMAL);
    EXPECT_EQ(inferBreach(-1.0, 0.0, 20.0), TOO_LOW);
    EXPECT_EQ(inferBreach(25.0, 0.0, 20.0), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureForPassiveCooling) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 20), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -5), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, SendsAlertToController) {
    testing::internal::CaptureStdout();
    TypewiseAlertSender::sendToController(TOO_LOW);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 1\n");  // Assuming TOO_LOW is represented as 1
}

TEST(TypeWiseAlertTestSuite, SendsAlertToEmail) {
    testing::internal::CaptureStdout();
    TypewiseAlertSender::sendToEmail(TOO_HIGH);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");
}
