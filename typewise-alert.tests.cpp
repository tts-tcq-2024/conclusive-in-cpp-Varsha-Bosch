#include <gtest/gtest.h>
#include "typewise-alert.h"
#include "typewisealert_sender.h"

// Test for inferBreach function
TEST(TypeWiseAlertTestSuite, InferBreach_NormalRange) {
    EXPECT_EQ(inferBreach(25.0, 0.0, 35.0), NORMAL);  
}

TEST(TypeWiseAlertTestSuite, InferBreach_TooLow) {
    EXPECT_EQ(inferBreach(-5.0, 0.0, 35.0), TOO_LOW);  
}

TEST(TypeWiseAlertTestSuite, InferBreach_TooHigh) {
    EXPECT_EQ(inferBreach(45.0, 0.0, 35.0), TOO_HIGH); 
}

// Test for getCoolingTypeLimits function
TEST(TypeWiseAlertTestSuite, GetCoolingLimits_Passive) {
    Limits limits = getCoolingTypeLimits(PASSIVE_COOLING);
    EXPECT_EQ(limits.lowerLimit, 0);
    EXPECT_EQ(limits.upperLimit, 35); 
}

TEST(TypeWiseAlertTestSuite, GetCoolingLimits_HiActive) {
    Limits limits = getCoolingTypeLimits(HI_ACTIVE_COOLING);
    EXPECT_EQ(limits.lowerLimit, 0);
    EXPECT_EQ(limits.upperLimit, 45);  
}

// Test for classifyTemperatureBreach function
TEST(TypeWiseAlertTestSuite, ClassifyBreach_Normal) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 20.0), NORMAL);  
}

TEST(TypeWiseAlertTestSuite, ClassifyBreach_TooHigh) {
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50.0), TOO_HIGH);  
}

// Test for checkAndAlert function with different alert targets
TEST(TypeWiseAlertTestSuite, CheckAndAlert_Controller_High) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 40.0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");  
}

TEST(TypeWiseAlertTestSuite, CheckAndAlert_Email_Low) {
    BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BrandY"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, -10.0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");  
}

// Test for checkAndAlert function with TO_EMAIL and NORMAL condition (no alert should be sent)
TEST(TypeWiseAlertTestSuite, CheckAndAlert_Email_Normal) {
    BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BrandZ"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 20.0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");  
}

// Test for TypewiseAlertSender::sendToController with TOO_LOW breach type
TEST(TypeWiseAlertTestSuite, SendToController_TooLow) {
    testing::internal::CaptureStdout();
    TypewiseAlertSender::sendToController(TOO_LOW);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 1\n");  
}

// Test for TypewiseAlertSender::sendToEmail with TOO_HIGH breach type
TEST(TypeWiseAlertTestSuite, SendToEmail_TooHigh) {
    testing::internal::CaptureStdout();
    TypewiseAlertSender::sendToEmail(TOO_HIGH);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");  
}

// Test for TypewiseAlertSender::sendToEmail with NORMAL breach type (no alert should be sent)
TEST(TypeWiseAlertTestSuite, SendToEmail_Normal) {
    testing::internal::CaptureStdout();
    TypewiseAlertSender::sendToEmail(NORMAL);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");  
}

// Test for TypewiseAlertSender::sendToController
TEST(TypeWiseAlertTestSuite, SendToController_TooHigh) {
    testing::internal::CaptureStdout();
    TypewiseAlertSender::sendToController(TOO_HIGH);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");  
}

// Test for TypewiseAlertSender::sendToEmail
TEST(TypeWiseAlertTestSuite, SendToEmail_TooLow) {
    testing::internal::CaptureStdout();
    TypewiseAlertSender::sendToEmail(TOO_LOW);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");  
}
