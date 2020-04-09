#pragma once
/**
 * ��ʱ����ʵ��
 * ֧��int setTimer(T interval,function action):����һ����ʱ����ָ�����interval�ͻص�����action,���ض�ʱ��id
 * ֧��void deleteTimer(int timerId):ɾ��һ����ʱ��
 * ���ݽṹ:��С��ģ�ͣ����ն�ʱ��������ʱ������
 * author:jiangpengfei
 * date:2017-05-09
 */
#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
#include <memory>
#include "SortedHeap.h"

class EventTimer 
{
private:
	std::chrono::milliseconds tick;

	double timeline;     //��ǰʱ����,long double���ֽ���Ϊ12

	bool isStart;        //��־��ǰ��ʱ��������״̬

	struct SchedulerEvent 
	{
		unsigned int id;                   //��ʱ�¼���Ψһ��ʾid
		double interval;                   //�¼��Ĵ�����������ظ��¼��л��õ��������
		double deadline;                   //��ʱ�¼��Ĵ���ʱ��
		std::function<void()> action;      //�������¼�
		bool isRepeat;                     //�Ƿ����ظ�ִ���¼�
		SchedulerEvent(double interval, double timeline, std::function<void()> action, bool isRepeat) {
			this->interval = interval;
			this->deadline = interval + timeline;
			this->action = action;
			this->isRepeat = isRepeat;
		}
	};

	SortedHeap<SchedulerEvent> eventQueue;

	/**
	 * ִ�е������޵Ķ�ʱ��
	 */
	void loopForExecute();

	//˽�еĹ��캯��
	EventTimer(std::chrono::milliseconds tick) 
		: eventQueue([](SchedulerEvent& a, SchedulerEvent& b){return a.deadline < b.deadline;}) 
	{
		this->timeline = 0;
		this->tick = tick;
		this->isStart = false;
	}

public:

	//����ģʽ
	static EventTimer* getInstance(std::chrono::milliseconds tick)
	{
		static EventTimer timer(tick);
		return &timer;
	}

	/**
	 * ���ö�ʱ��
	 * @param interval ��ʱ���
	 * @param action ��ʱִ�еĶ���
	 * @param isRepeat �Ƿ��ظ�ִ��,Ĭ�ϲ��ظ�ִ��
	 * @return unsigned int ��ʱ����id,���Ը������idִ��ɾ������
	 */
	unsigned int addEvent(double interval, std::function<void()> action, bool isRepeat = false);

	/**
	 * ɾ����ʱ��
	 * @param timerId ��ʱ��id
	 *
	 */
	void deleteEvent(unsigned int timerId);

	/**
	 * ͬ��ִ��������ʱ��
	 */
	void syncStart();

	/**
	* �첽ִ��������ʱ��
	*/
	void asyncStart();

};


/*
//���Դ��룺
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <functional>
#include <thread>
#include <memory>
#include <fstream>
#include "EventTimer.h"

void myprint(std::string msg) {
	std::ofstream of("timer.txt", std::ios::app);
	std::thread::id this_id = std::this_thread::get_id();
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	of << "From Thread " << this_id << "at time " << std::put_time(std::localtime(&t), "%Y-%m-%d %H.%M.%S") << ":" << msg << std::endl;
}

int main() 
{
	std::chrono::milliseconds tick(2000);       //1000������Ϊһ������
	EventTimer* timer = EventTimer::getInstance(tick);
	std::function<void()> f1 = std::bind(myprint, "��һ������,10tick��ִ��");
	std::function<void()> f2 = std::bind(myprint, "�ڶ������룬��ɾ����ִ��");
	std::function<void()> f3 = std::bind(myprint, "���������룬ÿ5tick�ظ�ִ��");
	std::function<void()> f4 = std::bind(myprint, "���ĸ����룬5tick��ִ��");
	std::function<void()> f5 = std::bind(myprint, "��������룬5tick��ִ��");
	std::function<void()> f6 = std::bind(myprint, "���������룬5tick��ִ��");
	std::function<void()> f7 = std::bind(myprint, "���߸����룬5tick��ִ��");
	std::function<void()> f8 = std::bind(myprint, "�ڰ˸����룬5tick��ִ��");
	std::function<void()> f9 = std::bind(myprint, "�ھŸ����룬5tick��ִ��");
	std::function<void()> f10 = std::bind(myprint, "��ʮ�����룬5tick��ִ��");
	std::function<void()> f11 = std::bind(myprint, "��ʮһ�����룬15tick��ִ��");
	std::function<void()> f12 = std::bind(myprint, "��ʮ������ִ�к���룬20tick+5s��ִ��");

	timer->addEvent(10, f1);
	int id = timer->addEvent(11, f2);
	timer->addEvent(5, f3, true);
	timer->addEvent(5, f4);
	timer->addEvent(5, f5);
	timer->addEvent(5, f6);
	timer->addEvent(5, f7);
	timer->addEvent(5, f8);
	timer->addEvent(5, f9);
	timer->addEvent(5, f10);
	timer->addEvent(15, f11);

	timer->deleteEvent(id);

	myprint("�߳̿�ʼ����,ÿtick��2��");

	//�첽ִ�У������˳����ʱ��Ҳ����ֹ�����������ʹ��whileѭ����֤���򲻻��˳�
	timer->asyncStart();
	//timer->syncStart();


	//����5����
	std::this_thread::sleep_for(std::chrono::seconds(5));
	//Ӧ���ڴ��20*tick+5���ִ��,
	//TODO ִ�к����Ķ�ʱ������
	timer->addEvent(20, f12);

	getchar();

	return 0;
}
*/