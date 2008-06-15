#include <unittest++/UnitTest++.h>
#include <boost/shared_ptr.hpp>
using namespace boost;
#include <motorsport/Group.h>
#include <motorsport/Core.h>
#include <motorsport/Exception.h>
using namespace motorsport;
#include <motorsport-sim/Sim.h>
#include <motorsport-sim/Graphics.h>
using namespace motorsport_sim;
#include "OgreCollada.h"
using namespace OgreCollada;

#include "Ogre.h"
using namespace Ogre;
#include "OgreConfigFile.h"
#include "Ogre.h"
#include "OgreStringConverter.h"
#include "OgreException.h"

//Use this define to signify OIS will be used as a DLL (so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

class ExampleFrameListener: public FrameListener, public WindowEventListener
{
    public:
        // Constructor takes a RenderWindow because it uses that to determine input context
        ExampleFrameListener(RenderWindow* win, Camera* cam, SceneManager* mgr, bool bufferedKeys = false, bool bufferedMouse = false, bool bufferedJoy = false )
            : mCamera(cam), mTranslateVector(Vector3::ZERO), mWindow(win), mStatsOn(true), mNumScreenShots(0), mMoveScale(0.0f), mRotScale(0.0f), mTimeUntilNextToggle(0), mFiltering(TFO_BILINEAR), mAniso(1), mSceneDetailIndex(0), mMoveSpeed(100), mRotateSpeed(36), mDebugOverlay(0), mInputManager(0), mMouse(0), mKeyboard(0), mJoy(0), mCurvature(1), mTiling(15), mSceneMgr(mgr)
        {
            using namespace OIS;
            mDebugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");
            LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
            ParamList pl;
            size_t windowHnd = 0;
            std::ostringstream windowHndStr;
            win->getCustomAttribute("WINDOW", &windowHnd);
            windowHndStr << windowHnd;
            pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
            mInputManager = InputManager::createInputSystem( pl );
            //Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
            mKeyboard = static_cast<Keyboard*>(mInputManager->createInputObject( OISKeyboard, bufferedKeys ));
            mMouse = static_cast<Mouse*>(mInputManager->createInputObject( OISMouse, bufferedMouse ));
            try {
                mJoy = static_cast<JoyStick*>(mInputManager->createInputObject( OISJoyStick, bufferedJoy ));
            }
            catch(...) {
                mJoy = 0;
            }
            //Set initial mouse clipping size
            windowResized(mWindow);
            showDebugOverlay(true);
            //Register as a Window listener
            WindowEventUtilities::addWindowEventListener(mWindow, this);
        }
        //Adjust mouse clipping area
        void windowResized(RenderWindow* rw)
        {
            unsigned int width, height, depth;
            int left, top;
            rw->getMetrics(width, height, depth, left, top);
            const OIS::MouseState &ms = mMouse->getMouseState();
            ms.width = width;
            ms.height = height;
        }
        //Unattach OIS before window shutdown (very important under Linux)
        void windowClosed(RenderWindow* rw)
        {
            //Only close for window that created OIS (the main window in these demos)
            if( rw == mWindow )
            {
                if( mInputManager )
                {
                    mInputManager->destroyInputObject( mMouse );
                    mInputManager->destroyInputObject( mKeyboard );
                    mInputManager->destroyInputObject( mJoy );
                    OIS::InputManager::destroyInputSystem(mInputManager);
                    mInputManager = 0;
                }
            }
        }
        ~ExampleFrameListener()
        {
            //Remove ourself as a Window listener
            WindowEventUtilities::removeWindowEventListener(mWindow, this);
            windowClosed(mWindow);
        }

        bool processUnbufferedKeyInput(const FrameEvent& evt)
        {
            using namespace OIS;
            if(mKeyboard->isKeyDown(KC_A)) mTranslateVector.x = -mMoveScale;	// Move camera left
            if(mKeyboard->isKeyDown(KC_D)) mTranslateVector.x = mMoveScale;	// Move camera RIGHT
            if(mKeyboard->isKeyDown(KC_UP) || mKeyboard->isKeyDown(KC_W) ) mTranslateVector.z = -mMoveScale;	// Move camera forward
            if(mKeyboard->isKeyDown(KC_DOWN) || mKeyboard->isKeyDown(KC_S) ) mTranslateVector.z = mMoveScale;	// Move camera backward
            if(mKeyboard->isKeyDown(KC_PGUP)) mTranslateVector.y = mMoveScale;	// Move camera up
            if(mKeyboard->isKeyDown(KC_PGDOWN)) mTranslateVector.y = -mMoveScale;	// Move camera down
            if(mKeyboard->isKeyDown(KC_RIGHT)) mCamera->yaw(-mRotScale);
            if(mKeyboard->isKeyDown(KC_LEFT)) mCamera->yaw(mRotScale);
            if( mKeyboard->isKeyDown(KC_ESCAPE) || mKeyboard->isKeyDown(KC_Q) ) return false;
            if( mKeyboard->isKeyDown(KC_F) && mTimeUntilNextToggle <= 0 )
            {
                mStatsOn = !mStatsOn;
                showDebugOverlay(mStatsOn);
                mTimeUntilNextToggle = 1;
            }
            if( mKeyboard->isKeyDown(KC_T) && mTimeUntilNextToggle <= 0 )
            {
                switch(mFiltering)
                {
                    case TFO_BILINEAR:
                        mFiltering = TFO_TRILINEAR;
                        mAniso = 1;
                        break;
                    case TFO_TRILINEAR:
                        mFiltering = TFO_ANISOTROPIC;
                        mAniso = 8;
                        break;
                    case TFO_ANISOTROPIC:
                        mFiltering = TFO_BILINEAR;
                        mAniso = 1;
                        break;
                    default: break;
                }
                MaterialManager::getSingleton().setDefaultTextureFiltering(mFiltering);
                MaterialManager::getSingleton().setDefaultAnisotropy(mAniso);
                showDebugOverlay(mStatsOn);
                mTimeUntilNextToggle = 1;
            }
            if(mKeyboard->isKeyDown(KC_SYSRQ) && mTimeUntilNextToggle <= 0)
            {
                std::ostringstream ss;
                ss << "screenshot_" << ++mNumScreenShots << ".png";
                mWindow->writeContentsToFile(ss.str());
                mTimeUntilNextToggle = 0.5;
                mDebugText = "Saved: " + ss.str();
            }
            if(mKeyboard->isKeyDown(KC_R) && mTimeUntilNextToggle <=0)
            {
                mSceneDetailIndex = (mSceneDetailIndex+1)%3 ;
                switch(mSceneDetailIndex) {
                    case 0 : mCamera->setPolygonMode(PM_SOLID); break;
                    case 1 : mCamera->setPolygonMode(PM_WIREFRAME); break;
                    case 2 : mCamera->setPolygonMode(PM_POINTS); break;
                }
                mTimeUntilNextToggle = 0.5;
            }
            static bool displayCameraDetails = false;
            if(mKeyboard->isKeyDown(KC_P) && mTimeUntilNextToggle <= 0)
            {
                displayCameraDetails = !displayCameraDetails;
                mTimeUntilNextToggle = 0.5;
                if (!displayCameraDetails)
                    mDebugText = "";
            }
            // Print camera details
            if(displayCameraDetails) mDebugText = "P: " + StringConverter::toString(mCamera->getDerivedPosition()) + " " + "O: " + StringConverter::toString(mCamera->getDerivedOrientation());
            // Return true to continue rendering
            return true;
        }
        bool processUnbufferedMouseInput(const FrameEvent& evt)
        {
            using namespace OIS;
            // Rotation factors, may not be used if the second mouse button is pressed
            // 2nd mouse button - slide, otherwise rotate
            const MouseState &ms = mMouse->getMouseState();
            if( ms.buttonDown( MB_Right ) )
            {
                mTranslateVector.x += ms.X.rel * 0.13;
                mTranslateVector.y -= ms.Y.rel * 0.13;
            }
            else
            {
                mRotX = Degree(-ms.X.rel * 0.13);
                mRotY = Degree(-ms.Y.rel * 0.13);
            }
            return true;
        }
        void moveCamera()
        {
            // Make all the changes to the camera
            // Note that YAW direction is around a fixed axis (freelook style) rather than a natural YAW (e.g. airplane)
            mCamera->yaw(mRotX);
            mCamera->pitch(mRotY);
            mCamera->moveRelative(mTranslateVector);
        }
        void showDebugOverlay(bool show)
        {
            if (mDebugOverlay)
            {
                if (show) mDebugOverlay->show();
                else mDebugOverlay->hide();
            }
        }

        bool frameRenderingQueued(const FrameEvent& evt)
        {
            // Change curvature / tiling
            // Delay timer to stop too quick updates of curvature
            static Real timeDelay = 0;
            bool updateSky;
            updateSky = false;
            bool result = false;
            using namespace OIS;
            if(!mWindow->isClosed())
            {
                //Need to capture/update each device
                mKeyboard->capture();
                mMouse->capture();
                if( mJoy ) mJoy->capture();
                bool buffJ = (mJoy) ? mJoy->buffered() : true;
                //Check if one of the devices is not buffered
                if( !mMouse->buffered() || !mKeyboard->buffered() || !buffJ )
                {
                    // one of the input modes is immediate, so setup what is needed for immediate movement
                    if (mTimeUntilNextToggle >= 0) mTimeUntilNextToggle -= evt.timeSinceLastFrame;
                    // Move about 100 units per second
                    mMoveScale = mMoveSpeed * evt.timeSinceLastFrame;
                    // Take about 10 seconds for full rotation
                    mRotScale = mRotateSpeed * evt.timeSinceLastFrame;
                    mRotX = 0;
                    mRotY = 0;
                    mTranslateVector = Ogre::Vector3::ZERO;
                }
                //Check to see which device is not buffered, and handle it
                result = processBuffers(evt, buffJ);
            }
            if (!result) return false;
            if (timeDelay > 0) timeDelay -= evt.timeSinceLastFrame;
            if (updateSky) mSceneMgr->setSkyDome(true, "Examples/CloudySky", mCurvature, mTiling);
            return true;
        }
        bool processBuffers(const FrameEvent &evt, bool buffJ)
        {
            bool result = false;
            if( !mKeyboard->buffered() ) if( processUnbufferedKeyInput(evt) == false ) return false;
            if( !mMouse->buffered() ) if( processUnbufferedMouseInput(evt) == false ) return false;
            if( !mMouse->buffered() || !mKeyboard->buffered() || !buffJ ) moveCamera();
            result = true;
            return result;
        }
        bool frameEnded(const FrameEvent& evt)
        {
            static String currFps = "Current FPS: ";
            static String avgFps = "Average FPS: ";
            static String bestFps = "Best FPS: ";
            static String worstFps = "Worst FPS: ";
            static String tris = "Triangle Count: ";
            static String batches = "Batch Count: ";
            // update stats when necessary
            try {
                OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
                OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
                OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
                OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");
                const RenderTarget::FrameStats& stats = mWindow->getStatistics();
                guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
                guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
                guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS) +" "+StringConverter::toString(stats.bestFrameTime)+" ms");
                guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS) +" "+StringConverter::toString(stats.worstFrameTime)+" ms");
                OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
                guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));
                OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
                guiBatches->setCaption(batches + StringConverter::toString(stats.batchCount));
                OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
                guiDbg->setCaption(mDebugText);
            }
            catch(...) { /* ignore */ }
            return true;
        }
    protected:
        Camera* mCamera;
        Vector3 mTranslateVector;
        RenderWindow* mWindow;
        bool mStatsOn;
        std::string mDebugText;
        unsigned int mNumScreenShots;
        float mMoveScale;
        Degree mRotScale;
        // just to stop toggles flipping too fast
        Real mTimeUntilNextToggle ;
        Radian mRotX, mRotY;
        TextureFilterOptions mFiltering;
        int mAniso;
        int mSceneDetailIndex ;
        Real mMoveSpeed;
        Degree mRotateSpeed;
        Overlay* mDebugOverlay;
        //OIS Input devices
        OIS::InputManager* mInputManager;
        OIS::Mouse*    mMouse;
        OIS::Keyboard* mKeyboard;
        OIS::JoyStick* mJoy;
        Real mCurvature;
        Real mTiling;
        SceneManager* mSceneMgr;
};

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <CoreFoundation/CoreFoundation.h>
#endif

// This function will locate the path to our application on OS X, unlike windows you can not rely on the curent working directory for locating your configuration files and resources.
std::string getSharePath()
{
    std::string result = "usr/share/motorsport-sim-tests";
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    char path[1024];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    assert(mainBundle);
    CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
    assert(mainBundleURL);
    CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
    assert(cfStringRef);
    CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);
    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);
    result = std::string(path);
#endif
    return result + "/";
}
std::string getResourcePath()
{
    std::string result = ".";
    // Provide a nice cross platform solution for locating the configuration files. On windows files are searched for in the current working directory, on OS X however you must provide the full path, the helper function getSharePath does this for us.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    result = getSharePath() + "Contents/Resources";
#else
    result = getSharePath();
#endif
    return result + "/";
}

class GraphicsApp
{
    public:
        GraphicsApp()
        : mFrameListener(0), mRoot(0)
        {
            String pluginsPath;
            // only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
            pluginsPath = getResourcePath() + "cfg/plugins.cfg";
#endif
            mRoot = new Root(pluginsPath, getResourcePath() + "cfg/ogre.cfg", getResourcePath() + "logs/Ogre.log");
            // Load resource paths from config file
            ConfigFile cf;
            cf.load(getResourcePath() + "cfg/resources.cfg");
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
                    ResourceGroupManager::getSingleton().addResourceLocation( String(getSharePath() + archName), typeName, secName);
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

                LogManager::getSingleton().setLogDetail( LL_BOREME );
            }
        }
        ~GraphicsApp()
        {
            if (mFrameListener) delete mFrameListener;
            if (mRoot) delete mRoot;
        }
        int start(void)
        {
            mRoot->startRendering();
            /*/ frame by frame...
            mRoot->_fireFrameStarted ();
            mWindow->update ();
            mRoot->_fireFrameEnded ();
            //*/
            return 0;
        }
        void loadCollada(std::string filename)
        {
            filename = getSharePath() + "data/" + filename;
                std::cout << "Loading: -------------------------------" << filename<< std::endl;
            ImpExp* pImpExp = CreateImpExp(mRoot, mSceneMgr);
            pImpExp->importCollada(filename.c_str());
            DestroyImpExp(pImpExp);
        }
    protected:
        SceneManager* mSceneMgr;
        ExampleFrameListener* mFrameListener;
        RenderWindow* mWindow;
        Root *mRoot;
};

SUITE(testSim)
{
    TEST(construction)
    {
        shared_ptr<Sim> sim(new Sim());
        shared_ptr<Core> core(sim->getCore());
        CHECK(core);
        shared_ptr<Group> world(core->getWorld());
        CHECK(world);
        CHECK_EQUAL(world->getId(),"default world");
    }
    TEST(tempGraphicsApp)
    {
        GraphicsApp * app = new GraphicsApp();
        //app->loadCollada("bristol/bristol test.dae");
        //app->loadCollada("LancerEX/Mitsubishi Lancer Evo X.dae");
        //app->loadCollada("FF430/FF430.dae");
        //app->loadCollada("Phoenix/Phoenix City Square.dae");
        //app->loadCollada("Chevrolet Chevelle SS (1)/models/Chevrolet Chevelle SS (1).dae");
        //app->loadCollada("shopping center.dae");
        app->loadCollada("beyron.dae");
        CHECK_EQUAL(0, app->start());
    }
    TEST(graphics)
    {
        shared_ptr<Graphics> g1 (new Graphics(40.0));
        // At this point, there should be a window on the screen.
        //CHECK_THROW(g1->loadCollada("doesntExist.dae"), Exception); //file doesn't exist
        //g1->loadCollada("algo.dae");
        g1->start();
        boost::this_thread::sleep(seconds(5));
        CHECK_EQUAL(false, g1->isPaused());
    }
}

int main(int , char**)
{
    return UnitTest::RunAllTests();
}

