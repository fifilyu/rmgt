/*
 * Host.cpp
 *
 *  Created on: 2012-4-13
 *      Author: lvfifi
 */

#include "Host.h"
#include "common.h"

Host::Host()
        : m_id(""),
          m_os(""),
          m_ip_address(""),
          m_port(""),
          m_user(""),
          m_password(""),
          m_description("") {

}

Host::~Host() {

}

string Host::OS() {
    return m_os;
}

string Host::IPAddress() {
    return m_ip_address;
}

string Host::ID() {
    return m_id;
}

string Host::UserName() {
    return m_user;
}

string Host::Password() {
    return m_password;
}

string Host::Port() {
    return m_port;
}

string Host::Description() {
    return m_description;
}

void Host::setOS(const string &os) {
    m_os = os;
}

void Host::setIPAddress(const string &ip_address) {
    m_ip_address = ip_address;
}

void Host::setID(const string &id) {
    m_id = id;
}

void Host::setUserName(const string &user) {
    m_user = user;
}

void Host::setPassword(const string &password) {
    m_password = password;
}

void Host::setPort(const string &port) {
    m_port = port;
}

void Host::setDescription(const string &desc) {
    m_description = desc;
}
