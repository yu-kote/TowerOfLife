#include "InputEvent.h"
using namespace ci;
using namespace ci::app;

InputEvent & InputEvent::get()
{
    static InputEvent event;
    return event;
}

InputEvent::InputEvent()
{
    axisSetup();
    padAxisSetup();
}

bool InputEvent::isPush(const int& num)
{
    if (push.find(num) == push.end())
        return false;
    push.erase(push.find(num));
    return true;
}

bool InputEvent::isPress(const int& num)
{
    if (press.find(num) == press.end())
        return false;
    return true;
}

bool InputEvent::isPull(const int& num)
{
    if (pull.find(num) == pull.end())
        return false;
    pull.erase(pull.find(num));
    return true;
}

void InputEvent::mouseMove(ci::app::MouseEvent event)
{
    mouse_position = event.getPos();
}

void InputEvent::mouseDrag(ci::app::MouseEvent event)
{
    mouse_position = event.getPos();
}

void InputEvent::mouseDown(MouseEvent event)
{
    if (event.isLeft())
    {
        setPush(MouseEvent::LEFT_DOWN);
        setPress(MouseEvent::LEFT_DOWN);
    }
    if (event.isRight())
    {
        setPush(MouseEvent::RIGHT_DOWN);
        setPress(MouseEvent::RIGHT_DOWN);
    }
    if (event.isMiddle())
    {
        setPush(MouseEvent::MIDDLE_DOWN);
        setPress(MouseEvent::MIDDLE_DOWN);
    }
}

void InputEvent::mouseUp(MouseEvent event)
{
    if (event.isLeft())
    {
        setPull(MouseEvent::LEFT_DOWN);
        erasePress(MouseEvent::LEFT_DOWN);
    }
    if (event.isRight())
    {
        setPull(MouseEvent::RIGHT_DOWN);
        erasePress(MouseEvent::RIGHT_DOWN);
    }
    if (event.isMiddle())
    {
        setPull(MouseEvent::MIDDLE_DOWN);
        erasePress(MouseEvent::MIDDLE_DOWN);
    }
}

void InputEvent::keyDown(KeyEvent event)
{
    setPush(event.getCode());
    setPress(event.getCode());
}

void InputEvent::keyUp(KeyEvent event)
{
    setPull(event.getCode());
    erasePress(event.getCode());
}

void InputEvent::setPush(const int& num)
{
    if (press.find(num) == press.end())
        push.emplace(num);
}

void InputEvent::setPress(const int& num)
{
    press.emplace(num);
}

void InputEvent::setPull(const int& num)
{
    pull.emplace(num);
}

void InputEvent::erasePress(const int& num)
{
    if (press.find(num) != press.end())
        press.erase(press.find(num));
}


void InputEvent::axisSetup()
{
    keys_serch.insert(std::make_pair("Horizontal_LR", KeyEvent::KEY_RIGHT));

    keys_serch.insert(std::make_pair("Vertical_UD", KeyEvent::KEY_UP));
    keys_serch.insert(std::make_pair("Horizontal_AD", KeyEvent::KEY_d));
    keys_serch.insert(std::make_pair("Vertical_WS", KeyEvent::KEY_w));
}

// axis_name_    軸の名前(例 : Horizontal_AD A.Dキーを押したときの値1~-1)
// velocity_     増減量 1frame
// W.A.S.Dキーと UP.DOWN.RIGHT.LEFT Arrowキーの 1から-1までの軸で返す
float InputEvent::getAxis(std::string axis_name_, const float& velocity_)
{
    if (keys_serch.find(axis_name_) == keys_serch.end())
        assert(!"Not axis name");
    int press_key = keys_serch.find(axis_name_)->second;
    if (keys.find(press_key) == keys.end())
    {
        if (press_key == KeyEvent::KEY_RIGHT)
            keys.insert(std::make_pair(press_key, KeyEvent::KEY_LEFT));
        if (press_key == KeyEvent::KEY_UP)
            keys.insert(std::make_pair(press_key, KeyEvent::KEY_DOWN));
        if (press_key == KeyEvent::KEY_w)
            keys.insert(std::make_pair(press_key, KeyEvent::KEY_s));
        if (press_key == KeyEvent::KEY_d)
            keys.insert(std::make_pair(press_key, KeyEvent::KEY_a));
        axis_value.insert(std::make_pair(axis_name_, 0.0f));
    }
    else
    {
        if (isPress(press_key))
        {
            axis_value.find(axis_name_)->second += velocity_;
            axis_value.find(axis_name_)->second = std::min(axis_value.find(axis_name_)->second, 1.0f);
        }
        else if (isPress(keys.find(press_key)->second))
        {
            axis_value.find(axis_name_)->second -= velocity_;
            axis_value.find(axis_name_)->second = std::max(axis_value.find(axis_name_)->second, -1.0f);
        }
        else
        {
            if (axis_value.find(axis_name_)->second < 0)
                axis_value.find(axis_name_)->second += velocity_;
            if (axis_value.find(axis_name_)->second > 0)
                axis_value.find(axis_name_)->second -= velocity_;

            if (axis_value.find(axis_name_)->second < velocity_ &&
                axis_value.find(axis_name_)->second > -velocity_)
                axis_value.find(axis_name_)->second = 0;
        }
    }
    return axis_value.find(axis_name_)->second;
}

// ボタン判定消去
void InputEvent::flushInput()
{
    push.clear();
    pull.clear();
}

// 消す処理があるので呼ぶ必要がない
void InputEvent::end()
{
    flushInput();
}

void onButtonDown(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context)
{
    if (verbose)
    {
        //console() << "Button " << buttonID << " down on device " << device->deviceID << " at " << timestamp << " with context " << context << std::endl;

        env.setPadPush(buttonID);
        env.setPadPress(buttonID);
    }
}

void onButtonUp(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context)
{
    if (verbose)
    {
        //console() << "Button " << buttonID << " up on device " << device->deviceID << " at " << timestamp << " with context " << context << std::endl;

        env.setPadPull(buttonID);
        env.erasePadPress(buttonID);
    }
}

void onAxisMoved(struct Gamepad_device * device, unsigned int axisID, float value, float lastValue, double timestamp, void * context)
{
    if (verbose && (value < 0.2f || value > 0.2)) // reduce the output noise by making a dead zone
    {
        //console() << "Axis " << axisID << " moved from " << lastValue << " to " << value << " on device " << device->deviceID << " at " << timestamp << " with context " << context << std::endl;

        env.setPadAxis(axisID, value);
    }
}

void onDeviceAttached(struct Gamepad_device * device, void * context)
{
    if (verbose)
    {
        //console() << "Device ID " << device->deviceID << " attached (vendor = " << device->vendorID << "; product = " << device->productID << ") with context" << context << std::endl;
    }
}

void onDeviceRemoved(struct Gamepad_device * device, void * context)
{
    if (verbose)
    {
        //console() << "Device ID " << device->deviceID << " removed with context " << context << std::endl;
    }
}

void InputEvent::padSetup()
{
    Gamepad_deviceAttachFunc(onDeviceAttached, (void *)0x1);
    Gamepad_deviceRemoveFunc(onDeviceRemoved, (void *)0x2);
    Gamepad_buttonDownFunc(onButtonDown, (void *)0x3);
    Gamepad_buttonUpFunc(onButtonUp, (void *)0x4);
    Gamepad_axisMoveFunc(onAxisMoved, (void *)0x5);
    Gamepad_init();
}

void InputEvent::padUpdate()
{
    static unsigned int iterationsToNextPoll = POLL_ITERATION_INTERVAL;

    iterationsToNextPoll--;
    if (iterationsToNextPoll == 0)
    {
        Gamepad_detectDevices();
        iterationsToNextPoll = POLL_ITERATION_INTERVAL;
    }
}

void InputEvent::padShutDown()
{
    Gamepad_shutdown();
}

void InputEvent::padProcessEvent()
{
    Gamepad_processEvents();
}

void InputEvent::setPadPush(const int & num)
{
    if (padpress.find(num) == padpress.end())
        padpush.emplace(num);
}

void InputEvent::setPadPress(const int & num)
{
    padpress.emplace(num);
}

void InputEvent::setPadPull(const int & num)
{
    padpull.emplace(num);
}

void InputEvent::erasePadPress(const int & num)
{
    padpress.erase(padpress.find(num));
}

bool InputEvent::isPadPush(const int & num)
{
    if (padpush.find(num) == padpush.end())
        return false;
    padpush.erase(padpush.find(num));
    return true;
}

bool InputEvent::isPadPress(const int & num)
{
    if (padpress.find(num) == padpress.end())
        return false;
    return true;
}

bool InputEvent::isPadPull(const int & num)
{
    if (padpull.find(num) == padpull.end())
        return false;
    padpull.erase(padpull.find(num));
    return true;
}

void InputEvent::setPadAxis(const int & num, const float & value_)
{
    pad_stick_axis_value.find(num)->second = value_;
}

void InputEvent::padAxisSetup()
{
    pad_stick_axis_value.insert(std::make_pair(STICK_LEFT_HORIZONTAL, 0.0f));
    pad_stick_axis_value.insert(std::make_pair(STICK_LEFT_VERTICAL, 0.0f));
    pad_stick_axis_value.insert(std::make_pair(STICK_RIGHT_HORIZONTAL, 0.0f));
    pad_stick_axis_value.insert(std::make_pair(STICK_RIGHT_VERTICAL, 0.0f));
    pad_stick_axis_value.insert(std::make_pair(CROSS_HORIZONTAL, 0.0f));
    pad_stick_axis_value.insert(std::make_pair(CROSS_VERTICAL, 0.0f));

    pad_stick_search.insert(std::make_pair("Horizontal_Left", STICK_LEFT_HORIZONTAL));
    pad_stick_search.insert(std::make_pair("Vertical_Left", STICK_LEFT_VERTICAL));
    pad_stick_search.insert(std::make_pair("Horizontal_Right", STICK_RIGHT_HORIZONTAL));
    pad_stick_search.insert(std::make_pair("Vertical_Right", STICK_RIGHT_VERTICAL));
    pad_stick_search.insert(std::make_pair("Horizontal_Cross", CROSS_HORIZONTAL));
    pad_stick_search.insert(std::make_pair("Vertical_Cross", CROSS_VERTICAL));

}

float InputEvent::getPadAxis(std::string axis_name_)
{
    if (pad_stick_search.find(axis_name_) == pad_stick_search.end())
        assert(!"Not pad axis name");

    float axis_value = pad_stick_axis_value.find(pad_stick_search.find(axis_name_)->second)->second;

    // 縦だけ逆だったので修正
    if (axis_name_ == "Vertical_Left" || axis_name_ == "Vertical_Right")
        axis_value *= -1;

    return axis_value;
}

float InputEvent::getPadAxis(const int & pad_num)
{
    if (pad_stick_axis_value.find(pad_num) == pad_stick_axis_value.end())
        assert(!"Not pad axis num");

    // 縦だけ逆だったので修正
    if (pad_num == STICK_LEFT_VERTICAL || pad_num == STICK_RIGHT_VERTICAL)
        pad_stick_axis_value.find(pad_num)->second *= -1;

    return pad_stick_axis_value.find(pad_num)->second;
}
