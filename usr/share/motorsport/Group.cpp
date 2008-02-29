
#include "motorsport/Group.h"
#include "motorsport/Exception.h"

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
void Group::setId(const string & id) {
  // Bouml preserved body begin 0001F723
    Loggable::setId(id);

    string::size_type loc = id.find('/');
    if( loc != string::npos )
        throw Exception(string("Can't set the id \"")+id+"\", it must not contain '/' characters.");

    this->id = id;
  // Bouml preserved body end 0001F723
}
/** \returns a string that helps identify the object in the generated logs. */
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

/** Changes the \ref parent. */
void Group::setParent(shared_ptr< Group > parent) {
  // Bouml preserved body begin 0001FC66
    if (shared_ptr<Group> p = this->parent.lock())
    {
        if (p != parent)
        {
            p->removeGroup(shared_from_this());
        }
    }
    this->parent = parent;
  // Bouml preserved body end 0001FC66
}
/** Moves a group to the \ref groups list of this group. The group gets its parent group changed accordingly. */
void Group::addGroup(shared_ptr< Group > group) {
  // Bouml preserved body begin 0001F9E5
  shared_ptr<Group> t = shared_from_this();
  group->setParent(t);
  groups.push_back(group);
  // Bouml preserved body end 0001F9E5
}

/** Moves a group to the \ref groups list of this group. The group gets its parent group changed accordingly. */
void Group::removeGroup(shared_ptr< Group > group) {
  // Bouml preserved body begin 0001F544
    vector< shared_ptr<Group> >::iterator i;
    vector< shared_ptr<Group> >::iterator g = groups.end();
    for(i=groups.begin(); i!=groups.end(); i++)
    {
        if(*i == group) g = i;
    }
    if (g != groups.end())
        groups.erase(g);
  // Bouml preserved body end 0001F544
}

/** Default constructor, should not be used. */
Group::Group(): Loggable("") {
  // Bouml preserved body begin 0001FBE6
    throw Exception("What the hell?!");
  // Bouml preserved body end 0001FBE6
}

} // namespace motorsport
