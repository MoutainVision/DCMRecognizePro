#pragma once
/**
 * ����ѵ�ʵ��
 * ��ʹ�õ�����ȫ�������Ľṹ��ʹ�����飨������㿪ʼ�����棬��ô���һ����Ҷ�ӽڵ�Ϊ(n - 1) / 2
 * �ѵĹ���һֱ����������Ļ����ϵģ���ôÿ�ε���ֻ��Ƚ�i��(i - 1) / 2��Ԫ�أ���������
 * ֧�������������
 * ��ǰ����֧�ֶ��̻߳����µ�ʹ��
 * author:jiangpengfie
 * date:2017-05-09
 */
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>


template<class T>
class SortedHeap 
{
private:
	struct HeapNode 
	{
		unsigned int id;
		
		T obj;
		
		HeapNode(unsigned int id, T t) : obj(t) 
		{
			this->id = id;
		}
	};

	std::vector<HeapNode> heap;

	unsigned int autoIncrementId;
	
	std::function<bool(T&, T&)> cmp;    //�ȽϺ�����ʵ��ѡ�������ѻ�����С��
	
	std::mutex mu1;
	std::mutex mu2;

	/**
	 * ����ڵ��������в����ϵĽڵ�
	 */
	void adjustAfterInsert();

	/**
	 * pop���Ѷ�Ԫ�غ�������в����ϵĽڵ�
	 */
	void adjustAfterPopTop();

	/**
	 * ɾ���ڵ��������в����ϵĽڵ�
	 * @param i ɾ���Ľڵ�id
	 */
	void adjustAfterDelete(int id);

	void swap(HeapNode& t1, HeapNode& t2);

	void deleteNodeByPos(const unsigned int pos);

public:
	/**
	 * ���캯��
	 * @param cmp �����Ƚ�
	 */
	SortedHeap(std::function<bool(T&, T&)> cmp);

	/**
	 * ����ڵ�
	 * @param node ����Ľڵ�
	 */
	unsigned int insertNode(T& node);

	/**
	 * ɾ���ڵ㣬ʱ�临�Ӷ�ΪO(n)
	 * @param id  Ҫɾ���Ľڵ�id
	 */
	void deleteNode(unsigned int id);

	/**
	 * pop��С�Ľڵ�
	 * @return T* ���ص�����Ľڵ�ָ��
	 */
	std::unique_ptr<T> popTopNode();

	/**
	 * ��ȡ����Ľڵ�
	 * @return T ����Ľڵ�ָ��
	 */
	std::unique_ptr<T> getTopNode();

	/**
	 * ɾ�������Ľڵ�
	 *
	 */
	void deleteTopNode();
};

template<typename T>
SortedHeap<T>::SortedHeap(std::function<bool(T&, T&)> cmp) 
{
	this->cmp = cmp;
	this->autoIncrementId = 0;
}

template<typename T>
void SortedHeap<T>::swap(HeapNode& t1, HeapNode& t2)
{
	HeapNode tmp = t1;
	t1 = t2;
	t2 = tmp;
}

template<typename T>
void SortedHeap<T>::adjustAfterInsert() 
{
	int last = this->heap.size() - 1;
	int flag = true;
	//�Ӳ���Ľڵ�λ�ÿ�ʼ���ϵ���
	while (last > 0 && flag)
	{
		if (this->cmp(this->heap[last].obj, this->heap[(last - 1) / 2].obj)) 
		{
			this->swap(this->heap[(last - 1) / 2], this->heap[last]);
		}
		else 
		{
			//����Ҫ������
			flag = false;
		}
		last = (last - 1) / 2;
	}
}

template<typename T>
void SortedHeap<T>::adjustAfterDelete(int pos)
{
	//��posλ�ÿ�ʼ���µ���
	int last = this->heap.size() - 1;
	if (last == 0)
		return;     //���һ������Ҫ����

	bool flag = true;   //����Ƿ���Ҫ����

	while (pos <= (last - 1) / 2 && flag)
	{
		//һֱ���������һ����Ҷ�ӽ��
		int topNum = 0;     //��¼��С�Ľ����

		  //(pos + 1) * 2 - 1�����ӣ�pos�Ǹ�
		if (this->cmp(this->heap[(pos + 1) * 2 - 1].obj, this->heap[pos].obj))
		{
			topNum = (pos + 1) * 2 - 1;
		}
		else 
		{
			topNum = pos;
		}

		if ((pos + 1) * 2 <= last) 
		{
			//��������ҽ��
			if (this->cmp(this->heap[(pos + 1) * 2].obj, this->heap[topNum].obj))
			{
				topNum = (pos + 1) * 2;
			}
		}

		//����topNum�ǲ����Լ�
		if (pos == topNum) 
		{
			//���Լ��Ͳ��õ�����
			flag = false;
		}
		else 
		{
			//����
			this->swap(this->heap[pos], this->heap[topNum]);
		}
		pos = topNum;
	}
}


template<typename T>
void SortedHeap<T>::deleteNodeByPos(const unsigned int pos) 
{
	unsigned int last = this->heap.size() - 1;
	if (pos > last) 
	{
		return;
	}
	std::lock(mu1, mu2);             //����
	std::lock_guard<std::mutex> locker1(mu1, std::adopt_lock);
	std::lock_guard<std::mutex> locker2(mu2, std::adopt_lock);

	//�����һ������
	swap(this->heap[pos], this->heap[last]);

	//ɾ�����һ��
	this->heap.pop_back();

	this->adjustAfterDelete(pos);
}



template<typename T>
unsigned int SortedHeap<T>::insertNode(T& node) 
{
	HeapNode hNode(this->autoIncrementId++, node);

	std::lock(mu1, mu2);             //����
	std::lock_guard<std::mutex> locker1(mu1, std::adopt_lock);
	std::lock_guard<std::mutex> locker2(mu2, std::adopt_lock);

	this->heap.push_back(hNode);     //�Ƚ�node�������һλ

	if (this->heap.size() != 1)
	{
		//�����С������1�����������ڵ�����
		this->adjustAfterInsert();
	}

	return this->autoIncrementId - 1;
}


template<typename T>
void SortedHeap<T>::deleteNode(unsigned int id)
{
	for (unsigned int i = 0; i < this->heap.size(); i++) 
	{
		if (heap[i].id == id)
		{
			//�ҵ���id
			this->deleteNodeByPos(i);
			break;
		}
	}


}

template<typename T>
std::unique_ptr<T> SortedHeap<T>::popTopNode() 
{
	if (this->heap.size() != 0) 
	{
		std::unique_ptr<T> top(new T(this->heap[0].obj));
		this->deleteNodeByPos(0);
		return top;
	}
	else 
	{
		std::unique_ptr<T> p = nullptr;
		return p;
	}
}

template<typename T>
std::unique_ptr<T> SortedHeap<T>::getTopNode()
{
	if (this->heap.size() != 0) 
	{
		std::unique_ptr<T> top(new T(this->heap[0].obj));
		return top;
	}
	else 
	{
		std::unique_ptr<T> p = nullptr;
		return p;
	}
}

template<typename T>
void SortedHeap<T>::deleteTopNode() 
{
	if (this->heap.size() != 0) 
	{
		this->deleteNodeByPos(0);
	}
}
