#pragma once
/**
 * 定时器的实现
 * 支持int setTimer(T interval,function action):设置一个定时器，指定间隔interval和回调函数action,返回定时器id
 * 支持void deleteTimer(int timerId):删除一个定时器
 * 数据结构:最小堆模型，按照定时器触发的时间排序
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

	double timeline;     //当前时间线,long double的字节数为12

	bool isStart;        //标志当前定时器的启动状态

	struct SchedulerEvent 
	{
		unsigned int id;                   //定时事件的唯一标示id
		double interval;                   //事件的触发间隔，在重复事件中会用到这个属性
		double deadline;                   //定时事件的触发时间
		std::function<void()> action;      //触发的事件
		bool isRepeat;                     //是否是重复执行事件
		SchedulerEvent(double interval, double timeline, std::function<void()> action, bool isRepeat) {
			this->interval = interval;
			this->deadline = interval + timeline;
			this->action = action;
			this->isRepeat = isRepeat;
		}
	};

	SortedHeap<SchedulerEvent> eventQueue;

	/**
	 * 执行到达期限的定时器
	 */
	void loopForExecute();

	//私有的构造函数
	EventTimer(std::chrono::milliseconds tick) 
		: eventQueue([](SchedulerEvent& a, SchedulerEvent& b){return a.deadline < b.deadline;}) 
	{
		this->timeline = 0;
		this->tick = tick;
		this->isStart = false;
	}

public:

	//单例模式
	static EventTimer* getInstance(std::chrono::milliseconds tick)
	{
		static EventTimer timer(tick);
		return &timer;
	}

	/**
	 * 设置定时器
	 * @param interval 定时间隔
	 * @param action 定时执行的动作
	 * @param isRepeat 是否重复执行,默认不重复执行
	 * @return unsigned int 定时器的id,可以根据这个id执行删除操作
	 */
	unsigned int addEvent(double interval, std::function<void()> action, bool isRepeat = false);

	/**
	 * 删除定时器
	 * @param timerId 定时器id
	 *
	 */
	void deleteEvent(unsigned int timerId);

	/**
	 * 同步执行启动定时器
	 */
	void syncStart();

	/**
	* 异步执行启动定时器
	*/
	void asyncStart();

};


/*
//测试代码：
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
	std::chrono::milliseconds tick(2000);       //1000毫秒作为一个周期
	EventTimer* timer = EventTimer::getInstance(tick);
	std::function<void()> f1 = std::bind(myprint, "第一个加入,10tick后执行");
	std::function<void()> f2 = std::bind(myprint, "第二个加入，被删除不执行");
	std::function<void()> f3 = std::bind(myprint, "第三个加入，每5tick重复执行");
	std::function<void()> f4 = std::bind(myprint, "第四个加入，5tick后执行");
	std::function<void()> f5 = std::bind(myprint, "第五个加入，5tick后执行");
	std::function<void()> f6 = std::bind(myprint, "第六个加入，5tick后执行");
	std::function<void()> f7 = std::bind(myprint, "第七个加入，5tick后执行");
	std::function<void()> f8 = std::bind(myprint, "第八个加入，5tick后执行");
	std::function<void()> f9 = std::bind(myprint, "第九个加入，5tick后执行");
	std::function<void()> f10 = std::bind(myprint, "第十个加入，5tick后执行");
	std::function<void()> f11 = std::bind(myprint, "第十一个加入，15tick后执行");
	std::function<void()> f12 = std::bind(myprint, "第十二个在执行后加入，20tick+5s后执行");

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

	myprint("线程开始启动,每tick是2秒");

	//异步执行，程序退出后计时器也会终止，因此在下面使用while循环保证程序不会退出
	timer->asyncStart();
	//timer->syncStart();


	//休眠5秒钟
	std::this_thread::sleep_for(std::chrono::seconds(5));
	//应该在大概20*tick+5秒后执行,
	//TODO 执行后加入的定时器不对
	timer->addEvent(20, f12);

	getchar();

	return 0;
}
*/