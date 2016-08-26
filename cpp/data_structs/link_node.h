#ifndef DEPENDENCE_KILLER_DATASTRUCTS_LINKNODE_H_
#define DEPENDENCE_KILLER_DATASTRUCTS_LINKNODE_H_

#include "graph.h"

class LinkNode : public INode {
public:
	class iterator {
	public:
		iterator(LinkNode *node) : m_cur(node) {}
		LinkNode *operator->() { return m_cur; }
		const LinkNode *operator->() const { return m_cur; }
		LinkNode *operator*() { return m_cur; }
		const LinkNode *operator*() const { return m_cur; }
		bool operator==(const iterator &node) const { return m_cur == node.m_cur; }
		bool operator!=(const iterator &node) const { return m_cur != node.m_cur; }
		LinkNode *operator++();
		LinkNode *operator++(int);
	private:
		LinkNode *operator--();
		LinkNode *operator--(int);

		LinkNode *m_cur;
	};

	LinkNode(IComparable *data) : INode(data), m_fstchild(nullptr), m_cousin(nullptr) {}
	~LinkNode() {}
	virtual bool AddChild(INode *child);
	virtual INode *GetChild(IComparable *data);
	
	iterator begin() { return iterator(m_fstchild); }
	iterator end() { return iterator(nullptr); }
private:
	LinkNode *m_fstchild;
	LinkNode *m_cousin;	
};

#endif
