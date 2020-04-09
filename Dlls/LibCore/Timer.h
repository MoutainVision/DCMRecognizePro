#pragma once

#include<iostream>

#include<chrono>
using namespace std;
using namespace std::chrono;

namespace avs
{
	class Timer
	{
	public:
		Timer() : m_begin(high_resolution_clock::now())
		{
		}

		void reset()
		{
			m_begin = high_resolution_clock::now();
		}

		//默认输出秒
		double elapsed() const
		{
			return duration_cast<duration<double>>(high_resolution_clock::now() - m_begin).count();
		}

		//默认输出毫秒
		int64_t elapsed_millisec() const
		{
			return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
		}

		//微秒
		int64_t elapsed_micro() const
		{
			return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
		}

		//纳秒
		int64_t elapsed_nano() const
		{
			return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
		}

		//秒
		int64_t elapsed_seconds() const
		{
			return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
		}

		//分
		int64_t elapsed_minutes() const
		{
			return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
		}

		//时
		int64_t elapsed_hours() const
		{
			return duration_cast<chrono::hours>(high_resolution_clock::now() - m_begin).count();
		}

		static std::string getCurrentSystemTime()
		{
			auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			struct tm ptm;
			localtime_s(&ptm, &tt);

			char date[60] = { 0 };
			sprintf_s(date, "%d-%02d-%02d-%02d-%02d-%02d",
				(int)ptm.tm_year + 1900, (int)ptm.tm_mon + 1, (int)ptm.tm_mday,
				(int)ptm.tm_hour, (int)ptm.tm_min, (int)ptm.tm_sec);
			return std::string(date);
		}

		static std::string getCurrentDate()
		{
			auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			struct tm ptm;
			localtime_s(&ptm, &tt);

			char date[60] = { 0 };
			sprintf_s(date, "%d-%02d-%02d",
				(int)ptm.tm_year + 1900, (int)ptm.tm_mon + 1, (int)ptm.tm_mday);
			return std::string(date);
		}

	private:
		time_point<high_resolution_clock> m_begin;
	};
}




//调用示例：

//void fun()
//{
//	std::cout << "hello word" << endl;
//}
//
//int main()
//{
//	Timer t; //开始计时
//	fun();
//	std::cout << t.elapsed() << endl; //打印fun函数耗时多少毫秒
//	std::cout << t.elapsed_micro() << endl; //打印微秒
//	std::cout << t.elapsed_nano() << endl; //打印纳秒
//	std::cout << t.elapsed_seconds() << endl; //打印秒
//	std::cout << t.elapsed_minutes() << endl; //打印分钟
//	std::cout << t.elapsed_hours() << endl; //打印小时
//}