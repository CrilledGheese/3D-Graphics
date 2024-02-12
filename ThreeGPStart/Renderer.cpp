#include "Renderer.h"
#include "Camera.h"

Renderer::Renderer() 
{

}

// On exit must clean up any OpenGL resources e.g. the program, the buffers
Renderer::~Renderer()
{
	// TODO: clean up any memory used including OpenGL objects via glDelete* calls
	glDeleteProgram(m_program);
	glDeleteBuffers(1, &m_VAO);
	glDeleteBuffers(1, &t_VAO);
}

// Use IMGUI for a simple on screen GUI
void Renderer::DefineGUI()
{
	// Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui::Begin("3GP");						// Create a window called "3GP" and append into it.

	ImGui::Text("Visibility.");					// Display some text (you can use a format strings too)	

	ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable

	ImGui::Checkbox("Cull Face", &m_cullFace);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
	ImGui::End();
}

bool Renderer::Cube()
{

	GLuint posVBO;
	GLuint colVBO;
	GLuint eleVBO;

	std::vector<GLfloat> cVertices = 
	{
		//Front
		100.f,100.f,100.f,
		-100.f,100.f,100.f,
		-100.f,-100.f,100.f,
		100.f,-100.f,100.f,


		//Right
		100.f,-100.f,100.f,
		100.f,-100.f,-100.f,
		100.f,100.f,-100.f,
		100.f,100.f,100.f,

		//Back
		100.f,100.f,-100.f,
		100.f,-100.f,-100.f,
		-100.f,-100.f,-100.f,
		-100.f,100.f,-100.f,

		//Top 
		-100.f,100.f,-100.f,
		-100.f,100.f,100.f,
		100.f,100.f,100.f,
		100.f,100.f,-100.f,

		//Left
		-100.f,100.f,100.f,
		-100.f,100.f,-100.f,
		-100.f,-100.f,-100.f,
		-100.f,-100.f,100.f,

		//Bottom
		-100.f,-100.f,100.f,
		-100.f,-100.f,-100.f,
		 100.f,-100.f,-100.f,
		 100.f,-100.f,100.f,
	};

	std::vector<GLuint> Elements = 
	{
		//Front
		0,1,2,2,3,0,

		//right
		4,5,6,6,7,4,

		//Back
		8,9,10,10,11,8,

		//Top
		12,13,14,14,15,12,

		//Left
		16,17,18,18,19,16,

		//Bottom
		20,21,22,22,23,20

	};

	std::vector<glm::vec3> colours = {
		glm::vec3(1.0f,0.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),

		glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f),

		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(0.0f,0.0f,1.0f),

		glm::vec3(1.0f,1.0f,0.0f),
		glm::vec3(1.0f,1.0f,0.0f),
		glm::vec3(1.0f,1.0f,0.0f),
		glm::vec3(1.0f,1.0f,0.0f),

		glm::vec3(1.0f,0.0f,1.0f),
		glm::vec3(1.0f,0.0f,1.0f),
		glm::vec3(1.0f,0.0f,1.0f),
		glm::vec3(1.0f,0.0f,1.0f),

		glm::vec3(0.0f,1.0f,1.0f),
		glm::vec3(0.0f,1.0f,1.0f),
		glm::vec3(0.0f,1.0f,1.0f),
		glm::vec3(0.0f,1.0f,1.0f),

	};

	c_numElements = Elements.size();

	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * cVertices.size(), cVertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colours.size(), colours.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &eleVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eleVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * Elements.size(), Elements.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &c_VAO);
	glBindVertexArray(c_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, colVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eleVBO);

	glBindVertexArray(0);

	return true;
}

GLuint loadCubeMap(std::vector<std::string> Faces)
{
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	int Width, Height;

	Helpers::ImageLoader skyText;

	for (int x = 0; x < Faces.size(); x++)
	{
		skyText.Load(Faces[x]);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + x,
			0,
			GL_RGBA,
			skyText.Width(),
			skyText.Height(),
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			skyText.GetData()
		);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texID;
}

bool Renderer::CreateTerrain(int numCellsX, int numCellsZ, float sizeX, float sizeZ, const std::string& textureFilename)
{
	std::vector<GLuint> Elements;
	std::vector<glm::vec3>pos;

	Helpers::ImageLoader heightMap;
	Helpers::ImageLoader texture2;
	Helpers::Mesh mesh;


	if(!heightMap.Load("Data\\Heightmaps\\curvy.gif"))
		return false;

	BYTE* imageData = heightMap.GetData();

	//Number of vertices will be one more in each dimension
	int numVertsX{ numCellsX + 1 };
	int numVertsZ{ numCellsZ + 1 };
	int numVerts{ numVertsX * numVertsZ };
	int NOC = (numCellsZ) * (numCellsX);

	float imageVX = (float)heightMap.Width() / numVertsX;
	float imageVZ = (float)heightMap.Height() / numVertsZ;

	bool diamondPattern = true;
	std::vector<glm::vec2> uvCoords;

	for (float z = 0; z <= numCellsZ; z++)
	{
		for (float x = 0; x <= numCellsX; x++)
		{
			int imageX = imageVX * x;
			int imageZ = imageVZ * z;

			size_t Offset = ((size_t)imageX + (size_t)imageZ * heightMap.Width()) * 4;
			BYTE height = imageData[Offset];
			float PosY = (float)height * 5;

			pos.push_back(glm::vec3(x * sizeX, PosY, z * sizeZ));
			uvCoords.push_back(glm::vec2(x * sizeX/ (float)numCellsX, z * sizeZ / (float)numCellsZ)); // creates coords for texture from 0 - 1
		}
	}

	for (int z = 0; z < numCellsZ; z++)
	{
		for (int x = 0; x < numCellsX; x++)
		{
			int vertIndex = z * numVertsX + x;

			if (diamondPattern)
			{
				Elements.push_back(vertIndex); //0
				Elements.push_back(vertIndex + numVertsX); //2
				Elements.push_back(vertIndex + 1); //1

				Elements.push_back(vertIndex + numVertsX + 1); //3
				Elements.push_back(vertIndex + 1); //1
				Elements.push_back(vertIndex + numVertsX); //2
			}
			else
			{
				Elements.push_back(vertIndex); //0
				Elements.push_back(vertIndex + numVertsX + 1); //3
				Elements.push_back(vertIndex + 1); //1

				Elements.push_back(vertIndex + numVertsX + 1); //3
				Elements.push_back(vertIndex); //0
				Elements.push_back(vertIndex + numVertsX); //2
			}
			diamondPattern =! diamondPattern;
		}
		diamondPattern =! diamondPattern;
	}

	GLuint ElementsVBO;
	GLuint posVBO;
	GLuint normVBO;
	GLuint textVBO;

	t_numElements = Elements.size();

	glGenBuffers(1, &ElementsVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * Elements.size(), Elements.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * pos.size(), pos.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * pos.size(), pos.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &textVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvCoords.size(), uvCoords.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &t_VAO);
	glBindVertexArray(t_VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsVBO);

	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, normVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindVertexArray(0);

	if (texture2.Load("Data\\Textures\\grass11.bmp"))
	{
		glGenTextures(1, &text);
		glBindTexture(GL_TEXTURE_2D, text);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture2.Width(), texture2.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture2.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
	}

	return true;
}

// Load, compile and link the shaders and create a program object to host them
bool Renderer::CreateProgram()
{
	if (m_program)
		glDeleteProgram(m_program);

	if (s_program)
		glDeleteProgram(s_program);

	if (c_program)
		glDeleteProgram(c_program);

	// Create a new program (returns a unqiue id)
	m_program = glCreateProgram();
	s_program = glCreateProgram();
	c_program = glCreateProgram();

	// Load and create vertex and fragment shaders
	GLuint vertex_shader{ Helpers::LoadAndCompileShader(GL_VERTEX_SHADER, "Data/Shaders/vertex_shader.vert") };
	GLuint fragment_shader{ Helpers::LoadAndCompileShader(GL_FRAGMENT_SHADER, "Data/Shaders/fragment_shader.frag") };

	GLuint skybox_vertex_shader{ Helpers::LoadAndCompileShader(GL_VERTEX_SHADER, "Data/Shaders/sky_vertex_shader.vert") };
	GLuint skybox_fragment_shader{ Helpers::LoadAndCompileShader(GL_FRAGMENT_SHADER, "Data/Shaders/sky_fragment_shader.frag") };

	GLuint cube_vertex_shader{ Helpers::LoadAndCompileShader(GL_VERTEX_SHADER, "Data/Shaders/cube_vertex_shader.vert") };
	GLuint cube_fragment_shader{ Helpers::LoadAndCompileShader(GL_FRAGMENT_SHADER, "Data/Shaders/cube_fragment_shader.frag") };

	//if (vertex_shader == 0 || fragment_shader == 0)
	//	return false;

	// Attach the vertex shader to this program (copies it)
	glAttachShader(m_program, vertex_shader);

	// The attibute location 0 maps to the input stream "vertex_position" in the vertex shader
	// Not needed if you use (location=0) in the vertex shader itself
	//glBindAttribLocation(m_program, 0, "vertex_position");

	// Attach the fragment shader (copies it)
	glAttachShader(m_program, fragment_shader);

	glAttachShader(s_program, skybox_vertex_shader);
	glAttachShader(s_program, skybox_fragment_shader);

	glAttachShader(c_program, cube_vertex_shader);
	glAttachShader(c_program, cube_fragment_shader);

	// Done with the originals of these as we have made copies
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glDeleteShader(skybox_vertex_shader);
	glDeleteShader(skybox_fragment_shader);

	glDeleteShader(cube_vertex_shader);
	glDeleteShader(cube_fragment_shader);

	// Link the shaders, checking for errors
	if (!Helpers::LinkProgramShaders(m_program))
		return false;

	if (!Helpers::LinkProgramShaders(s_program))
		return false;

	if (!Helpers::LinkProgramShaders(c_program))
		return false;

	return true;
}

// Load / create geometry into OpenGL buffers	
bool Renderer::InitialiseGeometry()
{
	Renderer::CreateTerrain(20, 20, 200, 200, "Data\\Heightmaps\\curvy.GIF");
	Renderer::Cube();

	// Load and compile shaders into m_program
	if (!CreateProgram())
		return false;

	//sky
	std::vector<std::string> skyFace
	{
		"Data\\Models\\Sky\\Clouds\\SkyBox_Left.PNG",
		"Data\\Models\\Sky\\Clouds\\SkyBox_Right.PNG",
		"Data\\Models\\Sky\\Clouds\\SkyBox_Top.PNG",
		"Data\\Models\\Sky\\Clouds\\SkyBox_Bottom.PNG",
		"Data\\Models\\Sky\\Clouds\\SkyBox_Front.PNG",
		"Data\\Models\\Sky\\Clouds\\SkyBox_Back.PNG"
	};

	std::vector<glm::vec3> skyVerts =
	{
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		 glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),

		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),

		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),

		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),

		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),

		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f)
	};

	GLuint Sky_VerticesVBO;
	//Sky_NormalsVBO, Sky_ElementsVBO, Sky_TextureVBO;

	glGenBuffers(1, &Sky_VerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Sky_VerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * skyVerts.size(), skyVerts.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &s_VAO);
	glBindVertexArray(s_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, Sky_VerticesVBO);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer
	(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	s_numElements = skyVerts.size();

	Helpers::ModelLoader skyModel;
	if (!skyModel.LoadFromFile("Data\\Models\\Sky\\Clouds\\skybox.x"))
		return false;

	skyTex = loadCubeMap(skyFace);

	// Helpers has an object for loading 3D geometry, supports most types

	// E.g. Load in the jeep
	Helpers::ModelLoader loader;
	if (!loader.LoadFromFile("Data\\Models\\Jeep\\jeep.obj"))
		return false;

	Model newModel;

	// Now we can loop through all the mesh in the loaded model:
	for (const Helpers::Mesh& mesh : loader.GetMeshVector())
	{
		// We can extract from the mesh via:
		//mesh.vertices  - a vector of glm::vec3 (3 floats) giving the position of each vertex
		//mesh.elements - a vector of unsigned ints defining which vertices make up each triangle

		// TODO: create VBO for the vertices and a EBO for the elements
		GLuint posVBO;
		GLuint eleVBO;
		GLuint normVBO;
		GLuint texVBO;

		// TODO: create a VBA to wrap everything and specify locations in the shaders

		m_numElements = mesh.elements.size();
		//tex = vec3 texture_colour;

		glGenBuffers(1, &posVBO);
		glBindBuffer(GL_ARRAY_BUFFER, posVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &normVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.normals.size(), mesh.normals.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &texVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * mesh.uvCoords.size(), mesh.uvCoords.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &eleVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eleVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.elements.size(), mesh.elements.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eleVBO);

		glBindBuffer(GL_ARRAY_BUFFER, posVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ARRAY_BUFFER, normVBO);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ARRAY_BUFFER, texVBO);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindVertexArray(0);

		// Add this as a mesh
		MyMesh newMesh;
		newMesh.m_VAO = m_VAO;
		// etc.

		newModel.mesh.push_back(newMesh);
	}

	// Add to collection of models
	m_models.push_back(newModel);

	Helpers::ImageLoader texture;

	if(texture.Load("Data\\Models\\Jeep\\jeep_army.jpg"));
	{
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.Width(), texture.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
	}

	return true;
}

// Render the scene. Passed the delta time since last called.
void Renderer::Render(const Helpers::Camera& camera, float deltaTime)
{			
	// Configure pipeline settings
	glEnable(GL_DEPTH_TEST);

	if (m_cullFace)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Wireframe mode controlled by ImGui
	if (m_wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Clear buffers from previous frame
	glClearColor(0.0f, 0.0f, 0.0f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO: Compute viewport and projection matrix
	GLint viewportSize[4];
	glGetIntegerv(GL_VIEWPORT, viewportSize);
	const float aspect_ratio = viewportSize[2] / (float)viewportSize[3];
	glm::mat4 projection_xform = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 400000.0f);

	// TODO: Compute camera view matrix and combine with projection matrix for passing to shader
	glm::mat4 view_xform = glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetLookVector(), camera.GetUpVector());
	GLuint combined_xform_id;
	glm::mat4 combined_xform = projection_xform * view_xform;

	glm::mat4 view_xform2 = glm::mat4(glm::mat3(view_xform));
	glm::mat4 combined_xform2 = projection_xform * view_xform2;

	glm::mat4 model_xform = glm::mat4(1);

	// TODO: Send the combined matrix to the shader in a uniform
	combined_xform_id = glGetUniformLocation(m_program, "combined_xform");
	glUniformMatrix4fv(combined_xform_id, 1, GL_FALSE, glm::value_ptr(combined_xform));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(glGetUniformLocation(m_program, "sam_tex"), 0);

	// TODO: render each mesh. Send the correct model matrix to the shader in a uniform
	GLuint model_xform_id = glGetUniformLocation(m_program, "model_xform");
	glUniformMatrix4fv(model_xform_id, 1, GL_FALSE, glm::value_ptr(model_xform));

	glUseProgram(s_program);

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	combined_xform_id = glGetUniformLocation(s_program, "combined_xform");
	glUniformMatrix4fv(combined_xform_id, 1, GL_FALSE, glm::value_ptr(combined_xform2));

	GLuint model_xform_id2 = glGetUniformLocation(s_program, "model_xform");
	glUniformMatrix4fv(model_xform_id2, 1, GL_FALSE, glm::value_ptr(model_xform));

	glBindVertexArray(s_VAO);
	glDrawArrays(GL_TRIANGLES, 0, s_numElements);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyTex);

	glUniform1i(
		glGetUniformLocation(s_program, "cubemap"),
		0
	);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(TRUE);

	glUseProgram(c_program);

	glm::mat4 cube_model_xform = glm::mat4(1);

	static float angle = 0;
	static bool rotateY = true;
	if (rotateY) // Rotate around y axis		
		cube_model_xform = glm::translate(cube_model_xform, glm::vec3{ 0, angle * 100, 0 }) * (glm::rotate(cube_model_xform, angle, glm::vec3{ 0, 1, 0 }));
	else // Rotate around x axis		
		cube_model_xform = glm::translate(cube_model_xform, glm::vec3{ 0, 0, angle * 100 }) * (glm::rotate(cube_model_xform, angle, glm::vec3{ 1, 0, 0 }));
	angle += 0.001f;

	if (angle > glm::two_pi<float>())
	{


		angle = 0;
		rotateY = !rotateY;
	}

	GLuint cube_model_xform_id = glGetUniformLocation(c_program, "model_xform");
	glUniformMatrix4fv(cube_model_xform_id, 1, GL_FALSE, glm::value_ptr(cube_model_xform));
	combined_xform_id = glGetUniformLocation(c_program, "combined_xform");
	glUniformMatrix4fv(combined_xform_id, 1, GL_FALSE, glm::value_ptr(combined_xform));
	glBindVertexArray(c_VAO);
	glDrawElements(GL_TRIANGLES, c_numElements, GL_UNSIGNED_INT, (void*)0);

	glUseProgram(m_program);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_numElements, GL_UNSIGNED_INT, (void*)0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, text);
	glUniform1i(glGetUniformLocation(m_program, "sam_tex"), 0);

	glBindVertexArray(t_VAO);
	glDrawElements(GL_TRIANGLES, t_numElements, GL_UNSIGNED_INT, (void*)0);
}