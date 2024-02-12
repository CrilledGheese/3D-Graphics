#pragma once

#include "ExternalLibraryHeaders.h"

#include "Helper.h"
#include "Mesh.h"
#include "Camera.h"
#include "ImageLoader.h"


// TODO: need to add a mesh as some models have multiple mesh
struct MyMesh
{
	GLuint m_VAO{ 0 };
	GLuint tex{ 0 };
	GLuint m_numElements{ 0 };
};

// A model which can have multiple mesh
struct Model
{
	std::vector<MyMesh> mesh;
};

class Renderer
{
private:
	std::vector<Model> m_models;

	// Program object - to host shaders
	GLuint m_program{ 0 };
	GLuint s_program{ 0 };
	GLuint c_program{ 0 };
	GLuint t_program{ 0 };

	// Vertex Array Object to wrap all render settings
	GLuint m_VAO{ 0 };
	GLuint c_VAO{ 0 };
	GLuint t_VAO{ 0 };
	GLuint s_VAO{ 0 };

	GLuint skyTex{ 0 };
	GLuint tex{ 0 };
	GLuint text{ 0 };

	// Number of elments to use when rendering
	GLuint m_numElements{ 0 };
	GLuint c_numElements{ 0 };
	GLuint t_numElements{ 0 };
	GLuint s_numElements{ 0 };

	Helpers::ModelLoader Loader;

	bool m_wireframe{ false };
	bool m_cullFace{ true };	
public:
	Renderer();
	~Renderer();

	// Draw GUI
	void DefineGUI();

	// Create the program. This is the compiled shaders.
	bool CreateProgram();

	// Create and / or load geometry, this is like 'level load'
	bool InitialiseGeometry();

	// Render the scene
	void Render(const Helpers::Camera& camera, float deltaTime);

	//Create Land
	bool CreateTerrain(int numCellsX, int numCellsZ, float sizeX, float sizeZ , const std::string& textureFilename);

	//create cube
	bool Cube();
};