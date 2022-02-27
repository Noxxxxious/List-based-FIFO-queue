#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	struct node* prev;
	struct node* next;
};

void add_beg(node** head, node** tail, int value) {
	node* newNode = new node;
	newNode->data = value;
	if (!*head) {
		newNode->next = newNode->prev = newNode;
		*head = *tail = newNode;
	}
	else {
		newNode->next = *head;
		newNode->prev = *tail;
		(*head)->prev = newNode;
		*head = newNode;
	}
	(*tail)->next = *head;
}

void add_end(node** head, node** tail, int value) {
	node* newNode = new node;
	newNode->data = value;
	if (!*tail) {
		newNode->prev = newNode->next = newNode;
		*tail = *head =  newNode;
	}
	else {
		newNode->prev = *tail;
		newNode->next = *head;
		(*tail)->next = newNode;
		*tail = newNode;
	}
	(*head)->prev = *tail;
}

void del_beg(node** front, node** back, node** head, node** tail) {
	if (*head) {
		if (*head != *tail) {
			if (*front == *head)
				*front = (*front)->next;
			if (*back == *head)
				*back = (*back)->next;
			node* tmp = (*head)->next;
			tmp->prev = *tail;
			delete* head;
			*head = tmp;
			(*tail)->next = tmp;
		}
		else {
			delete* head;
			*head = *tail = nullptr;
		}
	}
}

void del_end(node** front, node** back, node** head, node** tail) {
	if (*tail) {
		if (*tail != *head) {
			if (*back == *tail)
				*back = (*back)->next;
			if (*front == *tail)
				*front = (*front)->next;
			node* tmp = (*tail)->prev;
			tmp->next = *head;
			delete* tail;
			*tail = tmp;
			(*head)->prev = tmp;
		}
		else {
			delete* tail;
			*tail = *head = nullptr;
		}
	}
}

void print_forward(node* head) {
	if (head) {
		node* act = head;
		while (act->next != head) {
			cout << act->data << " ";
			act = act->next;
		}
		cout << act->data;
	}
	else
		cout << "NULL";
	cout << endl;
}

void print_backward(node* tail) {
	if (tail) {
		node* act = tail;
		while (act->prev != tail) {
			cout << act->data << " ";
			act = act->prev;
		}
		cout << act->data;
	}
	else
		cout << "NULL";
	cout << endl;
}

int size(node* head) {
	if (head) {
		int size = 1;
		node* act = head;
		while (act->next != head) {
			size++;
			act = act->next;
		}
		return size;
	}
	else return 0;
}

int count(node* front, node* back) {
	if (front) {
		int count = 1;
		node* act = back;
		while (act != front) {
			count++;
			act = act->next;
		}
		return count;
	}
	else return 0;
}

void push(node** front, node** back, node** head, node** tail, int value) {
	if (*front) {
		if (size(*head) > count(*front, *back)) {
			*back = (*back)->prev;
			(*back)->data = value;
		}
		else {
			if (*back == *head) {
				add_beg(head, tail, value);
				*back = *head;
			}
			else {
				node* newNode = new node;
				newNode->data = value;
				newNode->next = *back;
				newNode->prev = (*back)->prev;
				newNode->prev->next = newNode;
				(*back)->prev = newNode;
				*back = newNode;
			}
		}
	}
	else {
		if (*head) {
			*front = *back = *tail;
			(*back)->data = value;
		}
		else {
			add_beg(head, tail, value);
			*front = *back = *tail;
		}
	}
}

void pop(node** front, node** back) {
	if (*front) {
		cout << (*front)->data << endl;
		if (*front == *back)
			*front = *back = nullptr;
		else
			*front = (*front)->prev;
	}
	else
		cout << "NULL" << endl;
}

void print_queue(node* front, node* back) {
	if (front) {
		node* act = front;
		while (act != back) {
			cout << act->data << " ";
			act = act->prev;
		}
		cout << act->data;
	}
	else
		cout << "NULL";
	cout << endl;
}

void garbage_soft(node* front, node* back, node* head, node* tail) {
	node* act;
	if (front) {
		act = front->next;
		while (act != back) {
			act->data = 0;
			act = act->next;
		}
	}
	else {
		act = head;
		while (act != tail) {
			act->data = 0;
			act = act->next;
		}
		act->data = 0;
	}
}

void garbage_hard(node** front, node** back, node** head, node** tail) {
	node* act;
	if (*front) {
		act = (*front)->next;
		(*front)->next = *back;
		(*back)->prev = *front;
		while (act != *back) {
			if (act == *tail)
				*tail = *front;
			if (act == *head)
				*head = *back;
			node* tmp = act->next;
			delete act;
			act = tmp;
		}
	}
	else {
		while (*head) {
			del_beg(front, back, head, tail);
		}
	}
}

int main() {
	node* front = nullptr, * back = nullptr, * head = nullptr, * tail = nullptr;
	string command;
	int value;
	while (cin >> command) {
		if (command == "ADD_BEG") {
			cin >> value;
			add_beg(&head, &tail, value);
		}
		else if (command == "ADD_END") {
			cin >> value;
			add_end(&head, &tail, value);
		}
		else if (command == "DEL_BEG")
			del_beg(&front, &back, &head, &tail);
		else if (command == "DEL_END")
			del_end(&front, &back, &head, &tail);
		else if (command == "PRINT_FORWARD")
			print_forward(head);
		else if (command == "PRINT_BACKWARD")
			print_backward(tail);
		else if (command == "SIZE")
			cout << size(head) << endl;
		else if (command == "PUSH") {
			cin >> value;
			push(&front, &back, &head, &tail, value);
		}
		else if (command == "POP")
			pop(&front, &back);
		else if (command == "PRINT_QUEUE")
			print_queue(front, back);
		else if (command == "COUNT")
			cout << count(front, back) << endl;
		else if (command == "GARBAGE_SOFT")
			garbage_soft(front, back, head, tail);
		else if (command == "GARBAGE_HARD")
			garbage_hard(&front, &back, &head, &tail);
		else {
			while(head)
				del_beg(&front, &back, &head, &tail);
			return 0;
		}
	}
}