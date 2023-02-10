#pragma once
#include<iostream>
using namespace std;
template<class T>
class queue{
	class node{
	public:
		T data;
		node* next;
		node(){ next = NULL; }
		node(T ele){
			data = ele;
			next = NULL;
		}
	};
	node* head;
	node* tail;
	int size;
public:
	queue(){ head = tail = NULL; size = 0; }
	bool isEmpty(){ return size == 0; }
	void push(T ele){
		node* temp = new node(ele);
		if (isEmpty())
			head = tail = temp;
		else{
			tail->next = temp;
			tail = temp;
		}
		size++;
		//print();
	}
	void pop(){
		node* temp = head;
		if (isEmpty())
			cout << "Empty Queue\n";
		else{
			head = head->next;
			delete temp;
			size--;
		}
		//print();
	}
	void print(){
		node *p = head;
		while (p){
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
	int Size(){ return size; }
	T front(){ return head->data; }
	T rear(){ return tail->data; }
    ~queue(){while(head) pop();}
};
