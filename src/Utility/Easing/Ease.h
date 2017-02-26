#pragma once
#include <cinder/app/App.h>
#include <boost/coroutine/all.hpp>
#include <unordered_map>
#include <deque>
#include "EaseType.h"

#define Easing Ease::instance()
class RunEase;
using easecoroutine = boost::coroutines::coroutine<RunEase*>;

// イージングの元
class EaseOrigin
{
public:
    EaseOrigin() {}
    EaseOrigin(float begin, float end, int end_frame, EaseType type)
    {
        setup(begin, end, end_frame, type);
    }

    void setup(float begin, float end, int end_frame, EaseType type)
    {
        begin_ = begin;
        end_ = end;
        end_frame_ = static_cast<float>(end_frame);
        easefunc_ = getEaseFunc(type);
        count_ = 0.0f;
    }

    void update()
    {
        count_++;
    }

    float currentTargetValue()
    {
        if (!easefunc_)
            return begin_;
        return easefunc_(count_ / end_frame_, begin_, end_);
    }

    // 終わったらtrue
    bool isDone()
    {
        return count_ > end_frame_;
    }

    float getBegin()
    {
        return begin_;
    }
    void setBegin(float begin)
    {
        begin_ = begin;
    }
private:

    float begin_;
    float end_;
    float end_frame_;
    std::function<float(float, float, float)> easefunc_;
    float count_;
};


// ターゲットに追加されているイージングを実行するクラス
class RunEase
{
public:
    RunEase() :co(action)
    {
    }

    bool isEaseEnd()
    {
        return ease_accum.empty();
    }

    void update()
    {
        if (ease_accum.empty())return;
        co(this);
    }

    static void action(easecoroutine::pull_type & yield)
    {
        yield();
        while (true)
        {
            auto my_info = yield.get();
            auto ease_begin = my_info->ease_accum.begin();
            if (ease_begin->isDone())
            {
                ease_begin++;
                if (ease_begin != my_info->ease_accum.end())
                    ease_begin->setBegin(*my_info->target_);
                my_info->pop();
                yield();
            }
            else
            {
                *my_info->target_ = ease_begin->currentTargetValue();
                ease_begin->update();
                yield();
            }
        }
    }

    void add(float& target, float end, int end_frame, EaseType ease_type)
    {
        target_ = &target;
        ease_accum.push_back(EaseOrigin(target, end, end_frame, ease_type));
    }
    void add(float& target, int wait)
    {
        target_ = &target;
        ease_accum.push_back(EaseOrigin(target, target, wait, EaseType::NONE));
    }

    void pop()
    {
        ease_accum.pop_front();
    }

    void clear()
    {
        ease_accum.clear();
    }
private:

    std::deque<EaseOrigin> ease_accum;
    easecoroutine::push_type co;
    float* target_;
};


// イージングを追加するクラス
class Ease
{
private:
    Ease() {}
public:
    static Ease& instance()
    {
        static Ease easing;
        return easing;
    }


    void add(float& target, float end, int end_frame, EaseType ease_type)
    {
        ease[&target].add(target, end, end_frame, ease_type);
    }
    void add(ci::Vec3f & target, ci::Vec3f end, int end_frame, EaseType ease_type)
    {
        ease[&target.x].add(target.x, end.x, end_frame, ease_type);
        ease[&target.y].add(target.y, end.y, end_frame, ease_type);
        ease[&target.z].add(target.z, end.z, end_frame, ease_type);
    }

    void wait(float& target, int wait_count)
    {
        ease[&target].add(target, wait_count);
    }
    void wait(ci::Vec3f & target, int wait_count)
    {
        ease[&target.x].add(target.x, wait_count);
        ease[&target.y].add(target.y, wait_count);
        ease[&target.z].add(target.z, wait_count);
    }

    bool isEaseEnd(float& target)
    {
        return ease[&target].isEaseEnd();
    }

    void update()
    {
        for (auto it = ease.begin(); it != ease.end();)
        {
            if (it->second.isEaseEnd())
            {
                it = ease.erase(it);
                continue;
            }
            it->second.update();
            it++;
        }
    }

    void kill(float& target)
    {
        ease[&target].clear();
    }

    void kill(ci::Vec3f & target)
    {
        ease[&target.x].clear();
        ease[&target.y].clear();
        ease[&target.z].clear();
    }

    void allClear()
    {
        for (auto & it : ease)
        {
            it.second.clear();
        }
        ease.clear();
    }

private:
    std::unordered_map<float*, RunEase> ease;
};

