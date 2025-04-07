//
// Created by baijingren on 25-4-3.
//
#include "Log.cpp"
#include <QtTest/QtTest>

class LoggerTest : public QObject{
	Q_OBJECT
private slots:
	void initTestCase();
	void testLogInfo();
	void testLogWarn();
	void testLogErro();
};

QTEST_MAIN(LoggerTest)
#include "LoggerTest.moc"

void LoggerTest::initTestCase() {
	Logger::setLogFile("Log.txt");
}

void LoggerTest::testLogInfo() {
	LOG_INFO << "Test info log";
	QVERIFY(true);
}
void LoggerTest::testLogWarn() {
	LOG_WARNING << "Test warn log";
	QVERIFY(true);
}
void LoggerTest::testLogErro() {
	LOG_ERROR << "Test error log";
	QVERIFY(true);
}