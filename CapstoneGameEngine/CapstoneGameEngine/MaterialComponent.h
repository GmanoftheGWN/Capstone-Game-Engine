#pragma once
#include <glew.h>
#include <iostream>
#include "Component.h"
class MaterialComponent: public Component {
	private:
		GLuint textureID;
		std::string filename;
	public:
		MaterialComponent(Ref<Component> parent_, const char* filename_);
		virtual ~MaterialComponent();
		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime_);
		virtual void Render()const;

		inline GLuint getTextureID() const { return textureID; }
};

