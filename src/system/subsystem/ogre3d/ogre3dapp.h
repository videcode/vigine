#pragma once

#include <OGRE/Ogre.h>
#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/Bites/OgreInput.h>

#include <OGRE/OgreColourValue.h>

#include <iostream>
#include "glm/glm.hpp"

/*
#include <clang/Basic/Diagnostic.h>
//#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/Utils.h>
#include <clang/Frontend/ASTUnit.h>
*/


namespace subsystem{
	namespace ogre3d {

		class iFigure{
			public:
				iFigure() = default;
				virtual ~iFigure(){}
			private:
		};





		class Ogre3DApp: public OgreBites::ApplicationContext, public OgreBites::InputListener{
			public:
				Ogre3DApp();

				bool keyPressed(const OgreBites::KeyboardEvent& evt);
				virtual void windowResized 	(Ogre::RenderWindow * rw);
				void setup(void);

			private:
				Ogre::SceneNode* camNode{nullptr};
				Ogre::SceneNode* nodeOgreHead{nullptr};

				Ogre::SceneNode* createFigureDecl(const Ogre::Vector3& pos);
				Ogre::SceneNode* createFigureStmt(const Ogre::Vector3& pos);
				Ogre::SceneNode* createLine(const Ogre::Vector3& from, const Ogre::Vector3& to);


				void parseFile();

				std::list<Ogre::SceneNode*> listiFigureVisible;
				Ogre::SceneManager*			scnMgr{nullptr};
				float d;
		};
	}
}


