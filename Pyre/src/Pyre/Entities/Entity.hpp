#pragma once
#include "Pyre/Core/Base.hpp"
#include <type_traits>
#include <vector>

namespace Pyre {

    class Component {
    public:
        friend class Entity;

        Component() = default;
        virtual ~Component() = default;

        virtual void Tick(float dt) {}
        virtual void OnConstruct() {}
        virtual void OnPlay() {}

        virtual const char* GetName() const = 0;
        virtual uint32_t GetComponentID() const = 0;

        Entity* GetParent()             { return m_Parent; }
        const Entity* GetParent() const { return m_Parent; }

        void SetTickEnabled(bool enabled) { m_TickEnabled = enabled; }
        bool GetTickEnabled() const       { return m_TickEnabled; }

    private:
        Entity* m_Parent;
        bool m_TickEnabled = false;
    };

#define PYRE_GEN_COMPONENT(name) \
    static uint32_t GetStaticID()            { return Hash32_FNV1a(#name); } \
    uint32_t GetComponentID() const override { return GetStaticID(); } \
    const char* GetName() const override     { return #name; }

    class Entity {
    public:
        Entity() = default;
        virtual ~Entity() = default;

        virtual void Tick(float dt) {
            for (auto& component : m_Components) {
                if (component->GetTickEnabled()) {
                    component->Tick(dt);
                }
            }
        }

        template<typename T, typename... Args, std::enable_if_t<std::is_base_of<Component, T>::value, int> = 0>
        T* AddComponent(Args... args) {
            m_Components.push_back(MakeScope<T>(args...));
            T* component = static_cast<T*>(m_Components.back().get());
            component->m_Parent = this;
            component->OnConstruct();
            return component;
        }

        void RemoveComponent(Component* component) {
            for (size_t i = 0; i < m_Components.size(); i++) {
                if (m_Components[i].get() == component) {
                    m_Components.erase(m_Components.begin() + i);
                    return;
                }
            }
            PYRE_CORE_WARN("Removable component not owned by this entity!");
        }

        template<typename T, std::enable_if_t<std::is_base_of<Component, T>::value, int> = 0>
        bool HasComponent() {
            for (const auto& component : m_Components) {
                if (component->GetComponentID() == T::GetStaticID()) {
                    return true;
                }
            }
            return false;
        }

        template<typename T, std::enable_if_t<std::is_base_of<Component, T>::value, int> = 0>
        void RequireComponent() {
            if (!HasComponent<T>()) {
                PYRE_CORE_WARN("Adding missing '{}' component!", T::GetName());
                AddComponent<T>();
            }
        }

    protected:
        using Super = Entity;

    private:
        std::vector<Scope<Component>> m_Components;
    };

}