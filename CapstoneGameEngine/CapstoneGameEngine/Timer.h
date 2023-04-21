#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>

#include <chrono>
#include <unordered_map>

class Timer {
public:
	Timer();
	~Timer();

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTicks() const;
	static void SetSingleEvent(Uint32 interval,void* param);
private:	
	unsigned int prevTicks;
	unsigned int currentTicks;
	static unsigned int singleEventID;
	static Uint32 callBackFuncion(Uint32 interval, void* singleEventParam);
};

class ProfilingTimer {
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;

	std::unordered_map<const char*, float>* UpdateProfiling;

public:
	ProfilingTimer(const char* name, std::unordered_map<const char*, float>* UpdateProfiling_) : m_Name(name), m_Stopped(false) {
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
		UpdateProfiling = UpdateProfiling_;
	}
	~ProfilingTimer() {
		if (!m_Stopped) {
			Stop();
		}
	}

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.0001f;
		UpdateProfiling->at(m_Name) += duration;
	}
};

#endif
