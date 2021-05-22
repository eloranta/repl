#include <iostream>
#include <string>

class Label;

class SExpression
{
public:
    static SExpression* Parse();
    virtual SExpression* Eval() = 0;
    virtual void Print() = 0;
};

class Number : public SExpression
{
    char c;
public:
    static SExpression* Parse();
    Number(char c) : c(c) {}
    SExpression* Eval()
    {
        return this;
    }
    void Print()
    {
        std::cout << "number\n";
    }
};

class List : public SExpression
{
    char c;
public:
    static SExpression* Parse();
    List(char c) : c(c) {}
    SExpression* Eval()
    {
        return this;
    }
    void Print()
    {
        std::cout << "list\n";
    }
};

class Label : public SExpression
{
    char c;
public:
    static SExpression* Parse();
    Label(char c) : c(c) {}
    SExpression* Eval()
    {
        return this;
    }
    void Print()
    {
        std::cout << "label\n";
    }
};

SExpression* SExpression::Parse()
{
    char c;
    std::cin >> c;
    std::cin.putback(c);

    if (std::isdigit(c))
    {
        return Number::Parse();
    }
    else if (c == '{')
    {
        return List::Parse();
    }
    else
    {
        return Label::Parse();
    }
}

SExpression* Number::Parse()
{
    char c;
    std::cin >> c;
    return new Number(c);
}

SExpression* List::Parse()
{
    char c;
    std::cin >> c;
    return new List(c);
}

SExpression* Label::Parse()
{
    char c;
    std::cin >> c;
    return new Label(c);
}


int main()
{
    while (true)
        SExpression::Parse()->Eval()->Print();
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
