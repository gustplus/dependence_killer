#include "graph.h"
#include "../framework/comparable.h"

INode::~INode() {
	if(m_data) {
		delete m_data;
		m_data = nullptr;
	}
}

