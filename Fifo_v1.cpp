/*****************************************************************************/
/* ���������� ������������ ������ FIFO � ������� ������������� ����������    */
/* +: ����� ������ ������, ������� � ���� �������� �� ������������� ��       */
/* -: ���� ����� ��������, ����� ������ ��������                             */
/* Implementing a circular FIFO with a library container                     */
/* +: the buffer stores the data that was put into it without overwriting it */
/* -: if the buffer is full, new data is lost                                */
/*****************************************************************************/

#include <iostream>
#include <vector>
#include <string>
class MyException							// Exception handling class. ����� ��������� ����������
{
public:
	std::string stringWhat_;
	MyException() {};
	MyException(const std::string stringWhat) : stringWhat_(stringWhat) {};
};

template <typename T>
class Queue									// FIFO circular buffer class. ����� ������������ ������ FIFO
{
private:
	size_t size_ = 3;						// Buffer size. ������ ������
	std::vector<T> queue_;
	size_t head_;							// Push. ������
	size_t tail_;							// Pop. ��������
public:
	Queue() : queue_(size_), head_(0), tail_(0) {};
	void enqueue(T data);
	T dequeue();
	bool isEmpty();
};

template <typename T>
void Queue<T>::enqueue(T data)
{
	if (tail_ != (head_ + 1) % size_) {		// The array stores size-1 elements. � ������� �������� size-1 ���������
		queue_[head_] = data;
		if (head_ == size_ - 1) {
			head_ = 0;
		}
		else {
			head_++;
		}
	}
	else throw MyException("Queue is full"); // An exception is thrown when trying to add another item
											 // �������� ���������� ��� ������� �������� ��� ���� �������
}

template <typename T>
T Queue<T>::dequeue()
{
	if (!isEmpty()) {
		T temp = queue_[tail_];
		queue_[tail_] = '\0';
		if (tail_ == size_ - 1) {
			tail_ = 0;
		}
		else {
			tail_++;
		}
		return temp;
	}
	else {
		throw MyException("Queue is empty");
	}
}

template <typename T>
bool Queue<T>::isEmpty()					// If the head and tail point to the same place in the array, then it is empty
{											// ���� ������ � ����� ��������� �� ���� ����� � ������� ������ �� ����
	return (head_ == tail_);
}


int main() {
	try {
		Queue<std::string> s;
		s.enqueue("a");
		s.enqueue("sS");
		std::cout << s.dequeue();
		std::cout << s.dequeue() << std::endl;

		Queue<char> c;
		c.enqueue('c');
		c.enqueue('z');
		std::cout << c.dequeue();
		std::cout << c.dequeue() << std::endl;

		Queue<int> i;
		i.enqueue(1);
		i.enqueue(2);
		std::cout << i.dequeue();
		std::cout << i.dequeue();
	}
	catch (MyException& e) { std::cout << e.stringWhat_ << std::endl; }
	return 0;
}