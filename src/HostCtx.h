/*
 * HostCtx.h
 *
 *  Created on: 2015年3月2日
 *      Author: Fifi Lyu
 */

#ifndef SRC_HOSTCTX_H_
#define SRC_HOSTCTX_H_

#include "Host.h"
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

typedef Host* HostPtr_t;
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

    typedef struct {
        KeyName_t key;
        string value;
    } KeyValue_t;

    typedef map<KeyName_t, string> KeyNameDescMap_t;
    typedef map<string, KeyName_t> DescKeyNameMap_t;

 private:
    static KeyNameDescMap_t m_key_name_desc_map;
    static DescKeyNameMap_t m_desc_key_name_map;
    HostPtrMap_t m_host_list;  // Host 对象指针列表
    string m_cfg_file;

 private:
    static KeyNameDescMap_t crt_KeyNameDescMap();
    static DescKeyNameMap_t crt_DescKeyNameMap();

    void validate_key(const string &s);
    KeyName_t to_keyname(const string &s);
    void delete_all_host_obj();

    string dump(HostPtr_t host);
    void parse_line(string &line);


 public:
    HostCtx(const string &cfg_file);
    ~HostCtx();

    void load();
    string dump();

    HostPtrMap_t& host_list();

    HostPtr_t get_host(const string &id);
    bool is_host_exist(const string &id);
    void add_host(HostPtr_t host);
    void del_host(const string &id);
    static void validate_host(HostPtr_t host);
    void save();
};

#endif /* SRC_HOSTCTX_H_ */
