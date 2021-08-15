#include "ogre3dapp.h"
#include <math.h>

using namespace subsystem::ogre3d;

Ogre3DApp::Ogre3DApp() : OgreBites::ApplicationContext("Ogre Tutorial App") {}

void Ogre3DApp::frameRendered(const Ogre::FrameEvent &evt) {
  float static cachePrevX{0};
  float static cachePrevY{0};

  if (this->isMouseMoveX && cachePrevX != this->prevX) {
    if (this->isMouseMoveLeft) {
      this->camNodeRotationCenter->yaw(Ogre::Radian(this->stepCameraRotateX));

    } else {
      this->camNodeRotationCenter->yaw(Ogre::Radian(-this->stepCameraRotateX));
    }

    cachePrevX = this->prevX;
  }
  if (this->isMouseMoveY && cachePrevY != this->prevY) {
    if (this->isMouseMoveUp) {
      this->camNodeRotationCenter->pitch(Ogre::Radian(this->stepCameraRotateY));

    } else {
      this->camNodeRotationCenter->pitch(
          Ogre::Radian(-this->stepCameraRotateY));
    }

    cachePrevY = this->prevY;
  }

  if (!this->dequeCurrKeyCode.empty()) {

    Ogre::Vector3 direct = Ogre::Vector3::ZERO;
    Ogre::Quaternion orientQuat = this->camNodeRotationCenter->getOrientation();
    Ogre::Matrix3 matRot;
    orientQuat.ToRotationMatrix(matRot);
    float step = 0.10f;

    switch (this->dequeCurrKeyCode.back()) {
    case 97: // a
      direct = matRot * Ogre::Vector3(-step, 0, 0);
      break;
    case 100: // d
      direct = matRot * Ogre::Vector3(step, 0, 0);
      break;
    case 115: // s
      direct = matRot * Ogre::Vector3(0, 0, step);
      break;
    case 119: // w
      direct = matRot * Ogre::Vector3(0, 0, -step);
      break;
    case 113: // q
      // direct = matRot * Ogre::Vector3(0, -step, 0);
      this->camNodeRotationCenter->yaw(Ogre::Radian(this->stepCameraRotateX));
      break;
    case 101: // e
      // direct = matRot * Ogre::Vector3(0, step, 0);
      this->camNodeRotationCenter->yaw(Ogre::Radian(-this->stepCameraRotateX));
      break;
    case 114: // r
      // direct = matRot * Ogre::Vector3(0, -step, 0);
      this->camNodeRotationCenter->pitch(
          Ogre::Radian(-this->stepCameraRotateY));
      break;
    case 102: // f
      // direct = matRot * Ogre::Vector3(0, step, 0);
      this->camNodeRotationCenter->pitch(Ogre::Radian(this->stepCameraRotateY));
      break;
    case 122: // z
      // direct = matRot * Ogre::Vector3(0, -step, 0);
      this->camNodeRotationCenter->roll(Ogre::Radian(this->stepCameraRotateY));
      break;
    case 120: // x
      // direct = matRot * Ogre::Vector3(0, -step, 0);
      this->camNodeRotationCenter->roll(Ogre::Radian(-this->stepCameraRotateY));
      break;
    case 99: // c
      direct = matRot * Ogre::Vector3(0, -step, 0);
      // this->camNodeRotationCenter->roll(Ogre::Radian(this->stepCameraRotateY));
      break;
    case 118: // v
      direct = matRot * Ogre::Vector3(0, step, 0);
      // this->camNodeRotationCenter->roll(Ogre::Radian(this->stepCameraRotateY));
      break;
    }

    std::cout << "matRot: " << matRot << std::endl;
    this->camNodeRotationCenter->translate(direct);
  }
}

bool Ogre3DApp::keyPressed(const OgreBites::KeyboardEvent &evt) {

  if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    getRoot()->queueEndRendering();

  auto item = std::find(this->dequeCurrKeyCode.begin(),
                        this->dequeCurrKeyCode.end(), evt.keysym.sym);
  if (item == this->dequeCurrKeyCode.end())
    this->dequeCurrKeyCode.push_back(evt.keysym.sym);

  std::cout << "key: " << evt.keysym.sym << " " << std::endl;

  return true;
}

bool Ogre3DApp::keyReleased(const OgreBites::KeyboardEvent &evt) {
  auto item = std::find(this->dequeCurrKeyCode.begin(),
                        this->dequeCurrKeyCode.end(), evt.keysym.sym);
  if (item != this->dequeCurrKeyCode.end()) {
    this->dequeCurrKeyCode.erase(item);
    this->dequeCurrKeyCode.shrink_to_fit();
  }
  return false;
}

void Ogre3DApp::windowResized(Ogre::RenderWindow *rw) {

  Ogre::Viewport *viewport = rw->getViewport(0);
  Ogre::Camera *cam =
      static_cast<Ogre::Camera *>(this->camNode->getAttachedObject("myCam"));
  Ogre::Radian rad(2 * atan(viewport->getActualHeight() / this->d / 2));

  cam->setFOVy(rad);
  cam->setAspectRatio((float)viewport->getActualWidth() /
                      (float)viewport->getActualHeight());
  std::cout << "windowResized: " << viewport->getWidth() << ":"
            << viewport->getActualWidth() << std::endl;
}

bool Ogre3DApp::mouseWheelRolled(const OgreBites::MouseWheelEvent &evt) {
  Ogre::Vector3 direct = Ogre::Vector3::ZERO;
  Ogre::Quaternion orientQuat = this->camNodeRotationCenter->getOrientation();
  Ogre::Matrix3 matRot;
  orientQuat.ToRotationMatrix(matRot);
  float step = 0.20f;

  if (evt.y == -1) {
    direct = matRot * Ogre::Vector3(0, 0, -step);
  } else {
    direct = matRot * Ogre::Vector3(0, 0, step);
  }

  this->camNodeRotationCenter->translate(direct);
  return false;
}

bool Ogre3DApp::mouseReleased(const OgreBites::MouseButtonEvent &evt) {
  this->isMousePressed = false;
  this->isMouseMoveX = false;
  this->isMouseMoveY = false;

  return false;
}

bool Ogre3DApp::mousePressed(const OgreBites::MouseButtonEvent &evt) {
  this->isMousePressed = true;
  return false;
}

bool Ogre3DApp::mouseMoved(const OgreBites::MouseMotionEvent &evt) {
  if (this->isMousePressed) {

    this->isMouseMoveX = true;
    if (evt.x > this->prevX) {
      this->isMouseMoveLeft = false;
    } else if (evt.x < this->prevX)
      this->isMouseMoveLeft = true;
    else {
      this->isMouseMoveX = false;
    }

    int diffX = evt.x - this->prevX;
    switch (diffX) {
    case 1:
    case -1:
      this->stepCameraRotateX = 0.01;
      break;
    case 2:
    case -2:
      this->stepCameraRotateX = 0.05f;
      break;
    case 3:
    case -3:
      this->stepCameraRotateX = 0.10;
      break;
    case 4:
    case -4:
      this->stepCameraRotateX = 0.15;
      break;
    case 5:
    case -5:
      this->stepCameraRotateX = 0.20;
      break;
    case 6:
    case -6:
      this->stepCameraRotateX = 0.25;
      break;
    case 7:
    case -7:
      this->stepCameraRotateX = 0.30;
      break;
    case 8:
    case -8:
      this->stepCameraRotateX = 0.35;
      break;
    case 9:
    case -9:
      this->stepCameraRotateX = 0.40;
      break;
    case 10:
    case -10:
      this->stepCameraRotateX = 0.45;
      break;
    default:

      break;
    }
    std::cout << "x: " << this->prevX << ":" << evt.x << std::endl;

    this->isMouseMoveY = true;
    if (evt.y > this->prevY) {
      this->isMouseMoveUp = false;
    } else if (evt.y < this->prevY)
      this->isMouseMoveUp = true;
    else {
      this->isMouseMoveY = false;
    }

    int diffY = evt.y - this->prevY;
    switch (diffY) {
    case 1:
    case -1:
      this->stepCameraRotateY = 0.01;
      break;
    case 2:
    case -2:
      this->stepCameraRotateY = 0.05f;
      break;
    case 3:
    case -3:
      this->stepCameraRotateY = 0.10;
      break;
    case 4:
    case -4:
      this->stepCameraRotateY = 0.15;
      break;
    case 5:
    case -5:
      this->stepCameraRotateY = 0.20;
      break;
    case 6:
    case -6:
      this->stepCameraRotateY = 0.25;
      break;
    case 7:
    case -7:
      this->stepCameraRotateY = 0.30;
      break;
    case 8:
    case -8:
      this->stepCameraRotateY = 0.35;
      break;
    case 9:
    case -9:
      this->stepCameraRotateY = 0.40;
      break;
    case 10:
    case -10:
      this->stepCameraRotateY = 0.45;
      break;
    default:

      break;
    }

    this->prevX = evt.x;
    this->prevY = evt.y;
  }

  return false;
}

void Ogre3DApp::setup(void) {
  using namespace Ogre;

  // do not forget to call the base first
  OgreBites::ApplicationContext::setup();

  // register for input events
  addInputListener(this);

  // get a pointer to the already created root
  Ogre::Root *root = getRoot();
  scnMgr = root->createSceneManager();
  scnMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.2, 0.1));
  scnMgr->setShadowTechnique(
      Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

  // register our scene with the RTSS
  Ogre::RTShader::ShaderGenerator *shadergen =
      Ogre::RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scnMgr);

  // without light we would just get a black screen
  Ogre::Light *light = scnMgr->createLight("MainLight");
  Ogre::SceneNode *lightNode =
      scnMgr->getRootSceneNode()->createChildSceneNode();
  lightNode->setPosition(-50, 20, 0);
  lightNode->attachObject(light);

  // create resource group
  // /usr/local/share/OGRE/Media/materials/programs/HLSL_Cg
  {
    Ogre::String lNameOfResourceGroup = "test_resource_group";
    Ogre::ResourceGroupManager &lRgMgr =
        Ogre::ResourceGroupManager::getSingleton();
    lRgMgr.createResourceGroup(lNameOfResourceGroup);

    std::string path = "/home/webliga/Documents/code/github/videcode/vigine/"
                       "src/app/codevis/data/mesh";

    std::vector<std::string> pathList;

    for (const auto &entry : stdfs::recursive_directory_iterator(path)) {
      if (std::find(pathList.begin(), pathList.end(),
                    entry.path().parent_path()) == pathList.end()) {
        pathList.push_back(entry.path().parent_path());
        std::cout << "***:" << entry.path().parent_path() << std::endl;
      }
    }

    for (const auto &item : pathList) {
      lRgMgr.addResourceLocation(item, "FileSystem", lNameOfResourceGroup,
                                 false);
    }
    for (const auto &item : pathList) {
      lRgMgr.addResourceLocation(item, "FileSystem", lNameOfResourceGroup,
                                 false);
    }
    lRgMgr.initialiseResourceGroup(lNameOfResourceGroup);
    lRgMgr.loadResourceGroup(lNameOfResourceGroup);
  }

  // create mesh sphere
  {
    const float r = 0.5f;
    const int nRings = 160, nSegments = 160;
    Ogre::MeshPtr pSphere = Ogre::MeshManager::getSingleton().createManual(
        "sphere", "test_resource_group");
    Ogre::SubMesh *pSphereVertex = pSphere->createSubMesh();

    pSphere->sharedVertexData = new Ogre::VertexData();
    Ogre::VertexData *vertexData = pSphere->sharedVertexData;

    // define the vertex format
    VertexDeclaration *vertexDecl = vertexData->vertexDeclaration;
    size_t currOffset = 0;
    // positions
    vertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_POSITION);
    currOffset += VertexElement::getTypeSize(VET_FLOAT3);
    // normals
    vertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_NORMAL);
    currOffset += VertexElement::getTypeSize(VET_FLOAT3);
    // two dimensional texture coordinates
    vertexDecl->addElement(0, currOffset, VET_FLOAT2, VES_TEXTURE_COORDINATES,
                           0);
    currOffset += VertexElement::getTypeSize(VET_FLOAT2);

    // allocate the vertex buffer
    vertexData->vertexCount = (nRings + 1) * (nSegments + 1);
    HardwareVertexBufferSharedPtr vBuf =
        HardwareBufferManager::getSingleton().createVertexBuffer(
            vertexDecl->getVertexSize(0), vertexData->vertexCount,
            HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    VertexBufferBinding *binding = vertexData->vertexBufferBinding;
    binding->setBinding(0, vBuf);
    float *pVertex =
        static_cast<float *>(vBuf->lock(HardwareBuffer::HBL_DISCARD));

    // allocate index buffer
    pSphereVertex->indexData->indexCount = 6 * nRings * (nSegments + 1);
    pSphereVertex->indexData->indexBuffer =
        HardwareBufferManager::getSingleton().createIndexBuffer(
            HardwareIndexBuffer::IT_16BIT, pSphereVertex->indexData->indexCount,
            HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    HardwareIndexBufferSharedPtr iBuf = pSphereVertex->indexData->indexBuffer;
    unsigned short *pIndices =
        static_cast<unsigned short *>(iBuf->lock(HardwareBuffer::HBL_DISCARD));

    float fDeltaRingAngle = (Math::PI / nRings);
    float fDeltaSegAngle = (2 * Math::PI / nSegments);
    unsigned short wVerticeIndex = 0;

    // Generate the group of rings for the sphere
    for (int ring = 0; ring <= nRings; ring++) {
      float r0 = r * sinf(ring * fDeltaRingAngle);
      float y0 = r * cosf(ring * fDeltaRingAngle);

      // Generate the group of segments for the current ring
      for (int seg = 0; seg <= nSegments; seg++) {
        float x0 = r0 * sinf(seg * fDeltaSegAngle);
        float z0 = r0 * cosf(seg * fDeltaSegAngle);

        // Add one vertex to the strip which makes up the sphere
        *pVertex++ = x0;
        *pVertex++ = y0;
        *pVertex++ = z0;

        Vector3 vNormal = Vector3(x0, y0, z0).normalisedCopy();
        *pVertex++ = vNormal.x;
        *pVertex++ = vNormal.y;
        *pVertex++ = vNormal.z;

        *pVertex++ = (float)seg / (float)nSegments;
        *pVertex++ = (float)ring / (float)nRings;

        if (ring != nRings) {
          // each vertex (except the last) has six indices pointing to it
          *pIndices++ = wVerticeIndex + nSegments + 1;
          *pIndices++ = wVerticeIndex;
          *pIndices++ = wVerticeIndex + nSegments;
          *pIndices++ = wVerticeIndex + nSegments + 1;
          *pIndices++ = wVerticeIndex + 1;
          *pIndices++ = wVerticeIndex;
          wVerticeIndex++;
        }
      }; // end for seg
    }    // end for ring

    // Unlock
    vBuf->unlock();
    iBuf->unlock();
    // Generate face list
    pSphereVertex->useSharedVertices = true;

    // the original code was missing this line:
    pSphere->_setBounds(AxisAlignedBox(Vector3(-r, -r, -r), Vector3(r, r, r)),
                        false);
    pSphere->_setBoundingSphereRadius(r);
    // this line makes clear the mesh is loaded (avoids memory leaks)
    pSphere->load();
  }

  // also need to tell where we are
  // this->camNodeRotationCenter =
  // scnMgr->getRootSceneNode()->createChildSceneNode();
  this->camNodeRotationCenter = this->createFigureDecl(Ogre::Vector3(0, 0, -5));
  this->camNodeRotationCenter->setScale(Ogre::Vector3(0.005f, 0.005f, 0.005f));
  // this->camNodeRotationCenter->setPosition(0, 0, -2);
  this->camNode = this->camNodeRotationCenter->createChildSceneNode();
  this->camNode->setPosition(0, 0, 55);
  this->camNode->lookAt(Ogre::Vector3::ZERO, Ogre::Node::TS_PARENT);

  // create the camera
  Ogre::Camera *cam = scnMgr->createCamera("myCam");
  cam->setNearClipDistance(0.1f); // specific to this sample
  cam->setAutoAspectRatio(true);
  this->camNode->attachObject(cam);

  // and tell it to render into the main window
  Ogre::Viewport *vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.2f, 0.1f, 0.6f));

  this->d = vp->getActualHeight() / 2 /
            (sin(cam->getFOVy().valueRadians() / 2) /
             cos(cam->getFOVy().valueRadians() / 2));
  parseFile();
}

Ogre::SceneNode *Ogre3DApp::createFigureDecl(const Ogre::Vector3 &pos) {
  using namespace Ogre;

  static int id = 0;

  Ogre::SceneNode *pNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  Ogre::Entity *ent = scnMgr->createEntity("sphere_" + std::to_string(++id),
                                           "sphere", "test_resource_group");
  ent->setCastShadows(true);
  Ogre::String nameMaterial = "sphere_material" + std::to_string(id);
  Ogre::MaterialPtr myManualObjectMaterial =
      Ogre::MaterialManager::getSingleton().create(nameMaterial,
                                                   "test_resource_group");
  myManualObjectMaterial->setReceiveShadows(false);
  myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);

  Ogre::ColourValue color(0.25f, 0.41f, 0.84f, 0);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(color);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(color);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(
      color);

  ent->setMaterial(myManualObjectMaterial);

  pNode->setPosition(pos);
  pNode->attachObject(ent);

  return pNode;
}

Ogre::SceneNode *Ogre3DApp::createFigureStmt(const Ogre::Vector3 &pos) {
  using namespace Ogre;
  static int id = 0;
  ManualObject *cube = new ManualObject("cube" + std::to_string(++id));
  Ogre::SceneNode *pNode =
      this->scnMgr->getRootSceneNode()->createChildSceneNode();

  Ogre::String nameMaterial = "cube_material" + std::to_string(id);
  Ogre::MaterialPtr myManualObjectMaterial =
      Ogre::MaterialManager::getSingleton().create(nameMaterial,
                                                   "test_resource_group");
  myManualObjectMaterial->setReceiveShadows(false);
  myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0.3, 0.1, 0.3,
                                                                  0);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0.3, 0.1,
                                                                  0.3);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(
      0.3, 0.1, 0.3);

  // create cube mesh
  cube->begin(nameMaterial, RenderOperation::OT_TRIANGLE_LIST,
              "test_resource_group");

  cube->position(0.5, -0.5, 1.0);
  cube->normal(0.408248, -0.816497, 0.408248);
  cube->textureCoord(1, 0);
  cube->position(-0.5, -0.5, 0.0);
  cube->normal(-0.408248, -0.816497, -0.408248);
  cube->textureCoord(0, 1);
  cube->position(0.5, -0.5, 0.0);
  cube->normal(0.666667, -0.333333, -0.666667);
  cube->textureCoord(1, 1);
  cube->position(-0.5, -0.5, 1.0);
  cube->normal(-0.666667, -0.333333, 0.666667);
  cube->textureCoord(0, 0);
  cube->position(0.5, 0.5, 1.0);
  cube->normal(0.666667, 0.333333, 0.666667);
  cube->textureCoord(1, 0);
  cube->position(-0.5, -0.5, 1.0);
  cube->normal(-0.666667, -0.333333, 0.666667);
  cube->textureCoord(0, 1);
  cube->position(0.5, -0.5, 1.0);
  cube->normal(0.408248, -0.816497, 0.408248);
  cube->textureCoord(1, 1);
  cube->position(-0.5, 0.5, 1.0);
  cube->normal(-0.408248, 0.816497, 0.408248);
  cube->textureCoord(0, 0);
  cube->position(-0.5, 0.5, 0.0);
  cube->normal(-0.666667, 0.333333, -0.666667);
  cube->textureCoord(0, 1);
  cube->position(-0.5, -0.5, 0.0);
  cube->normal(-0.408248, -0.816497, -0.408248);
  cube->textureCoord(1, 1);
  cube->position(-0.5, -0.5, 1.0);
  cube->normal(-0.666667, -0.333333, 0.666667);
  cube->textureCoord(1, 0);
  cube->position(0.5, -0.5, 0.0);
  cube->normal(0.666667, -0.333333, -0.666667);
  cube->textureCoord(0, 1);
  cube->position(0.5, 0.5, 0.0);
  cube->normal(0.408248, 0.816497, -0.408248);
  cube->textureCoord(1, 1);
  cube->position(0.5, -0.5, 1.0);
  cube->normal(0.408248, -0.816497, 0.408248);
  cube->textureCoord(0, 0);
  cube->position(0.5, -0.5, 0.0);
  cube->normal(0.666667, -0.333333, -0.666667);
  cube->textureCoord(1, 0);
  cube->position(-0.5, -0.5, 0.0);
  cube->normal(-0.408248, -0.816497, -0.408248);
  cube->textureCoord(0, 0);
  cube->position(-0.5, 0.5, 1.0);
  cube->normal(-0.408248, 0.816497, 0.408248);
  cube->textureCoord(1, 0);
  cube->position(0.5, 0.5, 0.0);
  cube->normal(0.408248, 0.816497, -0.408248);
  cube->textureCoord(0, 1);
  cube->position(-0.5, 0.5, 0.0);
  cube->normal(-0.666667, 0.333333, -0.666667);
  cube->textureCoord(1, 1);
  cube->position(0.5, 0.5, 1.0);
  cube->normal(0.666667, 0.333333, 0.666667);
  cube->textureCoord(0, 0);

  cube->triangle(0, 1, 2);
  cube->triangle(3, 1, 0);
  cube->triangle(4, 5, 6);
  cube->triangle(4, 7, 5);
  cube->triangle(8, 9, 10);
  cube->triangle(10, 7, 8);
  cube->triangle(4, 11, 12);
  cube->triangle(4, 13, 11);
  cube->triangle(14, 8, 12);
  cube->triangle(14, 15, 8);
  cube->triangle(16, 17, 18);
  cube->triangle(16, 19, 17);

  cube->end();
  pNode->attachObject(cube);

  pNode->setPosition(pos);

  return pNode;
}

Ogre::SceneNode *Ogre3DApp::createLine(
    const Ogre::Vector3 &from, const Ogre::Vector3 &to,
    const Ogre::ColourValue &color = Ogre::ColourValue(1, 1, 1, 0)) {
  using namespace Ogre;
  static int id = 0;
  Ogre::ManualObject *myManualObject =
      this->scnMgr->createManualObject("line_manual" + std::to_string(++id));
  Ogre::SceneNode *myManualObjectNode =
      this->scnMgr->getRootSceneNode()->createChildSceneNode();

  // NOTE: The second parameter to the create method is the resource group the
  // material will be added to. If the group you name does not exist (in your
  // resources.cfg file) the library will assert() and your program will crash
  Ogre::String nameMaterial = "line_material" + std::to_string(id);
  Ogre::MaterialPtr myManualObjectMaterial =
      Ogre::MaterialManager::getSingleton().create(nameMaterial,
                                                   "test_resource_group");
  myManualObjectMaterial->setReceiveShadows(false);
  myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(color);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(color);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(
      color);
  // myManualObjectMaterial->dispose();  // dispose pointer, not the material

  myManualObject->begin(nameMaterial, Ogre::RenderOperation::OT_LINE_LIST,
                        "test_resource_group");
  myManualObject->position(from);
  myManualObject->position(to);
  // etc
  myManualObject->end();

  myManualObjectNode->setPosition(from);
  myManualObjectNode->attachObject(myManualObject);

  return myManualObjectNode;
}

void Ogre3DApp::parseFile() {

  int argc = 3;
  const char *argument1 = "/home/webliga/Documents/code/github/videcode/vigine/"
                          "result/Debug/bin/run";
  const char *argument2 = "-p=/home/webliga/Documents/code/github/videcode/"
                          "vigine/src/app/codevis/data/files/";
  const char *argument3 = "/home/webliga/Documents/code/github/videcode/vigine/"
                          "src/app/codevis/data/files/testforclangparse.cpp";
  const char *argument4 = "--help";
  const char *argv[argc];
  argv[0] = argument1;
  argv[1] = argument2;
  argv[2] = argument3;
  // argv[1] = argument4;

  std::vector<std::string> sources;
  sources.push_back("testforclangparse.cpp");

  // CommonOptionsParser constructor will parse arguments and create a
  // CompilationDatabase.  In case of error it will terminate the program.
  // CommonOptionsParser optionsParser(argc, argv, MyToolCategory);

  // Use OptionsParser.getCompilations() and OptionsParser.getSourcePathList()
  // to retrieve CompilationDatabase and the list of input file paths.

  // ClangTool tool(optionsParser.getCompilations(),
  // optionsParser.getSourcePathList());
  /*
          int result =
     tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get());
          std::cout << "result: " << result << std::endl;
  */

  std::unique_ptr<FindNamedClassAction> findAct =
      std::make_unique<FindNamedClassAction>();

  Twine tw = "class X; class X{};";
  /*
    std::shared_ptr<clang::PreprocessorOptions> prepOpt;
    clang::DiagnosticsEngine diagEngine;
    clang::LangOptions langOpt;
    clang::SourceManager sourceManager;
    clang::HeaderSearch headerSearch;
    clang::ModuleLoader moduleLoader;

    clang::Preprocessor preprocessor(prepOpt, diagEngine, langOpt,
    sourceManager, headerSearch, moduleLoader);
    preprocessor.EnterMainSourceFile();
  */
  std::cout << "runToolOnCode: " << std::endl;
  clang::tooling::runToolOnCode(std::move(findAct), tw, argument3);
  std::cout << "runToolOnCode end " << std::endl;

  Ogre::Vector3 pos(0.0f, 0.0f, -10.0f);
  Ogre::Vector3 pos2(0.0f, 0.0f, -4.858f);
  Ogre::Vector3 pos3(24.0f, 0.0f, -4.858f);
  Ogre::Vector3 pos4(0.0f, 5.0f, -4.858f);
  Ogre::Vector3 pos5(0.0f, 0.0f, -9.858f);
  Ogre::SceneNode *lineX =
      this->createLine(pos2, pos3, Ogre::ColourValue(0, 1, 0, 0));
  Ogre::SceneNode *lineY =
      this->createLine(pos2, pos4, Ogre::ColourValue(1, 0, 0, 0));
  Ogre::SceneNode *lineZ =
      this->createLine(pos2, pos5, Ogre::ColourValue(0, 0, 1, 0));

  this->listiFigureVisible.push_back(this->createFigureDecl(pos));
  this->listiFigureVisible.push_back(this->createFigureDecl(pos));
  this->listiFigureVisible.push_back(this->createFigureStmt(pos));
  this->listiFigureVisible.push_back(this->createFigureDecl(pos));
  this->listiFigureVisible.push_back(this->createFigureDecl(pos));
  this->listiFigureVisible.push_back(this->createFigureDecl(pos));
  this->listiFigureVisible.push_back(this->createFigureStmt(pos));
  this->listiFigureVisible.push_back(this->createFigureDecl(pos));
  this->listiFigureVisible.push_back(this->createFigureStmt(pos));
  this->listiFigureVisible.push_back(this->createFigureStmt(pos));
  this->listiFigureVisible.push_back(this->createFigureStmt(pos));
  this->listiFigureVisible.push_back(this->createFigureStmt(pos));
  this->listiFigureVisible.push_back(this->createFigureDecl(pos));

  Ogre::Vector3 posDecl = pos;
  for (const auto &item : this->listiFigureVisible) {
    item->setPosition(posDecl);
    std::cout << "z: " << item->getPosition().z << std::endl;
    posDecl.x += 2;
  }
  std::cout << "zline: " << lineX->getPosition().z << std::endl;
}
