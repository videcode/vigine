#pragma once

#include <OGRE/Ogre.h>
#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/Bites/OgreInput.h>

#include <OGRE/OgreColourValue.h>

#include <iostream>
#include <deque>
#include "glm/glm.hpp"

#include "xlibmacrosdef.h"
/*
#include <clang/Basic/Diagnostic.h>
//#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/Utils.h>
#include <clang/Frontend/ASTUnit.h>
*/

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"

#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/PreprocessorOptions.h"

using namespace clang::tooling;
using namespace llvm;

#include "xlibmacrosdef.h"

#include <filesystem>

namespace stdfs = std::filesystem;


// Apply a custom category to all command-line options so that they are the
// only ones displayed.
// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);


namespace subsystem{
	namespace ogre3d {

		class iFigure{
			public:
				iFigure() = default;
				virtual ~iFigure(){}
			private:
		};

		class FindNamedClassVisitor: public clang::RecursiveASTVisitor<FindNamedClassVisitor>
		{
		public:
		explicit FindNamedClassVisitor(clang::ASTContext *Context)
				  : context(Context) {}

		  bool VisitCXXRecordDecl(clang::CXXRecordDecl *Declaration) {
			// For debugging, dumping the AST nodes will show which nodes are already
			// being visited.
			  std::cout << "dump: " << std::endl;
			Declaration->dump();

			// The return value indicates whether we want the visitation to proceed.
			// Return false to stop the traversal of the AST.
			return true;
		  }

			private:
		        clang::ASTContext *context;
		};

		class FindNamedClassConsumer : public clang::ASTConsumer {
		public:
				explicit FindNamedClassConsumer(clang::ASTContext *Context)
				  : Visitor(Context) {}

		  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
					// Traversing the translation unit decl via a RecursiveASTVisitor
					// will visit all nodes in the AST.
					Visitor.TraverseDecl(Context.getTranslationUnitDecl());
		  }
		private:
		  // A RecursiveASTVisitor implementation.
		  FindNamedClassVisitor Visitor;
		};

		class FindNamedClassAction : public clang::ASTFrontendAction {
			public:

				virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &compiler, llvm::StringRef InFile) {
					return std::unique_ptr<clang::ASTConsumer>(new FindNamedClassConsumer(&compiler.getASTContext()));
				}
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
