/*
 * common.cxx
 *
 *  Created on: 2015年3月3日
 *      Author: Fifi Lyu
 */

#include "common.h"
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>
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

MException::MException(const string &msg) : m_msg(msg) {
}

MException::~MException() {

}

string MException::what() {
  return m_msg;
}

// trim from start
string ltrim(const string &s) {
    string s_(s);

    s_.erase(
            s_.begin(),
            find_if(
                    s_.begin(),
                    s_.end(),
                    not1(ptr_fun<int, int>(isspace))
            )
    );

    return s_;
}

// trim from end
string rtrim(const string &s) {
    string s_(s);

    s_.erase(
            find_if(
                    s_.rbegin(),
                    s_.rend(),
                    not1(ptr_fun<int, int>(isspace))
            ).base(),
            s_.end()
    );

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
    string tmp_("");
    string content_("");
    ifstream infile_(filename.c_str(), ifstream::binary);

    if (!infile_)
        throw MException("cannot open \"" + filename + "\".");

    while(!infile_.eof()) {
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
    return;
}

bool is_host_id_str(const string &s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (!isalnum(s[i]) && s[i] != '.' && s[i] != '_')
            return false;
    }

    return true;
}

bool is_port(const string &s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (!isdigit(s[i]))
            return false;
    }

    return true;
}

bool is_file_exist(const string &path) {
  struct stat file_info_;
  const string path_(trim(path));
  return stat(path_.c_str(), &file_info_) == 0;
}

}  // namespace common
