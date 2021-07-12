#pragma once

#include "api.h"
#include API_INTERFACE_ICAMERA

#include <iostream>
#include <memory>

using namespace std;

namespace subsystem {
	class Camera: public api::iCamera{

		public:
			Camera();
			virtual ~Camera();

			vec3  pos(){return this->pos_;}
			vec3& rpos(){return this->pos_;}
			void  pos(vec3 posIn){ this->pos_ = posIn;}

			vec3  target(){return this->target_;}
			vec3& rtarget(){return this->target_;}
			void  target(vec3 targetIn){ this->target_ = targetIn;}

			vec3  up(){return this->up_;}
			vec3& rup(){return this->up_;}
			void  up(vec3 upIn){ this->up_ = upIn;}

			vec3  directMove(){return this->directMove_;}
			vec3& rdirectMove(){return this->directMove_;}
			void  directMove(vec3 directMoveIn){ this->directMove_ = directMoveIn;}

			mat4  view(){return this->view_;}
			mat4& rview(){return this->view_;}
			void  view(mat4 viewIn){ this->view_ = viewIn;}

			mat4  proj(){return this->proj_;}
			mat4& rproj(){return this->proj_;}
			void  proj(mat4 projIn){ this->proj_ = projIn;}

			float  angle(){return this->angle_;}
			float& rangle(){return this->angle_;}
			void   angle(float angleIn){ this->angle_ = angleIn;}

			void perspective(float fovy, float aspect, float near, float far){
				this->fovy_     = fovy;
				this->aspect_   = aspect;
				this->near_     = near;
				this->far_      = far;

				this->proj_ = glm::perspective(
				                       glm::radians(this->fovy_),
				                       this->aspect_,
				                       this->near_,
				                       this->far_
				                    );
			}

			void lookAt(glm::vec3 posIn, glm::vec3 targetIn, glm::vec3 upIn){
				this->pos_      = posIn;
				this->target_   = targetIn;
				this->up_       = upIn;

				this->view_ = glm::lookAt(
				    posIn, // Camera is at camPos, in World Space
				    targetIn, // and looks at the origin
				    upIn  // Head is up (set to 0,-1,0 to look upside-down)
				);
			}

			void lookAt(){
				this->view_ = glm::lookAt(
				    this->pos_, // Camera is at camPos, in World Space
				    this->target_, // and looks at the origin
				    this->up_  // Head is up (set to 0,-1,0 to look upside-down)
				);
			}

			void windowResize(int width, int height){
				this->perspective(this->fovy_, width/height, this->near_, this->far_);
			}

			void keyPress(int keyCode){
				cout << "Camera::keyPress: keyCode = " << keyCode << endl;

				switch(keyCode){
					case 25: { // w
						this->view_ = glm::translate(this->view_, this->directMove_);
					}
						break;

					case 39: { // s
						glm::quat q             = glm::angleAxis(180.0f * (3.14159f/180.0f), glm::vec3(0, 1, 0));
						glm::vec3 backDirect    = glm::rotate(q, this->directMove_);
						this->view_             = glm::translate(this->view_, backDirect);
					}
						break;
					case 38: { // a
						glm::quat q         = glm::angleAxis(-(this->angle_) * (3.14159f/180.0f), glm::vec3(0, 1, 0));
						//this->pCam_->rview() = glm::mat4_cast(q) * this->pCam_->view();
						this->view_         = this->view_ * glm::mat4_cast(q);
						this->directMove_   = glm::inverse(glm::mat4_cast(q)) * glm::vec4(this->directMove_, 0.0) ;
					}
						break;

					case 40: { // d
						glm::quat q         = glm::angleAxis(this->angle_ * (3.14159f/180.0f), glm::vec3(0, 1, 0));
						//this->pCam_->rview() = glm::mat4_cast(q) * this->pCam_->view();
						this->view_         = this->view_ * glm::mat4_cast(q);
						this->directMove_   = glm::inverse(glm::mat4_cast(q)) * glm::vec4(this->directMove_, 1.0) ;
					}
						break;
				}

				//print(this->view_);
			}

			void Delete(){
				//delete this;
			}


		protected:

		private:
			glm::vec3 pos_;
			glm::vec3 target_;
			glm::vec3 up_;

			glm::vec3 directMove_;

			glm::mat4 view_;
			glm::mat4 proj_;

			float angle_{10.0f};
			glm::quat quatCam_;

			// perspective vars
			float fovy_{0.0f};
			float aspect_{0.0f};
			float near_{0.0f};
			float far_{0.0f};
	};
}


namespace api{

	template<>
	class Impl< api::iCamera >{
		public:
			static std::unique_ptr< api::iCamera > make(){
				return std::unique_ptr< api::iCamera > ( static_cast<api::iCamera*>(new subsystem::Camera() ));
			}

		private:
			Impl< api::iCamera >();
			~Impl< api::iCamera >();
	};
}
















