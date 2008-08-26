
#include "Graphics.h"
#include "../motorsport/Os.h"

namespace motorsport_sim {

/** Simple constructor. */
Graphics::Graphics(float frequency): Threadable(frequency), mFrameListener(0), mRoot(0), mWindow(0) {
  // Bouml preserved body begin 0001F5C5
    std::string pluginsPath = "";
    #ifndef OGRE_STATIC_LIB
        // only use plugins.cfg if not static
        pluginsPath = motorsport::Os::getCfgPath("plugins.cfg");
    #endif
    std::string cfgPath = motorsport::Os::getCfgPath("ogre.cfg");
    std::string logPath = motorsport::Os::getLogsPath("ogre.log");
    // prevent Ogre logs from being output to screen. We manually have to create a new log *before* the root is created. It gets deleted automatically when deleting ogre.
    (new LogManager())->createLog(logPath, true, false, false); //TODO: redirect to our own logger.
    LogManager::getSingleton().setLogDetail( LL_BOREME );
    mRoot = new Root(pluginsPath, cfgPath, "");

    // Show the configuration dialog and initialise the system. You can skip this and use root.restoreConfig() to load configuration settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // user clicked OK
        mWindow = mRoot->initialise(true, "MotorsportSim (powered by Motorsport)");
        mSceneMgr = mRoot->createSceneManager(ST_GENERIC);
        loadResources("resources.cfg");
        // set some things up
        Camera* mCamera = mSceneMgr->createCamera("camera"); //what name should we use?
        mCamera->setPosition(Vector3(-3,3,-3));
        mCamera->lookAt(Vector3(0,0,0));
        mCamera->setNearClipDistance(1);
        mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
        mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
        Light* l = mSceneMgr->createLight("MainLight");
        l->setPosition(20,80,50);
        Viewport* vp = mWindow->addViewport(mCamera);
        TextureManager::getSingleton().setDefaultNumMipmaps(5);
        mCamera->setAspectRatio( Real(vp->getActualWidth()) / Real(vp->getActualHeight())); //alters the camera aspect ratio to match the viewport
        vp->setBackgroundColour(ColourValue(0,0,0));
        // we add input controllers
        mFrameListener= new ExampleFrameListener (mWindow, mCamera, mSceneMgr);
        mRoot->addFrameListener(mFrameListener);
        impExp = CreateImpExp(mRoot, mSceneMgr); // set up collada importer/exporter
    }
    else
    {
        //user closed the setup window
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
/** Loads the desired dae file (.dae) with pathname relative to Motorsport data directory. */
void Graphics::loadCollada(string filename) {
  // Bouml preserved body begin 0001F42B
    filename = motorsport::Os::getDataPath(filename);
    impExp->setResourceGroupName(filename);
    impExp->importCollada(filename.c_str());
  // Bouml preserved body end 0001F42B
}
/** Loads the desired ogre resources file (.cfg) with pathname relative to Motorsport data directory. */
void Graphics::loadResources(string filename) {
  // Bouml preserved body begin 0001F483
    filename = motorsport::Os::getDataPath(filename);
    ConfigFile cf;
    cf.load(filename);
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
    //this loads all resource groups to memory. remove for delayed/customized time of load. ogrecollada is not affected by this, i think.
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  // Bouml preserved body end 0001F483
}
/** Loop method, renders things to screen. TODO: make protected.*/
void Graphics::main() {
  // Bouml preserved body begin 0001F6C5
    mRoot->startRendering();
    // frame by frame...
    //mRoot->renderOneFrame();
  // Bouml preserved body end 0001F6C5
}
/** Retrieves a simple space separated list of all nodes existing in the Ogre scene tree, in no particular order.
\param node the Ogre node that will be recursively inspected and printed to string. If NULL or not specified, the Ogre root scene node will be used.
\param level the level of indentation, that is, the depth of the node. only has consequences on the output format (indentation). If 0 or not specified, the first node will have no levels indentation (but its children will, if present).
\returns a string with 4-space indentated,new-line separated node names.*/
string Graphics::getNodeListString(const Node * node, int level) {
  // Bouml preserved body begin 0001F403
    std::string result;
    if (node == NULL) node = mSceneMgr->getRootSceneNode();
    result = "\n";
    for (int j=level;j;j--) result += " ";
    result += node->getName();

    Ogre::Node::ConstChildNodeIterator i = node->getChildIterator();
    while (i.hasMoreElements())
    {
        result += getNodeListString( i.getNext(), level+4 );
    }
    return result;
  // Bouml preserved body end 0001F403
}

} // namespace motorsport_sim
