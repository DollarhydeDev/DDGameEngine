#pragma once

class DDGameObject;

class DDComponent
{
private:
    int _componentID;
    int _ownerID;
    DDGameObject* _owner;
    bool _enabled;

public:
    DDComponent();
    virtual ~DDComponent() = default;

    int GetComponentID() const;
    int GetOwnerID() const;
    DDGameObject* GetOwner() const;

    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    void SetComponentID(int componentID);
    void SetOwner(DDGameObject* owner);

    virtual void Start();
    virtual void Update(float deltaTime);
};