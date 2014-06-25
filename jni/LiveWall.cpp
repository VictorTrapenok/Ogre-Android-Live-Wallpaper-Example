
#include "main.h"

#include <jni.h>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

 AAssetManager* gAssetMgr = NULL;
 AConfiguration* config = NULL;

 Ogre::RenderWindow* gRenderWnd = NULL;
 Ogre::Root* gRoot = NULL;
 Ogre::SceneManager* gSceneMgr = NULL;
 Ogre::ShaderGeneratorTechniqueResolverListener* gMatListener = NULL;
 Ogre::StaticPluginLoader* gStaticPluginLoader = NULL;

 Ogre::Camera* camera = NULL;
 Ogre::SceneNode* pNode = NULL;
 Ogre::RaySceneQuery* mRayScnQuery = NULL;
 Ogre::TextAreaOverlayElement* textArea = NULL;
 Ogre::Viewport* vp = NULL;

 int CurentState = 0;

 Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName)
 {
	 if(gAssetMgr == NULL)
	 {
		 LOGE("openAPKFile error gAssetMgr == NULL [%s]", fileName.c_str());
	 }

	 LOGD("get asset start");
 	 Ogre::DataStreamPtr stream;
	 LOGD("get asset start 2");
     AAsset* asset = AAssetManager_open(gAssetMgr, fileName.c_str(), AASSET_MODE_BUFFER);
     if(asset)
     {
		 LOGD("asset ok");
 		 off_t length = AAsset_getLength(asset);
         void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
         memcpy(membuf, AAsset_getBuffer(asset), length);
         AAsset_close(asset);

         stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
 	 	 LOGI("openAPKFile ok %s", fileName.c_str());
     }
     else
     {
		 LOGE("openAPKFile error %s", fileName.c_str());
     }
     return stream;
 }

 /**
  * Загрузка ресурсов
  */
 Ogre::ConfigFile cf;
 void loadResources(const char *name)
 {
	LOGI("loadResources ok %s", name);
 	cf.load(openAPKFile(name));

 	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 	while (seci.hasMoreElements())
 	{
 		Ogre::String sec, type, arch;
 		sec = seci.peekNextKey();
 		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
 		Ogre::ConfigFile::SettingsMultiMap::iterator i;

 		for (i = settings->begin(); i != settings->end(); i++)
 		{
 			type = i->first;
 			arch = i->second;
 			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
 		}
 	}
 }


 void InitGameScene()
 {
 	if(CurentState != 1)
 	{
 		return;
 	}

 	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("General");

 	/**
 	 * Инициализация сцены
 	 */
 	Ogre::Entity* pEntity = gSceneMgr->createEntity("SinbadInstance", "Sinbad.mesh");
 	Ogre::SceneNode* pNode = gSceneMgr->getRootSceneNode()->createChildSceneNode();
 	pNode->attachObject(pEntity);

 	Ogre::Light* pDirLight = gSceneMgr->createLight();
 	pDirLight->setDirection(Ogre::Vector3(0,-1,0));
 	pDirLight->setType(Ogre::Light::LT_DIRECTIONAL);
 	pNode->attachObject(pDirLight);

 	mRayScnQuery = gSceneMgr->createRayQuery(Ogre::Ray());

 	CurentState = 2;
 }

 void InitStartScene()
 {
 	if(CurentState > 0)
 	{
 		return;
 	}

 	Ogre::RTShader::ShaderGenerator::initialize();
 	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->setTargetLanguage("glsles");
 	gMatListener = new Ogre::ShaderGeneratorTechniqueResolverListener();
 	Ogre::MaterialManager::getSingleton().addListener(gMatListener);

 	LOGW("Create SceneManager");
 	gSceneMgr = gRoot->createSceneManager(Ogre::ST_GENERIC);
 	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(gSceneMgr);

 	camera = gSceneMgr->createCamera("MyCam");
 	camera->setNearClipDistance(1.0f);
 	camera->setFarClipDistance(100000.0f);
 	camera->setPosition(0,0,20.0f);
 	camera->lookAt(0,0,0);
 	camera->setAutoAspectRatio(true);

 	vp = gRenderWnd->addViewport(camera);
 	vp->setBackgroundColour(Ogre::ColourValue(0.7f, 0.0f, 1.0f));
 	vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

 	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->invalidateScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
 	/**
 	 * http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Creating+Overlays+via+Code
 	 * http://www.ogre3d.org/forums/viewtopic.php?f=2&t=78278#p492027
 	 */
 	LOGW("Create OverlaySystem");
 	Ogre::OverlaySystem *mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();
 	gSceneMgr->addRenderQueueListener(mOverlaySystem);

 	LOGW("Create overlayManager");
 	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
 	//Ogre::OverlayManager* overlayManager = OGRE_NEW Ogre::OverlayManager();

 	LOGW("loadResources resources.cfg");
 	loadResources("resources.cfg");
 	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Start");

 	LOGW("Create a img overlay panel");
 	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "PanelLogo" ) );
 	panel->setPosition( vp->getActualWidth()/2 - 64, vp->getActualHeight()/2 - 64 - 20 );
 	panel->setDimensions( 128, 64 );
 	panel->setMaterialName("overlay_image_material");
 	panel->setMetricsMode(Ogre::GMM_PIXELS);

 	Ogre::Overlay* LogoOverlay = overlayManager.create( "OverlayLogo" );
 	LogoOverlay->add2D( panel );
 	LogoOverlay->show();


 	LOGW("Create a text overlay panel");
 	textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "TextAreaName"));
 	textArea->setMetricsMode(Ogre::GMM_PIXELS);
 	textArea->setPosition(0, 0);
 	textArea->setDimensions(100, 100);
 	textArea->setCaption("Hello, World!");
 	textArea->setCharHeight(48);
 	textArea->setFontName("QWcuckoo");
 	textArea->setColourBottom(Ogre::ColourValue(0.0f, 0.0f, 1.0f));
 	textArea->setColourTop(Ogre::ColourValue(1.0f, 0.0f, 0.0f));

 	Ogre::OverlayContainer* TextPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "PanelText" ) );
 	TextPanel->setPosition( vp->getActualWidth()/2 - 128, vp->getActualHeight()/2 + 20 );
 	TextPanel->setDimensions( 256, 64 );
 	TextPanel->setMaterialName("overlay_text_material");
 	TextPanel->setMetricsMode(Ogre::GMM_PIXELS);
 	TextPanel->addChild(textArea);

 	Ogre::Overlay* TextOverlay = overlayManager.create( "OverlayText" );
 	TextOverlay->add2D( TextPanel );
 	TextOverlay->show();

 	CurentState = 1;

 }

JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeDrawFrame(JNIEnv *env, jobject thisObj)
{
	LOGW("Hello World!");
	gRoot->renderOneFrame();
}

JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnCreate(JNIEnv * pEnv, jobject obj1, jobject aAssetManagerObj)
{
	LOGW("NativeOnCreate");

	if(gRoot == NULL)
	{
		LOGW(" gRoot = Ogre::Root");
		gRoot = new Ogre::Root();
		#ifdef OGRE_STATIC_LIB
		LOGW("1 gStaticPluginLoader new ");
			gStaticPluginLoader = new Ogre::StaticPluginLoader();
			LOGW("1 gStaticPluginLoader load");
			gStaticPluginLoader->load();
		#endif


			LOGW("1 setRenderSystem %d", gRoot->getAvailableRenderers().size());
		gRoot->setRenderSystem(gRoot->getAvailableRenderers().at(0));
		LOGW("1 initialise");
		gRoot->initialise(false);
	}

	if(gAssetMgr == NULL)
	{
		LOGW("set gAssetMgr");
		//gAssetMgr = (AAssetManager*)aAssetManagerObj;

		gAssetMgr = AAssetManager_fromJava(pEnv, aAssetManagerObj);


		LOGW("1 AConfiguration_new");
		config = AConfiguration_new();
		AConfiguration_fromAssetManager(config, gAssetMgr);

		LOGW("1 APKFileSystemArchiveFactory");
		Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(gAssetMgr) );
		LOGW("2 APKZipArchiveFactory");
		Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(gAssetMgr) );

	}
}

JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnDestroy(JNIEnv *env, jobject thisObj)
{
	LOGW("NativeOnDestroy");
}

JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnShow(JNIEnv *env, jobject thisObj)
{
	LOGW("NativeOnShow");
	gRoot->renderOneFrame();
}

JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnHide(JNIEnv *env, jobject thisObj)
{
	LOGW("NativeOnHide");
}


JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnSurfaceChanged(JNIEnv *env, jobject thisObj, jint width, jint height)
{
	LOGW("NativeOnSurfaceChanged");
	gRoot->renderOneFrame();
}

JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeSurfaceCreated(JNIEnv *env, jobject thisObj, jobject holder)
{
	LOGW("NativeSurfaceCreated");

	LOGW("1 ANativeWindow_fromSurface");
	ANativeWindow* window = ANativeWindow_fromSurface(env, holder);


	LOGW("!gRenderWnd");
	if(!gRenderWnd)
	{
		LOGW("NameValuePairList");
		Ogre::NameValuePairList opt;
		opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)window);
		opt["androidConfig"] = Ogre::StringConverter::toString((int)config);

		LOGW("gRoot->createRenderWindow");
		gRenderWnd = gRoot->createRenderWindow("OgreWindow", 0, 0, false, &opt);

		InitStartScene();
		InitGameScene();
	}
	else
	{
		LOGW("1 !gRenderWnd");
		static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_createInternalResources(window, config);
	}
	LOGW("AConfiguration_delete(config)");
	AConfiguration_delete(config);
}



JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnSurfaceDestroyed(JNIEnv *env, jobject thisObj)
{
	LOGW("NativeOnSurfaceDestroyed");
	//if(gRoot && gRenderWnd)
	//static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_destroyInternalResources();
}

JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnOffsetsChanged(JNIEnv *env, jobject thisObj)
{
	LOGW("NativeOnOffsetsChanged");
}


JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnTouchEvent(JNIEnv *env, jobject thisObj, jfloat width, jfloat height, jint action)
{
	LOGW("NativeOnTouchEvent");
	gRoot->renderOneFrame();
}

