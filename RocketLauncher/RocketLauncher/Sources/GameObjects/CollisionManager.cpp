#include "CollisionManager.h"

void CollisionManager::addObj(HitBox* hitBox)
{
    m_listObj.push_back(hitBox);
}

bool CollisionManager::checkCollision(HitBox* a, HitBox* b)
{
    return a->getGlobalBounds().intersects(b->getGlobalBounds());
}

void CollisionManager::Update()
{
    for (auto a : m_listObj) {
        if (a->isBlocked() == true) continue;

        for (auto b : m_listObj) {
            if (b->isBlocked() == true) continue;

            if (a->getTag() == b->getTag()) continue;

            if (!checkCollision(a, b)) continue;

            if (a->getTag() == ROCKET && b->getTag() == BLOCK) {
                a->setBlocked(true);
                      b->setBlocked(true);
            }
        }
    }
}
