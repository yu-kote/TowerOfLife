#include "TolGameDataManager.h"
#include "../Utility/Json/JsonInfo.h"

void tol::TolGameDataManager::setup()
{
    temp_coin = 0;
    coin = 0;
    score = 0;
    high_score = 0;
    load();

#if 1
    itemlist.push_back(TolItem::SCROLL_STOP);
    itemlist.push_back(TolItem::GIMMICK_STOP);
    itemlist.push_back(TolItem::TWO_STEP_JUMP);
#endif
}

bool tol::TolGameDataManager::hasItem(const TolItem & item)
{
    for (auto& it : itemlist)
    {
        if (it == item)
            return true;
    }
    return false;
}

void tol::TolGameDataManager::useItem(const TolItem & item)
{
    for (auto it = itemlist.begin(); it != itemlist.end();)
    {
        if ((*it) == item)
        {
            it = itemlist.erase(it);
            return;
        }
        it++;
    }
}

int tol::TolGameDataManager::itemCountCheck(const TolItem & item)
{
    int count = 0;
    for (auto& it : itemlist)
    {
        if (it == item)
            count++;
    }
    return count;
}

void tol::TolGameDataManager::coinInstance()
{
    coin += temp_coin;
}

int tol::TolGameDataManager::calcScore()
{
    auto total_score = score + (temp_coin * 100);
    if (high_score < total_score)
    {
        high_score = total_score;
    }
    return total_score;
}

std::string tol::TolGameDataManager::getItemName(const TolItem& item)
{
    switch (item)
    {
    case TolItem::SCROLL_STOP:
        return u8"�X�N���[���X�g�b�p�[";
    case TolItem::GIMMICK_STOP:
        return u8"�M�~�b�N�X�g�b�p�[";
    case TolItem::TWO_STEP_JUMP:
        return u8"�_�u���W�����p�[";
    }
}

std::string tol::TolGameDataManager::getItemInstruction(const TolItem & item)
{
    switch (item)
    {
    case TolItem::SCROLL_STOP:
        return u8"�g�p����ƁA�ꎞ�I�Ɏ����X�N���[����\n�@�@�@�~�߂邱�Ƃ��ł��܂��B";
    case TolItem::GIMMICK_STOP:
        return u8"�g�p����ƁA�ꎞ�I�Ƀu���b�N�̓�����\n�@�@�@�~�߂邱�Ƃ��ł��܂��B";
    case TolItem::TWO_STEP_JUMP:
        return u8"�g�p����ƁA�ꎞ�I�ɓ�i�W�����v�ł���悤�ɂȂ�܂��B";
    }
}

void tol::TolGameDataManager::load()
{
    JsonInfo json;
    if (!json.openJson("GameData/TolSaveData.json"))
        return;

    coin = json.root["coin"].asInt();
    high_score = json.root["highscore"].asInt();
}

void tol::TolGameDataManager::save()
{
    JsonInfo json;
    std::string file_name = "GameData/TolSaveData.json";
    if (!json.openJson(file_name))
        return;

    if (json.root["highscore"].asInt() < high_score)
        json.root["highscore"] = high_score;

    json.root["coin"] = coin;
    
    temp_coin = 0;
    score = 0;

    json.save(file_name);
}
