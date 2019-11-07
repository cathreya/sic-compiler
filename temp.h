#include "visitor.h"

#ifndef TEMP_H
#define TEMP_H

class Node{
public:
	Node(){}
	~Node(){}
	virtual void accept(Visitor *v) = 0;
};


class Term: public Node{
public:
	Term(){}
	~Term(){}
	virtual void accept(Visitor *v) = 0;
};

#endif