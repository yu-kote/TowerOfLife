#pragma once
#include "cinder/app/AppNative.h"

#include "../Object.h"
#include "../Component/Component.h"
#include "../Component/Components/Transform.h"
#include <unordered_map>
#include <string>
#include <typeinfo>

namespace tol
{
    class GameObject : public Object
    {
    public:

        GameObject();
        GameObject(const std::string& name_);

        virtual void setup() {};
        virtual void update() {};
        virtual void laterUpdate() {};
        virtual void draw() {};
        virtual void transDraw() {};
        virtual void laterDraw() {};
        virtual void transLaterDraw() {};

        void componentsUpdate();

        // �R���|�[�l���g�̕`�揉�߂̏���
        void drawBegin();
        // �R���|�[�l���g�̕`��I���̏���
        void drawEnd();
        void componentsDraw();
        void componentsDestroy();

    public:

        // �s��v�Z�̎n��
        void pushModelView();
        // �s��v�Z�I���
        void popModelView();

    public:
        /* �ʒu���]�Ȃǂ̏���A
           �s��v�Z�֐��Ȃǂ�����*/
        Transform transform;

        void setActive(const bool& value) { active_in_scene = value; }
        bool getActive() { return active_in_scene; }
        void setIsUpdateActive(const bool& value) { is_update_active = value; }
        bool getIsUpdateActive() { return is_update_active; }
    private:

    public:

        // �R���|�[�l���g�̒ǉ�
        template<typename T>
        void addComponent()
        {
            std::string componentname = createComponentName<T>();

            if (components.find(componentname) == components.end())
                components.insert(std::make_pair(componentname, std::make_shared<T>()));
        }

        // �R���|�[�l���g�̒ǉ�(�R���X�g���N�^����)
        template<typename T>
        void addComponent(const T& component_)
        {
            std::string componentname = createComponentName<T>();

            if (components.find(componentname) == components.end())
                components.insert(std::make_pair(componentname, std::make_shared<T>(component_)));
        }

        // �R���|�[�l���g�̎擾
        template<typename T>
        std::shared_ptr<T> getComponent()
        {
            int script_size = sizeof(T);
            std::string componentname = createComponentName<T>();
            if (components.find(componentname) == components.end())
                assert(!"Component Not Finded");
            /*
            if (script_size > 128)
            {
                return std::dynamic_pointer_cast<T>(components.find(componentname)->second);
            }
            else
            {
                return std::static_pointer_cast<T>(components.find(componentname)->second);
            }*/
            return std::static_pointer_cast<T>(components.find(componentname)->second);
        }

    private:
        template<typename T>
        static std::string createComponentName()
        {
            const type_info& id = typeid(T);

            std::string class_name = id.name();
            class_name.erase(0, 6);

            return class_name;
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<Component>> components;
        bool active_in_scene;
        bool is_update_active;
    };

}