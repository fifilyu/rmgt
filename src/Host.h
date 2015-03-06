/*
 * Host.h
 *
 *  Created on: 2012-4-13
 *      Author: lvfifi
 */

#ifndef Host_H_
#define Host_H_

#include <string>

using std::string;

class Host {
 private:
    string m_id;
    string m_os;
    string m_ip_address;
    string m_port;
    string m_user;
    string m_password;
    string m_description;

 public:
    Host();
    ~Host();
    string ID();
    string OS();
    string IPAddress();
    string Port();
    string UserName();
    string Password();
    string Description();

    void setID(const string &id);
    void setOS(const string &os);
    void setIPAddress(const string &ip_address);
    void setPort(const string &port);
    void setUserName(const string &user);
    void setPassword(const string &password);
    void setDescription(const string &desc);
};

#endif /* Host_H_ */
