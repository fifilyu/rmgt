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

#include "common.h"
#include "issue.h"
#include "HostCtx.h"
#include <pwd.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;

void add_host(
        const string& cfg_file,
        const string &id, const string &os, const string &ip,
        const string &port, const string &passwd,
        const string &usr, const string &desc);

void conn_host(const string& cfg_file, const string &id_, bool verbase);

void del_host(const string& cfg_file, const string &id_);

void show_all_host(const string& cfg_file);

void show_host(HostPtr_t host);

void show_host(const string& cfg_file, const string &id);

void show_version();

void usage();

void add_host(
        const string& cfg_file,
        const string &id, const string &os, const string &ip,
        const string &port, const string &passwd,
        const string &usr, const string &desc) {
    HostCtx host_ctx_(cfg_file);
    host_ctx_.load();

    HostPtr_t host_;

    if (host_ctx_.is_host_exist(id)) {
        host_ = host_ctx_.get_host(id);
    } else {
        host_ = new Host();
        host_->setID(id);
    }

    host_->setOS(os);
    host_->setIPAddress(ip);
    host_->setPort(port);
    host_->setUserName(usr);
    host_->setPassword(passwd);
    host_->setDescription(desc);

    host_ctx_.add_host(host_);
    host_ctx_.save();

    cout << "成功......增加或更新主机" << endl;
}

void conn_host(const string& cfg_file, const string &id_, bool verbase) {
    HostCtx host_ctx_(cfg_file);
    host_ctx_.load();
    HostPtr_t host_ = host_ctx_.get_host(id_);

    show_host(host_);

    string cmd_;

    if (host_->OS() == "windows") {
        if (host_->UserName().empty() || host_->Password().empty()) {
            cerr << "[Error] Windows 主机用户名或密码为空，不能执行远程连接" << endl;
            exit(EXIT_FAILURE);
        }

        cmd_ = "rdesktop "
               "-T'主机名: " + host_->ID() + ", IP地址:" + host_->IPAddress() + ", 端口:" + host_->Port() + "' "
               "-u" + host_->UserName() + " "
               // 使用单引号防止特殊字符被shell当做命令执行
               "-p'" + host_->Password() + "' "
               "-a 16 "
               "-g1920x1080 "
               "-rsound:off "
               "-rclipboard:PRIMARYCLIPBOARD "
               "-5 " + host_->IPAddress() + ":" + host_->Port();
    } else if (host_->OS() == "linux") {
        if (host_->UserName().empty()) {
            cerr << "[Error] Linux 主机用户名为空，不能执行远程连接" << endl;
            exit(EXIT_FAILURE);
        }

        cmd_ = "ssh -p" + host_->Port() + " " + host_->UserName() + "@" + host_->IPAddress();

        if (!host_->Password().empty())
            cmd_ = "sshpass -p '" + host_->Password() + "' " + cmd_;

        if (verbase)
            cmd_ += " -v";
    } else {
        cerr << "[Error] 操作系统参数不正确" << endl;
        exit(EXIT_FAILURE);
    }

    if (!cmd_.empty()) {
        cout << "远程主机连接中......" << endl;
        const int ret_ = system(cmd_.c_str());
        exit(ret_ ? EXIT_SUCCESS : EXIT_FAILURE);
    }
}

void del_host(const string& cfg_file, const string &id_) {
    HostCtx host_ctx_(cfg_file);
    host_ctx_.load();
    HostPtr_t host_ = host_ctx_.get_host(id_);

    show_host(host_);

    host_ctx_.del_host(id_);
    host_ctx_.save();

    cout << "成功......删除主机" << endl;
}

void show_all_host(const string& cfg_file) {
    HostCtx host_ctx_(cfg_file);
    host_ctx_.load();
    HostPtrMap_t &host_list_ = host_ctx_.host_list();

    HostPtr_t host_;

    cout << "主机名\t\t" << "IP地址" << endl;

    for (auto & it_ : host_list_) {
        host_ = it_.second;
        cout << host_->ID() << "\t\t" << host_->IPAddress() << endl;
    }
}

void show_host(const string& cfg_file, const string &id) {
    HostCtx host_ctx_(cfg_file);
    host_ctx_.load();
    HostPtr_t host_ = host_ctx_.get_host(id);
    show_host(host_);
}

void show_host(HostPtr_t host) {
    cout << "<主机信息>" << endl;
    cout << "  主机名: " << host->ID() << endl;
    cout << "操作系统: " << host->OS() << endl;
    cout << "  IP地址: " << host->IPAddress() << endl;
    cout << "远程端口: " << host->Port() << endl;
    cout << "  用户名: " << host->UserName() << endl;

    if (host->Password() == NONE_VALUE || host->Password().empty())
        cout << "    密码: " << endl;
    else
        cout << "    密码: **********" << endl;

    cout << "    描述: " << (host->Description() == NONE_VALUE ? "" : host->Description()) << endl;
    cout << endl;
}

void show_version() {
    cout << PACKAGE << "(remote management) " << VERSION << " - " << DESC << "\n" << endl;
}

void usage() {
    stringstream usage_;

    usage_ << "用法 :" << endl;
    usage_ << "\trmgt -V" << endl;
    usage_ << "\trmgt -c <主机名> [-v]" << endl;
    usage_ << "\trmgt -l" << endl;
    usage_ << "\trmgt -s <主机名>" << endl;
    usage_ << "\trmgt -r <主机名>" << endl;
    usage_ << "\trmgt -n <主机名> -o <操作系统> -i <IP地址> "
              "-p [远程端口[22|3389]] -u [用户名[root|administrator]] -w [密码] -d [描述]" << endl;
    usage_ << endl;
    usage_ << "参数 :" << endl;
    usage_ << "\t-c <主机名>\t\t将连接的主机名" << endl;
    usage_ << "\t-l \t\t\t显示所有主机信息" << endl;
    usage_ << "\t-s <主机名>\t\t显示指定主机信息" << endl;
    usage_ << "\t-r <主机名>\t\t从配置文件删除主机" << endl;
    usage_ << "\t-n <主机名>\t\t增加主机时，设置主机名" << endl;
    usage_ << "\t-o <操作系统>\t\t增加主机时，设置操作系统，可选值：linux windows" << endl;
    usage_ << "\t-i <IP地址>\t\t增加主机时，设置IP地址" << endl;
    usage_ << "\t-p [远程端口]\t\t增加主机时，设置远程端口，linux 默认值：22，windows 默认值：3389" << endl;
    usage_ << "\t-u [用户名]\t\t增加主机时，设置远程登录用户名，"
              "linux 默认值：root，windows 默认值：administrator" << endl;
    usage_ << "\t-w [密码]\t\t增加主机时，设置密码，默认值：空" << endl;
    usage_ << "\t-d [描述]\t\t增加主机时，设置描述，默认值：空" << endl;
    usage_ << "\t-h <显示帮助信息>\t显示帮助信息" << endl;
    usage_ << "\t-v <显示连接信息>\t显示连接信息" << endl;
    usage_ << "\t-V <显示版本信息>\t显示版本信息" << endl;

    cout << usage_.str();
}

int main(int argc, char *argv[]) {
    show_version();

    struct passwd *pw_ = getpwuid(getuid());
    const string home_dir_(pw_->pw_dir);

    if (argc <= 1) {
        usage();
        exit(EXIT_FAILURE);
    }

    const string cfg_filename_("." + string(PACKAGE) + ".conf");
    const string cfg_file_(home_dir_ + "/" + cfg_filename_);

    string p_id_for_conn_;
    string p_id_for_del_;

    bool is_show_list_ = false;
    string p_id_for_show_;

    string p_id_;
    string p_os_;
    string p_ip_;
    string p_port_;
    string p_passwd_;
    string p_usr_;
    string p_desc_;

    bool verbase_ = false;

    int c;

    while (-1 != (c = getopt(argc, argv,
                             "c:" // connect alias of host
                             "r:" // remove host
                             "l" // show host list
                             "s:" // show host
                             "n:" // host name
                             "o:" // os
                             "i:" // ipaddress
                             "p:" // Host port
                             "u:" // user
                             "w:" // password
                             "d:" // description
                             "h" // show help info
                             "v" // verbase
                             "V" // Version
    ))) {
        switch (c) {
            case 'c':
                p_id_for_conn_ = string(optarg);
                break;
            case 'l':
                is_show_list_ = true;
                break;
            case 's':
                p_id_for_show_ = string(optarg);
                break;
            case 'o':
                p_os_ = string(optarg);
                break;
            case 'i':
                p_ip_ = string(optarg);
                break;
            case 'n':
                p_id_ = string(optarg);
                break;
            case 'p':
                p_port_ = string(optarg);
                break;
            case 'w':
                p_passwd_ = string(optarg);
                break;
            case 'u':
                p_usr_ = string(optarg);
                break;
            case 'd':
                p_desc_ = string(optarg);
                break;
            case 'r':
                p_id_for_del_ = string(optarg);
                break;
            case 'h':
                usage();
                return EXIT_SUCCESS;
            case 'V':
                return EXIT_SUCCESS;
            case 'v':
                verbase_ = true;
                break;
            default:
                usage();
                return EXIT_FAILURE;
        }
    }

    try {
        if (is_show_list_)
            show_all_host(cfg_file_);
        else if (!p_id_for_show_.empty())
            show_host(cfg_file_, p_id_for_show_);
        else if (!p_id_for_conn_.empty())
            conn_host(cfg_file_, p_id_for_conn_, verbase_);
        else if (!p_id_for_del_.empty())
            del_host(cfg_file_, p_id_for_del_);
        else if (!p_id_.empty() && !p_os_.empty() && !p_ip_.empty())
            add_host(cfg_file_, p_id_, p_os_, p_ip_, p_port_, p_passwd_, p_usr_, p_desc_);
        else {
            usage();
            return EXIT_FAILURE;
        }
    } catch (common::MException &e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

