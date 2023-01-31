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

#include "Host.h"

Host::Host()= default;

Host::~Host() = default;

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
