#ifndef DEPENDENCE_KILL_MAP_ITEMS_H_
#define DEPENDENCE_KILL_MAP_ITEMS_H_

#include <vector>
#include <string>
#include "../../framework/comparable.h"
#include "../../info.h"

typedef enum ItemType {
	TYPE_SRC_FILE,
	TYPE_PACKAGE,
} ItemType;

class Item : public IComparable{
public:
	Item(const std::string &name, ItemType type) : m_name(name), m_type(type), m_parent(nullptr) {}
	~Item();

	virtual bool Equals(const IComparable *other);

	void AddChild(Item *item);
	Item *GetChild(const std::string &name, ItemType type);
	bool HasChild(Item *item);
	void AddDependence(Item *item);
	Item *GetDependence(const std::string &name, ItemType type);
	bool HasDependence(Item *item);

	const std::string &Name() const { return m_name; }
	void SetName(const std::string &name) { m_name = name; }
	const ItemType Type() const { return m_type; }
	Item *Parent() { return m_parent; }
	const Item *Parent() const { return m_parent; }
	
	void Print(int level, bool is_dep = false);
	void PrintDependences(int level, bool show_dep = true);

	void IncreaseR() { ++m_info.R; }
	void IncreaseN() { 
		++m_info.N; 
	}
	void IncreaseAC() { ++m_info.AC; }
	void IncreaseCe() { ++m_info.Ce; }
	void IncreaseCa() { ++m_info.Ca; }

private:
	void _PrintDependences(int level);

	std::string m_name;
	ItemType m_type;
	std::vector<Item *> m_dependences;

	std::vector<Item *> m_children;
	Item *m_parent;

	Info m_info;
};

#endif
