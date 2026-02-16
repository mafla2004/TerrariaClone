#ifndef __OBJ__
#define __OBJ__

#include <list>
#include <string>
#include <hash_map>
#include <cinttypes>
#include "EngMath.h"
#include "GenericEngineDefs.h"

typedef std::string string;
typedef unsigned char byte;

class Object;

// ==================================================================
// PROGRAM STATE
// ==================================================================

/*	HOW THE GARBAGE COLLECTOR WORKS:
*	The garbage collector will only keep track of references kept in memory "persistently".
*	That is, it will only keep track of pointers declared in the fields of a class.
* 
*	Any pointer gotten through getter methods and stored say in the variable of a function
*	or anyhow stored through a simple assignment is inherently less safe, thus such assignments
*	will only be allowed inside function bodies, in synthesis:
* 
*	function foo()
*	{
*		Object* some_object = some_other_object->getField(); // GOOD!
*	}
* 
*	function bar()
*	{
*		some_object->field = some_other_object->getField(); // BAD!
*	}
* 
*	To avoid such situations, make all pointers to objects inside a class private and update
*	the reference counters in the setters.
*	Not protected. Private.
*	The basics of OOP exist for a reason.
*/

struct prog_state
{
private:
	/*
	*	This table keeps a reference to all pointers created in the
	*	lifecycle of the program as well as a counter of all the
	*	references to them, if the counter hits 0, the object is
	*	destroyed.
	*/
	std::hash_map<Object*, uint32_t> ptr_table;
public:
	bool addObj(Object*);						// Called by the constructor of an object - creates the pointer in the pointer table and initializes the reference counter to 1
	bool onReferenceCreation(Object*);			// Called when the reference to an object is set, increments the reference counter of a pointer by 1
	bool onReferenceDestruction(Object*);		// Called when the reference to an object is nullified or set to something else, decrements the reference counter by 1
};

prog_state getProgramState();

// ==================================================================
// OBJECT
// ==================================================================

class Object
{
friend struct prog_state;
private:
	std::list<string> tags;

protected:
	virtual ~Object() = default;

public:
	virtual int32_t getTagNum() final;
	virtual bool hasTag(const string&) final;
	virtual void addTag(const string&) final;
	virtual void removeTag(const string&) final;

	Object();
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

	/*	NOTE:
	*	Since attached actors are not part of the actor per se,
	*	just actors attached to it at runtime, the reference to parent
	*	does count for the pointer count in the GC.
	* 
	*	Actors made of multiple actors can exist, but in that case the actors will
	*	be actual members of the class, not attached actors.
	* 
	*	In such composite actors, when the ref count of the parent actor reaches 0,
	*	all actors below will be deleted in cascade.
	*/

	Actor* parent;						// The actor this actor is attached to, can be null
	std::list<Actor*> attached_actors;	// The actors attached to this actor

	void detachChild(Actor*);

protected:
	~Actor();

public:
	virtual Vector_2D getPosition() final;
	virtual Vector_2D getVelocity() final;
	virtual byte getLayer() final;

	virtual bool hasChild(Actor*) final;
	virtual void detachFromParent() final;

	Actor();
};

inline Vector_2D Actor::getPosition() { return position; }
inline Vector_2D Actor::getVelocity() { return velocity; }
inline byte Actor::getLayer() { return layer; }

#endif