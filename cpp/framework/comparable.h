#ifndef DEPENDENCE_KILLER_FRAMEWORK_CMOPARABLE_H_
#define DEPENDENCE_KILLER_FRAMEWORK_CMOPARABLE_H_

class IComparable {
public:
	virtual ~IComparable() {}
	virtual bool Equals(const IComparable *other) { return false; }
};

#endif
