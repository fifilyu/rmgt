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
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cctype>
#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>

using std::strerror;
using std::find_if;
using std::not1;
using std::ptr_fun;
using std::istringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

namespace common {

    MException::MException(string msg) : m_msg(std::move(msg)) {
    }

    string MException::what() {
        return m_msg;
    }

    // trim from start
    string ltrim(const string &s) {
        string s_(s);

        s_.erase(
                s_.begin(),
                std::find_if(
                        s_.begin(),
                        s_.end(),
                        std::not_fn([](unsigned char x) { return std::isspace(x); }))
        );

        return s_;
    }

    // trim from end
    string rtrim(const string &s) {
        string s_(s);

        s_.erase(std::find_if(s_.rbegin(),
                                s_.rend(),
                                std::not_fn([](unsigned char x) { return std::isspace(x); })).base(),
                 s_.end());

        return s_;
    }

    // trim from both ends
    string trim(const string &s) {
        return ltrim(rtrim(s));
    }

    string rtrim2(const string &s, const string &delim) {
        return s.substr(0, s.find_last_not_of(delim) + 1);
    }

    string ltrim2(const string &s, const string &delim) {
        return s.substr(s.find_first_not_of(delim));
    }

    string trim2(const string &s, const string &delim) {
        return ltrim2(rtrim2(s, delim), delim);
    }

    void to_vector(const string &s, vector<string> &strs, char delim) {
        istringstream istream_(s);
        string s_;

        while (getline(istream_, s_, delim))
            strs.push_back(s_);
    }

    bool rm_file(const string &pathname) {
        return unlink(pathname.c_str()) == 0;
    }

    string read_file(const string &filename) {
        string tmp_;
        string content_;
        ifstream infile_(filename.c_str(), ifstream::binary);

        if (!infile_)
            throw MException("cannot open \"" + filename + "\".");

        while (!infile_.eof()) {
            infile_ >> tmp_;

            if (content_.empty())
                content_ += tmp_;
            else
                content_ += " " + tmp_;
        }

        infile_.close();

        return content_;
    }

    void write_file(const string &filename, const string &content) {
        ofstream outfile_(filename.c_str(), ofstream::binary);

        if (!outfile_)
            throw MException("cannot open \"" + filename + "\".");

        outfile_ << content;
        outfile_.close();
    }

    bool is_host_id_str(const string &s) {
        return std::all_of(s.cbegin(), s.cend(), [](int i) { return isalnum(i) || i == '.' || i == '_'; });
    }

    bool is_port(const string &s) {
        return std::all_of(s.cbegin(), s.cend(), [](int i) { return isdigit(i); });
    }

    bool is_file_exist(const string &path) {
        struct stat file_info_{};
        const string path_(trim(path));
        return stat(path_.c_str(), &file_info_) == 0;
    }

}  // namespace common
