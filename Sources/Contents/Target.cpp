#include "Target.h"
#include "Maths/3DMaths.h"

#include <stdio.h>

Target::Target(Renderer* pRenderer) : m_pRenderer(pRenderer)
{
	m_pTargetObject = new VoxelObject();
	m_pTargetObject->SetRenderer(m_pRenderer);
	m_pTargetObject->LoadObject("Resources/gamedata/models/Contents/Target.qb", false);

	m_position = glm::vec3(37.0f, 2.8f, 27.0f);
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_center = m_pTargetObject->GetCenter();
	
	m_projectileHitboxRadius = 0.6f;

	m_projectileHitboxCenterOffset = glm::vec3(0.0f, 0.3f, 0.2f);
	m_projectileHitboxXLength = m_projectileHitboxRadius;
	m_projectileHitboxYLength = m_projectileHitboxRadius;
	m_projectileHitboxZLength = 0.4f;
}

Target::~Target()
{
	delete m_pTargetObject;
}

void Target::CalculateWorldTransformMatrix()
{
	m_worldMatrix.LoadIdentity();
	m_worldMatrix.SetTranslation(m_position);
}


bool Target::IsHitedTarget(Projectile* pProjectile)
{
	Matrix4 rotationMatrix;
	rotationMatrix.SetYRotation(DegreeToRadian(m_rotation.y));
	glm::vec3 projectileHitboxCenter = m_projectileHitboxCenterOffset + m_position;

	Plane3D planes[6];
	planes[0] = Plane3D(rotationMatrix * glm::vec3(-1.0f, 0.0f, 0.0f), projectileHitboxCenter + (rotationMatrix * glm::vec3(m_projectileHitboxXLength, 0.0f, 0.0f)));
	planes[1] = Plane3D(rotationMatrix * glm::vec3(1.0f, 0.0f, 0.0f), projectileHitboxCenter + (rotationMatrix * glm::vec3(-m_projectileHitboxXLength, 0.0f, 0.0f)));
	planes[2] = Plane3D(rotationMatrix * glm::vec3(0.0f, -1.0f, 0.0f), projectileHitboxCenter + (rotationMatrix * glm::vec3(0.0f, m_projectileHitboxYLength, 0.0f)));
	planes[3] = Plane3D(rotationMatrix * glm::vec3(0.0f, 1.0f, 0.0f), projectileHitboxCenter + (rotationMatrix * glm::vec3(0.0f, -m_projectileHitboxYLength, 0.0f)));
	planes[4] = Plane3D(rotationMatrix * glm::vec3(0.0f, 0.0f, -1.0f), projectileHitboxCenter + (rotationMatrix * glm::vec3(0.0f, 0.0f, m_projectileHitboxZLength)));
	planes[5] = Plane3D(rotationMatrix * glm::vec3(0.0f, 0.0f, 1.0f), projectileHitboxCenter + (rotationMatrix * glm::vec3(0.0f, 0.0f, -m_projectileHitboxZLength)));

	bool hitByProjectile = false;
	float distance;
	int inside = 0;

	for (int i = 0; i < 6; ++i)
	{
		distance = planes[i].GetPointDistance(pProjectile->GetCenter());

		if (distance < -pProjectile->GetRadius())
		{
			// Outside...
		}
		else if (distance < pProjectile->GetRadius())
		{
			// Intersecting..
			inside++;
		}
		else
		{
			// Inside...
			inside++;
		}
	}

	if (inside == 6)
	{
		hitByProjectile = true;
	}
	
	return hitByProjectile;
}

void Target::Render()
{
	m_pRenderer->PushMatrix();
	m_pRenderer->MultiplyWorldMatrix(m_worldMatrix);
	m_pRenderer->ScaleWorldMatrix(0.08f, 0.08f, 0.08f);
	m_pRenderer->RotateWorldMatrix(m_rotation.x, m_rotation.y, m_rotation.z);
	m_pTargetObject->Render(false, false, false, Color());
	m_pRenderer->PopMatrix();

	m_pRenderer->PushMatrix();
	float length = m_projectileHitboxXLength;
	float height = m_projectileHitboxYLength;
	float width = m_projectileHitboxZLength;

	m_pRenderer->SetRenderMode(RenderMode::WIREFRAME);
	m_pRenderer->SetCullMode(CullMode::NOCULL);
	m_pRenderer->SetLineWidth(1.0f);

	m_pRenderer->MultiplyWorldMatrix(m_worldMatrix);
	m_pRenderer->RotateWorldMatrix(0.0f, m_rotation.y, 0.0f);
	m_pRenderer->TranslateWorldMatrix(m_projectileHitboxCenterOffset.x, m_projectileHitboxCenterOffset.y, m_projectileHitboxCenterOffset.z);

	m_pRenderer->EnableImmediateMode(ImmediateModePrimitive::QUADS);

	m_pRenderer->ImmediateColorAlpha(1.0f, 1.0f, 0.0f, 1.0f);
	m_pRenderer->ImmediateNormal(0.0f, 0.0f, -1.0f);
	m_pRenderer->ImmediateVertex(length, -height, -width);
	m_pRenderer->ImmediateVertex(-length, -height, -width);
	m_pRenderer->ImmediateVertex(-length, height, -width);
	m_pRenderer->ImmediateVertex(length, height, -width);

	m_pRenderer->ImmediateNormal(0.0f, 0.0f, 1.0f);
	m_pRenderer->ImmediateVertex(-length, -height, width);
	m_pRenderer->ImmediateVertex(length, -height, width);
	m_pRenderer->ImmediateVertex(length, height, width);
	m_pRenderer->ImmediateVertex(-length, height, width);

	m_pRenderer->ImmediateNormal(1.0f, 0.0f, 0.0f);
	m_pRenderer->ImmediateVertex(length, -height, width);
	m_pRenderer->ImmediateVertex(length, -height, -width);
	m_pRenderer->ImmediateVertex(length, height, -width);
	m_pRenderer->ImmediateVertex(length, height, width);

	m_pRenderer->ImmediateNormal(-1.0f, 0.0f, 0.0f);
	m_pRenderer->ImmediateVertex(-length, -height, -width);
	m_pRenderer->ImmediateVertex(-length, -height, width);
	m_pRenderer->ImmediateVertex(-length, height, width);
	m_pRenderer->ImmediateVertex(-length, height, -width);

	m_pRenderer->ImmediateNormal(0.0f, -1.0f, 0.0f);
	m_pRenderer->ImmediateVertex(-length, -height, -width);
	m_pRenderer->ImmediateVertex(length, -height, -width);
	m_pRenderer->ImmediateVertex(length, -height, width);
	m_pRenderer->ImmediateVertex(-length, -height, width);

	m_pRenderer->ImmediateNormal(0.0f, 1.0f, 0.0f);
	m_pRenderer->ImmediateVertex(length, height, -width);
	m_pRenderer->ImmediateVertex(-length, height, -width);
	m_pRenderer->ImmediateVertex(-length, height, width);
	m_pRenderer->ImmediateVertex(length, height, width);

	m_pRenderer->DisableImmediateMode();
	m_pRenderer->SetCullMode(CullMode::BACK);
	m_pRenderer->PopMatrix();
}

void Target::SetPosition(glm::vec3 worldPosition)
{
	m_position = worldPosition;
}
