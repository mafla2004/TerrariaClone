#ifndef __OBJ__
#define __OBJ__

#include <list>
#include <string>
#include <hash_map>
#include <cinttypes>
#include "EngMath.h"

typedef std::string string;
typedef unsigned char byte;

class Object;

// ==================================================================
// PROGRAM STATE
// ==================================================================

struct prog_state
{
private:
	/*
	*	This table keeps a reference to all pointers created in the
	*	lifecycle of the program as well as a counter of all the
	*	references to them, if the counter hits 0, the object is
	*	destroyed.
	*/
	std::hash_map<void*, uint32_t> ptr_table;
public:
	bool addObj(void*);							// Called by the constructor of an object - creates the pointer in the pointer table and initializes the reference counter to 1
	bool onReferenceCreation(void*);			// Called when the reference to an object is set, increments the reference counter of a pointer by 1
	bool onReferenceDestruction(void*);			// Called when the reference to an object is nullified or set to something else, decrements the reference counter by 1
};

prog_state getProgramState();

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

	Object();
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

	Actor* parent;						// The actor this actor is attached to, can be null
	std::list<Actor*> attached_actors;	// The actors attached to this actor

	void detachChild();
public:
	virtual Vector_2D getPosition() final;
	virtual Vector_2D getVelocity() final;
	virtual byte getLayer() final;

	virtual void detachFromParent() final;

	Actor();
	~Actor();
};

inline Vector_2D Actor::getPosition() { return position; }
inline Vector_2D Actor::getVelocity() { return velocity; }
inline byte Actor::getLayer() { return layer; }

#endif