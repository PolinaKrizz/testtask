/*****************************************************************************/
/* ���������� ������������ ������ FIFO � ������� ������������� ����������    */
/* +: ����� ������ ��������� ���������� ������                               */
/* -: ����� �������������� ������, ������ ������ ��������                    */
/* Implementing a circular FIFO with a library container                     */
/* +: the buffer stores the last put data                                    */
/* -: buffer overwrites data, old data is lost                               */
/*****************************************************************************/

#include <iostream>
#include <vector>
#include <string>
class MyException								// Exception handling class. ����� ��������� ����������
{
public:
	std::string stringWhat_;
	MyException() {};
	MyException(const std::string stringWhat) : stringWhat_(stringWhat) {};
};

template <typename T>
class Queue
{
private:
	size_t size_ = 3;							// Buffer size. ������ ������
	std::vector<T> queue_;
	size_t head_;								// Push. ������
	size_t tail_;								// Pop. ��������
	bool isEmpty_;
	bool isFull_;
public:
	Queue() : queue_(size_), head_(0), tail_(0), isEmpty_(true), isFull_(false) {};
	void enqueue(T data);
	T dequeue();
};

template <typename T>
void Queue<T>::enqueue(T data)
{
	if (head_ == tail_ && !isEmpty_) {			// If the head has caught up with the tail, move it
		isFull_ = true;							// ���� ������ ������� �����, �������� ���
		tail_++;
	}
	queue_[head_] = data;						// Add data. ��������� �������
	if (head_ == size_ - 1) {					// Move head. �������� ������
		head_ = 0;
	}
	else {
		head_++;
	}

	if (isEmpty_ == true) {						// If it was empty, change the flag
		isEmpty_ = false;						// ���� ��� ����, ������
	}

}

template <typename T>
T Queue<T>::dequeue()
{
	if (!isEmpty_) {							
		T temp = queue_[tail_];
		queue_[tail_] = 0;
		if (tail_ == size_ - 1) {
			tail_ = 0;
		}
		else {
			tail_++;
		}

		if (isFull_ == true) {					// If it was full, change the flag
			isFull_ = false;					// ���� ��� �����, ������
		}

		if (tail_ == head_) {					// If the tail has caught up with the head, the array is empty
			isEmpty_ = true;					// ���� ����� ������ ������, ������ ����
		}
		return temp;
	}
	else {
		throw MyException("Queue is empty");
	}
}


int main() {
	try {
		Queue<int> q;
		q.enqueue(1);
		q.enqueue(2);
		q.enqueue(3);
		q.enqueue(4);
		std::cout << q.dequeue();
		std::cout << q.dequeue();
		std::cout << q.dequeue(); 
		std::cout << q.dequeue();
	}
	catch (MyException& e) { std::cout << e.stringWhat_ << std::endl; }
	return 0;
}