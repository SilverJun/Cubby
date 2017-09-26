/*************************************************************************
> File Name: Target.h
> Project Name: Cubby
> Author: Eun-Jun Jang (SilverJun)
> Purpose: Target
> Created Time: 2017/09/25
> Copyright (c) 2016, Chan-Ho Chris Ohk
*************************************************************************/

#ifndef CUBBY_TARGET_H
#define CUBBY_TARGET_H

#include "Models/VoxelObject.h"
#include "Projectile/Projectile.h"

class Target
{
public:
	Target(Renderer* pRenderer);
	~Target();

	void CalculateWorldTransformMatrix();
	bool IsHitedTarget(Projectile* pProjectile);

	void Render();

private:
	Renderer* m_pRenderer;

	VoxelObject* m_pTargetObject;
	Matrix4 m_worldMatrix;
	glm::vec3 m_position;
	glm::vec3 m_center;
	glm::vec3 m_rotation;

	// Projectile hitbox
	float m_projectileHitboxRadius;
	glm::vec3 m_projectileHitboxCenterOffset;
};

#endif