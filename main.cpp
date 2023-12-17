#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>
#include "supportLib.hpp"
#include "pbPlots.hpp"
#include <vector>

// global variables
std::stack<std::string> operators;
std::string postExpr;

// finding precedence of operators and
// adding them to stack and new postfix equation
void precedence( std::string op1, std::string op2 )
{
	if( op2 == "(" || op2 == "sin" || op2 == "cos" || op2 == "tan" )
	{
		if( op1 != ")" )
			operators.push(op1);
		else
		{

			postExpr += (operators.top() + " ");
			operators.pop();
		}

		return;
	}
	if( op1 == "(" ){
		operators.push(op1);
		return;
	}
	else if( op1 == ")" )
	{
		while( operators.top() != "(" && operators.top() != "sin" &&
		operators.top() != "cos" && operators.top() != "tan" )
		{
			postExpr += (operators.top() + " ");
			operators.pop();
		}
		if( operators.top() == "(" )
			operators.pop();
		return;	

	}
	else if( op1 == "sin(" )	
	{
		op1.pop_back();
		if( operators.top() != "sin" && operators.top() != "cos"
		&& operators.top() != "tan" )
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
	else if( op1 == "cos(" )	
	{
		op1.pop_back();
		if( operators.top() != "sin" && operators.top() != "cos"
		&& operators.top() != "tan" )
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if( !operators.empty() )
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}
		return;
	}
	else if( op1 == "tan(" )	
	{
		op1.pop_back();
		if( operators.top() != "sin" && operators.top() != "cos"
		&& operators.top() != "tan" )
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if( !operators.empty() )
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}
		return;
	}
	
	else if( op1 == "^" )
	{
		if( operators.top() != "^" && operators.top() != "sin" && 
		operators.top() != "cos" && operators.top() != "tan" )
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if( !operators.empty() )
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}
		return;
	}
	
	else if( op1 == "*" )
	{
		if( operators.top() != "^" && operators.top() != "*" && operators.top() != "/"
		&& operators.top() != "sin" && operators.top() != "cos" && operators.top() != "tan" )
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if( !operators.empty() )
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}
		return;
	}
	else if( op1 == "/" )
	{
		if( operators.top() != "^" && operators.top() != "*" && operators.top() != "/"
		&& operators.top() != "sin" && operators.top() != "cos" && operators.top() != "tan" )
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if( !operators.empty() )
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}
		return;
	}
	else if( op1 == "+" )
	{
		if( operators.top() != "^" && operators.top() != "*" && operators.top() != "/"
		&& operators.top() != "+" && operators.top() != "-" && operators.top() != "sin" 
		&& operators.top() != "cos" && operators.top() != "tan" )
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if( !operators.empty() )
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}

	}
	else if( op1 == "-" )
	{
		if( operators.top() != "^" && operators.top() != "*" && operators.top() != "/"
		&& operators.top() != "+" && operators.top() != "-" && operators.top() != "sin"
		&& operators.top() != "cos" && operators.top() != "tan" )
			operators.push(op1);
		else
		{
			postExpr += (operators.top() + " ");
			operators.pop();
			if( !operators.empty() )
				precedence(op1, operators.top());
			else
				operators.push(op1);
		}

	}
	
}

// calculating the result of a postfix equation
double calc( std::string postExpr )
{
	std::stack<double> result;
	std::string i;
	std::stringstream ss(postExpr);
	while( ss >> i )
	{
		if(i == "+" || i == "-" || 
		i == "*" || i == "/" || i == "^")
		{
			double op2 = result.top();
			result.pop();
			double op1 = result.top();
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
		
		else if(i == "sin")
		{
			double op1 = result.top();
			result.pop();
			result.push(sin(op1*3.14159265/180));
		}
		
		else if(i == "cos")
		{
			double op1 = result.top();
			result.pop();
			result.push(cos(op1*3.14159265/180));
		}
		
		else if(i == "tan")
		{
			double op1 = result.top();
			result.pop();
			result.push(tan(op1*3.14159265/180));
		}
		
		else
			result.push(stof(i));
	}
	double r = result.top();
	result.pop();
	return r;
	
}

// parsing expression and calculating result
double in_to_post(std::string expr)
{
	postExpr = "";
	std::string i;
    std::stringstream ss(expr);  
	while( ss >> i )
	{
		if(i != "(" && i != ")" && i != "+" && i != "-" && i != "*"
		&& i != "/" && i != "^" && i != "sin(" && i != "cos(" && i != "tan(")
			postExpr+= (i + " ");
		else{
			if(operators.empty()){
				if(i == "sin(" || i == "cos(" || i == "tan(")
					i.pop_back();
				operators.push(i);
			}
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

//parsing equation and calculating result for given value of x
double in_to_post(std::string expr, int xval)
{
	postExpr = "";
	std::string i;
    std::stringstream ss(expr);  
	while( ss >> i )
	{
		if(i != "(" && i != ")" && i != "+" && i != "-" && i != "*"
		&& i != "/" && i != "^" && i != "sin(" && i != "cos(" && i != "tan(")
			if(i == "x")
				postExpr += (std::to_string(xval) + " ");
			else
				postExpr += (i + " ");
		else{
			if(operators.empty()){
				if(i == "sin(" || i == "cos(" || i == "tan(")
					i.pop_back();
				operators.push(i);
			}
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
	std::string input;
    std::getline(std::cin, input);
	// if the expression is not parameterized
	if(input.find("x") == -1)
		std::cout << in_to_post(input) << std::endl;
	
	else{
		
		RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
		StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
		
		std::vector<double> x;
		std::vector<double> y;
		
		for( int i = -30; i <= 30; ++i)
		{
			x.push_back(i);
			y.push_back(in_to_post(input, i));
		}
		
		DrawScatterPlot(imageRef, 1000, 800, &x, &y, errorMessage);
		
		std::vector<double> *pngData = ConvertToPNG(imageRef->image);
		
		WriteToFile(pngData, "plot.png");
		
		DeleteImage(imageRef->image);
	}
	return 0;
}
