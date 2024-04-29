#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// 着色器代码
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    uniform mat4 projection;
    uniform mat4 view;
    void main() {
        gl_Position = projection * view * vec4(aPos.x, aPos.y,0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

// 相机类
class Camera
{
public:
    glm::mat4 view;
    glm::vec3 position;
    glm::vec3 center;
    float     zoom;

    Camera() : position(0.0f, 0.0f, 0.0f), center(0, 0, -1), zoom(1.0f) { updateViewMatrix(); }

    void updateViewMatrix() { view = glm::lookAt(position, center, glm::vec3(0.0f, 1.0f, 0.0f)); }

    void zoomIn()
    {
        zoom += 0.1f;
        updateViewMatrix();
    }

    void zoomOut()
    {
        zoom -= 0.1f;
        updateViewMatrix();
    }

    void moveLeft(float deltaTime)
    {
        position.x -= 0.1f * deltaTime;
        center.x -= 0.1f * deltaTime;
        updateViewMatrix();
    }

    void moveRight(float deltaTime)
    {
        position.x += 0.1f * deltaTime;
        center.x += 0.1f * deltaTime;
        updateViewMatrix();
    }

    void moveUp(float deltaTime)
    {
        position.y += 0.1f * deltaTime;
        center.y += 0.1f * deltaTime;
        updateViewMatrix();
    }

    void moveDown(float deltaTime)
    {
        position.y -= 0.1f * deltaTime;
        center.y -= 0.1f * deltaTime;
        updateViewMatrix();
    }

    void ProcessMouseScroll(float yoffset)
    {
        if (yoffset < 0.0f)
            zoomIn();
        if (yoffset > 0.0f)
            zoomOut();
    }
};

// 全局变量
const int WIDTH = 800;
const int HEIGHT = 600;
Camera    camera;

// 时间变量
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// 窗口大小改变回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

// 输入处理函数
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.moveUp(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.moveDown(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.moveLeft(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.moveRight(deltaTime);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

int main()
{
    // 初始化 GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Camera Example", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 初始化 glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // 设置视口
    glViewport(0, 0, WIDTH, HEIGHT);

    // 编译着色器程序
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 定义线段的顶点数据
    float vertices[] = {
        -0.5f,
        -0.5f, // 线段1的起点
        0.5f,
        0.5f, // 线段1的终点
        -0.5f,
        0.5f, // 线段2的终点（与线段1的终点重合）
        0.5f,
        -0.5f // 线段2的起点（与线段1的起点重合）
    };

    // 定义线段的索引数据
    unsigned int indices[] = {
        0,
        1, // 第一条线段的起点和终点
        1,
        2, // 第二条线段的起点和终点
        2,
        3 // 第三条线段的起点和终点
    };

    // 创建并绑定顶点缓冲对象（VBO）和索引缓冲对象（EBO）
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // 渲染命令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);

        // 设置投影矩阵
        glm::mat4 projection = glm::ortho(
            -1.0f * camera.zoom,
            1.0f * camera.zoom,
            -1.0f * camera.zoom * (float)HEIGHT / (float)WIDTH,
            1.0f * camera.zoom * (float)HEIGHT / (float)WIDTH,
            -1.0f,
            1.0f);
        // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)HEIGHT / (float)WIDTH, 0.1f, 100.0f);
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // 设置视图矩阵
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));

        // 绘制线段
        glBindVertexArray(VAO);
        glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0); // 绘制六个顶点，按顺序连接成三条线段

        // 交换缓冲并查询事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理资源
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    // 关闭 GLFW
    glfwTerminate();
    return 0;
}