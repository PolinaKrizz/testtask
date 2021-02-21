/*****************************************************************************/
/* ���������� ������������ ������ FIFO � ������� ��������� Node              */
/* +: ������ � ������ �������� �� ���������������                            */
/*    ����� ������ ������, ������� � ���� �������� �� ������������� ��       */
/* -: ���� ����� ��������, ����� ������ ��������                             */
/* Implementing a circular FIFO with a library container                     */
/* +: data in memory is not stored sequentially                              */
/*    the buffer stores the data that was put into it without overwriting it */
/* -: if the buffer is full, new data is lost                                */
/*****************************************************************************/


#include <iostream>
#include <string>
class MyException								// Exception handling class. ����� ��������� ����������
{
public:
	std::string stringWhat_;
	MyException() {};
	MyException(const std::string stringWhat) : stringWhat_(stringWhat) {};
};

template <typename T>
class QueueLinkedList
{
	struct  Node
	{
		T data_;
		Node* next_;
	};
	Node *head_, *tail_;						// Push, pop. ������, ��������
	size_t size_ = 3;							// Buffer size. ������ ������
	int counter_;								// Number of elements in the buffer. ���-�� ��������� � �������
public:
	QueueLinkedList();
	~QueueLinkedList();
	void push(T data);
	T pop();

};

template <typename T>
QueueLinkedList<T>::QueueLinkedList()			//Buffer creation. �������� ������
{
	Node* temp = new Node;
	head_ = temp;
	tail_ = temp;

	for (size_t i = 1; i < size_; i++) {
		Node* temp = new Node;
		head_->next_ = temp;
		head_ = temp;
	}
	head_->next_ = tail_;
	head_ = tail_;

	counter_ = 0;
}

template <typename T>
QueueLinkedList<T>::~QueueLinkedList()			//Delete buffer. �������� ������
{
	while (size_ != 0)							//While the size of the list is not 0. ���� ����������� ������ �� ������ �������
	{
		Node* temp = head_->next_;
		delete head_;                           //Remove each element in turn
		head_ = temp;                           //������� ������ ������� �� �������
		size_--;                                
	}
}

template <typename T>
void QueueLinkedList<T>::push(T data) {			// Push. ���������� � �����
	if (counter_ != size_) {					// Check if there is a place. ��������� ���� �� �����
		counter_++;								// Increasing the number of elements in the buffer
												// ����������� ���-�� ��������� � ������
		head_->data_ = data;					// Add data. ��������� �������
		head_ = head_->next_;					// Move head. �������� ������
	}
	else throw MyException("Queue is full");
}

template <typename T>
T QueueLinkedList<T>::pop() {					// Pop. ����� �� ������
	if (counter_ != 0) {						// Checking if there are elements. ��������� ���� �� ��������
		counter_--;								// Reducing the number of elements 
												// ��������� ���-�� ���������
		T temp = tail_->data_;					// Remember the data. ���������� ������
		tail_ = tail_->next_;					// Move tail. �������� �����
		return temp;
	}
	else throw MyException("Queue is empty");
}

int main() {
	try {
		QueueLinkedList<int> q;
		q.push(1);
		q.push(2);
		q.push(3);
		std::cout << q.pop();
		q.push(4);
		std::cout << q.pop();
		std::cout << q.pop();
	}
	catch (MyException& e) { std::cout << e.stringWhat_ << std::endl; }
	return 0;
}