/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_GROUP_H
#define MOTORSPORT_GROUP_H

#include <string>
using namespace std;
#include <boost/shared_ptr.hpp>
using namespace boost;
#include <vector>
using namespace std;
#include <boost/weak_ptr.hpp>
using namespace boost;
#include "motorsport/Loggable.h"
#include <boost/enable_shared_from_this.hpp>
using namespace boost;

namespace motorsport { class Exception; } 

namespace motorsport {

/** A Group is a class that can hold other \ref groups inside it. Each group represents a concept in the Motorsport virtual world, for example a car, a track, a pitbox, a person, etc. Many classes are derived from this. */
class Group : public Loggable, public enable_shared_from_this<Group> {
  public:
    /** Simple constructor.
    \param name the name that will be used in its logs. */
    Group(const string & id);
    /** Simple destructor. */
    virtual ~Group();
    virtual void setId(const string & id);
    /** \returns a string that helps identify the object in the generated logs. */
    virtual const string getGlobalId() const;
    /** Changes the \ref parent. */
    void setParent(shared_ptr< Group > parent);
    /** Moves a group to the \ref groups list of this group. The group gets its parent group changed accordingly. */
    void addGroup(shared_ptr< Group > group);

    /** Moves a group to the \ref groups list of this group. The group gets its parent group changed accordingly. */
    void removeGroup(shared_ptr< Group > group);

    /** Returns an string with some debug information about the group. */
    virtual const string debugStr(int indent = 0) const;

  protected:
    /** Children groups. For example, a car has 4 wheels and a chassis. Therefore, a "car" group would contain 5 groups. */
    vector<shared_ptr<Group> > groups;

    /** Refers to the group that contains this. Each group can only have one parent. The root group parent is zero or null.
    \sa addGroup
    \sa setParent */
    weak_ptr<Group> parent;


  private:
    /** Default constructor, should not be used. */
    Group();
};

} // namespace motorsport
#endif
