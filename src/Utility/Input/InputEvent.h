#pragma once
#include "cinder\app\KeyEvent.h"
#include "cinder\app\AppNative.h"

#include <set>
#include <vector>
#include <unordered_map>
#include <map>

extern "C"
{
#include "Gamepad/Gamepad.h"
}

#pragma comment(lib,"winmm.lib")
#if _DEBUG
#pragma comment(lib,"../lib/msw/x86/Gamepad_d.lib")
#else
#pragma comment(lib,"../lib/msw/x86/Gamepad.lib")
#endif 

static bool verbose = true;

#define POLL_ITERATION_INTERVAL 30

class InputEvent : private boost::noncopyable
{
private:
    InputEvent();

    std::set<int> push;
    std::set<int> press;
    std::set<int> pull;
    bool mouse_left_press;
    bool mouse_right_press;

    void setPush(const int& num);
    void setPress(const int& num);
    void setPull(const int& num);
    void erasePress(const int& num);

public:

    static InputEvent& get();

    // if(env.isPush(KeyEvent::KEY_1)
    bool isPush(const int& num);
    bool isPress(const int& num);
    bool isPull(const int& num);

    void mouseDown(ci::app::MouseEvent event);
    void mouseUp(ci::app::MouseEvent event);
    void keyDown(ci::app::KeyEvent event);
    void keyUp(ci::app::KeyEvent event);

    void flushInput();
    void end();

private:

    std::map<std::string, int> keys_serch;		// 名前からキーを登録
    std::map<int, int> keys;					// 押しているキー
    std::map<std::string, float> axis_value;	// 押しているキーの増減値

    void axisSetup();
public:

    // env.getAxis("Vertical_UD", 0.15f)
    float getAxis(std::string axis_name_, const float& velocity_ = 0.3f);


public:// ゲームパッド

    // maincppで呼ぶ
    void padSetup();
    void padUpdate();
    void padShutDown();
    void padProcessEvent();

private:
    std::set<int> padpush;
    std::set<int> padpress;
    std::set<int> padpull;
public:
    void setPadPush(const int& num);
    void setPadPress(const int& num);
    void setPadPull(const int& num);
    void erasePadPress(const int& num);


    bool isPadPush(const int& num);
    bool isPadPress(const int& num);
    bool isPadPull(const int& num);


private:
    std::map<int, float> pad_stick_axis_value;
public:

    void setPadAxis(const int& num, const float& value_);

private:
    std::map<std::string, int> pad_stick_search;
    void padAxisSetup();
public:

    float getPadAxis(std::string axis_name_);
    float getPadAxis(const int& pad_num);

    enum PadNum
    {
        STICK_LEFT_HORIZONTAL = 0,
        STICK_LEFT_VERTICAL = 1,
        STICK_RIGHT_HORIZONTAL = 2,
        STICK_RIGHT_VERTICAL = 3,
        CROSS_HORIZONTAL = 4,
        CROSS_VERTICAL = 5,
        BUTTON_1 = 0,
        BUTTON_2 = 1,
        BUTTON_3 = 2,
        BUTTON_4 = 3,
        BUTTON_5 = 4,
        BUTTON_6 = 5,
        BUTTON_7 = 6,
        BUTTON_8 = 7,
        BUTTON_9 = 8,
        BUTTON_10 = 9,
        BUTTON_11 = 10,
        BUTTON_12 = 11,

    };

};

void onButtonDown(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context);
void onButtonUp(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context);
void onAxisMoved(struct Gamepad_device * device, unsigned int axisID, float value, float lastValue, double timestamp, void * context);
void onDeviceAttached(struct Gamepad_device * device, void * context);
void onDeviceRemoved(struct Gamepad_device * device, void * context);


#define env InputEvent::get()