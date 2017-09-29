#include "Target.h"
#include "Maths/3DMaths.h"

Target::Target(Renderer* pRenderer) : m_pRenderer(pRenderer)
{
	m_pTargetObject = new VoxelObject();
	m_pTargetObject->SetRenderer(m_pRenderer);
	m_pTargetObject->LoadObject("Resources/gamedata/models/Contents/Target.qb", false);

	m_position = glm::vec3(37.0f, 2.8f, 27.0f);
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_center = m_pTargetObject->GetCenter();
	
	m_projectileHitboxRadius = 0.5f;

	m_projectileHitboxCenterOffset = glm::vec3(0.0f, 0.0f, 0.0f);
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
	glm::vec3 projectileHitboxCenter = m_position + m_projectileHitboxCenterOffset;

	glm::vec3 projectilePos = pProjectile->GetPosition();
	glm::vec2 toProjectile = glm::vec2(projectileHitboxCenter.x, projectileHitboxCenter.z) - glm::vec2(projectilePos.x, projectilePos.z);
	glm::vec2 inCircle = glm::vec2(projectileHitboxCenter.x, projectileHitboxCenter.y) - glm::vec2(projectilePos.x, projectilePos.y);
	
	printf("projectile x : %.2f, y : %.2f, z : %.2f\n", projectilePos.x, projectilePos.y, projectilePos.z);
	printf("projectileHitboxCenter x : %.2f, y : %.2f, z : %.2f\n", projectileHitboxCenter.x, projectileHitboxCenter.y, projectileHitboxCenter.z);
	printf("inCircleLength : %.2f\n", length(inCircle));

	return length(toProjectile) <= 2.0f && length(inCircle) <= m_projectileHitboxRadius;
}

void Target::Render()
{
	m_pRenderer->PushMatrix();
	m_pRenderer->MultiplyWorldMatrix(m_worldMatrix);
	m_pRenderer->ScaleWorldMatrix(0.08f, 0.08f, 0.08f);
	m_pRenderer->RotateWorldMatrix(m_rotation.x, m_rotation.y, m_rotation.z);
	m_pTargetObject->Render(false, false, false, Color());
	m_pRenderer->PopMatrix();
}

void Target::SetPosition(glm::vec3 worldPosition)
{
	m_position = worldPosition;
}
