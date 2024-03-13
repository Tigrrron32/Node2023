#pragma once
#define INTLIST_H_INCLUDED
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
    int x;
    Node* next;//�������� �� ������ ������ ����
    Node(int x) {//����������� � ������� �����(���������)
        this->x = x;//this->(������ �) ���������� ����� �(��� �� � ��������)
        next = nullptr;
    }
};

class IntList {
    Node* first;
    Node* last;
    int Size;
    Node* getNodeByIdx(int idx) const{
        int cnt = 0;
        Node* node = first;//��������� �������� �� ���� �������� ������ ������� ����
        while (node) {//���� ������� �� ����(���� ���� �����)
            if (cnt == idx) return node;
            cnt++;
            node = node->next;
        }
        return nullptr;
    }

public:
    IntList() {
        first = nullptr;
        last = nullptr;
        Size = 0;
    }
    IntList(int* A, int n){
        for (int i = 0; i < n; i++) {
            push_back(A[i]);
        }
    }
    //����������
    virtual ~IntList() {
        clear();
    }
    bool isEmpty() const {
        //if (first==nullptr) return true;
        return !first;//���� first
    }
    int size() const{
        int cnt = 0;
        Node* node = first;//��������� �������� �� ���� �������� ������ ������� ����
        while (node) {//���� ������ �� ����(���� ���� �����)
            cnt++;
            node = node->next;
        }
        return cnt;
    }
    int getSize() const {
        return Size;
    }
    void push_back(int x) {
        Node* node = new Node(x);//������ �������� ���� ����
        if (isEmpty()) {
            first = node;//������� �� ���� ����
            last = node;//������� �� �� ���� ����
        }
        else {
            last->next = node;//////////////////////////////////////�������� �� ��� ������!!!
            last = node;//����� �� ���� ����
        }
        Size++;
    }
    void push_front(int x){
        Node* node = new Node(x);
        if (isEmpty()) {
            first = node;//������� �� ���� ����
            last = node;//������� �� �� ���� ����
        }
        else {
            node->next = first;
            first = node;
        }
        Size++;
    }
    void insert(int x, int pos) {
        if (pos < 0) {
            throw "IntList.insert(int x, int pos) - Error: pos<0";
        }
        int n = getSize();
        if (pos > n) {
            throw "IntList.insert(int x, int pos) - Error: pos is too much";
        }
        if (pos == 0) {
            push_front(x);
            return;
        }
        if (pos == n) {
            push_back(x);
            return;
        }
        Node* prev = getNodeByIdx(pos - 1);
        Node* node = new Node(x);
        node->next = prev->next;
        prev->next = node;
        Size++;
    }
    int deleteByPos(int pos) {
        if (pos < 0) {
            throw "IntList.deleteByPos(int pos) - Error: pos<0";
        }

        int n = getSize();
        if (pos >= n) {
            throw "IntList.deleteByPos(int pos) - Error: pos is too much";
        }

        if (pos == 0) {
            return pop_front();
        }

        if (pos == n-1) {
            return pop_back();
        }

        Node* prev = getNodeByIdx(pos - 1);
        Node* tmp = prev->next;
        int ans = tmp->x;
        prev->next = tmp->next;
        delete tmp;
        Size--;
        return ans;
    }
    int pop_front(){
        if (isEmpty()) {
            throw "IntList.pop_front() - Error: List is empty()!";
        }

        int ans = 0;
        if (first) {
            ans = first->x;
            Node* node = first;
            first = first->next;
            delete node;
            if (!first) last = nullptr;//���� ������� ��. �������� �� last ���������� ����
            Size--;
        }
        return ans;
    }
    int pop_back(){
        if (isEmpty()) {
            throw "IntList.pop_back() - Error: List is empty()!";
        }

        if (first == last) {
            int ans = first->x;
            delete first;
            first = nullptr;
            last = nullptr;
            Size = 0;
            return ans;
        }
        else {
            Node* prev = first;
            while (prev->next != last) {
                prev = prev->next;
            }
            int ans = last->x;
            last = prev;
            delete last->next;
            last->next = nullptr;
            Size--;
            return ans;
        }
    }
    void clear() {
        while (first) {
            pop_front();
        }
    }
    void show() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        //���������� �� ������ ������
        Node* node = first;//��������� �������� �� ���� �������� ������ ������� ����
        while (node) {//���� ������ �� ����(���� ���� �����)
            cout << node->x << " ";//� ��� ��������� � ���� �� ��������
            node = node->next;//���������� �� ���������� ����
        }
        cout << endl;
    }
    int toArray(int* A, int n) const {
        int i = 0;
        Node* node = first;
        while (node && i<n) {
            A[i] = node->x;
            i++;
            node = node->next;
        }
        return i;
    }
    void Sort() {
        int n = getSize();
        int* A = new int[n];
        toArray(A, n);
        sort(A, A + n);
        clear();
        for (int i = 0; i < n; i++) {
            push_back(A[i]);
        }
        delete[]A;
    }

    void reverse() {
        int n = size();
        int* A = new int[n];
        toArray(A, n);//���� ������ ���������� � �����
        int i = 0;
        int j = n-1;
        while (i < j) {
            swap(A[i], A[j]);
            i++;
            j--;
        }
        clear();
        for (int i = 0; i < n; i++) {
            push_back(A[i]);
            //cout << A[i] << endl;
        }
        delete[]A;
    }

    void reverse1() {
        IntList X;
        while (!isEmpty()) {
            X.push_back(pop_back());
        }
        while (!X.isEmpty()) {
            push_back(X.pop_front());
        }
    }
    //�������� ������ ������ �� �������� � ������� ������(������ �� ��������� �������� � �� ���� ����)
    //������ �� ���������(�� ���� ��'� ������� �����)
    // ������ �������� � ���� �����������!!!
    // �� ������� ��������� ��������
    // �������������� �������в�:
    int& operator[](int idx) {
        Node* node = getNodeByIdx(idx);
        cout << "---------1-------"<<endl;
        return node->x;
    }
    //��� ����� ���������� ������� ��������� ��������<<
    const int& operator[] (int idx) const {
        Node* node = getNodeByIdx(idx);//���������� ����������� const � getNodeByIdx(idx)
        //cout << "---------2-------"<<endl;
        return node->x;
    }

};


//��������� ��������
//���� � ������� �������� ����� IntList& L ���� ������ �onst, �� ���� ���������� ������ ���������
//������ ���� ���������� ������ ���������
ostream& operator<<(ostream& out, const IntList& L);




















