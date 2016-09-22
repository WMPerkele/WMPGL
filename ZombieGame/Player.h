#pragma once

#include "Human.h"
#include <WMPEngine/InputManager.h>
#include <WMPEngine/Camera2D.h>
#include "Bullet.h"

class Gun;

class Player : public Human
{
public:
    Player();
    ~Player();

    void init(float speed, glm::vec2 pos, WMPEngine::InputManager* inputManager, WMPEngine::Camera2D* camera, std::vector<Bullet>* bullets);

    void addGun(Gun* gun);

    void update(const std::vector<std::string>& levelData,
                std::vector<Human*>& humans,
                std::vector<Zombie*>& zombies) override;
private:
    WMPEngine::InputManager* _inputManager;

    std::vector<Gun*> _guns;
    int _currentGunIndex;

    WMPEngine::Camera2D* _camera;
    std::vector<Bullet>* _bullets;

};

