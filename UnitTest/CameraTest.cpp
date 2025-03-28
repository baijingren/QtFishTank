//
// Created by baijingren on 25-3-27.
//
#include "renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <QtTest/QtTest>

class CameraTest : public QObject {
	Q_OBJECT
private slots:
	void testSetProjectionMatrix();
	void testSetViewMatrix();
};

QTEST_MAIN(CameraTest)
#include "CameraTest.moc"

glm::mat4 stdProjectionMatrix(float fov, float aspect, float near, float far) {
	glm::mat4 ortho, projection, proj;
	projection = glm::mat4(1.0f);
	proj = glm::mat4{
		near, 0.0f, 0.0f, 0.0f,
		0.0f, near, 0.0f, 0.0f,
		0.0f, 0.0f, near + far, -near * far,
		0.0f, 0.0f, 1.0f, 0.0f
	};
	float h = near * std::tan(fov / 2.0f) / 2;
	float w = h * aspect;
	float z = far - near;
	ortho = glm::mat4{
		2.0f / w, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / h, 0.0f, 0.0f,
		0.0f, 0.0f, 2.0 / z, -(far + near) / (far - near),
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return projection = ortho * proj * projection;
}
void CameraTest::testSetProjectionMatrix() {
	Camera camera;
	camera.setProjectionMatrix(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	glm::mat4 projectionMatrix = camera.getProjectionMatrix();
//	debug(projectionMatrix);
	glm::mat4 answer = stdProjectionMatrix(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
//	debug(answer);
	QVERIFY(projectionMatrix == answer);
}
	glm::mat4 stdViewMatrix(glm::vec3 m_camPos, glm::vec3 m_cameraTarget, glm::vec3 m_cameraUp) {
		// 1. 归一化上向量
		glm::vec3 newUp = glm::normalize(m_cameraUp);

		// 2. 计算观察方向（摄像机到目标）
		glm::vec3 lookAt = glm::normalize(m_cameraTarget - m_camPos);

		// 3. 计算右向量和修正后的上向量
		glm::vec3 right = glm::normalize(glm::cross(newUp, lookAt));
		newUp = glm::normalize(glm::cross(lookAt, right)); // 右手法则

		// 4. 构造旋转矩阵（对齐到摄像机坐标系）
		glm::mat4 rotation = glm::mat4(
				glm::vec4(right, 0.0f),   // 右向量
				glm::vec4(newUp, 0.0f),   // 修正后的上向量
				glm::vec4(-lookAt, 0.0f), // 观察方向对准 -Z 轴
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);

		// 5. 构造平移矩阵（位置取反）
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), -m_camPos);
		debug(translation);
		// 6. 组合视图矩阵：先平移，再旋转
		glm::mat4 viewMatrix = rotation * translation;

		// 7. 可选：清理负零（仅影响显示）
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (std::abs(viewMatrix[i][j]) < 1e-6f) {
					viewMatrix[i][j] = 0.0f;
				}
			}
		}
//		debug(viewMatrix);
		return viewMatrix;
	}
void CameraTest::testSetViewMatrix() {
	Camera camera;
	camera.setViewMatrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 viewMatrix = camera.getViewMatrix();
	glm::mat4 answer = stdViewMatrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//	debug(viewMatrix);
//	debug((glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
//	debug(answer);
	QVERIFY(viewMatrix == answer);
}