#include "ogre3dapp.h"


using namespace subsystem::ogre3d;

Ogre3DApp::Ogre3DApp(): OgreBites::ApplicationContext("Ogre Tutorial App"){

}

bool Ogre3DApp::keyPressed(const OgreBites::KeyboardEvent& evt){

	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE){
		getRoot()->queueEndRendering();
	}

	if(evt.keysym.sym == 97)
		this->nodeOgreHead->rotate(Ogre::Vector<3, float>(0.0f, 1.0f, 0.0f), Ogre::Radian(-0.05f));
	else if(evt.keysym.sym == 100)
		this->nodeOgreHead->rotate(Ogre::Vector<3, float>(0.0f, 1.0f, 0.0f), Ogre::Radian(0.05f));
	else if(evt.keysym.sym == 119)
		this->nodeOgreHead->rotate(Ogre::Vector<3, float>(1.0f, 0.0f, 0.0f), Ogre::Radian(-0.05f));
	else if(evt.keysym.sym == 115)
		this->nodeOgreHead->rotate(Ogre::Vector<3, float>(1.0f, 0.0f, 0.0f), Ogre::Radian(0.05f));

	std::cout << "key: " << evt.keysym.sym << std::endl;

	return true;
}

void Ogre3DApp::setup(void){

	// do not forget to call the base first
	OgreBites::ApplicationContext::setup();

	// register for input events
	addInputListener(this);

	// get a pointer to the already created root
	Ogre::Root* root = getRoot();
	Ogre::SceneManager* scnMgr = root->createSceneManager();
	scnMgr->setAmbientLight(Ogre::ColourValue(0.9, 0.1, 0.9));

	// register our scene with the RTSS
	Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// without light we would just get a black screen
	Ogre::Light*		light		= scnMgr->createLight("MainLight");
	Ogre::SceneNode*	lightNode	= scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(-10, 10, 15);
	lightNode->attachObject(light);

	// also need to tell where we are
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 0, 15);
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

	// create the camera
	Ogre::Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);

	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);

	// finally something to render
	Ogre::Entity* ent = scnMgr->createEntity("ogrehead.mesh");

	nodeOgreHead = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 0, 100);
	nodeOgreHead->attachObject(ent);
}
