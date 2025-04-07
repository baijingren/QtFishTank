//
// Created by baijingren on 25-4-3.
//
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <mutex>
#include <cstring>

class Logger {
public:
	enum class Level { INFO, WARNING, ERROR };

	Logger(const char* file, int line, Level level)
			: file_(file), line_(line), level_(level) {
		auto now = std::chrono::system_clock::now();
		auto time_t_now = std::chrono::system_clock::to_time_t(now);
		tm local_time = *localtime(&time_t_now);

		char time_str[20];
		strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &local_time);
		oss_ << "[" << time_str << "]";
	}

	~Logger() {
		switch (level_) {
			case Level::INFO:    oss_ << " [INFO] "; break;
			case Level::WARNING: oss_ << " [WARN] "; break;
			case Level::ERROR:   oss_ << " [ERROR] "; break;
		}

		const char* base_name = strrchr(file_, '/');
		if (!base_name) base_name = file_; else base_name++;
		oss_ << "[" << base_name << ":" << line_ << "] ";

		std::lock_guard<std::mutex> lock(mutex_);
		std::cout << oss_.str() << std::endl;
		if (fileStream_.is_open()) {
			fileStream_ << oss_.str() << std::endl;
		}
	}

	template<typename T>
	Logger& operator<<(const T& msg) {
		oss_ << msg;
		return *this;
	}

	static void setLogFile(const std::string& filename) {
		std::lock_guard<std::mutex> lock(mutex_);
		if (fileStream_.is_open()) {
			fileStream_.close();
		}
		fileStream_.open(filename, std::ios::app);
		if (!fileStream_) {
			std::cerr << "Failed to open log file: " << filename << std::endl;
		}
	}

private:
	std::ostringstream oss_;
	const char* file_;
	int line_;
	Level level_;
	inline static std::mutex mutex_;
	inline static std::ofstream fileStream_;
};

#define LOG_INFO    Logger(__FILE__, __LINE__, Logger::Level::INFO)
#define LOG_WARNING Logger(__FILE__, __LINE__, Logger::Level::WARNING)
#define LOG_ERROR   Logger(__FILE__, __LINE__, Logger::Level::ERROR)