#include "string_utils.h"
#include <string.h>

const char *StringUtils::SkipSpaces(const char *str) {
	while(str && (*str == ' ' || *str == '\t')) {
		++str;
	}
	return str;
}

void StringUtils::Trim(char *str) {
	char *search = str;
	while(*search) {
		if(search != str && *search != ' ' && *search != '\t') {
			*(str++) = *search;
		}
		++search;
	}
	*str = '\0';
}

bool StringUtils::StartWith(const char *str, const char *prefix, bool skip_space) {
        if(!prefix) return true;
        if(!str) return false;
	if(skip_space) {
		while(*str == ' ' || *str == '\t' || *str == '\n') {
			++str;
		}
	}
        while(*prefix && *str && *prefix == *(str++)) {++prefix;}
        return *prefix == '\0';
}

bool StringUtils::EndWith(const char *str, const char *postfix, bool skip_space) {
        if(!postfix) return true;
        if(!str) return false;
        const char *p_last = postfix + strlen(postfix) - 1;
        const char *s_last = str + strlen(str) - 1;
	if(skip_space) {
		while(*s_last == ' ' || *s_last == '\t' || *s_last == '\n') {
			--s_last;
		}
	}
        while(p_last >= postfix && s_last >= str && *p_last == *(s_last--)) {--p_last;}
        return (p_last + 1) == postfix;
}

int StringUtils::GetFirstDiffPos(const char *str1, const char *str2) {
	int pos = 0;
	while (*str1 == *str2++) {
		++pos;
		if(*str1++ == 0) {
			return -1;
		}
	}
	return pos;
}
