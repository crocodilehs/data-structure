#include <iostream>
#include <map>

using namespace std;

map<int, float> to_num(string input);

int main() {
    string input1, input2, temp;
    map<int, float> arr1, arr2, result;
    cin >> input1 >> input2;

    arr1 = to_num(input1);
    arr2 = to_num(input2);

    for (auto c : arr1)
        result[c.first] += c.second;
    for (auto c : arr2)
        result[c.first] += c.second;

    // 跳過第一個
    auto i = result.rbegin();
    if (i->second != 0)
        cout << i->second << "x^" << i->first;
    ++i;

    // first 指數，second 係數
    for (; i != result.rend(); ++i) {
        if (i->second > 0) {
            if (i->second != 1 && i->first != 0)
                cout << "+" << i->second << "x^" << i->first;
            else if (i->second == 1 && i->first != 0)
                cout << "+"
                     << "x^" << i->first;
            else if (i->first == 0 && i->second != 1)
                cout << "+" << i->second;
            else if (i->first == 0 && i->second == 1)
                cout << "+1";
        } else if (i->second == 0) {
            continue;
        } else if (i->second < 0) {
            if (i->second == -1 && i->first != 0)
                cout << "-";
            else
                cout << i->second;
            if (i->first != 0)
                cout << "x^" << i->first;
        }
    }
    // 如果所有係數都為0，輸出0
    bool allZero = true;
    for (const auto& term : result) {
        if (term.second != 0) {
            allZero = false;
            break;
        }
    }
    if (allZero)
        cout << "0";

    return 0;
}

map<int, float> to_num(string input) {
    string temp = "";
    int flag = 1;  // 1代表有x
    map<int, float> arr;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '+' && input[i + 1] == 'x') {
            temp += "1";
        } else if (input[i] == '-' && input[i + 1] == 'x') {
            temp += "-1";
        }
        if (input[i] == '+' || input[i] == 'x') {
            flag = 1;
            continue;
        }
        if (input[i] == '-')
            flag = 1;
        if (flag && input[i] != '^')
            temp += input[i];

        if (input[i] == '^') {
            float value = stof(temp);
            int key = input[++i] - '0';
            arr[key] = value;
            temp = "";
            flag = 0;
        }
        if (temp != "" && i == input.size() - 1) {
            float value = stof(temp);
            int key = 0;
            arr[key] = value;
            temp = "";
        }
    }
    return arr;
}
/*
key是指數
value是係數
*/

/*
input1
5x^5+3x^3+1
4x^4+2x^2+x^1
output1
5x^5+4x^4+3x^3+2x^2+x^1+1

input2
4x^3+2.1
-2.6x^3+4.9
output2
1.4x^3+7

input3
3.7x^5-4.7x^2
5.7x^2-x^1+5
output3
3.7x^5+x^2-x^1+5
*/