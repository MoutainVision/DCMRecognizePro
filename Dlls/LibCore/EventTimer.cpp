#include "EventTimer.h"

unsigned int EventTimer::addEvent(double interval, std::function<void()> action, bool isRepeat) 
{
	SchedulerEvent event(interval, this->timeline, action, isRepeat);
	return this->eventQueue.insertNode(event);
}

void EventTimer::deleteEvent(unsigned int timerId) 
{
	this->eventQueue.deleteNode(timerId);
}

void EventTimer::loopForExecute() 
{
	std::unique_ptr<SchedulerEvent> top = this->eventQueue.getTopNode();
	while (top != nullptr && top->deadline <= this->timeline) 
	{
		//����Ѿ�����ִ�е�ʱ��,�¿�һ�����߳�ִ������
		std::thread t(top->action);
		t.detach();    //���̷߳���

		if (top->isRepeat) {
			//������ظ��¼�,���������
			this->addEvent(top->interval, top->action, top->isRepeat);
		}

		//�Ӷ���ɾ��
		this->eventQueue.deleteTopNode();
		top = this->eventQueue.getTopNode();
	}
	//ִ��һ�κ�ȴ�һ������
	std::this_thread::sleep_for(this->tick);
	//������1
	this->timeline++;
}

void EventTimer::asyncStart() 
{
	if (!this->isStart)
	{
		std::thread daemon_thread(&EventTimer::syncStart, this);
		daemon_thread.detach();     //�ӵ�ǰ���̷߳���
	}
}

void EventTimer::syncStart() 
{
	if (!this->isStart) 
	{
		while (1)
			this->loopForExecute();
	}
}