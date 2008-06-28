/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_SIM_GRAPHICS_H
#define MOTORSPORT_SIM_GRAPHICS_H

#include <string>
using namespace std;
#include "../motorsport/Threadable.h"
#include <motorsport-sim/GraphicsHelper.h>

#include <Ogre.h>
using namespace Ogre;
#include <OgreCollada.h>
using namespace OgreCollada;

namespace motorsport { class Os; } 

namespace motorsport_sim {

/** Implementation of graphics engine. Takes care of displaying the virtual world on screen. */
class Graphics : public motorsport::Threadable {
  public:
    Graphics(float frequency);
    virtual ~Graphics();
    void loadCollada(string filename);
    void operator()();

  private:
    ExampleFrameListener* mFrameListener;
    SceneManager* mSceneMgr;
    Root* mRoot;
    RenderWindow* mWindow;
};

} // namespace motorsport_sim
#endif
