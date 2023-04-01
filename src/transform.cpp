#include "transform.hpp"

Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale):
	m_pos(pos), m_rot(rot), m_scale(scale) { }

glm::mat4 Transform::GetModel() const
{
	glm::mat4 posMat = glm::translate(m_pos);
	glm::mat4 rotXMat = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
	glm::mat4 rotYMat = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZMat = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));
	glm::mat4 scaleMat = glm::scale(m_scale);

	glm::mat4 rotMat = rotZMat * rotYMat * rotXMat;

	return posMat * rotMat * scaleMat;
}

