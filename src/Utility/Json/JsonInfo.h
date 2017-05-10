#pragma once
#include "jsoncpp/json/json.h"

namespace tol
{
    class JsonInfo
    {
    public:

        // jsonファイルを開く処理 assetからのファイル階層
        bool openJson(const std::string& file_name);

        // 引数のrootに子供がいるかどうかチェックする
        bool isValue(const Json::Value& value);

        // keyのvalueを返す
        Json::Value getValue(const std::string& key, const Json::Value& value);

        // 書き込み
        void save(const std::string & file_name);

    public:
        Json::Value root;
    private:
        Json::Reader reader;
    };
}