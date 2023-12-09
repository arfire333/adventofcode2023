#include <gtest/gtest.h>
#include "2023day07_2.cpp"

TEST(Test2023day07, FiveOfAKind) {
  Hand a("QQQQQ", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::FIVE);
}
TEST(Test2023day07, FourOfAKind) {
  Hand a("QQQQ3", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::FOUR);
}
TEST(Test2023day07, FullHouse) {
  Hand a("QQQ22", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::FULL);
}
TEST(Test2023day07, ThreeOfAKind) {
  Hand a("QQQ23", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::THREE);
}
TEST(Test2023day07, TwoPair) {
  Hand a("AQQ22", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::TWO);
}
TEST(Test2023day07, Pair) {
  Hand a("QQ523", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::ONE);
}
TEST(Test2023day07, High) {
  Hand a("KQ523", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::HIGH);
}
TEST(Test2023day07, WildFiveOfAKind) {
  Hand a("QQJQQ", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::FIVE);
}
TEST(Test2023day07, WildFourOfAKind) {
  Hand a("JJQJ3", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::FOUR);
}
TEST(Test2023day07, WildFullHouse) {
  Hand a("QQJ22", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::FULL);
}
TEST(Test2023day07, WildThreeOfAKind) {
  Hand a("JJQ23", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::THREE);
}
TEST(Test2023day07, WildPair) {
  Hand a("QJ523", 1);
  ASSERT_EQ(a.type(), Hand::HAND_TYPES::ONE);
}