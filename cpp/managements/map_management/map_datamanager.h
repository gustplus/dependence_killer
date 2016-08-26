#ifndef DEPENDENCE_KILLER_MAP_DATA_MANAGER_H_
#define DEPENDENCE_KILLER_MAP_DATA_MANAGER_H_

#include <string>
#include "map_items.h"
#include "../../framework/i_datamanager.h"

class MapDataManager : public IDataManager {
public:
	MapDataManager() : m_root(nullptr), m_cur(nullptr) {}
	~MapDataManager() {}
	virtual void ReceiveImport(Data &data);
	virtual void ReceiveInherit(Data &data);
	virtual void ReceiveAbsoluteClass(Data &data);
	virtual void EnterPath(const char *path);
	virtual void ExitPath();
	virtual void Dump();
	virtual void DumpDependences();

private:
	void RollRoot();
	Item *GetChild(Item *parent, const std::string &name, ItemType type);
	Item *GetChildFromPackage(Item *parent, Item *dep_pkg, const std::string &name);
	void DealWithDependence(Item *item, const char *relative_path);
	
	/*
		m_root和m_cur节点用于记录整个项目的结构(包括项目的树形结构以及各文件的依赖关系)
		m_deproot和m_curpkg节点用于记录项目中各包之间的依赖关系以及包的度量数据(度量数据
		详见<敏捷软件开发:原则,模式与实践> P249)
	*/

	//map struct
	Item *m_root;	//项目根目录节点
	Item *m_cur;	//当前的工作节点(由EnterPath和ExitPath改变)

	//record the dependences bettween packages
	Item *m_deproot;	//项目根目录节点
	Item *m_curpkg;		//当前的工作节点(由EnterPath和ExitPath改变)
};

#endif
