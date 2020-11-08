#include <iostream>
#include "gtest/gtest.h"
#include "main.h"

TEST(Concatination, 0) {
	EXPECT_EQ(MinWordPrefixK("ab.", 'a', 2), INF);
}
TEST(Concatination, 1) {
	EXPECT_EQ(MinWordPrefixK("ab.", 'a', 1), 2);
}
TEST(Concatination, 2) {
	EXPECT_EQ(MinWordPrefixK("bb.", 'b', 2), 2);
}
TEST(Concatination, 3) {
	EXPECT_EQ(MinWordPrefixK("bb.", 'b', 1), INF);
}
TEST(Concatination, 4) {
	EXPECT_EQ(MinWordPrefixK("bbb..", 'b', 3), 3);
}
TEST(Concatination, 5) {
	EXPECT_EQ(MinWordPrefixK("bba..", 'b', 2), 3);
}
TEST(Concatination, 6) {
	EXPECT_EQ(MinWordPrefixK("bab..", 'b', 1), 3);
}
TEST(Concatination, 7) {
	EXPECT_EQ(MinWordPrefixK("bab..b.", 'b', 1), 4);
}
TEST(Concatination, 8) {
	EXPECT_EQ(MinWordPrefixK("bb.ab..b.", 'b', 2), 5);
}

TEST(Plus, 0) {
	EXPECT_EQ(MinWordPrefixK("ab+", 'a', 2), INF);
}
TEST(Plus, 1) {
	EXPECT_EQ(MinWordPrefixK("ab+", 'a', 1), 1);
}
TEST(Plus, 2) {
	EXPECT_EQ(MinWordPrefixK("bb+", 'b', 2), INF);
}
TEST(Plus, 3) {
	EXPECT_EQ(MinWordPrefixK("ab+", 'a', 1), 1);
}

TEST(Star, 0) {
    EXPECT_EQ(MinWordPrefixK("a*", 'a', 3), 3);
}
TEST(Star, 1) {
    EXPECT_EQ(MinWordPrefixK("a*b*.", 'a', 3), 3);
}
TEST(Star, 2) {
    EXPECT_EQ(MinWordPrefixK("a*b*c*..", 'a', 7), 7);
}
TEST(Star, 3) {
    EXPECT_EQ(MinWordPrefixK("ab.*", 'a', 7), 14);
}

TEST(Spooky, 0) {
    EXPECT_EQ(MinWordPrefixK("aaab.*.a.ab.*.b+*.", 'a', 1), 1);
}
TEST(Spooky, 1) {
    EXPECT_EQ(MinWordPrefixK("aaab.*.a.ab.*.b+*.", 'a', 2), INF);
}
TEST(Spooky, 2) {
    EXPECT_EQ(MinWordPrefixK("aaab.*.a.ab.*.b+*.", 'a', 3), 3);
}
TEST(Spooky, 3) {
    EXPECT_EQ(MinWordPrefixK("aaab.*.a.ab.*.b+*.", 'a', 4), 5);
}
TEST(Spooky, 4) {
    EXPECT_EQ(MinWordPrefixK("aaab.*.a.ab.*.b+*.", 'a', 5), 5);
}
TEST(Spooky, 5) {
    EXPECT_EQ(MinWordPrefixK("aaab.*.a.ab.*.b+*.", 'a', 6), 7);
}


int main(int depth, char **layer) {
	::testing::InitGoogleTest(&depth, layer);
	return RUN_ALL_TESTS();
}
