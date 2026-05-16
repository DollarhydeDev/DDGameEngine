#pragma once

class DDGameWorld;

class DDMovementSystem
{
public:
    DDMovementSystem();
    ~DDMovementSystem();

    void Update(DDGameWorld* world, float deltaTime);
};