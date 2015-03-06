/*
 * common.h
 *
 *  Created on: 2015年3月3日
 *      Author: Fifi Lyu
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <string>
#include <vector>
#include <map>

using std::string;
using std::map;
using std::vector;

static const string NONE_VALUE("NONE");

namespace common {

typedef enum {
    OS_linux,
    OS_windows
} OS_t;

// 错误异常类
// 用法： throw Mexception("错误内容")
class MException {
private:
  string m_msg;

public:
  // explicit 只对构造函数起作用，用来抑制隐式转换。
  explicit MException(const string &msg);
  ~MException();
  string what();
};

string ltrim(const string &s);
string rtrim(const string &s);
string trim(const string &s);

string ltrim2(const string &s, const string &delim = " \f\n\r\t\v");
string rtrim2(const string &s, const string &delim = " \f\n\r\t\v");
string trim2(const string &s, const string &delim = " \f\n\r\t\v");

void to_vector(const string &s, vector<string> &strs, char delim = ' ');

bool rm_file(const string &pathname);
string read_file(const string &filename);
void write_file(const string &filename, const string &content);

// 字母、数字以、点以及下划线组成的字符串
// 1.1.1.1
// host1
// host_usa_2.3
bool is_host_id_str(const string &s);

bool is_port(const string &s);

bool is_file_exist(const string &path);

} // namespace common

#endif /* SRC_COMMON_H_ */
