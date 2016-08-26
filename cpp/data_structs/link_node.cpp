#include "link_node.h"
#include <assert.h>
#include "../framework/comparable.h"

LinkNode *LinkNode::iterator::operator++() {
	LinkNode *node = m_cur;
	m_cur = m_cur->m_cousin;
	return node;
}

LinkNode *LinkNode::iterator::operator++(int) {
	m_cur = m_cur->m_cousin;
	return m_cur;
}

bool LinkNode::AddChild(INode *child) {
	if(!child) return false;
	LinkNode *lchild = dynamic_cast<LinkNode *>(child);
	assert(lchild);
	if(!this->m_fstchild) {
		this->m_fstchild = lchild;
	}else{
		LinkNode *node = this->m_fstchild;
		while(nullptr != node->m_cousin) {
			node = node->m_cousin;
		}
		node->m_cousin = lchild;
	}
	lchild->m_parent = this;
	return true;
}

INode *LinkNode::GetChild(IComparable *data) {
	LinkNode *node = this->m_fstchild;
	while(node && !(node->Data()->Equals(data))) {
		node = node->m_cousin;
	}
	return node;
}
