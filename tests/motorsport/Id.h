#ifndef ID_H_
#define ID_H_

//This file and its classes are drafts.

#include <string>
#include <vector>

typedef std::string Instance;
enum Class { World, Area, Vehicle, Wheel };
std::string class2str(Class c)
{
    std::string result;
    switch (c)
    {
        case World: result = "World"; break;
        case Area: result = "Area"; break;
        case Vehicle: result = "Vehicle"; break;
        case Wheel: result = "Wheel"; break;
        default: result = ""; break;
    }
    return result;
}
class ClassInstance
{
  public:
    ClassInstance(Class c, Instance i)
    {
        this->c = c;
        this->i = i;
    }
    ~ClassInstance();
    std::string str()
    {
        return class2str(c) + "::" + i;
    }
  private:
    Class c;
    Instance i;
};

class Id
{
  public:
	Id(Id parent, Class c, Instance i)
	{
	    classInstances = parent.classInstances.copy().append(new ClassInstance(c, i));
	}
	void move(Id parent)
	{
	    classInstances = parent.copy().append(getClassInstance);
	}
	ClassInstance getClassInstance()
	{
	    return classInstances.last();
	}
	/** Used for serializing and developer debug texts */
	std::string str()
	{
	    std::string result;
	    foreach (classInstance in classInstances)
	    {
	        result += "/" + classInstance.str();
	    }
	}
	virtual ~Id();
  private:
    vector<ClassInstance> classInstances;
};

#endif /*ID_H_*/
