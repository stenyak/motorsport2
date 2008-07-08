/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_SIM_GRAPHICS_H
#define MOTORSPORT_SIM_GRAPHICS_H

#include <string>
using namespace std;
#include <motorsport-sim/GraphicsHelper.h>

#include <Ogre.h>
using namespace Ogre;
#include "../motorsport/Threadable.h"
#include <OgreCollada.h>
using namespace OgreCollada;

namespace motorsport { class Os; } 

namespace motorsport_sim {

/** Implementation of graphics engine. Takes care of displaying the virtual world on screen. */
class Graphics : public motorsport::Threadable {
  public:
    /** Simple constructor. */
    Graphics(float frequency);
    /** Simple destructor. */
    virtual ~Graphics();
    /** Loads the desired file with pathname relative to Motorsport data directory. */
    void loadCollada(string filename);
    /** Loop method, renders things to screen. */
    void main();

  private:
    ExampleFrameListener* mFrameListener;
    SceneManager* mSceneMgr;
    Root* mRoot;
    RenderWindow* mWindow;
    ImpExp* impExp;
};

} // namespace motorsport_sim
#endif
