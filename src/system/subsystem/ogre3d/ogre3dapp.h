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
				void setup(void);

			private:
				Ogre::SceneNode* camNode{nullptr};
				Ogre::SceneNode* nodeOgreHead{nullptr};

				std::unique_ptr<iFigure> createFigureDecl(const glm::vec3& pos);
				std::unique_ptr<iFigure> createFigureStmt(const glm::vec3& pos);
				std::unique_ptr<iFigure> createLine(const glm::vec3& from, const glm::vec3& to);

				void parseFile();

				std::list<std::shared_ptr<iFigure>> listiFigureVisible;
		};
	}
}


