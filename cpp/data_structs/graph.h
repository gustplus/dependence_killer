#ifndef DEPENDENCE_KILLER_DATASTURCTS_GRAPH_H_
#define DEPENDENCE_KILLER_DATASTURCTS_GRAPH_H_

#include <string>
#include <stdio.h>

class IComparable;

class INode {
public:
	INode(IComparable *data) : m_data(data) {}
	virtual ~INode();
	virtual bool AddChild(INode *child) = 0;
	virtual INode *GetChild(IComparable *data) = 0;
	
	INode *Parent() {
		return m_parent;
	}
	IComparable *Data() {
		return m_data;
	}

protected:
	INode *m_parent;
	IComparable *m_data;
};

class Graph {
public:
	Graph() : m_root(nullptr) {}
	~Graph() {
		if(m_root) {
			delete m_root;
			m_root = nullptr;
		}
	}

	void SetRoot(INode *node) {
		if(m_root) {
			delete m_root;
		}
		m_root = node;
	}

	INode *Root() { return m_root; }
private:
	INode *m_root;
};

#endif
