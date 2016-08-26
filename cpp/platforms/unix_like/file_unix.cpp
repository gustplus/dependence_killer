#include "file_unix.h"
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include "../../utils/string_utils.h"

FileUnix::~FileUnix() {
	if(m_dir) {
		closedir(m_dir);
		m_dir = NULL;
	}
}

const char *FileUnix::Path() {
	return m_path.c_str();
}

bool FileUnix::Exist() {
	if(0 == access(m_path.c_str(), F_OK)) {
		return true;
	}
	return false;
}

bool FileUnix::IsDirectory() {
	struct stat buf;
	return (0 == stat(m_path.c_str(), &buf) && S_ISDIR(buf.st_mode));
}

bool FileUnix::IsFile() {
	struct stat buf;
	return (0 == stat(m_path.c_str(), &buf) && S_ISREG(buf.st_mode));
}

const char *FileUnix::NextEntityName() {
	if(m_dir == NULL) {
		m_dir = opendir(m_path.c_str());
	}
	if(m_dir) {
		struct dirent *entity = NULL;
		if((entity = readdir(m_dir)) != NULL) {
			return entity->d_name;
		}
		closedir(m_dir);
		m_dir = NULL;
	}
	return NULL;
}

File *FileUtilsUnix::OpenFile(const char *path) {
	return new FileUnix(path);
}

bool FileUtilsUnix::GetParentPath(const char *file_name, char *buf, size_t buf_len) {
        if(file_name == NULL || buf == NULL) {
                return false;
        }
        char *dst = strrchr(file_name, '/');
        if(dst) {
                if(dst == file_name) {
                        *buf++ = '/';
                        *buf = '\0';
                }else{
                        size_t len = dst - file_name;
                        if(len >= buf_len) {
                                return false;
                        }else{
                                strncpy(buf, file_name, len);
                                buf[len] = '\0';
                        }
                }
        }else{
                GetAbsolutePath(file_name, buf, buf_len);
                GetParentPath(file_name, buf, buf_len);
        }
        return true;
}

bool FileUtilsUnix::GetAbsolutePath(const char *file_name, char *buf, size_t buf_len) {
        int name_len = 0;
        if('/' != file_name[0] && getcwd(buf, buf_len)) {
                if(StringUtils::StartWith(file_name, "./")) {
                        file_name += 2;
                }
                if(0 != strcmp(buf, "/")) {
                        if(StringUtils::StartWith(file_name, "../")) {
                                GetParentPath(buf, buf, buf_len);
                                file_name += 3;
                        }
                        name_len = strlen(buf);
                        if(buf[name_len - 1] != '/') {
                                buf[name_len++] = '/';
                        }
                }
                strcpy(&buf[name_len], file_name);
        }else{
                strcpy(buf, file_name);
        }
        name_len = strlen(buf);
/*	if('/' == buf[name_len - 1]) {
                buf[--name_len] = '\0'; //remove all last '/', for path redir
        }*/
        if(name_len > 3 && StringUtils::EndWith(buf, "/..")) { //deal with "*/.."
                buf[name_len - 3] = '\0';
                char *p = strrchr(buf, '/');
                if(p != NULL) {
                        *p = '\0';
                }
        }else if (name_len > 2 && StringUtils::EndWith(buf, "/.")) {       //deal with "*/.", ignore "/."
                buf[name_len - 2] = '\0';
        }
        return true;
}
