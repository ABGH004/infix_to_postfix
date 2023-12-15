#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>
#include "supportLib.hpp"
#include "pbPlots.hpp"
#include <vector>
std::stack<std::string> operators;
std::string postExpr;
void precedence(std::string op1, std::string op2)
{
	if(op2 == "(")
	{
		operators.push(op1);
		return;
	}
	if(op1 == "("){
		operators.push(op1);
		return;
	}
	else if(op1 == ")")
	{
		while(operators.top() != "(")
		{
			postExpr += (operators.top() + " ");
			operators.pop();
		}
		operators.pop();
		return;	

	}
	
	else if(op1 == "^")
	{
		if(operators.top() != "^")
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if(!operators.empty())
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}
		return;
	}
	
	else if(op1 == "*")
	{
		if(operators.top() != "^" && operators.top() != "*" && operators.top() != "/")
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if(!operators.empty())
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}
		return;
	}
	else if(op1 == "/")
	{
		if(operators.top() != "^" && operators.top() != "*" && operators.top() != "/")
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if(!operators.empty())
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}
		return;
	}
	else if(op1 == "+")
	{
		if(operators.top() != "^" && operators.top() != "*" && operators.top() != "/"
		&& operators.top() != "+" && operators.top() != "-")
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if(!operators.empty())
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}

	}
	else if(op1 == "-")
	{
		if(operators.top() != "^" && operators.top() != "*" && operators.top() != "/"
		&& operators.top() != "+" && operators.top() != "-")
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if(!operators.empty())
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}

	}
	
}
int calc(std::string postExpr)
{
	std::stack<int> result;
	std::string i;
	std::stringstream ss(postExpr);
	while(ss >> i)
	{
		if(i == "+" || i == "-" || 
		i == "*" || i == "/" || i == "^")
		{
			int op2 = result.top();
			result.pop();
			int op1 = result.top();
			result.pop();
			switch(i.c_str()[0]){
				case '+':
					result.push(op1 + op2);
					break;
				case '-':
					result.push(op1 - op2);
					break;
				case '*':
					result.push(op1 * op2);
					break;
				case '/':
					result.push(op1 / op2);
					break;
				case '^':
					result.push(pow(op1, op2));
					break;
			}
		}
		else
			result.push(stoi(i));
		
	}
	int r = result.top();
	result.pop();
	return r;
	
}
int in_to_post(std::string expr)
{
	std::string i;
    std::stringstream ss(expr);  
	while( ss >> i )
	{
		if(i != "(" && i != ")" && i != "+" && i != "-" && i != "*" && i != "/" && i != "^")
			postExpr+= (i + " ");
		else{
			if(operators.empty())
				operators.push(i);
			else
				precedence(i, operators.top());
		
		}
	}
	while(!operators.empty())
	{
		postExpr += (operators.top() + " ");
		operators.pop();
	}
	std::cout << postExpr << std::endl;
	return calc(postExpr);

}
int in_to_post(std::string expr, int xval)
{
	std::string i;
    std::stringstream ss(expr);  
	while( ss >> i )
	{
		if(i != "(" && i != ")" && i != "+" && i != "-" && i != "*" && i != "/" && i != "^")
			postExpr+= (std::to_string(xval) + " ");
		else{
			if(operators.empty())
				operators.push(i);
			else
				precedence(i, operators.top());
		
		}
	}
	while(!operators.empty())
	{
		postExpr += (operators.top() + " ");
		operators.pop();
	}
	return calc(postExpr);

}
int main()
{
	//std::string input;
   	//std::getline(std::cin, input); 
	//std::cout << in_to_post(input) << std::endl;

	std::string input2;
	std::getline(std::cin, input2);
	RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
	StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
	std::vector<double> x;
	std::vector<double> y;
	for( int i = 1; i <= 20; ++i)
	{
		x.push_back(i);
		y.push_back(in_to_post(input2, i));
	}
	DrawScatterPlot(imageRef, 600, 400, &x, &y, errorMessage);
	std::vector<double> *pngData = ConvertToPNG(imageRef->image);
	WriteToFile(pngData, "plot.png");
	DeleteImage(imageRef->image);

	return 0;
}
