#pragma once
#include "jsoncpp/json/json.h"

namespace tol
{
    class JsonInfo
    {
    public:

        // json�t�@�C�����J������ asset����̃t�@�C���K�w
        bool openJson(const std::string& file_name);

        // ������root�Ɏq�������邩�ǂ����`�F�b�N����
        bool isValue(const Json::Value& value);

        // key��value��Ԃ�
        Json::Value getValue(const std::string& key, const Json::Value& value);

        // ��������
        void save(const std::string & file_name);

    public:
        Json::Value root;
    private:
        Json::Reader reader;
    };
}