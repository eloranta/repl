#include <iostream>
#include <string>
#include <vector>

class SExpression
{
public:
    static SExpression* Read();
    virtual SExpression* Eval() = 0;
    virtual void Print() = 0;
};

class Number : public SExpression
{
    int value;
public:
    static SExpression* Read();
    Number(int value) : value(value) {}
    SExpression* Eval()
    {
        return this;
    }
    void Print()
    {
        std::cout << value;
    }
};

class List : public SExpression
{
    std::vector<SExpression *> value;
public:
    static SExpression* Read();
    List(std::vector<SExpression*> value) : value(value) {}
    SExpression* Eval()
    {
        return this;
    }
    void Print()
    {
        std::cout << "(";
        std::vector<SExpression*>::iterator i = value.begin();
        if (i != value.end())
        {
            (*i++)->Print();
            while (i != value.end())
            {
                std::cout << " ";
                (*i++)->Print();
            }
        }
 
        std::cout << ")";
    }
};

class Label : public SExpression
{
    std::string value;
public:
    static SExpression* Read();
    Label(std::string value) : value(value) {}
    SExpression* Eval()
    {
        return this;
    }
    void Print()
    {
        std::cout << value;
    }
};

SExpression* SExpression::Read()
{
    char c;

    do
    {
        std::cin >> c;
    }
    while (std::isspace(c));

    std::cin.putback(c);

    if (std::isdigit(c))
    {
        return Number::Read();
    }
    else if (c == '(')
    {
        return List::Read();
    }
    else
    {
        return Label::Read();
    }
}

SExpression* Number::Read()
{
    char c;
    std::string s;
    std::cin >> c;
    while (std::isdigit(c))
    {
        s.push_back(c);
        std::cin >> c;
    }
    if (std::isspace(c) || c == ')')
    {
        if (c == ')')
            std::cin.putback(c);
        return new Number(stoi(s));
    }
    
    s.push_back(c);
    return new Label("Invalid number: " + s);
}

SExpression* List::Read()
{
    char c;
    std::cin >> c;
    std::cin >> c;
    std::vector<SExpression*> list;

    while (c != ')')
    {
        std::cin.putback(c);
        SExpression* expr = SExpression::Read();
        list.push_back(expr);
        std::cin >> c;
    }
    return new List(list);
}

SExpression* Label::Read()
{
    char c;
    std::string s;
    std::cin >> c;
    while (!std::isspace(c) && c != ')')
    {
        s.push_back(c);
        std::cin >> c;
    }
    if (c == ')')
        std::cin.putback(c);

    return new Label(s);
}

int main()
{
    std::cin.unsetf(std::ios_base::skipws);

    while (true)
    {
        SExpression::Read()->Eval()->Print();
        std::cout << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
