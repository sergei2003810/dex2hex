#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

void tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

vector<int> loadArrFromFile(string str)
{
    ifstream in;
    vector<int> numbers;
    in.open(str);
    if (in.is_open())
    {
        string temp;
        while (getline(in, temp))
        {
            vector<string> vec;
            tokenize(temp, ' ', vec);
            for (string str0 : vec)
            {
                numbers.push_back(stoi(str0));
            }
        }
    }
    else cout << "File opening error [maybe file with this name does not exist]" << endl;
    in.close();
    return numbers;
}

string dec2hex(int value)
{
    if (value < 0) value += 0x100000000;
    ostringstream ss;
    ss << hex << value;
    return ss.str();
}

vector<string> vec2hex(vector<int> vec)
{
    vector<string> res;
    for (int x : vec)
    {
        res.push_back(dec2hex(x));
    }
    return res;
}

template <typename T> void printVector(vector<T> vec)
{
    for (auto x : vec)
    {
        cout << x << " ";
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    string FILEIN;
    string FILEOUT;
    cout << "Имя или адрес конвертируемого файла (*.asq): "; getline(cin, FILEIN);
    cout << "Имя или адрес выходного файла (*.hex): "; getline(cin, FILEOUT);
    cout << "Начинаю процесс конвертации ..." << endl;
    vector<int> dec = loadArrFromFile(FILEIN);
    vector<string> hex = vec2hex(dec);
    ofstream out;
    out.open(FILEOUT);
    out << "v2.0 raw\n";
    for (string str : hex) out << str << " ";
    out.close();
    cout << "Готово!" << endl;
    return 0;
}