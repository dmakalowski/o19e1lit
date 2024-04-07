// o19e1lit.cpp : This is a solution for XIX IT Olympiad task: Litery.
// It mainly works on a principle that we need to move every first occurence of the letter to it's place.
// To account for change of place of other letters efficiently, simplified interval tree is used.
//

#include <iostream>
#include<vector>
using namespace std;

#define alphabetID(x) (int(x) - int('A'))
constexpr int maxSize = 1 << 20; //minimal power of 2 greater than 1 000 000
int intervalTree[maxSize * 2 + 1];

void insert(int index) {
    int v = maxSize + index;
    intervalTree[v] = 1;
    while (v > 1) {
        v /= 2;
        intervalTree[v] = intervalTree[2 * v] + intervalTree[2 * v + 1];
    }
}

int query(int index) {
    int va = maxSize + index;
    int wyn = intervalTree[va];
    while (va > 1) {
        if (va % 2 == 0) wyn += intervalTree[va + 1];
        va /= 2;
    }
    return wyn;
}

int main()
{
    ios::sync_with_stdio(false);

    int n, index;
    long long result = 0;
    string jas, malgosia;
    vector<vector<int>> jasInt(26);
    cin >> n;
    cin >> jas;
    cin >> malgosia;

    for (int i = n - 1; i >= 0; i--)
    {
        jasInt[alphabetID(jas[i])].push_back(i);
    }
    for (int i = 0; i < n; i++)
    {
        index = jasInt[alphabetID(malgosia[i])].back();
        jasInt[alphabetID(malgosia[i])].pop_back();
        insert(index);
        index += query(index + 1);
        result += index - i;
    }
    cout << result << endl;
    return 0;
}