#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/gtx/string_cast.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define PI 3.14159265
//#include <learnopengl/filesystem.h>
#include "shader.h"
#include "camera.h"
#include <omp.h>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
using namespace std;
using namespace glm;
#define GLM_ENABLE_EXPERIMENTAL
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(-20, 20); // define the range


struct tunel{
    vec3 a{0.0,1.0,0.0};
    vector<vec3> rpoints;
    vector<vec3> rnor; //vector t
    vector<vec3> temp1;//perpendicular
    vector<vec3> temp2;//normal
    vector<vec3> normales;
    vector<int> dist;
    void cre()
    {
        rpoints.emplace_back(vec3(0,0,0));
        int x1 = 0,y1 = 0,z1 = 0;
        for(int i=0;i<10;i++)
        {
            float r1;int x,y,z;
            do{
                x = distr(gen),y=distr(gen),z=distr(gen);
                r1 = pow((pow((x - x1),2) +pow((y - y1),2)+pow((z - z1),2)),0.5);
            }while(r1<7 or r1>10);
            dist.push_back(r1);

            rnor.emplace_back(normalize(vec3(x-x1,y-y1,z-z1)));

            temp1.emplace_back(normalize(cruz(vec3(x-x1,y-y1,z-z1),a)));

            temp2.emplace_back(normalize(cruz(vec3(x-x1,y-y1,z-z1),normalize(cruz(vec3(x-x1,y-y1,z-z1),a)))));

            rpoints.emplace_back(vec3(x, y, z));

            x1=x;y1=y;z1=z;
        }
    }
    vec3 cruz(vec3 v,vec3 b) {
        return vec3(v.y*b.z - v.z*b.y,
                    v.z*b.x - v.x*b.z,
                    v.x*b.y - v.y*b.x);
    }
};


int main() {
    tunel a;
    a.cre();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    Shader lightingShader("../2.1.point.vs", "../2.1.point.fs", "../2.1.point.gs");
    //Shader lightCubeShader("../2.1.light_cube.vs", "../2.1.light_cube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    vector<vec3> allpoints;

    #pragma omp parallel for
    for(int i=0;i<10;i++) 
    {
        std::cout<<glm::to_string(a.rpoints[i])<<std::endl;

        int n=50;
        int r=1;
        for(int p=0;p<a.dist[0];p+=1)
        {
            vec3 temp = a.rnor[i];
            temp*=p;
            vec3 curr = a.rpoints[i]+temp;
            for(int j=0;j<n;j++)
            {
                vec3 x1 = a.temp1[i];
                vec3 y1 = a.temp2[i];
                std::cout<<glm::to_string(x1)<<std::endl;
                std::cout<<glm::to_string(y1)<<std::endl;
                y1*=(r*sin(2*PI*j/(n-1)));
                x1*=(r*cos(2*PI*j/(n-1)));

                vec3 vec_rad = curr+x1+y1;

                std::cout<<glm::to_string(vec_rad)<<std::endl;
                allpoints.emplace_back(vec_rad);
                a.normales.emplace_back(normalize(vec3(1,1,1)));
            }
        }
        
    }

    // first, configure the cube's VAO (and VBO)
    unsigned int VBO[2], cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(cubeVAO);
    // position attribute
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, allpoints.size() * sizeof(vec3), allpoints.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, a.normales.size() * sizeof(vec3), a.normales.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
    glPointSize(2);

    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_POINTS, 0, allpoints.size());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
