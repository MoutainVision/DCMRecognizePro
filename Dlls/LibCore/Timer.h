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

		//Ĭ�������
		double elapsed() const
		{
			return duration_cast<duration<double>>(high_resolution_clock::now() - m_begin).count();
		}

		//Ĭ���������
		int64_t elapsed_millisec() const
		{
			return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
		}

		//΢��
		int64_t elapsed_micro() const
		{
			return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
		}

		//����
		int64_t elapsed_nano() const
		{
			return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
		}

		//��
		int64_t elapsed_seconds() const
		{
			return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
		}

		//��
		int64_t elapsed_minutes() const
		{
			return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
		}

		//ʱ
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




//����ʾ����

//void fun()
//{
//	std::cout << "hello word" << endl;
//}
//
//int main()
//{
//	Timer t; //��ʼ��ʱ
//	fun();
//	std::cout << t.elapsed() << endl; //��ӡfun������ʱ���ٺ���
//	std::cout << t.elapsed_micro() << endl; //��ӡ΢��
//	std::cout << t.elapsed_nano() << endl; //��ӡ����
//	std::cout << t.elapsed_seconds() << endl; //��ӡ��
//	std::cout << t.elapsed_minutes() << endl; //��ӡ����
//	std::cout << t.elapsed_hours() << endl; //��ӡСʱ
//}