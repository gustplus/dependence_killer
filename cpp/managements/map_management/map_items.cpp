#include "map_items.h"
#include <stdio.h>
#include <assert.h>
#include "../../framework/i_logger.h"

Item::~Item() {
	std::vector<Item *>::reverse_iterator it = m_children.rbegin();
	for(; it != m_children.rend(); ++it) {
		delete *it;
	}
}

bool Item::Equals(const IComparable *other) {
	const Item *o = dynamic_cast<const Item *>(other);
	assert(o);
	return (o->Name() == this->Name() && o->Type() == this->Type());
}

void Item::AddChild(Item *item) {
	if(item->Parent()) {
		printf("re add:%s (%s/%s)\n", item->Name().c_str(), item->Parent()->Name().c_str(), this->Name().c_str());
	}
	assert(!item->m_parent);
	item->m_parent = this;
	m_children.push_back(item);
}

Item *Item::GetChild(const std::string&name, ItemType type) {
	std::vector<Item *>::iterator it = m_children.begin();
	for(; it != m_children.end(); ++it) {
		if((*it)->Name() == name && (*it)->Type() == type) {
			return *it;	
		}
	}
	return nullptr;
}

bool Item::HasChild(Item *item) {
	std::vector<Item *>::iterator c = find(this->m_children.begin(), this->m_children.end(), item);
	return c != m_children.end();
}

void Item::AddDependence(Item *item) {
	m_dependences.push_back(item);
}

Item *Item::GetDependence(const std::string &name, ItemType type) {
	std::vector<Item *>::iterator it = m_dependences.begin();
	for(; it != m_dependences.end(); ++it) {
		if((*it)->Name() == name && (*it)->Type() == type) {
			return *it;	
		}
	}
	Item *i = new Item(name, type);
	AddDependence(i);
	return i;
}

bool Item::HasDependence(Item *item) {
	std::vector<Item *>::iterator d = find(this->m_dependences.begin(), this->m_dependences.end(), item);
	return d != m_dependences.end();
}

void Item::Print(int level, bool is_dep) {
	int retain_lv = level;
	while(--retain_lv >= 0) {
		ILogger::GetInstance()->Log("\t");
	}
	if(m_type == TYPE_PACKAGE) {
		ILogger::GetInstance()->Log("package: %s\n", m_name.c_str());
		std::vector<Item *>::iterator it = m_children.begin();
		for(; it != m_children.end(); ++it) {
			(*it)->Print(level + 1, false);
		}
	}else{
		ILogger::GetInstance()->Log("%s: %s\n", is_dep ? "dep" : "src", m_name.c_str());
		if(!is_dep) {
			std::vector<Item *>::iterator it = m_dependences.begin();
			for(; it != m_dependences.end(); ++it) {
				(*it)->Print(level + 1, true);
			}
		}
	}
}

void Item::PrintDependences(int level, bool show_dep) {
	if(m_type == TYPE_PACKAGE) {
		int retain_lv = level;
		while(--retain_lv >= 0) {
			ILogger::GetInstance()->Log("\t");
		}
		m_info.Calculate();
		ILogger::GetInstance()->Log("pkg: %s", m_name.c_str());
		if(m_info.N > 0) {
			ILogger::GetInstance()->Log(": R:%d, N:%d, AC:%d, Ce:%d, Ca:%d, H:%.3f, A:%.3f, I:%.3f, D:%.3f D':%.3f\n", m_info.R, m_info.N, m_info.AC, m_info.Ce, m_info.Ca, m_info.GetH(), m_info.GetA(), m_info.GetI(), m_info.GetD(), m_info.GetD2());
			++level;
		}else{
			ILogger::GetInstance()->Log("\n");
		}
		this->_PrintDependences(level);
		std::vector<Item *>::iterator it = m_children.begin();
		for(; it != m_children.end(); ++it) {
			(*it)->PrintDependences(level + 1);
		}
	}else{
		fprintf(stderr, "%s's type is err!\n", m_name.c_str());
	}
}

void Item::_PrintDependences(int level) {
	std::vector<Item *>::iterator it = m_dependences.begin();
	for(; it != m_dependences.end(); ++it) {
		int retain_lv = level;
		while(--retain_lv >= 0) {
			ILogger::GetInstance()->Log("\t");
		}
		ILogger::GetInstance()->Log("dep: %s\n", (*it)->m_name.c_str());
	}
}
