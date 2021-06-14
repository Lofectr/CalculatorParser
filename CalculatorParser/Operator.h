#pragma once
#include "Node.h"
#include "Number.h"

class Operator : public Node
{
public:
	enum OperatorType
	{
		Add = 43,
		Sub = 45,
		Mul = 42,
		Div = 47
	};
	Operator(OperatorType opType) : opType(opType), Node(Node::Operator) {}
	inline void SetOpType(OperatorType num) { this->opType = opType; }
	inline OperatorType GetOpType() { return opType; }

	Node* nodeFirst;
	Node* nodeSecond;

	int eval() override
	{
		int first = nodeFirst->eval(), second = nodeSecond->eval();
		switch (opType)
		{
		case Operator::Add:
			return first + second;
			break;
		case Operator::Sub:
			return first - second;
			break;
		case Operator::Mul:
			return first * second;
			break;
		case Operator::Div:
			return first / second;
			break;
		default:
			return 0;
			break;
		}
	}
	int z = 0;
private:
	OperatorType opType;
};