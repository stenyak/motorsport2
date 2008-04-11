
#include "Group.h"
#include "Exception.h"

namespace motorsport {

/** Simple constructor.
\param name the name that will be used in its logs. */
Group::Group(const string & id): Loggable(id) {
  // Bouml preserved body begin 0001FAE6
    setId(id);
  // Bouml preserved body end 0001FAE6
}
/** Simple destructor. */
Group::~Group() {
  // Bouml preserved body begin 0001FB66
  // Bouml preserved body end 0001FB66
}
/** Changes the id of this group. The new id should be unique amongst its siblings' ids. \sa addChild */
void Group::setId(const string & id) {
  // Bouml preserved body begin 0001F723
    string::size_type loc = id.find('/');
    if( loc != string::npos )
        throw Exception(string("Can't set the id \"")+id+"\", it must not contain '/' characters.");

    Loggable::setId(id);
  // Bouml preserved body end 0001F723
}
/** \returns a string that helps identify the object in the generated logs. Syntax is similar unix file paths, using forward slashes for separating a group from its parent. For example "/world/vehicle/rearLeftWheel". */
const string Group::getGlobalId() const {
  // Bouml preserved body begin 0001FE66
    string result;

    if (shared_ptr<Group> p = parent.lock())
        result += p->getGlobalId();

    result += "/";
    result += Loggable::getId();

    return result;
  // Bouml preserved body end 0001FE66
}

/** Adds a group to the list of \ref children of this group. It will first be detached from its previous parent group if necessary. No child id can be shared amongst several children of the same group. */
void Group::addChild(shared_ptr< Group > child) {
  // Bouml preserved body begin 0001F9E5
    if (!child)
        throw Exception("Couldn't add child, it's uninitialized.");
    shared_ptr<Group> t = shared_from_this();
    if (t == child)
        throw Exception("Couldn't add child to itself.");
    if (isChild(child))
        throw Exception("Couldn't add child, it's already a child.");
    if (isAncestor(child))
        throw Exception("Couldn't add child, it must not be any ancestor of this group.");
    if (isChild(child->getId()))
        throw Exception("Couldn't add child, its id is already in use by another child.");

    child->setParent(t);
    children.push_back(child);
  // Bouml preserved body end 0001F9E5
}

/** Returns the child group that has the provided id string. \sa addChild */
shared_ptr<Group> Group::getChild(const string & id) const {
  // Bouml preserved body begin 0001F5C0
    vector<shared_ptr<Group> >::const_iterator result;
    if (!isChild(id))
        throw Exception ("Couldn't get child, none has the provided id.");

    for(result=children.begin(); result!=children.end(); result++)
        if ((*result)->getId() == id)
            break;

    return *result;
  // Bouml preserved body end 0001F5C0
}
/** Removes a child from the list of \ref children of this group. \note The child does *not* get deleted unless it's the last reference of it. */
void Group::removeChild(shared_ptr< Group > child) {
  // Bouml preserved body begin 0001F544
    vector<shared_ptr<Group> >::iterator it;
    for(it=children.begin(); it!=children.end(); it++)
        if (*it == child)
            break;

    children.erase(it);
  // Bouml preserved body end 0001F544
}

/** Changes the \ref parent group. \warning It does *not* remove this from the parent's list of \children. */
void Group::setParent(shared_ptr< Group > parent) {
  // Bouml preserved body begin 0001FC66
    if (shared_ptr<Group> p = this->parent.lock())
        if (p != parent)
            p->removeChild(shared_from_this());

    this->parent = parent;
  // Bouml preserved body end 0001FC66
}
/** Returns true if an inmediate child is found on this group.
\param id the id of the child to be searched. */
bool Group::isChild(const string & id) const {
  // Bouml preserved body begin 0001F6C0
    bool result = true;
    vector<shared_ptr<Group> >::const_iterator it;
    for(it=children.begin(); it!=children.end(); it++)
        if ((*it)->getId() == id)
            break;

    if (it == children.end())
        result = false;

    return result;
  // Bouml preserved body end 0001F6C0
}
/** Returns true if an inmediate child is found on this group.
\param child the child to be searched. */
bool Group::isChild(shared_ptr< Group > child) const {
  // Bouml preserved body begin 0001F740
    bool result = true;
    vector<shared_ptr<Group> >::const_iterator it;
    for(it=children.begin(); it!=children.end(); it++)
        if (*it == child)
            break;

    if (it == children.end())
        result = false;

    return result;
  // Bouml preserved body end 0001F740
}
/** Returns true if any of the ancestors (beginning with this's parent) is the provided group.
\param group the group to be searched as ancestor. */
bool Group::isAncestor(shared_ptr< Group > group) const {
  // Bouml preserved body begin 0001F640
    bool result = false;

    shared_ptr<Group const> t = shared_from_this();
    if (group == t)
        result = true;
    else
        if (shared_ptr<Group const> p = parent.lock())
            result = p->isAncestor(group);

    return result;
  // Bouml preserved body end 0001F640
}

} // namespace motorsport
