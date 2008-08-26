/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_SIM_GRAPHICS_H
#define MOTORSPORT_SIM_GRAPHICS_H

#include <string>
using namespace std;
#include <Ogre.h>
using namespace Ogre;
#include <motorsport-sim/GraphicsHelper.h>

#include <OgreCollada.h>
using namespace OgreCollada;
#include "../motorsport/Threadable.h"

namespace motorsport { class Os; } 

namespace motorsport_sim {

/** Implementation of graphics engine. Takes care of displaying the virtual world on screen. */
class Graphics : public motorsport::Threadable {
  public:
    /** Simple constructor. */
    Graphics(float frequency);
    /** Simple destructor. */
    virtual ~Graphics();
    /** Loads the desired dae file (.dae) with pathname relative to Motorsport data directory. */
    void loadCollada(string filename);
    /** Loads the desired ogre resources file (.cfg) with pathname relative to Motorsport data directory. */
    void loadResources(string filename);
    /** Loop method, renders things to screen. TODO: make protected.*/
    void main();
    /** Retrieves a simple space separated list of all nodes existing in the Ogre scene tree, in no particular order.
    \param node the Ogre node that will be recursively inspected and printed to string. If NULL or not specified, the Ogre root scene node will be used.
    \param level the level of indentation, that is, the depth of the node. only has consequences on the output format (indentation). If 0 or not specified, the first node will have no levels indentation (but its children will, if present).
    \returns a string with 4-space indentated,new-line separated node names.*/
    string getNodeListString(const Node * node = NULL, int level = 0);

  private:
    ExampleFrameListener* mFrameListener;
    SceneManager* mSceneMgr;
    Root* mRoot;
    RenderWindow* mWindow;
    ImpExp* impExp;
};

} // namespace motorsport_sim
#endif
