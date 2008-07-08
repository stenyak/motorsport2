
#include "Graphics.h"
#include "../motorsport/Os.h"

namespace motorsport_sim {

/** Simple constructor. */
Graphics::Graphics(float frequency): Threadable(frequency), mFrameListener(0), mRoot(0), mWindow(0) {
  // Bouml preserved body begin 0001F5C5
    std::string pluginsPath = "";
    // only use plugins.cfg if not static
    #ifndef OGRE_STATIC_LIB
        pluginsPath = motorsport::Os::getCfgPath("plugins.cfg");
    #endif
    std::string cfgPath = motorsport::Os::getCfgPath("ogre.cfg");
    std::string logPath = motorsport::Os::getLogsPath("ogre.log");
    mRoot = new Root(pluginsPath, cfgPath, logPath);
    //Ogre::LogManager::getSingleton().getDefaultLog()->setDebugOutputEnabled(false);
    // Load resource paths from config file
    std::string resourcesPath = motorsport::Os::getCfgPath("resources.cfg");
    ConfigFile cf;
    cf.load(resourcesPath);
    // Go through all sections & settings in the file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();
    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation( String(motorsport::Os::getDataPath(archName)), typeName, secName);
        }
    }
    // Show the configuration dialog and initialise the system. You can skip this and use root.restoreConfig() to load configuration settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true);
        // Create the SceneManager, in this case a generic one
        mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "ExampleSMInstance");
        // Create the camera
        Camera* mCamera = mSceneMgr->createCamera("PlayerCam");
        // Position it at 500 in Z direction
        mCamera->setPosition(Vector3(-3,3,-3));
        // Look back along -Z
        mCamera->lookAt(Vector3(0,0,0));
        mCamera->setNearClipDistance(1);
        // Create one viewport, entire window
        Viewport* vp = mWindow->addViewport(mCamera);
        vp->setBackgroundColour(ColourValue(0,0,0));
        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio( Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
        // Set default mipmap level (NB some APIs ignore this)
        TextureManager::getSingleton().setDefaultNumMipmaps(5);
        // Initialise, parse scripts etc
        /// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
        ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

        // General render setup
        mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
        mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
        Light* l = mSceneMgr->createLight("MainLight");
        l->setPosition(20,80,50);
        mFrameListener= new ExampleFrameListener (mWindow, mCamera, mSceneMgr);
        mRoot->addFrameListener(mFrameListener);
        
        // Set up collada importer/exporter
        impExp = CreateImpExp(mRoot, mSceneMgr);

        LogManager::getSingleton().setLogDetail( LL_BOREME );
    }
  // Bouml preserved body end 0001F5C5
}
/** Simple destructor. */
Graphics::~Graphics() {
  // Bouml preserved body begin 0001F645
    if (mFrameListener)
    {
        delete mFrameListener;
        mFrameListener = NULL;
    }
    if (mRoot)
    {
        delete mRoot; 
        mRoot = NULL;
    }
    if (impExp)
    {
        DestroyImpExp(impExp);
        impExp = NULL;
    }
  // Bouml preserved body end 0001F645
}
/** Loads the desired file with pathname relative to Motorsport data directory. */
void Graphics::loadCollada(string filename) {
  // Bouml preserved body begin 0001F42B
    filename = motorsport::Os::getDataPath(filename);
    impExp->setResourceGroupName(filename);
    impExp->importCollada(filename.c_str());
  // Bouml preserved body end 0001F42B
}
/** Loop method, renders things to screen. */
void Graphics::main() {
  // Bouml preserved body begin 0001F6C5
    mRoot->startRendering();
    // frame by frame...
    //mRoot->renderOneFrame();
  // Bouml preserved body end 0001F6C5
}

} // namespace motorsport_sim
