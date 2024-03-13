#pragma once
#define INTLIST_H_INCLUDED
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
    int x;
    Node* next;//покажчик на такого самого нода
    Node(int x) {//конструктор в середині класу(структури)
        this->x = x;//this->(верхній х) призначуємо новий х(той що в параметрі)
        next = nullptr;
    }
};

class IntList {
    Node* first;
    Node* last;
    int Size;
    Node* getNodeByIdx(int idx) const{
        int cnt = 0;
        Node* node = first;//створюємо покажчик на ноду записуємо адресу першого нода
        while (node) {//доки вказуємо на ноду(поки існує вузол)
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
    //деструктор
    virtual ~IntList() {
        clear();
    }
    bool isEmpty() const {
        //if (first==nullptr) return true;
        return !first;//нема first
    }
    int size() const{
        int cnt = 0;
        Node* node = first;//створюємо покажчик на ноду записуємо адресу першого нода
        while (node) {//доки взкаємо на ноду(поки існує вузол)
            cnt++;
            node = node->next;
        }
        return cnt;
    }
    int getSize() const {
        return Size;
    }
    void push_back(int x) {
        Node* node = new Node(x);//робимо динамічно нову ноду
        if (isEmpty()) {
            first = node;//вказуємо на нову ноду
            last = node;//вказуємо на ту саму ноду
        }
        else {
            last->next = node;//////////////////////////////////////Запитати за цей момент!!!
            last = node;//вказує на нову ноду
        }
        Size++;
    }
    void push_front(int x){
        Node* node = new Node(x);
        if (isEmpty()) {
            first = node;//вказуємо на нову ноду
            last = node;//вказуємо на ту саму ноду
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
            if (!first) last = nullptr;//коли останній ел. вилучили то last присвоюємо нуль
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
        //пробігаємось по всьому списку
        Node* node = first;//створюємо покажчик на ноду записуємо адресу першого нода
        while (node) {//доки взкаємо на ноду(поки існує вузол)
            cout << node->x << " ";//в ноді захований х який ми показуємо
            node = node->next;//переходить до наступного ноду
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
        toArray(A, n);//весь список перекинули в масив
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
    //отримуємо прямий доступ до елемента в середині списку(доступ до існуючого елементу а не його копію)
    //доступ до посилання(ще одне ім'я існуючої змінної)
    // Завжди робиться у двох екземплярах!!!
    // не потрібен потоковий оператор
    // ПЕРЕВАНТАЖЕННЯ ОПЕРАТОРІВ:
    int& operator[](int idx) {
        Node* node = getNodeByIdx(idx);
        cout << "---------1-------"<<endl;
        return node->x;
    }
    //для цього екземпляру потрібен потоковий оператор<<
    const int& operator[] (int idx) const {
        Node* node = getNodeByIdx(idx);//незабуваємо прописувати const в getNodeByIdx(idx)
        //cout << "---------2-------"<<endl;
        return node->x;
    }

};


//потоковий оператор
//якщо в другому параметрі перед IntList& L буде стояти сonst, то буде визиватись другий екземпляр
//інакше буде визиватись перший екземпляр
ostream& operator<<(ostream& out, const IntList& L);




















