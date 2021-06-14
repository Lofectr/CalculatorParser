#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Operator.h"
using namespace std;

inline bool isNum(char ch)
{
	return ch >= 48 && ch <= 57;
}

inline bool isOp(char ch)
{
	return ch == 42 || ch == 43 || ch == 45 || ch == 47;
}


enum OperatorTypeWS
{
	_Add,
	_Sub,
	_Mul,
	_Div
};

Node* GetParent(const vector<Node*>& nodes, int& index)
{
	Operator* parent = nullptr;
	for (int i = 0; i < nodes.size(); ++i)
	{
		Operator* op = dynamic_cast<Operator*>(nodes[i]);
		if (op != nullptr && (parent == nullptr || op->z <= parent->z))
		{
			parent = op;
			index = i;
		}
	}
	if (parent == nullptr)
	{
		index = 0;
		return nodes[0];
	}
	return parent;
}

template<class T>
inline vector<T> mid(const vector<T>& vec, int from, int size)
{
	return vector<T>(vec.begin() + from, vec.begin() + from + size);
}

void ProcessNodes(const vector<Node*>& nodes, Node* parent, int indexParent)
{
	int newIndexPrev, newIndexNext;
	vector<Node*> expPrev = mid(nodes, 0, indexParent);
	Node* prev = GetParent(expPrev, newIndexPrev);

	vector<Node*> expNext = mid(nodes, indexParent + 1, nodes.size() - indexParent - 1);
	Node* next = GetParent(expNext, newIndexNext);
		

	Operator* op = dynamic_cast<Operator*>(parent);
	if (op == nullptr)
		return;
	op->nodeFirst = prev;
	op->nodeSecond = next;

	if(next->GetNodeType() != Node::Number)
		ProcessNodes(expNext, next, newIndexNext);

	if (prev->GetNodeType() != Node::Number)
		ProcessNodes(expPrev, prev, newIndexPrev);
}

int Calc(const string& str)
{
	vector<Node*> nodes;
	string strNum;
	int z = 0;
	OperatorTypeWS st = _Add;

	for (int i = 0; i < str.size(); ++i)
	{
		if (isNum(str[i]))
		{
			strNum += str[i];
		}
		else if(!strNum.empty())
		{
			nodes.push_back(new Number(stoi(strNum)));
			strNum.clear();
		}
	
		if (isOp(str[i]))
		{
			if (str[i] == '*')
			{
				if(st != _Mul && st != _Div)++z;
				st = _Mul;
			}
			else if (str[i] == '/')
			{
				if (st != _Mul && st != _Div)++z;
				st = _Div;
			}
			else if (str[i] == '+')
			{
				if (st != _Add && st != _Sub)--z;
				st = _Add;
			}
			else if (str[i] == '-')
			{
				if (st != _Add && st != _Sub)--z;
				st = _Sub;
			}
			Operator* newOp = new Operator((Operator::OperatorType)str[i]);
			newOp->z = z;
			nodes.push_back(newOp);
		}
		else if (str[i] == '(')
		{
			++z;
		}
		else if (str[i] == ')')
		{
			--z;
		}
	}
	if (!strNum.empty())
	{
		nodes.push_back(new Number(stoi(strNum)));
		strNum.clear();
	}

	int parentIndex;
	Node* parent = GetParent(nodes, parentIndex);

	ProcessNodes(nodes, parent, parentIndex);

	return parent->eval();
}

int main()
{
	string data = "99 * 3 - (100 / 9 + 1)";
	cout << Calc(data);
	return 0;
}