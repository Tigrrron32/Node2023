#include "IntList.h"
#include <iostream>

using namespace std;

int main()
{
    try {
        cout << "Hello world!" << endl;
        int B[] = { 2, 5, 66, 2, 83, 77 };
        int n = sizeof(B) / sizeof(B[0]);
        IntList L(B, n);
        //L.show();
        cout << L << endl;

        L.push_front(5);
        L.push_front(4);
        L.push_front(3);
        L.push_front(2);
        L.push_front(1);
        cout << L << endl;

       /* L.toArray(B, 3);
        for (int i = 0; i < n; i++) {
            cout << B[i] << " ";
        }
        cout << endl;
        cout << endl;*/

        L.Sort();
        cout << L << endl;

        L.reverse1();
        cout << L << endl;
        L.insert(333, 3);
        L.deleteByPos(4);
        cout << L << endl;

        cout << "getSize= " << L.getSize() << endl;
      /*  cout << L.isEmpty() << endl;
        L.push_front(123123);
        L.push_back(3);
        L.push_back(2);
        L.push_back(1);
        L.push_back(0);
        L.push_back(6);
        L.push_back(333);
        L.push_back(444);
        L.push_back(555);
        L.push_front(77777);
        L.push_front(99999);
        cout << L.isEmpty() << endl;
        L.show();*/

        //cout << L.size() << endl;
        //cout << L << endl;

       /* while (L.size() > 0) {
            int K = L.pop_front();
            cout << "K = " << K << endl;
            cout << L << endl;
        }*/

        //L.clear();

        //L.insert(123321, -5);
        //cout << L << endl;

        /*while (!L.isEmpty()) {
            int x = L.pop_back();
            cout << x << endl;
            cout << L << endl;
        }*/

        /*int idx;
        cout << "idx= "; cin >> idx;
        L.deleteByPos(idx);*/
        //cout << L << endl;


    }
    catch (const char* msg) {
        cout << msg << endl;
    }

    return 0;
}