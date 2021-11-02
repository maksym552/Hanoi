#include <iostream>
#include <stack>
#include <conio.h>
#ifdef _WIN32
#include <Windows.h>

void sleep(unsigned int miliseconds) {
    Sleep(miliseconds);
}

#else

#include <unistd.h>
void sleep(unsigned int miliseconds) {
    usleep(miliseconds * 1000);
}

#endif

using namespace std;

int maxx = 0;

void scrclr() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void start(stack<int>& stos, int size) {
    for (int i = size; i > 0; i--) {
        stos.push(i * 2 + 1);
    }
    maxx = size;
}

void draw(stack<int> stos) {
    cout << endl;
    if (!stos.empty()) {
        if (stos.size() != maxx) {
            for (int i = maxx - stos.size(); i > 0; i--) {
                for (int j = 0; j < maxx; j++)
                    cout << "  ";
                cout << char(179) << char(179) << endl;
            }
        }
        while (!stos.empty()) {
            for (int i = 0; i < maxx - (stos.top() - 1) / 2; i++)
                cout << "  ";
            for (int i = 0; i < stos.top(); i++)
                cout << char(219) << char(219);
            stos.pop();
            cout << endl;
        }
    }
    else {
        for (int i = 0; i < maxx; i++) {
            for (int j = 0; j < maxx; j++)
                cout << "  ";
            cout << char(179) << char(179);
            cout << endl;
        }
    }

}

bool move(stack<int>& a, stack<int>& b) {
    if (a.empty()) {
        return false;
    }
    if (!b.empty()) {
        if (b.top() < a.top()) {
            return false;
        }
    }
    b.push(a.top());
    a.pop();
    return true;
}

bool win(stack<int> third) {
    if (third.size() != maxx)
        return false;
    return true;
}

void display(stack<int> a, stack<int> b, stack<int> c, int moves, int opt) {
    scrclr();
    cout << endl << " 1 " << endl;
    draw(a);
    cout << endl << " 2 " << endl;
    draw(b);
    cout << endl << " 3 " << endl;
    draw(c);
    cout << "Moves: " << moves << " Optimal: " << opt << endl;
}

void hanoi(int n, char a, char b, char c, string& steps) {
    if (n > 1)hanoi(n - 1, a, c, b, steps);
    steps += a;
    steps += c;
    if (n > 1)hanoi(n - 1, b, a, c, steps);
}

int main()
{
    int size; bool bot = false;
    cout << "Podaj rozmiar stosu: "; cin >> size;
    cout << "Czy wlaczyc bota (1 / 0): "; cin >> bot;
    int opt = pow(2, size) - 1;
    string steps = "";
    if (bot)
        hanoi(size, '0', '1', '2', steps);
    stack<int> stos[3];
    start(stos[0], size);
    int a, b, moves = 0;
www:
    while (!win(stos[2])) {
        if (bot) {
            display(stos[0], stos[1], stos[2], moves, opt);
            move(stos[int(steps[moves * 2]) - int('0')], stos[int(steps[moves * 2 + 1]) - int('0')]);
            sleep(1000);
        }
        else {
            do {
                display(stos[0], stos[1], stos[2], moves, opt);
                cout << "Podaj numery (np.: 1 2): ";
                cin >> a >> b;
                if ((a == b) || !(a > 0 && a < 4) || !(b > 0 && b < 4)) goto www;
            } while (!move(stos[a - 1], stos[b - 1]));
        }
        moves++;
    }
    display(stos[0], stos[1], stos[2], moves, opt);
    cin.get();
    return 0;
}