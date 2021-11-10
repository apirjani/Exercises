#include "stack.h"
#include <iostream>

using namespace std;

int main()
{
    Stack<int> a;
    for (int i = 0; i < 10; i++)
    {
        a.push(i+1);
    }
    cout << a.top() << endl;
    a.pop();
    cout << a.top() << endl;
    a.pop();
    cout << a.top() << endl;
    a.pop();
    cout << a.top() << endl;
    a.pop();
    cout << a.top() << endl;
    a.pop();
    cout << a.size() << endl;
    cout << a.top() << endl;
    a.pop();
    cout << a.top() << endl;
    a.pop();
    cout << a.top() << endl;
    a.pop();
    cout << a.top() << endl;
    a.pop();
    cout << a.top() << endl;
    a.pop();
    cout << a.size() << endl;
    cout << a.top() << endl;
    a.pop();
    cout << a.size() << endl;
    cout << a.top() << endl;
    a.pop();

}
