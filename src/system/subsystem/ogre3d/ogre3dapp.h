#pragma once

#include <OGRE/Ogre.h>
#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/Bites/OgreInput.h>

#include <OGRE/OgreColourValue.h>

#include <iostream>
#include <deque>
#include "glm/glm.hpp"

#include "xlibmacrosdef.h"
#include <clang/Basic/Diagnostic.h>
//#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/Utils.h>
#include <clang/Frontend/ASTUnit.h>
#include "xlibmacrosdef.h"



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
				void frameRendered(const Ogre::FrameEvent& evt);
				bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
				bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
				void windowResized 	(Ogre::RenderWindow * rw) override;
				bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) override;
				bool mouseReleased(const OgreBites::MouseButtonEvent& evt) override;
				bool mousePressed(const OgreBites::MouseButtonEvent& evt);
				bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
				void setup(void);

			private:
				Ogre::SceneNode* camNode{nullptr};
				Ogre::SceneNode* camNodeRotationCenter{nullptr};
				Ogre::SceneNode* nodeOgreHead{nullptr};

				Ogre::SceneNode* createFigureDecl(const Ogre::Vector3& pos);
				Ogre::SceneNode* createFigureStmt(const Ogre::Vector3& pos);
				Ogre::SceneNode* createLine(const Ogre::Vector3& from, const Ogre::Vector3& to, const Ogre::ColourValue& color);


				void parseFile();

				std::list<Ogre::SceneNode*> listiFigureVisible;
				Ogre::SceneManager*			scnMgr{nullptr};
				float d;


				// key vars
				std::deque<int> dequeCurrKeyCode;

				// mouse vars
				bool isMousePressed{false};
				bool isMouseMoveX{false};
				bool isMouseMoveY{false};
				bool isMouseMoveLeft{false};
				bool isMouseMoveUp{false};

				float prevX{0};
				float prevY{0};
				float stepCameraRotateX{0.01f};
				float stepCameraRotateY{0.01f};
		};
	}
}


