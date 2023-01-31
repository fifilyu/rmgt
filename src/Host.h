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
