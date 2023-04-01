#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
	public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

	glm::mat4 GetViewProjection() const;

	protected:
	private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};

#endif
