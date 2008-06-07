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
#include "Loggable.h"
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
    /** Changes the id of this group. The new id should be unique amongst its siblings' ids. \sa addChild */
    virtual void setId(const string & id);
    /** \returns a string that helps identify the object in the generated logs. Syntax is similar unix file paths, using forward slashes for separating a group from its parent. For example "/world/vehicle/rearLeftWheel". */
    virtual const string getGlobalId() const;
    /** Adds a group to the list of \ref children of this group. It will first be detached from its previous parent group if necessary. No child id can be shared amongst several children of the same group. */
    virtual void addChild(shared_ptr< Group > child);

    /** Returns the child group that has the provided id string. \sa addChild */
    virtual shared_ptr<Group> getChild(const string & id) const;
    /** Removes a child from the list of \ref children of this group. \note The child does *not* get deleted unless it's the last reference of it. */
    virtual void removeChild(shared_ptr< Group > child);


  private:
    /** Changes the \ref parent group. \warning It does *not* remove this from the parent's list of \children. */
    virtual void setParent(shared_ptr< Group > parent);
    /** Returns true if an inmediate child is found on this group.
    \param id the id of the child to be searched. */
    virtual bool isChild(const string & id) const;
    /** Returns true if an inmediate child is found on this group.
    \param child the child to be searched. */
    virtual bool isChild(shared_ptr< Group > child) const;
    /** Returns true if any of the ancestors (beginning with this's parent) is the provided group.
    \param group the group to be searched as ancestor. */
    virtual bool isAncestor(shared_ptr< Group > group) const;
    /** Children groups. For example, a car has 4 wheels and a chassis. Therefore, a "car" group would contain 5 children groups. */
    vector<shared_ptr<Group> > children;
    /** Refers to the group that contains this. Each group can only have one parent. The root group parent is zero or null.
    \sa addGroup
    \sa setParent */
    weak_ptr<Group> parent;

};

} // namespace motorsport
#endif
