#pragma once

class Node
{
public:
	enum NodeType
	{
		Operator,
		Number
	};
	virtual ~Node() {}

	Node(NodeType nodeType) :nodeType(nodeType) {}
	inline void SetCodeType(NodeType nodeType) { this->nodeType = nodeType; }
	inline NodeType GetNodeType() { return nodeType; }

	virtual int eval() = 0;

private:
	NodeType nodeType;
};