/*************************************************************************
> File Name: TargetSystem.h
> Project Name: Cubby
> Author: Eun-Jun Jang (SilverJun)
> Purpose: For Target Contents. This Class manages everything about target
> Created Time: 2017/09/23
> Copyright (c) 2016, Chan-Ho Chris Ohk
*************************************************************************/

#ifndef CUBBY_TARGET_SYSTEM_H
#define CUBBY_TARGET_SYSTEM_H

#include "Target.h"

class Projectile;
class ProjectileManager;
class Renderer;

class TargetSystem
{
public:
	/// Constructor, Destructor
	TargetSystem(Renderer* pRenderer, ProjectileManager* pProjectileManager);
	~TargetSystem();
	
	/// Updating
	void Update(float dt);
	void CalculateWorldTransformMatrix();
	void Render();

private:
	Renderer* m_pRenderer;
	ProjectileManager* m_pProjectileManager;

	Target* m_pTarget;
};

#endif