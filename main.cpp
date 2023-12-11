#include <iostream>
#include <stack>
#include <string>
std::stack<char> operators;
char precedence(char op1, char op2)
{

	return 0;
}
void in_to_post(std::string expr)
{
	std::string postExpr;
	for(char i : expr)
	{
		if(i != '(' && i != ')' && i != '+' && i != '-' && i != '*' && i != '/' && i != '^')
			postExpr+=i;
		else
			precedence(i, operators.top());
	}
	std::cout << postExpr;

}

int main()
{
	std::string input;
	std::cin >> input;
	in_to_post(input);
	return 0;
}
