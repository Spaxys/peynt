#include <GLFW/glfw3.h>
#include <thread>

int main()
{
    glfwInit();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    glfwTerminate();
}

