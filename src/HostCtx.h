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

#ifndef SRC_HOSTCTX_H_
#define SRC_HOSTCTX_H_

#include "Host.h"
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

typedef Host *HostPtr_t;
typedef string HostID_t;
typedef map<HostID_t, HostPtr_t> HostPtrMap_t;

class HostCtx {
private:
    typedef enum {
        KN_Host,
        KN_OS,
        KN_IPAddress,
        KN_Port,
        KN_Password,
        KN_UserName,
        KN_Description
    } KeyName_t;

    typedef map<KeyName_t, string> KeyNameDescMap_t;
    typedef map<string, KeyName_t> DescKeyNameMap_t;

private:
    static KeyNameDescMap_t m_key_name_desc_map;
    static DescKeyNameMap_t m_desc_key_name_map;
    HostPtrMap_t m_host_list;  // Host 对象指针列表
    string m_cfg_file;

private:
    static DescKeyNameMap_t crt_DescKeyNameMap();

    static void validate_key(const string &s);

    static KeyName_t to_keyname(const string &s);

    void delete_all_host_obj();

    static string dump(HostPtr_t host);

    void parse_line(string &line);


public:
    explicit HostCtx(string cfg_file);

    ~HostCtx();

    void load();

    string dump();

    HostPtrMap_t &host_list();

    HostPtr_t get_host(const string &id);

    bool is_host_exist(const string &id);

    void add_host(HostPtr_t host);

    void del_host(const string &id);

    static void validate_host(HostPtr_t host);

    void save();
};

#endif /* SRC_HOSTCTX_H_ */
