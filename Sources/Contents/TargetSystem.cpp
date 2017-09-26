#include "TargetSystem.h"
#include "Projectile/Projectile.h"
#include "Projectile/ProjectileManager.h"

TargetSystem::TargetSystem(Renderer* pRenderer, ProjectileManager* pProjectileManager) : m_pRenderer(pRenderer), m_pProjectileManager(pProjectileManager)
{
	m_pTarget = new Target(m_pRenderer);
}

TargetSystem::~TargetSystem()
{
	delete m_pTarget;
}

void TargetSystem::Update(float dt)
{
	// Check projectile hits
	for (int i = 0; i < m_pProjectileManager->GetNumProjectiles(); ++i)
	{
		Projectile* pProjectile = m_pProjectileManager->GetProjectile(i);

		if (pProjectile != nullptr && pProjectile->GetErase() == false && pProjectile->CanAttackPlayer() == false && pProjectile->CanAttackEnemies() == true)
		{
			// pProjectile Collision Check.
			if (m_pTarget->IsHitedTarget(pProjectile))
			{
				pProjectile->Explode();
				// Target 위치 재생성
			}
		}
	}
}

void TargetSystem::CalculateWorldTransformMatrix()
{
	m_pTarget->CalculateWorldTransformMatrix();
}


void TargetSystem::Render()
{
	m_pTarget->Render();
}
