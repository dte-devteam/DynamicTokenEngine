#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

#include "hard_api/include/vulkan_api.h"


#include "tokenfunction/include/algebra.h"
int main() {
    tokenfunction::argument A, B, C, D, E;
    int a = 2, b = 2, c = 8, d = 0, e = 0;
    A.valuepointer = &a;
    B.valuepointer = &b;
    C.valuepointer = &c;
    D.valuepointer = &d;
    E.valuepointer = &e;
    tokenfunction::algebra::addinstance.execute({ A, B, D });
    return *(int*)D.valuepointer;



    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    hard_api::window* win = nullptr;
    hard_api::VK_INSTANCE->createwindow(win);
    if (win->getvkres() != VK_SUCCESS) return -1;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    //while (!glfwWindowShouldClose(window)) {
    while (!glfwWindowShouldClose(win->getwin())) {
        glfwPollEvents();
    }

    //glfwDestroyWindow(window);
    delete win;

    glfwTerminate();

    return 0;
}