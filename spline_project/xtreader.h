#ifndef _XTREADER_H_
#define _XTREADER_H_

#include "nlohmann/json.hpp"

// 读取 JSON 文件
class XTReader {
    private:
        nlohmann :: json data;
    public:
        XTReader (const char *filename);
        auto getData (const char *key) const -> decltype (data[key]) {
            return data[key];
        }
        bool hasKey (const char *key) const {
            return data.contains (key);
        }
        ~XTReader () {}
};

#endif