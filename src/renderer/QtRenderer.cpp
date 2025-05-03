//
// Created by Jingren Bai on 25-5-1.
//

#include "QtRenderer.h"
#include "Log.cpp"
#include <QPainter>

/**
 * @brief 构造一个新的 QtRenderer 对象
 *
 * @param parent 指向父级 QWidget 的指针，用于确定渲染器的依附窗口
 */
QtRenderer::QtRenderer(QWidget *parent) {
	/* 斜向45度的相机配置
	// 初始化默认相机配置
	camera = Camera();
	// 设置相机观察目标点为原点
	camera.setCameraTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	// 设置相机正上方向为(-1/sqrt(2),1,-1/sqrt(2))
	camera.setCameraUp(glm::vec3(-1/sqrt(2), 1.0f, -1/sqrt(2)));
	// 配置投影矩阵参数：80度视野角，800/600宽高比，0.1-100深度范围
	camera.setProjectionMatrix(80.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	// 设置视图矩阵参数：相机位置(1,1,1)，目标点(0,0,0)，上方向(-1/sqrt(2),1,-1/sqrt(2))
	camera.setViewMatrix(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1/sqrt(2), 1.0f, -1/sqrt(2)));
	 */
	/*
	// 创建一个默认的相机配置
	camera = Camera();
	camera.setCameraTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	camera.setCameraUp(glm::vec3(0.0f, 1.0f, 0.0f));
	camera.setProjectionMatrix(80.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	camera.setViewMatrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	 */
	camera = Camera();
	camera.setCameraTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	camera.setCameraUp(glm::vec3(-1.0f, -10.0f, -1.0f));
	camera.setProjectionMatrix(80.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	camera.setViewMatrix(glm::vec3(50.0f, 10.0f, 50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, -10.0f, -1.0f));
	init();
	// 创建定时器
	simulationTimer = new QTimer(this);
	connect(simulationTimer, &QTimer::timeout, this, &QtRenderer::updateSimulation);
	simulationTimer->start(16); // 每 16ms 更新一次（约 60 FPS）
}

void QtRenderer::updateSimulation() {
	simulator.runPBF(); // 执行一次模拟步进
	particles = simulator.getParticles(); // 获取最新粒子数据
	update(); // 触发重绘
}


QPointF QtRenderer::projectToScreen(const glm::vec3 &worldPos, Camera camera, int screen_x, int screen_y) {
	// Step 1: 转换到裁剪空间
	glm::vec4 clipPos = camera.getProjectionMatrix() * camera.getViewMatrix() * glm::vec4(worldPos, 1.0f);

	// Step 2: 检查 clipPos.w 是否为正数（点是否在摄像机前方）
	if (clipPos.w <= 0.0f) {
		return QPointF(-1.0, -1.0); // 无效坐标
	}

	// Step 3: 转换到 NDC 坐标
	glm::vec3 ndcPos = glm::vec3(clipPos) / clipPos.w;

	// Step 4: 检查 NDC 坐标是否在 [-1, 1] 范围内（视锥体内部）
	if (ndcPos.x < -1.0f || ndcPos.x > 1.0f ||
		ndcPos.y < -1.0f || ndcPos.y > 1.0f) {
		return QPointF(-1.0, -1.0); // 无效坐标
	}

	// Step 5: 转换到屏幕坐标
	float screenX = (ndcPos.x + 1.0f) * 0.5f * screen_x;
	float screenY = (1.0f - ndcPos.y) * 0.5f * screen_y;

	return QPointF(screenX, screenY);
}

bool QtRenderer::projectToScreen(const glm::vec3 &worldPos, Camera camera,
								 int screen_x, int screen_y, QPointF &out) {
	glm::vec4 clipPos = camera.getProjectionMatrix() * camera.getViewMatrix() * glm::vec4(worldPos, 1.0f);
	if (clipPos.w <= 0.0f) return false;

	glm::vec3 ndcPos = glm::vec3(clipPos) / clipPos.w;

	if (ndcPos.x < -1.0f || ndcPos.x > 1.0f ||
		ndcPos.y < -1.0f || ndcPos.y > 1.0f) return false;

	float screenX = (ndcPos.x + 1.0f) * 0.5f * screen_x;
	float screenY = (1.0f - ndcPos.y) * 0.5f * screen_y;

	out = QPointF(screenX, screenY);
	return true;
}
void QtRenderer::init(){
	particles.clear();
	simulator.init(particleNum);

}
void QtRenderer::paintEvent(QPaintEvent *event) {
#ifdef DEBUG
	/*
	auto particlesCache = simulator.getParticles();
	for (const auto& p : particlesCache) {
		LOG_INFO << p.pos.x << " " << p.pos.y << " " << p.pos.z;
	}
	 */
#endif
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// 设置背景颜色
	painter.fillRect(rect(), Qt::white);

	// 获取窗口尺寸
	int w = width();
	int h = height();

	// 可选：按距离排序，确保从后到前绘制
	auto camPos = camera.getCamPos();
	std::vector<std::pair<float, Particle>> sortedParticles;
	for (const auto& p : particles) {
		float dist = glm::length(p.pos - camPos);
		sortedParticles.emplace_back(dist, p);
	}
	std::sort(sortedParticles.begin(), sortedParticles.end(), [](const auto& a, const auto& b){
		return a.first < b.first;
	});

	// 绘制粒子
	painter.setPen(QColor(102, 204, 255)); // #66ccff
	painter.setBrush(QColor(102, 204, 255));
	for (const auto& [dist, p] : sortedParticles) {
		QPointF pos = projectToScreen(p.pos, camera, w, h);
		if(pos == QPointF(-1.0, -1.0)){
			continue;
		}
//		painter.drawPoint(pos);
		// 或者绘制为圆形
		 painter.drawEllipse(pos, 3, 3);
	}
}
