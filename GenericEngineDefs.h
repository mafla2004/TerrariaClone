#ifndef __ENGDEFS__
#define __ENGDEFS__

#define getter(clazz, field) inline clazz* get##field() { return field; }
#define setter(clazz, field) inline void set##field(clazz* nf)			\
{																		\
	if (field)															\
	{																	\
		getProgramState().onReferenceDestruction(field);				\
	}																	\
																		\
	field = nf;															\
	if (field)															\
	{																	\
		getProgramState().onReferenceCreation(field);					\
	}																	\
}

#endif