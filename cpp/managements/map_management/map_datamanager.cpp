#include "map_datamanager.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "map_items.h"
#include "../../framework/i_logger.h"

void MapDataManager::Dump() {
	if(this->m_root) {
		ILogger::GetInstance()->Log("map:\n");
		this->m_root->Print(1);
		ILogger::GetInstance()->Log("\n\n\n");
	}
}

void MapDataManager::DumpDependences() {
	if(this->m_deproot) {
		ILogger::GetInstance()->Log("dependences:\n");
		ILogger::GetInstance()->Log("R: 包内部类的关系数目\n\
N: 包内类总数\n\
AC: 抽象类数目\n\
Ce: 输入耦合度(对本包有依赖的包的数目)\n\
Ca: 输出耦合度(被本包依赖的包的数目)\n\
 H: 内聚性\n\
 A: 抽象性\n\
 I: 不稳定性\n");
		this->m_deproot->PrintDependences(1);
	}
}

void MapDataManager::RollRoot() {
	const char *cur_root_path = this->m_root->Name().c_str();
	const char *parent_c = strrchr(cur_root_path, '/');
	assert(parent_c);
	int root_path_len = parent_c - cur_root_path;

	Item *new_root = new Item(std::string(cur_root_path, root_path_len), TYPE_PACKAGE);
	Item *new_dep_root = new Item(new_root->Name(), TYPE_PACKAGE);

	this->m_root->SetName(cur_root_path + 1);
	this->m_deproot->SetName(this->m_root->Name());

	new_root->AddChild(this->m_root);
	this->m_root = new_root;
	
	new_dep_root->AddChild(this->m_deproot);
	this->m_deproot = new_dep_root;
}

Item *MapDataManager::GetChild(Item *parent, const std::string &name, ItemType type) {
	Item *i = parent->GetChild(name, type);
	if(!i) {
		i = new Item(name, type);
		parent->AddChild(i);
	}
	return i;
}

Item *MapDataManager::GetChildFromPackage(Item *parent, Item *dep_pkg, const std::string &name) {
	assert(parent->Type() == TYPE_PACKAGE);
	Item *i = parent->GetChild(name, TYPE_SRC_FILE);
	if(!i) {
		i = new Item(name, TYPE_SRC_FILE);
		parent->AddChild(i);
		dep_pkg->IncreaseN();
	}
	return i;
}

void MapDataManager::DealWithDependence(Item *item, const char *relative_path) {
	if(item) {
		const char *path = relative_path;
		Item *working_pkg = m_cur;
		Item *working_dep = m_curpkg;
		while(strncmp(path, "../", 3) == 0) {
			if(!working_pkg->Parent()) {
				RollRoot();
				working_pkg = this->m_root;
				working_dep = this->m_deproot;
			}else{
				working_pkg = working_pkg->Parent();
				working_dep = working_dep->Parent();
			}
			path += 3;
		}
		char *end = NULL;
		while(NULL != (end = strchr(path, '/'))) {
			std::string pkg(path, end - path);
			path = end + 1;
			Item *new_pkg = GetChild(working_pkg, pkg, TYPE_PACKAGE);
			Item *new_dep = GetChild(working_dep, pkg, TYPE_PACKAGE);
			working_pkg = new_pkg;
			working_dep = new_dep;
		}

		if(this->m_curpkg != working_dep) {
			if(!this->m_curpkg->HasDependence(working_dep)) {
				m_curpkg->AddDependence(working_dep);
				working_dep->IncreaseCa();
				this->m_curpkg->IncreaseCe();
			}
		}else{
			this->m_curpkg->IncreaseR();
		}
		
		end = strrchr(path, '.');
		std::string dep_name = end ? std::string(path, end - path) : path;
		Item *src = GetChildFromPackage(working_pkg, working_dep, dep_name);
		if(item != src) {
			item->AddDependence(src);
		}
	}
}

void MapDataManager::ReceiveImport(Data &data) {
	Item *src = GetChildFromPackage(this->m_cur, this->m_curpkg, data.data0.c_str());
	DealWithDependence(src, data.data1.c_str());
}

void MapDataManager::ReceiveInherit(Data &data) {

}

void MapDataManager::ReceiveAbsoluteClass(Data &data) {
	m_curpkg->IncreaseAC();
}

void MapDataManager::EnterPath(const char *path) {
	if(!this->m_root) {
		this->m_root = new Item(path, TYPE_PACKAGE);
		this->m_cur = this->m_root;
		this->m_deproot = new Item(path, TYPE_PACKAGE);
		this->m_curpkg = this->m_deproot;
	}else{
		const char * name = strrchr(path, '/');
		name = name != NULL ? name + 1 : path;
		m_cur = GetChild(m_cur, name, TYPE_PACKAGE);
		m_curpkg = GetChild(m_curpkg, name, TYPE_PACKAGE);
	}
}

void MapDataManager::ExitPath() {
	m_cur = m_cur->Parent();
	m_curpkg = m_curpkg->Parent();
}
