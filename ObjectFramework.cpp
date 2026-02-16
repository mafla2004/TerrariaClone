#include "EngineBase.h"

// ==================================================================
// OBJECT
// ==================================================================

Object::Object()
{

}

bool Object::hasTag(const string& tag)
{
	for (string t : tags)
	{
		if (t == tag)
		{
			return true;
		}
	}
	return false;
}

// ==================================================================
// ACTOR
// ==================================================================

Actor::Actor()
{
	Object::Object();

	parent = nullptr;

	attached_actors = std::list<Actor*>();
}

Actor::~Actor()
{
	Object::~Object();

	/* This constructor will be called IF AND ONLY IF */
}

void Actor::detachFromParent()
{
	parent->detachChild(this);

	getProgramState().onReferenceDestruction(parent);
	parent = nullptr;
}

void Actor::detachChild(Actor* c)
{
	if (!hasChild(c))
	{
		return;
	}

	attached_actors.remove(c);
	getProgramState().onReferenceDestruction(c);
}