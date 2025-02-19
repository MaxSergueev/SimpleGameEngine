#pragma once

class Actor;

class Component
{
protected:
    bool mIsActive;
    Actor* mOwner;
    int mUpdateOrder;
public:
    Component() = delete;
    Component(Actor* pOwner, int pUpdateOrder = 100);
    virtual ~Component();
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    
    virtual void OnStart();
    virtual void Update();
    virtual void OnEnd();
    int GetUpdateOrder(){return mUpdateOrder;}
};
