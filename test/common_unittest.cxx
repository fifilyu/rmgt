/*
 * common_unittest.cxx
 *
 *  Created on: 2015年3月3日
 *      Author: Fifi Lyu
 */

#include <gtest/gtest.h>
#include "../src/common.h"

TEST(CommonTest, MException) {
    try {
        throw common::MException("test message.");
    } catch (common::MException &e) {
        EXPECT_STREQ("test message.", e.what().c_str());
    }
}

TEST(CommonTest, ltrim) {
  EXPECT_STREQ("abc   ", common::ltrim("   abc   ").c_str());
}

TEST(CommonTest, rtrim) {
  EXPECT_STREQ("   abc", common::rtrim("   abc   ").c_str());
}

TEST(CommonTest, trim) {
  EXPECT_STREQ("abc", common::trim("   abc   ").c_str());
}

TEST(CommonTest, ltrim2) {
  EXPECT_STREQ("abc\n   ", common::ltrim2(" \n  abc\n   ").c_str());
}

TEST(CommonTest, rtrim2) {
  EXPECT_STREQ(" \n  abc", common::rtrim2(" \n  abc\n   ").c_str());
}

TEST(CommonTest, trim2) {
  EXPECT_STREQ("abc", common::trim2(" \n  abc\n   ").c_str());
}

TEST(CommonTest, to_vector) {
    vector<string> strs1_;
    common::to_vector("key value", strs1_);
    EXPECT_EQ(2, strs1_.size());

    vector<string> strs2_;
    common::to_vector(";123;456;789;0", strs2_, ';');
    EXPECT_EQ(5, strs2_.size());

    vector<string> strs3_;
    common::to_vector("line1 key value\nline2 key value\n", strs3_, '\n');
    EXPECT_EQ(2, strs3_.size());
}

TEST(CommonTest, rm_file1) {
    EXPECT_FALSE(common::rm_file("test.txt"));
}

TEST(CommonTest, read_and_write_file) {
    EXPECT_NO_THROW(common::write_file("test.txt", "this is test text."));
    EXPECT_NO_THROW(common::read_file("test.txt"));

    const string content_(common::read_file("test.txt"));

    EXPECT_STREQ("this is test text.", content_.c_str());
}

TEST(CommonTest, rm_file2) {
    EXPECT_TRUE(common::rm_file("test.txt"));
}

TEST(CommonTest, is_host_id_str) {
    EXPECT_TRUE(common::is_host_id_str("1.1.1.1"));
    EXPECT_TRUE(common::is_host_id_str("host1"));
    EXPECT_TRUE(common::is_host_id_str("host_usa_2.3"));

    EXPECT_FALSE(common::is_host_id_str("h?!ost_usa_2.3+"));
}

TEST(CommonTest, is_port) {
    EXPECT_TRUE(common::is_port("22"));
    EXPECT_TRUE(common::is_port("3389"));
    EXPECT_FALSE(common::is_port("22a"));
}

TEST(CommonTest, is_file_exist) {
    EXPECT_FALSE(common::is_file_exist("test.txt"));
}
