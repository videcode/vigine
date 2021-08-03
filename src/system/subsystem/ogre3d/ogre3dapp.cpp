#include "ogre3dapp.h"
#include <filesystem>
namespace fs = std::filesystem;

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
	scnMgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

	// register our scene with the RTSS
	Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// without light we would just get a black screen
	Ogre::Light*		light		= scnMgr->createLight("MainLight");
	Ogre::SceneNode*	lightNode	= scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(-10, 10, 0);
	lightNode->attachObject(light);

	// also need to tell where we are
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 0, 0);
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

	// create the camera
	Ogre::Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);

	// and tell it to render into the main window
	Ogre::Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0.1f, 0.3f));

	// create resource group /usr/local/share/OGRE/Media/materials/programs/HLSL_Cg
	{
		Ogre::String				lNameOfResourceGroup	= "test_resource_group";
		Ogre::ResourceGroupManager& lRgMgr					= Ogre::ResourceGroupManager::getSingleton();
		lRgMgr.createResourceGroup(lNameOfResourceGroup);


		std::string path = "/home/webliga/Documents/code/github/videcode/vigine/src/app/codevis/data/mesh";

		std::vector<std::string> pathList;

		for (const auto & entry : fs::recursive_directory_iterator(path)){
			if (std::find(pathList.begin(), pathList.end(), entry.path().parent_path()) == pathList.end()){
				pathList.push_back(entry.path().parent_path());
				std::cout << "***:" << entry.path().parent_path() << std::endl;
			}
		}

		for(const auto& item: pathList){
			lRgMgr.addResourceLocation(item, "FileSystem", lNameOfResourceGroup, false);
		}
		for(const auto& item: pathList){
			lRgMgr.addResourceLocation(item, "FileSystem", lNameOfResourceGroup, false);
		}

		lRgMgr.initialiseResourceGroup(lNameOfResourceGroup);
		lRgMgr.loadResourceGroup(lNameOfResourceGroup);

	}


	// finally something to render
	Ogre::Entity* ent = scnMgr->createEntity("sphere", "sphere.mesh");
	ent->setCastShadows(true);

	nodeOgreHead = scnMgr->getRootSceneNode()->createChildSceneNode();
	nodeOgreHead->setPosition(0, 0, -50);
	std::cout << "sphere : " << ent->getBoundingRadius() << std::endl;
	nodeOgreHead->setScale(Ogre::Vector3(0.01,0.01,0.01));
	std::cout << "sphere : " << nodeOgreHead->getScale().x << std::endl;
	nodeOgreHead->attachObject(ent);
}

std::unique_ptr<iFigure> Ogre3DApp::createFigureDecl(const glm::vec3& pos){

}

std::unique_ptr<iFigure> Ogre3DApp::createFigureStmt(const glm::vec3& pos){

}

std::unique_ptr<iFigure> Ogre3DApp::createLine(const glm::vec3& from, const glm::vec3& to){

}

void Ogre3DApp::parseFile(){

	std::shared_ptr<iFigure> fig1 = this->createFigureDecl(glm::vec3(0.0f, 0.0f, 0.0f));
	std::shared_ptr<iFigure> fig2 = this->createFigureDecl(glm::vec3(3.0f, 0.0f, 0.0f));
	std::shared_ptr<iFigure> fig3 = this->createFigureStmt(glm::vec3(6.0f, 0.0f, 0.0f));
	std::shared_ptr<iFigure> line = this->createLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(6.0f, 0.0f, 0.0f));

	this->listiFigureVisible.push_back(fig1);
	this->listiFigureVisible.push_back(fig2);
	this->listiFigureVisible.push_back(fig3);
	this->listiFigureVisible.push_back(line);

	for(const auto& item: this->listiFigureVisible){

	}
}
