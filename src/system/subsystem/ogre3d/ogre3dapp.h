#pragma once

#include <OGRE/Ogre.h>
#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/Bites/OgreInput.h>

#include <OGRE/OgreColourValue.h>

#include <iostream>

namespace subsystem{
	namespace ogre3d {
	}
}
        class Ogre3DApp: public OgreBites::ApplicationContext, public OgreBites::InputListener{
			public:
				Ogre3DApp();

				bool keyPressed(const OgreBites::KeyboardEvent& evt);
				void setup(void);

			private:
				Ogre::SceneNode* camNode{nullptr};
				Ogre::SceneNode* nodeOgreHead{nullptr};
		};


