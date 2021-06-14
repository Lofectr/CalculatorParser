#pragma once
#include "Node.h"

class Number : public Node
{
public:
	Number(int num = 0) : num(num), Node(Node::Number) {}
	inline void SetNum(int num) { this->num = num; }
	int eval() override { return num; }
private:
	int num;
};