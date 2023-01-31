// The MIT License (MIT)
//
// Copyright (c) 2023 Fifi Lyu
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
//         of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//         to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//         copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//         copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//         AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <gtest/gtest.h>
#include "../src/HostCtx.h"
#include "../src/common.h"
#include <iostream>

using std::cout;
using std::endl;

const string g_cfg(
        "Host server1\n"
        "    OS windows\n"
        "    IPAddress 1.1.1.1\n"
        "    Port 3389\n"
        "    UserName administrator1\n"
        "    Password saung8aenighaeGhahla\n"
        "    Description test server1\n"
        "\n"
        "Host server2\n"
        "    OS windows\n"
        "    IPAddress 2.2.2.2\n"
        "    Port 3389\n"
        "    UserName administrator2\n"
        "    Password fi5ieph3vaith5ooZie5\n"
        "    Description test server2\n"
);

const string g_cfg1(
        "Host server1\n"
        "    OS windows\n"
        "    IPAddress 1.1.1.1\n"
        "    Port 3389\n"
        "    UserName administrator1\n"
        "    testkey testvalue\n"
        "    Password saung8aenighaeGhahla\n"
        "    Description test server1\n"
        "\n"
        "Host server2\n"
        "    OS windows\n"
        "    IPAddress 2.2.2.2\n"
        "    Port 3389\n"
        "    UserName administrator2\n"
        "    Password fi5ieph3vaith5ooZie5\n"
        "    Description test server2\n"
);

const string g_cfg2(
        "Host server1\n"
        "    OS windows\n"
        "    IPAddress 1.1.1.1\n"
        "    Port 3389\n"
        "    Useradministrator1\n"
        "    Password saung8aenighaeGhahla\n"
        "    Description test server1\n"
        "\n"
        "Host server2\n"
        "    OS windows\n"
        "    IPAddress 2.2.2.2\n"
        "    Port 3389\n"
        "    UserName administrator2\n"
        "    Password fi5ieph3vaith5ooZie5\n"
        "    Description test server2\n"
);

const string g_cfg_file("rmgt.conf");

TEST(HostCtxTest, load) {
    // 正确的配置
    common::rm_file(g_cfg_file);
    common::write_file(g_cfg_file, g_cfg);

    HostCtx host_ctx_(g_cfg_file);
    EXPECT_NO_THROW(host_ctx_.load());

    // 存在未知的指令 testkey
    common::rm_file(g_cfg_file);
    common::write_file(g_cfg_file, g_cfg1);

    HostCtx host_ctx1_(g_cfg_file);
    EXPECT_THROW(host_ctx1_.load(), common::MException);

    // 存在错误的指令格式
    common::rm_file(g_cfg_file);
    common::write_file(g_cfg_file, g_cfg2);

    HostCtx host_ctx2_(g_cfg_file);
    EXPECT_THROW(host_ctx2_.load(), common::MException);

    common::rm_file(g_cfg_file);
}

TEST(HostCtxTest, host_list_and_host_size) {
    common::rm_file(g_cfg_file);
    common::write_file(g_cfg_file, g_cfg);

    HostCtx host_ctx_(g_cfg_file);
    host_ctx_.load();

    HostPtrMap_t &host_list_ = host_ctx_.host_list();
    EXPECT_EQ(2, host_list_.size());

    if (host_list_.size() != 2)
        return;

    HostPtr_t host_ = host_list_.begin()->second;
    EXPECT_STREQ("server1", host_->ID().c_str());
    EXPECT_STREQ("windows", host_->OS().c_str());
    EXPECT_STREQ("1.1.1.1", host_->IPAddress().c_str());
    EXPECT_STREQ("3389", host_->Port().c_str());
    EXPECT_STREQ("saung8aenighaeGhahla", host_->Password().c_str());
    EXPECT_STREQ("administrator1", host_->UserName().c_str());
    EXPECT_STREQ("test server1", host_->Description().c_str());

    host_ = (++host_list_.begin())->second;
    EXPECT_STREQ("server2", host_->ID().c_str());
    EXPECT_STREQ("windows", host_->OS().c_str());
    EXPECT_STREQ("2.2.2.2", host_->IPAddress().c_str());
    EXPECT_STREQ("3389", host_->Port().c_str());
    EXPECT_STREQ("fi5ieph3vaith5ooZie5", host_->Password().c_str());
    EXPECT_STREQ("administrator2", host_->UserName().c_str());
    EXPECT_STREQ("test server2", host_->Description().c_str());
    common::rm_file(g_cfg_file);
}

TEST(HostCtxTest, dump) {
    common::rm_file(g_cfg_file);
    common::write_file(g_cfg_file, g_cfg);

    HostCtx host_ctx_(g_cfg_file);
    host_ctx_.load();

    const string cfg_(host_ctx_.dump());
    EXPECT_STREQ(g_cfg.c_str(), cfg_.c_str());

    common::rm_file(g_cfg_file);
}

TEST(HostCtxTest, xxx_host) {
    HostCtx host_ctx_(g_cfg_file);
    auto host_ = new Host();

    host_->setID("host1");
    host_->setOS("linux");
    host_->setIPAddress("3.3.3.3");
    host_->setPort("22");
    host_->setPassword("password");
    host_->setUserName("root");
    host_->setDescription("this is test");
    // 验证 Host
    EXPECT_NO_THROW(host_ctx_.validate_host(host_));

    // 增加 Host
    EXPECT_NO_THROW(host_ctx_.add_host(host_));

    HostPtrMap_t &host_list_ = host_ctx_.host_list();
    EXPECT_EQ(1, host_list_.size());

    if (host_list_.size() != 1)
        return;

    host_ = host_list_.begin()->second;
    EXPECT_STREQ("host1", host_->ID().c_str());
    EXPECT_STREQ("linux", host_->OS().c_str());
    EXPECT_STREQ("3.3.3.3", host_->IPAddress().c_str());
    EXPECT_STREQ("22", host_->Port().c_str());
    EXPECT_STREQ("password", host_->Password().c_str());
    EXPECT_STREQ("root", host_->UserName().c_str());
    EXPECT_STREQ("this is test", host_->Description().c_str());

    // 修改 Host
    host_->setIPAddress("4.4.4.4");
    host_->setPort("2222");
    host_->setPassword("password2");
    EXPECT_NO_THROW(host_ctx_.validate_host(host_));

    // 获取 Host
    EXPECT_NO_THROW(host_ctx_.get_host("host1"));
    EXPECT_THROW(host_ctx_.get_host("host2"), common::MException);

    // 删除 Host
    EXPECT_NO_THROW(host_ctx_.del_host(host_->ID()));
    EXPECT_EQ(0, host_list_.size());
}

TEST(HostCtxTest, save) {
    HostCtx host_ctx_(g_cfg_file);
    EXPECT_NO_THROW(host_ctx_.save());
    common::rm_file(g_cfg_file);
}
