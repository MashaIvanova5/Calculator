
#include "Functii.h"

bool error(std::string s)//неверно написаны знаки возле скобок
{

    if (std::count(s.begin(), s.end(), '(') != std::count(s.begin(), s.end(), ')'))
    {
        return true;
    }
    else
    if (s.find("*)") != std::string::npos || s.find("/)") != std::string::npos || s.find("-)") != std::string::npos || s.find("+)") != std::string::npos || s.find("^)") != std::string::npos)
    {
        return true;
    }
    else
    if (s.find("--") != std::string::npos || s.find("-+") != std::string::npos || s.find("+-") != std::string::npos || s.find("++") != std::string::npos || s.find("*-") != std::string::npos || s.find("*+") != std::string::npos || s.find("*/") != std::string::npos || s.find("**") != std::string::npos || s.find("-*") != std::string::npos || s.find("+*") != std::string::npos || s.find("/*") != std::string::npos || s.find("/-") != std::string::npos || s.find("/+") != std::string::npos || s.find("//") != std::string::npos || s.find("+/") != std::string::npos || s.find("-/") != std::string::npos || s.find("^*") != std::string::npos || s.find("^-") != std::string::npos || s.find("^+") != std::string::npos || s.find("^/") != std::string::npos || s.find("^^") != std::string::npos || s.find("-^") != std::string::npos || s.find("+^") != std::string::npos || s.find("*^") != std::string::npos || s.find("/*") != std::string::npos)
    {
        return true;
    }
    else return false;
}

bool isSeparator(char s)//это разделитель
{
    std::string seps = " ";
    if (seps.find(s) == std::string::npos)//если не встречен пробел, то...
    {
        return false; //вернуть false
    }
    else
        return true;//иначе вернуть true

}

int priority(char s)//приоритетность: + и - это 1, * и / это 2, ^ это 3
{
    switch (s)
    {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

bool isOperator(char s)//это опрератор...
{
    std::string seps = "-+/*^()";
    if (seps.find(s) == std::string::npos)//если не встречен оператор, то...
    {
        return false;//вернуть false
    }
    else
        return true;//иначе вернуть true
}

float doIt(char s, float a, float b)//считаем в зависимости от встреченного оператора
{
    switch (s)
    {
        case '+':
            return a + b;//сложение
        case '-':
            return a - b;//вычитание
        case '*':
            return a * b;//умножение
        case '/':
            return a / b;//деление
        case '^':
            return std::pow(a, b);//степень
    }
    return 0;
}

std::string trigonometry(std::string input, int buf)//для излечения из скобок у тригоном и экспоненты, где buf-позиция начала выражения
{
    int open = 1;
    int close = 0;
    int i = buf + 4;
    while (close != open)
    {
        if (input[i] == '(')
        {
            open += 1;
        }
        else if (input[i] == ')')
        {
            close += 1;
        }
        i += 1;
    }
    std::string sub = input.substr(buf + 3, i - buf - 3);//присваиваем подстроку вида (...)
    return sub;
}
std::string trigonometryforsqrt(std::string input, int buf)//для излечения из скобок у корня, где buf-позиция начала выражения
{
    int open = 1;
    int close = 0;
    int i = buf + 5;
    while (close != open)
    {
        if (input[i] == '(')
        {
            open += 1;
        }
        else if (input[i] == ')')
        {
            close += 1;
        }
        i += 1;
    }
    std::string sub = input.substr(buf + 3, i - buf - 3);
    return sub;
}

float counter(std::string input)
{
    std::map<std::string, float> constants{ {"pi", M_PI},{"e", exp(1)} };
    std::stack<float> numbers;
    std::stack<char> operations;
    bool unMinus = true;

    for (int i = 0; i < static_cast<int>(input.length()); i++)
    {
        if (isSeparator(input[i]))
        {
            continue;
        }

        if (isOperator(input[i]))
        {
            if (operations.empty())
            {
                if ((numbers.empty()) && (unMinus))
                {
                    numbers.push(0);
                }
                operations.push(input[i]);
                unMinus = false;
            }
            else
            if (input[i] == '(')
            {
                operations.push(input[i]);
                unMinus = true;
            }
            else
            if (input[i] == ')')
            {
                while (operations.top() != '(')
                {
                    float second = numbers.top();
                    numbers.pop();
                    float first = numbers.top();
                    numbers.pop();
                    float result = doIt(operations.top(), first, second);
                    if (std::isinf(result))
                    {
                        std::cout << "Деление на ноль\n";
                        return 0;
                    }
                    numbers.push(result);
                    operations.pop();
                }
                operations.pop();

            }
            else
            if (operations.top() == '(' && unMinus)
            {
                numbers.push(0);
                operations.push(input[i]);
            }
            else
            if ((priority(input[i]) > priority(operations.top())) || (operations.top() == '('))
            {
                operations.push(input[i]);
            }
            else
            {
                float second = numbers.top();
                numbers.pop();
                float first = numbers.top();
                numbers.pop();
                float result = doIt(operations.top(), first, second);
                if (std::isinf(result))
                {
                    std::cout << "Деление на ноль\n";
                    return 0;
                }
                numbers.push(result);
                operations.pop();
                operations.push(input[i]);
            }
            continue;
        }

        if (isdigit(input[i]))
        {
            unMinus = false;
            std::string longNumber;
            while (!isSeparator(input[i]) && !isOperator(input[i]) && i < static_cast<int>(input.length()))
            {
                longNumber += input[i];
                i++;
            }
            i--;
            numbers.push(std::stof(longNumber));
        }
        else
        {
            unMinus = false;
            std::string cons;//прога догадывается, что встречена константа
            while (!isSeparator(input[i]) && !isOperator(input[i]) && i < static_cast<int>(input.length()))
            {
                cons += input[i];
                i++;
            }
            i--;
            numbers.push(constants[cons]);
        }
    }

    while (!operations.empty())
    {
        float second = numbers.top();
        numbers.pop();
        float first = numbers.top();
        numbers.pop();
        float result = doIt(operations.top(), first, second);
        if (std::isinf(result))
        {
            std::cout << "Деление на ноль/n";
            return 0;
        }
        numbers.push(result);
        operations.pop();
    }
    return numbers.top();
}
