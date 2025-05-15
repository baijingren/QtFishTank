#include <QtTest>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "../src/renderer/Camera.h"
#include "../src/Log.cpp"

class TestCameraSetViewMatrix : public QObject
{
    Q_OBJECT

private:
    Camera camera;

    void assertMat4Equal(const glm::mat4& expected, const glm::mat4& actual, qreal epsilon = 1e-5f) {
		LOG_INFO << "Expected:\n" << expected << "\nActual:\n" << actual << "\n";
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                QVERIFY(qAbs(expected[i][j] - actual[i][j]) < epsilon);
            }
        }
    }

private slots:
    void init() {
        // 初始化 Camera 成员变量
    }

    void cleanup() {
        // 清理资源
    }

    void testCase_TC01() {
        // TC01: 相机朝向-z，up=y
        glm::vec3 camPos(0.0f, 0.0f, 0.0f);
        glm::vec3 target(0.0f, 0.0f, -1.0f);
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        camera.setViewMatrix(camPos, target, up);
        glm::mat4 view = camera.getViewMatrix();

        glm::mat4 expected = glm::mat4(1.0f); // Identity matrix
        assertMat4Equal(expected, view);
    }

    void testCase_TC02() {
        // TC02: 相机从(0,0,3)看向原点
        glm::vec3 camPos(0.0f, 0.0f, 3.0f);
        glm::vec3 target(0.0f, 0.0f, 0.0f);
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        camera.setViewMatrix(camPos, target, up);
        glm::mat4 view = camera.getViewMatrix();

        glm::mat4 expected = glm::lookAt(camPos, target, up);
        assertMat4Equal(expected, view);
    }

    void testCase_TC03() {
        // TC03: 相机位置与目标点相同
        glm::vec3 camPos(0.0f, 0.0f, 0.0f);
        glm::vec3 target(0.0f, 0.0f, 0.0f);
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        camera.setViewMatrix(camPos, target, up);
        glm::mat4 view = camera.getViewMatrix();

        // lookAt 为零向量，可能产生 NaN 或异常矩阵
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                QVERIFY(!std::isnan(view[i][j]));
            }
        }
    }

    void testCase_TC04() {
        // TC04: cameraUp 与 lookAt 平行
        glm::vec3 camPos(0.0f, 0.0f, 0.0f);
        glm::vec3 target(0.0f, 0.0f, 1.0f);
        glm::vec3 up(0.0f, 0.0f, 1.0f); // 与 lookAt 方向一致

        camera.setViewMatrix(camPos, target, up);
        glm::mat4 view = camera.getViewMatrix();

        // 应该自动修正 newUp
        QVERIFY(view[0][0] != 0 || view[0][1] != 0 || view[0][2] != 0);
    }

    void testCase_TC05() {
        // TC05: 自定义复杂视角
        glm::vec3 camPos(1.0f, 2.0f, 3.0f);
        glm::vec3 target(4.0f, 5.0f, 6.0f);
        glm::vec3 up(-1.0f, 1.0f, 0.0f);

        camera.setViewMatrix(camPos, target, up);
        glm::mat4 view = camera.getViewMatrix();

        glm::mat4 expected = glm::lookAt(camPos, target, up);
        assertMat4Equal(expected, view);
    }
};

QTEST_APPLESS_MAIN(TestCameraSetViewMatrix)

#include "TestCameraSetViewMatrix.moc"
