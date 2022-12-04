#include<stdio.h>

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<Windows.h>
#ifdef _MSC_VER_
#pragma comment(linker,"/subsystem:\"windows\"/entry:\"mainCRTStartup\"")
#endif // _MSC_VER_

#include<thread>
#include <utility>
#include <chrono>
#include <functional>
#include <atomic>

#include"Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"stb_image.h"
#include"stb_image_write.h"
#include"stb_image_resize.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "LightPoint.h"

#include"Camera.h"
#include "Material.h"
#include"LightDirectional.h"
#include "LightSpot.h"
float lightx = 0, lighty = 100;
int WindowWidth,WindowHeight;
void ShiftLD() {
	lightx++;
	lighty++;
	

}
void Capture() {
	struct RGBA {
		char R;
		char G;
		char B;
		char A;
	};
	const char* Filepath ="";
	RGBA* PixelBuffer = new RGBA[970, 499];
	glReadPixels(0, 0, 970, 499, GL_RGBA, GL_UNSIGNED_BYTE,PixelBuffer);
	stbi_write_png("./Output/Img/Capture.png", 970, 499, 10, PixelBuffer, 0);
}

void CalculateFps() {
	double lastTime = glfwGetTime();
	int nbFrames = 0;


		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			printf("%d", nbFrames);
			nbFrames = 0;
			lastTime += 1.0;
	}
	
}
void ImGuiRender() {


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	{
		ImGui::Begin("Window",NULL,ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			ImGui::SetWindowPos(ImVec2(240, 0));
			ImGui::SetWindowSize(ImVec2(730,10));
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) {  }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { }
				if (ImGui::MenuItem("Close", "Ctrl+W")) {}
				if (ImGui::MenuItem("Refresh", "Ctrl+F")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("...", "..")) {  }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		ImGui::End();
	}
	ImGui::Begin("SideBar", NULL, ImGuiWindowFlags_MenuBar); {

		if (ImGui::BeginMenuBar())
		{
			ImGui::SetWindowPos(ImVec2(0, 0));
			ImGui::SetWindowSize(ImVec2(240, 10));
			

		}
		
		if (ImGui::Button("ScreenShot", ImVec2(100, 29))) {}
		ImGui::End();
	}
	ImGui::Render();
} 



#pragma region Model Data
GLfloat vertices[] = {
	/*0.5f,0.5f,0.0f,  1.0f,0.0f,1.0f,    1.0f,1.0f,
	0.5f,-0.5f,0.0f,   0.0f,1.0f,0.1f,    1.0f,0.0f,
	-0.5f,0.5f,0.0f,   0.0f,0.0f,1.0f,    0.0f,0.0f,
	-0.5f,-0.5f,0.0f,      1.0f,1.0f,0.0f,    0.0f,1.0f*/
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	//0.0f,0.5f,0.3f,0.5f,0.7f
	/*0.0f,0.1f,1.0f,
	-0.25f,0,0.0f, */
	//0.5f,-0.5f,0.0f,
	//0.0f,0.5f,0.0f,

};/*
unsigned int indices[] = {
	0,2,1,
	3,1,2
	//2,1,3
};*/
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(2.0f,5.0f,-15.0f),
	glm::vec3(-1.5f,-2.2f,-2.5f),
	glm::vec3(-3.8f,-2.0f,-12.3f),
	glm::vec3(2.4f,-0.4f,-3.5f),
	glm::vec3(-1.7f,3.0f,-7.5f),
	glm::vec3(1.3f,-2.0f,-2.5f),
	glm::vec3(1.5f,2.0f,-2.5f),
	glm::vec3(1.5f,0.2f,-1.5f),
	glm::vec3(-1.3f,1.0f,-1.5f)
};
#pragma endregion
#pragma region Camera Declare
//Camera.Class
//Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0,0, 0), glm::vec3(0, 1.0f, 0));

Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion
#pragma region LightDeclare
//LightSpot Light = LightSpot(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 1.0f, 1.0f));
LightPoint Light = LightPoint(glm::vec3(1.0f, 1.0f, -1.0f),glm::vec3(glm::radians(45.0f),glm::radians(45.0f),0),glm::vec3(2.0f,0,0));
#pragma endregion
#pragma region Input Declare
float lastX;
float lastY;
bool firstMouse = true;
bool mousestate = false;


void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	
	if (mousestate == true) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CENTER_CURSOR);
		if (firstMouse == true) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CENTER_CURSOR);
			//lastX = xPos;
			//lastY = yPos;
			firstMouse = false;
		}
		float deltaX, deltaY;
		deltaX = (xPos - 970/2);
		deltaY = (yPos - 499/2);
		
		lastX = xPos;
		lastY = yPos;
		glfwSetCursorPos(window, 970 / 2, 499 / 2);
		camera.ProcessMouseInput(deltaX, deltaY);
		
		//printf("%f\n", xPos);
	}
}

void processInput(GLFWwindow* window) {

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		if (/*glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && */ glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			if (mousestate == true) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				mousestate = false;
			}
			else
			{
				//glfwSetCursorPos(window, 970 / 2, 499 / 2);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CENTER_CURSOR);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				mousestate = true;
			}

		}
		if (mousestate == true) {
			glfwSetCursorPos(window, 970 / 2, 499 / 2);
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				camera.speedZ = 1.0f;
			}
			else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				camera.speedZ = -1.0f;
			}
			else {
				camera.speedZ = 0;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				camera.speedX = -1.0f;
			}
			else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				camera.speedX = 1.0f;
			}
			else {
				camera.speedX = 0;
			}

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
				camera.speedY = 1.0f;
			}
			else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
				camera.speedY = -1.0f;
			}
			else {
				camera.speedY = 0;
			}




			if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				camera.speedZ = -1.65f;
			}
			else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				camera.speedZ = 1.65f;
			}

			if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				camera.speedX = -1.25f;
			}
			else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				camera.speedX = 1.25f;
			}

		}








		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	
#pragma endregion
#pragma region Loading.Images
unsigned int LoadImageToGPU(const char* Filename,GLint internalFormat,GLenum Format,int textureSlot) {
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0+textureSlot);//Texture.Channel.0
	glBindTexture(GL_TEXTURE_2D, TexBuffer);


	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* dataA = stbi_load(Filename, &width, &height, &nrChannel, 0);
	if (dataA) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, Format, GL_UNSIGNED_BYTE, dataA);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Failed.To.Load.Image!:(");
	}
	stbi_image_free(dataA);
	return TexBuffer;
}
#pragma endregion
#pragma region V0.1Vert&Frag
/*const char* vertexShaderSource =
"#version 330 core \n										"
"layout(location = 0) in vec3 aPos;\n						"
"layout(location = 1) in vec3 aColor;\n						"
"out vec4 vertexColor;\n									"
"void main() {\n											"
"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\n"
"		vertexColor= vec4(aColor.x,aColor.y,aColor.z,1.0); \n"
"}\n	";

const char* fragmentShaderSource =
"#version 330 core \n								"
"in vec4 vertexColor;\n								"
"out vec4 FragColor;\n								"
"void main() {\n									"
"		FragColor = vertexColor;}\n					";
*/
#pragma endregion


int main() {
		#pragma region Opening.The.Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//GLEW.Open.Window
	GLFWwindow* window = glfwCreateWindow(970, 499,"Neon.V0.01.@~@",NULL,NULL);
	if (window == NULL) {
		printf("Window.Pointer=NULL,Failed.To.Create.Window");
		glfwTerminate();
		return -1;
	}
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsBlack();

	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_ENABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glewExperimental = true;
	//Init.GLEW
	if (glewInit()!=GLEW_OK) {
		printf("Init.Glew.Failed");
		glfwTerminate();
		return -1;
	}
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	//void framebuffer_size_callback(GLFWwindow * window,int width, int height){
		glViewport(0, 0,970, 499);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
#pragma endregion

		#pragma region Init.Shader
		Shader* MainShader = new Shader("vertexSource.vert", "fragmentSource.frag");
#pragma endregion
#pragma region Init.Material
		Material* MainMaterial = new Material(MainShader, 
			LoadImageToGPU("container2.png",GL_RGB,GL_RGBA,Shader::IMGDiffuse),
			LoadImageToGPU("container2_specular.png", GL_RGB, GL_RGBA, Shader::IMGSPECULAR), 
			glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
#pragma endregion
		#pragma region Init.Buffers.And.Load.Models-VAO&VBO
		unsigned int VAO;
		glGenVertexArrays(1,&VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

		//unsigned int EBO;
		//glGenBuffers(1, &EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//unsigned int vertexShader;
		//vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		//glCompileShader(vertexShader);
		//
		//unsigned int fragmentShader;
		//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		//glCompileShader(fragmentShader);
		//
		//unsigned int shaderProgram;
		//shaderProgram = glCreateProgram();
		//
		//glAttachShader(shaderProgram, vertexShader);
		//glAttachShader(shaderProgram, fragmentShader);
		//glLinkProgram(shaderProgram);

		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
		glEnableVertexAttribArray(0);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(4);
#pragma endregion

		#pragma region Init.And.Load.Images

		//unsigned int TexBufferA;
		//TexBufferA = LoadImageToGPU("Glass.jpeg",GL_RGB,GL_RGB,0);
		//unsigned int TexBufferB;
		//TexBufferB = LoadImageToGPU("nvidiafaq.png", GL_RGB, GL_RGB, 1);
		//glUseProgram(shaderProgram);
		// 
		//glGenTextures(1, &TexBufferB);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, TexBufferB);
#pragma endregion

		#pragma region Preparing.MVP.Matrices
		//glm::mat4 trans;
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0));
		glm::mat4 modelMat;
		//modelMat = glm::rotate(modelMat, glm::radians(-45.0f), glm::vec3(0, 1.0f, 1.0f));
		glm::mat4 viewMat;
		//viewMat = camera.GetViewMatrix();
		//viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
		glm::mat4 projMat;
		projMat = glm::perspective(glm::radians(45.0f),970.0f/499.0f, 0.1f, 100.0f);
		//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
#pragma endregion
		glCullFace(GL_BACK);
		//ProcessInput
		//std::thread t1(processInput,window);
		//t1.join();
		while (!glfwWindowShouldClose(window))
		{
			ShiftLD();
			processInput(window);
			ImGuiRender();
			glfwGetWindowSize(window, &WindowWidth, &WindowHeight);
			glViewport(0, 0, WindowWidth, WindowHeight);
			// LightDirectional Light = LightDirectional(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(glm::radians(lightx), glm::radians(lighty), 0));
			//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 0, 1.0f));
			//trans = glm::rotate(trans, glm::radians(0.1f), glm::vec3(0, 0, 0.001f));
			//trans = glm::translate(trans, glm::vec3(-0.001f, 0, 0));
			
			

			//ClearScreen
			//glClearColor(0.2f,0.2f,0.2f,1.0f);
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);



			viewMat = camera.GetViewMatrix();
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

			//float timeValue = glfwGetTime();
			//float changeValue = (sin(timeValue) / 2.0f) + 0.5;
			//int vertexColorLocation = glGetUniformLocation(shaderProgram, "inptColor");
			//
			//glUseProgram(shaderProgram);
			//glUniform4f(vertexColorLocation,0, changeValue, 0, 1.0f);
			
			for (int i = 0; i < 10; i++) {
				//glm::mat4 modelMat2;
				//SettingModelMatrix
				modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
				
				

				//SettingMaterial.To.ShaderProgram
				MainShader->use();
				//SettingMaterial.To.Textures
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, MainMaterial->diffuse);
				glActiveTexture(GL_TEXTURE0+1);
				glBindTexture(GL_TEXTURE_2D, MainMaterial->specular);

				//SettingMaterial.To.Uniforms
				//glUniform1i(glGetUniformLocation(testShader->ID, "TextureA"), 0);
				//glUniform1i(glGetUniformLocation(testShader->ID, "TextureB"), 1);
				//glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
				glUniformMatrix4fv(glGetUniformLocation(MainShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
				glUniformMatrix4fv(glGetUniformLocation(MainShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
				glUniformMatrix4fv(glGetUniformLocation(MainShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
				glUniform3f(glGetUniformLocation(MainShader->ID, "objectColor"),0.9f,0.9f,0.9f);
				glUniform3f(glGetUniformLocation(MainShader->ID, "ambientColor"), 0.4f, 0.4f, 0.4f);
				glUniform3f(glGetUniformLocation(MainShader->ID, "lightPos"),Light.LPPos.x, Light.LPPos.y, Light.LPPos.z);
				glUniform3f(glGetUniformLocation(MainShader->ID, "lightColor"), Light.LPColor.x, Light.LPColor.y, Light.LPColor.z);
				//glUniform3f(glGetUniformLocation(MainShader->ID, "lightDirUniform"),Light.LightPDirection.x, Light.LPDirection.y, Light.LPDirection.z);
				glUniform1f(glGetUniformLocation(MainShader->ID, "LightSpt.CosPhi"), Light.CosPhi);
				
				glUniform3f(glGetUniformLocation(MainShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
				//glUniform1f(glGetUniformLocation(MainShader->ID, "lightSpt.CosPhi"), Light.CosPhi);
				//glUniform1f(glGetUniformLocation(MainShader->ID, "LightPt.constant"), Light.constant);
				//glUniform1f(glGetUniformLocation(MainShader->ID, "LightPt.linear"), Light.linear);
				//glUniform1f(glGetUniformLocation(MainShader->ID, "LightPt.quadratic"), Light.quadratic);
				

				//glUniform3f(glGetUniformLocation(MainShader->ID, "material.ambient"));
				//MainMaterial->shader->SetUniform3f("material.diffuse", MainMaterial->diffuse);
				//MainMaterial->shader->SetUniform3f("material.specular", MainMaterial->specular);
				MainMaterial->shader->SetUniform3f("material.ambient", MainMaterial->ambient);
				MainMaterial->shader->SetUniform1f("material.shininess", MainMaterial->shininess);
				MainMaterial->shader->SetUniform1i("material.diffuse", Shader::IMGDiffuse);
				MainMaterial->shader->SetUniform1i("material.specular", Shader::IMGSPECULAR);
				MainMaterial->shader->SetUniform1f("material.shininess", MainMaterial->shininess);
				//MainMaterial->shader->SetUniform3f("material.specular", MainMaterial->specular);

				//glUniform3f(glGetUniformLocation(MainShader->ID, "material.diffuse"), 0, 0, 1.0f);
				//glUniform3f(glGetUniformLocation(MainShader->ID, "material.specular"), 1.0f, 1.0f, 1.0f);
				//glUniform1f(glGetUniformLocation(MainShader->ID, "material.shininess"), 64.0f);

				//SetingModel
				

				glBindVertexArray(VAO);
				//DrawCall
				glDrawArrays(GL_TRIANGLES, 0, 36);
				CalculateFps();
				//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				//glDrawArrays(GL_TRIANGLES,0,6);
				
			}
			//Cleanning.up&Preparing.For.Next.Render.Loop
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			glfwPollEvents();
			camera.UpdateCameraPosition();
			
		}
		//ExitProgramme
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
		return 0;
	//}
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

}

