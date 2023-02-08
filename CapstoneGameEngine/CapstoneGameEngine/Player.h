//
//  PlayerBody.h
//  DemoAI
//
//  Original version Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <SDL.h>
#include "Actor.h"
#include "TransformComponent.h"
#include "SceneManager.h"

class Player : public Actor
{
protected:
   class SceneManager* game;
    
public:
    Player() : Actor{ nullptr }, game(nullptr)
    {}

    Player(
        Ref<Component> parent_,
        Vec3 pos_, Quaternion orientation_,
        Vec3 vel_,
        Vec3 accel_,
        float mass_,
        float radius_,
        float rotation_,
        float angular_,
        float maxSpeed_,
        float maxAcceleration_,
        float maxRotation_,
        float maxAngular_,
        SceneManager* game_
    ) : Actor{ parent_ }, game(game_)
    {
        this->AddComponent<TransformComponent>(parent_, pos_, orientation_, vel_, accel_, mass_
            , radius_
            , rotation_
            , angular_
            , maxSpeed_
            , maxAcceleration_
            , maxRotation_
            , maxAngular_);
    }

    bool OnCreate();
    void Render();
    void HandleEvents(const SDL_Event& event);
    void Update(float deltaTime);
    void resetToOrigin();

};

#endif /* PLAYER_H */

