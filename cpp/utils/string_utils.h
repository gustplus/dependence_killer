#ifndef DEPENDENCE_KILLER_UTILS_STRINGUTILS_H_
#define DEPENDENCE_KILLER_UTILS_STRINGUTILS_H_

class StringUtils {
public:
	static const char *SkipSpaces(const char *str);
	static void Trim(char *str);

	static bool StartWith(const char *str, const char *prefix, bool skip_space = false);
	static bool EndWith(const char *str, const char *postfix, bool skip_space = false);
	static int GetFirstDiffPos(const char *str1, const char *str2);

};

#endif
