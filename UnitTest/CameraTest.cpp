#include <QtTest/QtTest>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include "../src/renderer/Camera.h" // 假设 Camera 类定义在此头文件

class TestCamera : public QObject
{
Q_OBJECT

private:
	// 比较两个矩阵是否在误差范围内相等
	void compareMatrices(const glm::mat4& result, const glm::mat4& expected, float epsilon = 1e-5f) {
		for (int col = 0; col < 4; ++col) {
			for (int row = 0; row < 4; ++row) {
				QVERIFY(std::abs(result[col][row] - expected[col][row]) < epsilon);
			}
		}
	}

private slots:
	// 测试正常参数情况
	void testNormalCase() {
		Camera camera;
		float fov = 60.0f;
		float aspect = 4.0f / 3.0f;
		float near = 0.1f;
		float far = 100.0f;

		camera.setProjectionMatrix(fov, aspect, near, far);

		// 使用 GLM 的 perspective 函数生成预期矩阵
		glm::mat4 expected = glm::perspective(glm::radians(fov), aspect, near, far);
		compareMatrices(camera.getProjectionMatrix(), expected);
	}

	// 测试 near 接近 0 的情况
	void testEdgeCase_NearZero() {
		Camera camera;
		float fov = 45.0f;
		float aspect = 1.0f;
		float near = 0.0001f;
		float far = 1000.0f;

		camera.setProjectionMatrix(fov, aspect, near, far);

		glm::mat4 expected = glm::perspective(glm::radians(fov), aspect, near, far);
		compareMatrices(camera.getProjectionMatrix(), expected);
	}

	// 测试 far 远大于 near 的情况
	void testEdgeCase_FarLarge() {
		Camera camera;
		float fov = 90.0f;
		float aspect = 2.0f;
		float near = 1.0f;
		float far = 1e6f;

		camera.setProjectionMatrix(fov, aspect, near, far);

		glm::mat4 expected = glm::perspective(glm::radians(fov), aspect, near, far);
		compareMatrices(camera.getProjectionMatrix(), expected);
	}

	// 测试 near >= far 的异常情况（函数不处理，验证无崩溃）
	void testInvalid_NearGreaterFar() {
		Camera camera;
		// 不抛出异常，但生成的矩阵可能无效
		camera.setProjectionMatrix(60.0f, 1.0f, 10.0f, 1.0f);
		// 验证矩阵元素无 NaN 或无穷大
		glm::mat4 projectionMatrix = camera.getProjectionMatrix();
		for (int col = 0; col < 4; ++col) {
			for (int row = 0; row < 4; ++row) {
				QVERIFY(!std::isnan(projectionMatrix[col][row]));
				QVERIFY(!std::isinf(projectionMatrix[col][row]));
			}
		}
	}

	// 测试负数 fov 或 aspect 的情况（函数不处理，验证无崩溃）
	void testInvalid_NegativeFovOrAspect() {
		Camera camera;
		// 负数 fov
		camera.setProjectionMatrix(-60.0f, 1.0f, 0.1f, 100.0f);
		// 负数 aspect
		camera.setProjectionMatrix(60.0f, -1.0f, 0.1f, 100.0f);
		// 验证矩阵元素无 NaN 或无穷大
		glm::mat4 projectionMatrix = camera.getProjectionMatrix();
		for (int col = 0; col < 4; ++col) {
			for (int row = 0; row < 4; ++row) {
				QVERIFY(!std::isnan(projectionMatrix[col][row]));
				QVERIFY(!std::isinf(projectionMatrix[col][row]));
			}
		}
	}
};

QTEST_MAIN(TestCamera)
#include "CameraTest.moc"
