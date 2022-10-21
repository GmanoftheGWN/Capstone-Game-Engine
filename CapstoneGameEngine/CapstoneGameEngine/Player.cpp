//
//  PlayerBody.cpp
//  DemoAI
//
//  Original version Created by Gail Harris on 2021-Dec-23.
//

#include <SDL.h>
#include "Player.h"

bool Player::OnCreate()
{
    Actor::OnCreate();
    return true;
}

void Player::Render()
{
    
}

void Player::HandleEvents(const SDL_Event& event)
{
    Ref<TransformComponent> transform = this->GetComponent<TransformComponent>();
    Vec3 vel = transform->getVel();
    Vec3 accel = transform->getAccel();
    // if key pressed, set velocity or acceleration

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.scancode)
        {
            // This section demonstrates using velocity for player movement
            //
            // Need to always normalize speed, otherwise having two keys down
            // results in velocity magnitude being sqrt(2) x maxSpeed.
            // However, this is being done in Update()
        case SDL_SCANCODE_W:
           vel.y = transform->getMaxSpeed() * 1.0f;
            break;
        case SDL_SCANCODE_A:
            vel.x = transform->getMaxSpeed() * -1.0f;
            break;
        case SDL_SCANCODE_S:
            vel.y = transform->getMaxSpeed() * -1.0f;
            break;
        case SDL_SCANCODE_D:
            vel.x = transform->getMaxSpeed() * 1.0f;
            break;

            // This section is for seeing how to use acceleration rather than velocity
            // for player movement.
            // Note: look at Update() to see that velocity is clipped, since
            // continuous acceleration means continually increasing velocity.
        case SDL_SCANCODE_DOWN:
            accel.y = transform->getMaxAcceleration() * -1.0f;
            break;
        case SDL_SCANCODE_UP:
            accel.y = transform->getMaxAcceleration() * 1.0f;
            break;
        case SDL_SCANCODE_LEFT:
            accel.x = transform->getMaxAcceleration() * -1.0f;
            break;
        case SDL_SCANCODE_RIGHT:
            accel.x = transform->getMaxAcceleration() * 1.0f;
            break;
        default:
            break;
        }
    }

    // if key is released, stop applying movement

    if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch (event.key.keysym.scancode)
        {
            // This section demonstrates using velocity for player movement
            //
            // Need to always normalize velocity, otherwise if player
            // releases one of two pressed keys, then speed remains at sqrt(0.5) of maxSpeed
        case SDL_SCANCODE_W:
            vel.y = 0.0f;
            if (VMath::mag(vel) > VERY_SMALL) vel = VMath::normalize(vel) * transform->getMaxSpeed();
            break;
        case SDL_SCANCODE_A:
            vel.x = -0.0f;
            if (VMath::mag(vel) > VERY_SMALL) vel = VMath::normalize(vel) * transform->getMaxSpeed();
            break;
        case SDL_SCANCODE_S:
            vel.y = -0.0f;
            if (VMath::mag(vel) > VERY_SMALL) vel = VMath::normalize(vel) * transform->getMaxSpeed();
            break;
        case SDL_SCANCODE_D:
            vel.x = 0.0f;
            if (VMath::mag(vel) > VERY_SMALL) vel = VMath::normalize(vel) * transform->getMaxSpeed();
            break;

            // This section is for seeing how to use acceleration rather than velocity
            // for player movement.
        case SDL_SCANCODE_DOWN:
            accel.y = 0.0;
            break;
        case SDL_SCANCODE_UP:
            accel.y = 0.0;
            break;
        case SDL_SCANCODE_LEFT:
            accel.x = 0.0;
            break;
        case SDL_SCANCODE_RIGHT:
            accel.x = 0.0;
            break;
        default:
            break;
        }
    }
    transform->SetVel(vel);
    transform->setAccel(accel);
}

void Player::Update(float deltaTime)
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion
    this->GetComponent<TransformComponent>()->Update(deltaTime);

    //// This will ensure player body stops at edges
    //float height, width;
    //height = game->getSceneHeight();
    //width = game->getSceneWidth();

    //if (pos.x < radius)
    //{
    //    pos.x = radius;
    //    vel.x = 0.0f;
    //}
    //if (pos.y < radius)
    //{
    //    pos.y = radius;
    //    vel.y = 0.0f;
    //}
    //if (pos.x > width - radius)
    //{
    //    pos.x = width - radius;
    //    vel.x = 0.0f;
    //}
    //if (pos.y > height - radius)
    //{
    //    pos.y = height - radius;
    //    vel.y = 0.0f;
    //}
}

void Player::resetToOrigin()
{
    //pos = Vec3(0.0f + radius, 0.0f + radius, 0.0f);
}