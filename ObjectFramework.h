#ifndef __OBJ__
#define __OBJ__

#include <list>
#include <string>
#include <cinttypes>
#include "EngMath.h"

typedef std::string string;
typedef unsigned char byte;

// ==================================================================
// OBJECT
// ==================================================================

class Object
{
private:
	std::list<string> tags;

public:
	virtual int32_t getTagNum() final;
	virtual bool hasTag(const string&) final;
	virtual void addTag(const string&) final;
	virtual void removeTag(const string&) final;

	~Object() = default;
};

inline int32_t Object::getTagNum() { return tags.size(); }
inline void Object::addTag(const string& t) { if (!hasTag(t)) tags.push_back(t); }
inline void Object::removeTag(const string& t) { tags.remove(t); }

// ==================================================================
// ACTOR
// ==================================================================

class Actor : public Object
{
private:
	Vector_2D position;
	Vector_2D velocity;
	byte layer;

public:
	virtual Vector_2D getPosition() final;
	virtual Vector_2D getVelocity() final;
	virtual byte getLayer() final;
};

#endif