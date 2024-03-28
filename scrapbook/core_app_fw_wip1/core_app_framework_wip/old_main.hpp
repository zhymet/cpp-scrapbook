//#include <iostream>
//
//#include <GL/glew.h>// GLEW
////#include <GL/GL.h> // OpenGL
//#include <GLFW/glfw3.h> // GLFW3
//#include <glm/glm.hpp> // GLM
//
//
//#include "imgui/imgui.h" //IMGUI
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"
//
//#include <glm/gtc/matrix_transform.hpp>
//
//#include "CoreAppFramework/include/caf/caf.hpp"
//#include "CoreAppFramework/include/vertux/vertux.hpp"
//
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor; \n"
//"void main()\n"
//"{ \n"
//"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
//"}\0";
//
////int main(void) {
//    /* Initialize CoreAppFramework library */
//    if (!caf::Engine::init())
//        return -1;
//
//    std::vector<caf::ContextHint> context_hints = {
//            { GLFW_SAMPLES, 4},                 // 4x antialiasing
//            { GLFW_CONTEXT_VERSION_MAJOR, 3 },  // We want OpenGL 3.3
//            { GLFW_CONTEXT_VERSION_MINOR, 3 },
//            { GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE },  // To make MacOS happy; should not be needed.
//            { GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE }   // We don't want the old OpenGL.
//    };
//
//    /* Create a windowed mode window and its OpenGL context */
//    auto main_context = caf::Context(640, 480, "Hello World!",
//        context_hints);
//
//    main_context.makeCurrent();
//
//
//    /* Loop until the user closes the window */
//    while (!main_window.shouldClose()) {
//
//        // Enable depth test
//        glEnable(GL_DEPTH_TEST);
//        // Accept fragment if it closer to the camera than the former one
//        glDepthFunc(GL_LESS);
//
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        /* Swap front and back buffers */
//        //glfwSwapBuffers(main_context);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//    //// The main UI context
//    //vux::Vertux main_canvas;
//    //main_canvas.origin.x = 200;
//    //main_canvas.origin.y = 200;
//    //main_canvas.transform.scale.x = 100;
//    //main_canvas.transform.scale.y = 100;
//
//    //// The top bar.
//    //vux::Vertux top_bar;
//    //vux::Layout top_bar_layout{ {1.f,0.1f},vux::Layout::AnchorType::TOP };
//
//    //// Register top bar as child of parent.
//    //top_bar.parent = &main_canvas;
//    //main_canvas.add_child(&top_bar);
//
//    ////Top bar inherits parents size by default.
//    //top_bar.origin = top_bar.parent->origin;
//    //top_bar.transform.scale = top_bar.parent->transform.scale;
//    //// Offset top bar size to fit the top 10% of the context.
//    ////Use the previously created Layout to apply a transformation on the top_bar vertux.
//    //top_bar_layout.apply(&top_bar);
//    //std::cout << "Size:" << top_bar.transform.scale.x << "," << top_bar.transform.scale.y << " Origin:" << top_bar.origin.x
//    //    << "," << top_bar.origin.y << std::endl;
//    //auto main_window = caf::Context(640, 480, "Hello World!");
//
//
//    //auto init_err = caf::Engine::init();
//
//    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
//
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window) {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//    glewExperimental = true; // Needed in core profile
//    GLenum err = glewInit();
//
//    // Initialize ImGUI
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    ImGui::StyleColorsDark();
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init("#version 330");
//
//
//    // OpenGLStuff
//    unsigned int vertexShader;
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//
//    unsigned int fragmentShader;
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//
//    //program object that we can activate by calling glUseProgram 
//    //Every shader and rendering call after glUseProgram will now use this program object (and thus the shaders).
//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram(); //The glCreateProgram function creates a program and returns the ID reference to the newly created program object. 
//    //Now we need to attach the previously compiled shaders to the program object and then link them with glLinkProgram:
//
//
//    //we attach the shaders to the program and link them via glLinkProgram.
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    //don't forget to delete the shader objects once we've linked them into the program object; we no longer need them anymore:
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//// ------------------------------------------------------------------
//    float vertices[] = {
//         0.5f,  0.5f, 0.0f,  // top right
//         0.5f, -0.5f, 0.0f,  // bottom right
//        -0.5f, -0.5f, 0.0f,  // bottom left
//        -0.5f,  0.5f, 0.0f   // top left 
//    };
//    unsigned int indices[] = {  // note that we start from 0!
//        0, 1, 3,  // first Triangle
//        1, 2, 3   // second Triangle
//    };
//
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//    /*
//    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//    glBindVertexArray(0);
//
//    */
//    // ..:: Initialization code :: ..
//// 1. bind Vertex Array Object
//    glBindVertexArray(VAO);
//    // 2. copy our vertices array in a vertex buffer for OpenGL to use
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    // 3. copy our index array in a element buffer for OpenGL to use
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    // 4. then set the vertex attributes pointers
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        // draw our first triangle
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//        //glDrawArrays(GL_TRIANGLES, 0, 3);
//        // 
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//
//        // // Tell OpenGL a new frame is about to begin
//        // ImGui_ImplOpenGL3_NewFrame();
//        // ImGui_ImplGlfw_NewFrame();
//        // ImGui::NewFrame();
//
//        // // ImGUI window creation
//        // ImGui::SetNextWindowSize({ main_canvas.transform.scale.x,main_canvas.transform.scale.y });
//        // ImGui::SetNextWindowPos({ main_canvas.origin.x,main_canvas.origin.y });
//        // ImGui::Begin("MainCanvas",0, ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar);
//        // // Text that appears in the window
//        ///* ImGui::Text("MainCanvas");
//        // ImGui::Text("Hello there adventurer!");*/
//        // // Checkbox that appears in the window
//        //// ImGui::Checkbox("Draw Triangle", &drawTriangle);
//        // // Slider that appears in the window
//        // //ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
//        // // Fancy color editor that appears in the window
//        //// ImGui::ColorEdit4("Color", color);
//        // // Ends the window
//        // ImGui::End();
//        // ImGui::SetNextWindowSize({ top_bar.transform.scale.x,top_bar.transform.scale.y });
//        // ImGui::SetNextWindowPos({ top_bar.origin.x,top_bar.origin.y });
//        // ImGui::Begin("MainCanvas2", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar);
//        // ImGui::End();
//        // // Renders the ImGUI elements
//        // ImGui::Render();
//        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // Deletes all ImGUI instances
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//
//    glfwTerminate();
//
//
//    //caf::Engine::is_init();
//    //caf::Engine::terminate();
//    //std::cout << ret;
//    //return 42;
//}
//
////#include "source/wrap/opengl/Shader.hpp"
////
////#include "source/wrap/opengl/wglVertexShader.hpp"
////#include "source/wrap/opengl/wglShaderProgram.hpp"
////
////
////
////
////static const GLfloat g_vertex_buffer_data_triangle[] = {
////        -1.0f, -1.0f, 0.0f,
////        1.0f, -1.0f, 0.0f,
////        0.0f,  1.0f, 0.0f,
////};
////
////// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
////// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
////static const GLfloat g_vertex_buffer_data_cube[] = {
////        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
////        -1.0f,-1.0f, 1.0f,
////        -1.0f, 1.0f, 1.0f, // triangle 1 : end
////        1.0f, 1.0f,-1.0f, // triangle 2 : begin
////        -1.0f,-1.0f,-1.0f,
////        -1.0f, 1.0f,-1.0f, // triangle 2 : end
////        1.0f,-1.0f, 1.0f,
////        -1.0f,-1.0f,-1.0f,
////        1.0f,-1.0f,-1.0f,
////        1.0f, 1.0f,-1.0f,
////        1.0f,-1.0f,-1.0f,
////        -1.0f,-1.0f,-1.0f,
////        -1.0f,-1.0f,-1.0f,
////        -1.0f, 1.0f, 1.0f,
////        -1.0f, 1.0f,-1.0f,
////        1.0f,-1.0f, 1.0f,
////        -1.0f,-1.0f, 1.0f,
////        -1.0f,-1.0f,-1.0f,
////        -1.0f, 1.0f, 1.0f,
////        -1.0f,-1.0f, 1.0f,
////        1.0f,-1.0f, 1.0f,
////        1.0f, 1.0f, 1.0f,
////        1.0f,-1.0f,-1.0f,
////        1.0f, 1.0f,-1.0f,
////        1.0f,-1.0f,-1.0f,
////        1.0f, 1.0f, 1.0f,
////        1.0f,-1.0f, 1.0f,
////        1.0f, 1.0f, 1.0f,
////        1.0f, 1.0f,-1.0f,
////        -1.0f, 1.0f,-1.0f,
////        1.0f, 1.0f, 1.0f,
////        -1.0f, 1.0f,-1.0f,
////        -1.0f, 1.0f, 1.0f,
////        1.0f, 1.0f, 1.0f,
////        -1.0f, 1.0f, 1.0f,
////        1.0f,-1.0f, 1.0f
////};
////
////// One color for each vertex. They were generated randomly.
////static const GLfloat g_color_buffer_data_cube[] = {
////        0.583f,  0.771f,  0.014f,
////        0.609f,  0.115f,  0.436f,
////        0.327f,  0.483f,  0.844f,
////        0.822f,  0.569f,  0.201f,
////        0.435f,  0.602f,  0.223f,
////        0.310f,  0.747f,  0.185f,
////        0.597f,  0.770f,  0.761f,
////        0.559f,  0.436f,  0.730f,
////        0.359f,  0.583f,  0.152f,
////        0.483f,  0.596f,  0.789f,
////        0.559f,  0.861f,  0.639f,
////        0.195f,  0.548f,  0.859f,
////        0.014f,  0.184f,  0.576f,
////        0.771f,  0.328f,  0.970f,
////        0.406f,  0.615f,  0.116f,
////        0.676f,  0.977f,  0.133f,
////        0.971f,  0.572f,  0.833f,
////        0.140f,  0.616f,  0.489f,
////        0.997f,  0.513f,  0.064f,
////        0.945f,  0.719f,  0.592f,
////        0.543f,  0.021f,  0.978f,
////        0.279f,  0.317f,  0.505f,
////        0.167f,  0.620f,  0.077f,
////        0.347f,  0.857f,  0.137f,
////        0.055f,  0.953f,  0.042f,
////        0.714f,  0.505f,  0.345f,
////        0.783f,  0.290f,  0.734f,
////        0.722f,  0.645f,  0.174f,
////        0.302f,  0.455f,  0.848f,
////        0.225f,  0.587f,  0.040f,
////        0.517f,  0.713f,  0.338f,
////        0.053f,  0.959f,  0.120f,
////        0.393f,  0.621f,  0.362f,
////        0.673f,  0.211f,  0.457f,
////        0.820f,  0.883f,  0.371f,
////        0.982f,  0.099f,  0.879f
////};
////
////const float screen_width = 640;
////const float screen_height = 480;
////
////float aspectaxis()
////{
////    float outputzoom = 1.0f;
////    float aspectorigin = 16.0f / 9.0f;
////    int aspectconstraint = 1;
////    switch (aspectconstraint)
////    {
////    case 1:
////        if ((screen_width / screen_height) < aspectorigin)
////        {
////            outputzoom *= (((float)screen_width / screen_height) / aspectorigin);
////        }
////        else
////        {
////            outputzoom *= ((float)aspectorigin / aspectorigin);
////        }
////        break;
////    case 2:
////        outputzoom *= (((float)screen_width / screen_height) / aspectorigin);
////        break;
////    default:
////        outputzoom *= ((float)aspectorigin / aspectorigin);
////    }
////    return outputzoom;
////}
////
////float recalculatefov()
////{
////    return 2.0f * glm::atan(glm::tan(glm::radians(45.0f / 2.0f)) / aspectaxis());
////}
////
////int main(void) {
////    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
////    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
////    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
////    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
////    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
////
////    GLFWwindow* window;
////
////    /* Initialize the library */
////    if (!glfwInit())
////        return -1;
////
////    /* Create a windowed mode window and its OpenGL context */
////    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
////    if (!window) {
////        glfwTerminate();
////        return -1;
////    }
////
////    /* Make the window's context current */
////    glfwMakeContextCurrent(window);
////    glewExperimental = true; // Needed in core profile
////    GLenum err = glewInit();
////
////    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
////    glm::mat4 projection = glm::perspective(recalculatefov(), 1.0f * 640 / 840, 0.1f, 10.0f);
////    // Or, for an ortho camera :
////    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
////
////    // Camera matrix
////    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
////    // Model matrix : an identity matrix (model will be at the origin)
////    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
////    // Our ModelViewProjection : multiplication of our 3 matrices
////    glm::mat4 mvp = projection * view * model; // Remember, matrix multiplication is the other way around
////
////
////
////    // OpenGl Camera vars
////    // position
////    glm::vec3 position = glm::vec3(0, 0, 5);
////    // horizontal angle : toward -Z
////    float horizontalAngle = 3.14f;
////    // vertical angle : 0, look at the horizon
////    float verticalAngle = 0.0f;
////    // Initial Field of View
////    //FoV is the level of zoom. 80° = very wide angle, huge deformations. 60° - 45° : standard. 20° : big zoom.
////    float initialFoV = 45.0f;
////
////    float speed = 3.0f; // 3 units / second
////    float mouseSpeed = 0.005f;
////
////
////    //////////////////////////////////////////////////////////////////////////////////////////////////////
////
////        /* OpenGl Example Init */
////    wogl::Shader gl_context_shader;
////    GLuint gl_context_shader_id = gl_context_shader.LoadShader("shaders/context.vert", "shaders/context.frag");
////
////    // Get a handle for our "MVP" uniform
////    // Only during the initialisation
////    GLuint MatrixID = glGetUniformLocation(gl_context_shader_id, "MVP");
////
////    // 1. create a Vertex Array Object and set it as the current one
////    // Do this once your window is created (= after the OpenGL Context creation) and before any other OpenGL call
////    GLuint VertexArrayID;
////    glGenVertexArrays(1, &VertexArrayID);
////    glBindVertexArray(VertexArrayID);
////
////    // 2. Create Vertex Buffer
////    // This will identify our vertex buffer, This needs to be done only once.
////    GLuint vertexbuffer;
////    // Generate 1 buffer, put the resulting identifier in vertexbuffer
////    glGenBuffers(1, &vertexbuffer);
////    // The following commands will talk about our 'vertexbuffer' buffer
////    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
////    // Give our vertices to OpenGL.
////    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_cube), g_vertex_buffer_data_cube, GL_STATIC_DRAW);
////
////    // 3. Create Color Buffer (bound and filled in the exact same way as the previous one)
////    GLuint colorbuffer;
////    glGenBuffers(1, &colorbuffer);
////    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
////    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data_cube), g_color_buffer_data_cube, GL_STATIC_DRAW);
////    float lastTime = 0.f;
////    /* Loop until the user closes the window */
////    while (!glfwWindowShouldClose(window)) {
////        double currentTime = glfwGetTime();
////        float deltaTime = float(currentTime - lastTime);
////
////
////        // Enable depth test
////        glEnable(GL_DEPTH_TEST);
////        // Accept fragment if it closer to the camera than the former one
////        glDepthFunc(GL_LESS);
////
////        /* Render here */
////        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////
////        // Use our shader
////        glUseProgram(gl_context_shader_id);
////
////        // Send our transformation to the currently bound shader, in the "MVP" uniform
////        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
////        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
////
////
////        // 1st attribute buffer : vertices
////        glEnableVertexAttribArray(0);
////        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
////        glVertexAttribPointer(
////            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
////            3,                  // size
////            GL_FLOAT,           // type
////            GL_FALSE,           // normalized?
////            0,                  // stride
////            (void*)0            // array buffer offset
////        );
////
////        // 2nd attribute buffer : colors
////        glEnableVertexAttribArray(1);
////        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
////        glVertexAttribPointer(
////            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
////            3,                                // size
////            GL_FLOAT,                         // type
////            GL_FALSE,                         // normalized?
////            0,                                // stride
////            (void*)0                          // array buffer offset
////        );
////
////        // Draw the triangle !
////        glDrawArrays(GL_TRIANGLES, 0, 3 * 12); // Starting from vertex 0; 3 vertices total -> 1 triangle
////        glDisableVertexAttribArray(0);
////
////        /* Swap front and back buffers */
////        glfwSwapBuffers(window);
////
////        /* Poll for and process events */
////        glfwPollEvents();
////    }
////
////    glfwTerminate();
////    return 0;
////}



///////////////////////////////////////////////


//
//void CallbackKeyboardKey(GLFWwindow* window, int key, int scancode, int action, int mods, KeyboardState& keyboard_state, ModifierState& modifier_state
//    , slice_buffer& buffer)
//{
//    // Push slice into slice buffer
//    gla::slice_keyboard_key slice;
//    slice.state = static_cast<KeyState>(action);
//    slice.id = static_cast<KeyboardKeyId>(key);
//    slice.mods = static_cast<ModifierKeyFlag>(mods);
//    slice.scancode = scancode;
//
//    // Push the slice into the buffer
//    buffer.push(slice);
//    // Action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
//    // scancode is unique for every key, regardless of whether it has a key token.
//    // query the scancode for any named key on the current platform with glfwGetKeyScancode.
//    // 
//    // Update the state
//    KeyboardKeyId key_id = static_cast<KeyboardKeyId>(key);
//    switch (static_cast<KeyState>(action)) {
//    case KeyState::PRESSED:
//        keyboard_state.state[key] = true; // Key is pressed
//        keyboard_state.fired_state[key] = true; // Key was triggered
//        keyboard_state.pressed_state[key] = true; // Key is pressed this frame
//        keyboard_state.released_state[key] = false; // Key is not released
//        keyboard_state.clicked_state[key] = false; // Key is not clicked
//        break;
//    case KeyState::RELEASED:
//        keyboard_state.state[key] = false; // Key is released
//        keyboard_state.fired_state[key] = true; // Key was triggered
//        keyboard_state.pressed_state[key] = false; // Key is not pressed
//        keyboard_state.released_state[key] = true; // Key is released this frame
//        keyboard_state.clicked_state[key] = true; // Key is clicked this frame
//        break;
//    case KeyState::REPEATED:
//        keyboard_state.state[key] = true; // Key is pressed
//        keyboard_state.fired_state[key] = true; // Key was triggered
//        keyboard_state.pressed_state[key] = true; // Key is pressed this frame
//        keyboard_state.released_state[key] = false; // Key is not released
//        keyboard_state.clicked_state[key] = false; // Key is not clicked
//        keyboard_state.repeated_state[key] = true; // Key is repeated
//        break;
//    }
//
//    switch (mods) {
//    case GLFW_MOD_SHIFT:
//        modifier_state.set(ModifierKeyFlag::SHIFT, true);
//        break;
//    case GLFW_MOD_CONTROL:
//        modifier_state.set(ModifierKeyFlag::CONTROL, true);
//        break;
//    case GLFW_MOD_ALT:
//        modifier_state.set(ModifierKeyFlag::ALT, true);
//        break;
//    case GLFW_MOD_SUPER:
//        modifier_state.set(ModifierKeyFlag::SUPER, true);
//        break;
//    case GLFW_MOD_CAPS_LOCK:
//        modifier_state.set(ModifierKeyFlag::CAPS_LOCK, true);
//        break;
//    case GLFW_MOD_NUM_LOCK:
//        modifier_state.set(ModifierKeyFlag::NUM_LOCK, true);
//        break;
//    default:
//        // Handle other mods if needed
//        break;
//    }
//
//    // Reset the timer for the next slice
//    buffer.resetTimer();
//}
//
//constexpr void CallbackCharacterEntered(GLFWwindow* window, unsigned int codepoint, KeyboardState& keyboard_state, slice_buffer& buffer) {
//    gla::sliceENTERED_CHAR slice;
//    slice.unicode = codepoint;
//
//    // Push the slice into the buffer
//    buffer.push(slice);
//
//    // Update the state
//    keyboard_state.char_entered = codepoint;
//
//    // Reset the timer for the next slice
//    buffer.resetTimer();
//}
//
//constexpr void CallbackCharacterEnteredMods(GLFWwindow* window, unsigned int codepoint, int mods, KeyboardState& keyboard_state, ModifierState& modifier_state, slice_buffer& buffer) {
//    keyboard_state.char_entered = codepoint;
//}
//
//constexpr void CallbackMousePosition(GLFWwindow* window, double x_pos, double y_pos, MouseState& mouse_state) {
//    mouse_state.x_position = x_pos;
//    mouse_state.y_position = y_pos;
//}
//
//constexpr void CallbackMouseScrolled(GLFWwindow* window, double x_offset, double y_offset, MouseState& mouse_state) {
//    mouse_state.x_scroll = x_offset;
//    mouse_state.y_scroll = y_offset;
//}
//
//constexpr void CallbackMouseEntered(GLFWwindow* window, int is_inside_window, MouseState& mouse_state) {
//    mouse_state.is_inside = (is_inside_window == GLFW_TRUE);
//}
//
//constexpr void CallbackMouseButton(GLFWwindow* window, int button, int action, int mods, MouseState& mouse_state, ModifierState& modifier_state) {
//    // Action is one of GLFW_PRESS or GLFW_RELEASE
//    MouseKeyId mouse_key_id = static_cast<MouseKeyId>(button);
//    switch (static_cast<KeyState>(action)) {
//    case KeyState::PRESSED:
//        mouse_state.state[button] = true; // Mouse button is pressed
//        mouse_state.fired_state[button] = true; // Mouse button was triggered
//        mouse_state.pressed_state[button] = true; // Mouse button is pressed this frame
//        mouse_state.released_state[button] = false; // Mouse button is not released
//        mouse_state.clicked_state[button] = false; // Mouse button is not clicked
//        break;
//    case KeyState::RELEASED:
//        mouse_state.state[button] = false; // Mouse button is released
//        mouse_state.fired_state[button] = true; // Mouse button was triggered
//        mouse_state.pressed_state[button] = false; // Mouse button is not pressed
//        mouse_state.released_state[button] = true; // Mouse button is released this frame
//        mouse_state.clicked_state[button] = true; // Mouse button is clicked this frame
//        break;
//    }
//
//    // Handle modifiers if needed
//    // ...
//
//    // Update modifier state
//    modifier_state.reset();
//    if (mods & GLFW_MOD_SHIFT) {
//        modifier_state.set(ModifierKeyFlag::SHIFT, true);
//    }
//    if (mods & GLFW_MOD_CONTROL) {
//        modifier_state.set(ModifierKeyFlag::CONTROL, true);
//    }
//    if (mods & GLFW_MOD_ALT) {
//        modifier_state.set(ModifierKeyFlag::ALT, true);
//    }
//    if (mods & GLFW_MOD_SUPER) {
//        modifier_state.set(ModifierKeyFlag::SUPER, true);
//    }
//    if (mods & GLFW_MOD_CAPS_LOCK) {
//        modifier_state.set(ModifierKeyFlag::CAPS_LOCK, true);
//    }
//    if (mods & GLFW_MOD_NUM_LOCK) {
//        modifier_state.set(ModifierKeyFlag::NUM_LOCK, true);
//    }
//}

//class slice_pointer_buffer {
//        void read_buffer(const slice_buffer& buffer_) {
//            for (auto& s : buffer_.slices_)
//            {
//                
//            }
//        }
//        /// Keyboard
//        std::vector<slice_keyboard_key*> keyboard_key_repeated;
//        std::vector<slice_keyboard_key*> keyboard_key_pressed;
//        std::vector<slice_keyboard_key*> keyboard_key_released;
//        std::vector<slice_keyboard_key*> keyboard_key_clicked;
//    
//};

//
//} // end namespcae gla


//    //namespace event {
//
//        /* Number of keys defined in the Key::Id enumerator */
//constexpr inline int GLA_EVENT_KEY_COUNT() {
//    return 124;
//}
///* Number of mouse buttons defined in MoueKeyId */
//constexpr inline int GLA_EVENT_BUTTON_COUNT() {
//    return  8;
//}
///* Number of modifier bitfields defined in ModifierKeyBitfield */
//constexpr inline int GLA_EVENT_MODIFIER_COUNT() {
//    return  7;
//}
///* Value indicating a key is in the pressed state, equivalent to true or 0. */
//constexpr inline int GLA_EVENT_STATE_KEY_PRESSED() { return  1; };
///* Value indicating a key is in the released state, equivalent to false or 0. */
//constexpr inline int GLA_EVENT_STATE_KEY_RELEASED() {
//    return  0;
//}
//
///* Type of input callbacks GLA can receive from GLFW. */
//enum class InputType : int {
//    MOUSE_BUTTON,
//    CURSOR_POSITION,
//    CURSOR_ENTER,
//    SCROLL_MOVE,
//    KEYBOARD_KEY,
//    ENTERED_CHAR,
//    ENTERED_CHAR_WITH_MODS,
//    FILE_DROP,
//    JOYSTICK_CONFIG,
//    GAMEPAD_STATE
//};
//
///* Key or button state. */
//enum class KeyState : int {
//    RELEASED = GLFW_RELEASE,
//    PRESSED = GLFW_PRESS,
//    REPEATED = GLFW_REPEAT,
//};
//
///* Keyboard key. */
//enum class KeyboardKeyId : int {
//    UNKNOWN = GLFW_KEY_UNKNOWN,
//    SPACE = GLFW_KEY_SPACE,
//    APOSTROPHE = GLFW_KEY_APOSTROPHE,
//    COMMA = GLFW_KEY_COMMA,
//    MINUS = GLFW_KEY_MINUS,
//    PERIOD = GLFW_KEY_PERIOD,
//    SLASH = GLFW_KEY_SLASH,
//    NUM0 = GLFW_KEY_0,
//    NUM1 = GLFW_KEY_1,
//    NUM2 = GLFW_KEY_2,
//    NUM3 = GLFW_KEY_3,
//    NUM4 = GLFW_KEY_4,
//    NUM5 = GLFW_KEY_5,
//    NUM6 = GLFW_KEY_6,
//    NUM7 = GLFW_KEY_7,
//    NUM8 = GLFW_KEY_8,
//    NUM9 = GLFW_KEY_9,
//    SEMICOLON = GLFW_KEY_SEMICOLON,
//    EQUAL = GLFW_KEY_EQUAL,
//    A = GLFW_KEY_A,
//    B = GLFW_KEY_B,
//    C = GLFW_KEY_C,
//    D = GLFW_KEY_D,
//    E = GLFW_KEY_E,
//    F = GLFW_KEY_F,
//    G = GLFW_KEY_G,
//    H = GLFW_KEY_G,
//    I = GLFW_KEY_I,
//    J = GLFW_KEY_J,
//    K = GLFW_KEY_K,
//    L = GLFW_KEY_L,
//    M = GLFW_KEY_M,
//    N = GLFW_KEY_N,
//    O = GLFW_KEY_O,
//    P = GLFW_KEY_P,
//    Q = GLFW_KEY_Q,
//    R = GLFW_KEY_R,
//    S = GLFW_KEY_S,
//    T = GLFW_KEY_T,
//    U = GLFW_KEY_U,
//    V = GLFW_KEY_V,
//    W = GLFW_KEY_W,
//    X = GLFW_KEY_X,
//    Y = GLFW_KEY_Y,
//    Z = GLFW_KEY_Z,
//    LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
//    BACKSLASH = GLFW_KEY_BACKSLASH,
//    BRACKET = GLFW_KEY_RIGHT_BRACKET,
//    ACCENT = GLFW_KEY_GRAVE_ACCENT,
//    WORLD_1 = GLFW_KEY_WORLD_1,
//    WORLD_2 = GLFW_KEY_WORLD_2,
//    ESCAPE = GLFW_KEY_ESCAPE,
//    ENTER = GLFW_KEY_ENTER,
//    TAB = GLFW_KEY_TAB,
//    BACKSPACE = GLFW_KEY_BACKSPACE,
//    INSERT = GLFW_KEY_INSERT,
//    DELETE = GLFW_KEY_DELETE,
//    RIGHT = GLFW_KEY_RIGHT,
//    LEFT = GLFW_KEY_LEFT,
//    DOWN = GLFW_KEY_DOWN,
//    UP = GLFW_KEY_UP,
//    PAGE_UP = GLFW_KEY_PAGE_UP,
//    PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
//    HOME = GLFW_KEY_HOME,
//    END = GLFW_KEY_END,
//    CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
//    SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
//    NUM_LOCK = GLFW_KEY_NUM_LOCK,
//    PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
//    PAUSE = GLFW_KEY_PAUSE,
//    F1 = GLFW_KEY_F1,
//    F2 = GLFW_KEY_F2,
//    F3 = GLFW_KEY_F3,
//    F4 = GLFW_KEY_F4,
//    F5 = GLFW_KEY_F5,
//    F6 = GLFW_KEY_F6,
//    F7 = GLFW_KEY_F7,
//    F8 = GLFW_KEY_F8,
//    F9 = GLFW_KEY_F9,
//    F10 = GLFW_KEY_F10,
//    F11 = GLFW_KEY_F11,
//    F12 = GLFW_KEY_F12,
//    F13 = GLFW_KEY_F13,
//    F14 = GLFW_KEY_F14,
//    F15 = GLFW_KEY_F15,
//    F16 = GLFW_KEY_F16,
//    F17 = GLFW_KEY_F17,
//    F18 = GLFW_KEY_F18,
//    F19 = GLFW_KEY_F19,
//    F20 = GLFW_KEY_F20,
//    F21 = GLFW_KEY_F21,
//    F22 = GLFW_KEY_F22,
//    F23 = GLFW_KEY_F23,
//    F24 = GLFW_KEY_F24,
//    F25 = GLFW_KEY_F25,
//    KP_0 = GLFW_KEY_KP_0,
//    KP_1 = GLFW_KEY_KP_1,
//    KP_2 = GLFW_KEY_KP_2,
//    KP_3 = GLFW_KEY_KP_3,
//    KP_4 = GLFW_KEY_KP_4,
//    KP_5 = GLFW_KEY_KP_5,
//    KP_6 = GLFW_KEY_KP_6,
//    KP_7 = GLFW_KEY_KP_7,
//    KP_8 = GLFW_KEY_KP_8,
//    KP_9 = GLFW_KEY_KP_9,
//    KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
//    KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
//    KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
//    KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
//    KP_ADD = GLFW_KEY_KP_ADD,
//    KP_ENTER = GLFW_KEY_KP_ENTER,
//    KP_EQUAL = GLFW_KEY_KP_EQUAL,
//    LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
//    LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
//    LEFT_ALT = GLFW_KEY_LEFT_ALT,
//    LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
//    RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
//    RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
//    RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
//    RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
//    MENU = GLFW_KEY_MENU
//}; // end enum class KeyboardKeyId : int
//
///* Keyboard key modifier bitfield. */
//enum class ModifierKeyFlag : int {
//    SHIFT = GLFW_MOD_SHIFT,           /// 0x0001
//    CONTROL = GLFW_MOD_CONTROL,       /// 0x0002
//    ALT = GLFW_MOD_ALT,               /// 0x0004
//    SUPER = GLFW_MOD_SUPER,           /// 0x0008
//    CAPS_LOCK = GLFW_MOD_CAPS_LOCK,   /// 0x0010
//    NUM_LOCK = GLFW_MOD_NUM_LOCK,     /// 0x0020
//    NONE = -1
//};
//
///* Mouse button. */
//enum class MouseKeyId : int {
//    UNKNOWN = -1,
//    MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1,  /// 0
//    MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2,  /// 1
//    MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3,  /// 2
//    MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,  /// 3
//    MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,  /// 4
//    MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,  /// 5
//    MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,  /// 6
//    MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8,  /// 7
//    MOUSE_LEFT = GLFW_MOUSE_BUTTON_LEFT,   /// GLFW_MOUSE_BUTTON_1
//    MOUSE_RIGHT = GLFW_MOUSE_BUTTON_RIGHT, /// GLFW_MOUSE_BUTTON_2
//};
//
//enum class MouseWindowState {
//    ENTERED = GLFW_TRUE,
//    EXITED = GLFW_FALSE
//};
//
//enum class JoystickConfigState : int {
//    CONNECTED = GLFW_CONNECTED,
//    DISCONNECTED = GLFW_DISCONNECTED
//};
//
///* Joystick input identifier. */
//enum class JoystickId : int {
//    IN_1 = GLFW_JOYSTICK_1, /// 0
//    IN_2 = GLFW_JOYSTICK_2, /// 1
//    IN_3 = GLFW_JOYSTICK_3, /// 2
//    IN_4 = GLFW_JOYSTICK_4, /// 3
//    IN_5 = GLFW_JOYSTICK_5, /// 4
//    IN_6 = GLFW_JOYSTICK_6, /// 5
//    IN_7 = GLFW_JOYSTICK_7, /// 6
//    IN_8 = GLFW_JOYSTICK_8, /// 7
//    IN_9 = GLFW_JOYSTICK_9, /// 8
//    IN_10 = GLFW_JOYSTICK_10, /// 9
//    IN_11 = GLFW_JOYSTICK_11, /// 10
//    IN_12 = GLFW_JOYSTICK_12, /// 11
//    IN_13 = GLFW_JOYSTICK_13, /// 12
//    IN_14 = GLFW_JOYSTICK_14, /// 13
//    IN_15 = GLFW_JOYSTICK_15, /// 14
//    IN_16 = GLFW_JOYSTICK_16, /// 15
//};
//
///* Joystick input hat state. */
//enum class JoystickHatState : int {
//    CENTERED = GLFW_HAT_CENTERED, /// 0
//    UP = GLFW_HAT_UP, /// 1
//    RIGHT = GLFW_HAT_RIGHT, /// 2
//    DOWN = GLFW_HAT_DOWN, /// 3
//    LEFT = GLFW_HAT_LEFT, /// 4
//    RIGHT_UP = GLFW_HAT_RIGHT_UP, /// (GLFW_HAT_RIGHT | GLFW_HAT_UP)
//    RIGHT_DOWN = GLFW_HAT_RIGHT_DOWN, ///  (GLFW_HAT_RIGHT | GLFW_HAT_DOWN)
//    LEFT_UP = GLFW_HAT_LEFT_UP, /// (GLFW_HAT_LEFT | GLFW_HAT_UP)
//    LEFT_DOWN = GLFW_HAT_LEFT_DOWN, /// (GLFW_HAT_LEFT | GLFW_HAT_DOWN)
//};
//
//enum class GamepadButtonId : int {
//
//};
//
//enum class GamepadAxis : int {};
//
///* Event Slice Class */
//struct slice {
//    virtual InputType type() = 0;
//};
//
//struct slice_keyboard_key : slice {
//    KeyState state;
//    KeyboardKeyId id;
//    ModifierKeyFlag mods;
//    int scancode;
//
//    explicit constexpr slice_keyboard_key(
//        KeyState state = KeyState::RELEASED,
//        KeyboardKeyId id = KeyboardKeyId::UNKNOWN,
//        ModifierKeyFlag mods = ModifierKeyFlag::NONE, int scancode = -1)
//        : state(state)
//        , id(id)
//        , mods(mods)
//        , scancode(scancode) {
//    }
//    constexpr slice_keyboard_key()
//        : state(KeyState::RELEASED)
//        , id(KeyboardKeyId::UNKNOWN)
//        , mods(ModifierKeyFlag::NONE)
//        , scancode(-1) {
//    }
//
//    InputType type() {
//        return InputType::KEYBOARD_KEY;
//    }
//};
//
//struct slice_MOUSE_BUTTON : slice {
//    using input_type = std::integral_constant<InputType, InputType::MOUSE_BUTTON>;
//    KeyState state;
//    MouseKeyId id;
//    ModifierKeyFlag mods;
//
//    explicit constexpr slice_MOUSE_BUTTON(KeyState state, MouseKeyId id, ModifierKeyFlag mods)
//        : state(state)
//        , id(id)
//        , mods(mods) {
//    }
//    constexpr slice_MOUSE_BUTTON()
//        : state(KeyState::RELEASED)
//        , id(MouseKeyId::UNKNOWN)
//        , mods(ModifierKeyFlag::NONE) {
//    }
//};
//
//struct slice_CURSOR_POSITION : slice {
//    using input_type = std::integral_constant<InputType, InputType::CURSOR_POSITION>;
//    double x_pos;
//    double y_pos;
//    explicit constexpr slice_CURSOR_POSITION(double x_pos, double y_pos)
//        : x_pos(x_pos)
//        , y_pos(y_pos) {
//    }
//    constexpr slice_CURSOR_POSITION() = default;
//
//};
//
//struct slice_CURSOR_ENTER : slice {
//    using input_type = std::integral_constant<InputType, InputType::CURSOR_ENTER>;
//    MouseWindowState state;
//    explicit constexpr slice_CURSOR_ENTER(MouseWindowState state) : state(state) {}
//    constexpr slice_CURSOR_ENTER() = default;
//};
//
//struct sliceSCROLL_MOVE : slice {
//    using input_type = std::integral_constant<InputType, InputType::SCROLL_MOVE>;
//    double x_offset;
//    double y_offset;
//    constexpr sliceSCROLL_MOVE() = default;
//    explicit constexpr sliceSCROLL_MOVE(double x_offset, double y_offset)
//        : x_offset(x_offset)
//        , y_offset(y_offset) {
//    }
//};
//
//struct sliceENTERED_CHAR : slice {
//    using input_type = std::integral_constant<InputType, InputType::ENTERED_CHAR>;
//    unsigned int unicode;
//    constexpr sliceENTERED_CHAR() = default;
//    explicit constexpr sliceENTERED_CHAR(unsigned int unicode)
//        : unicode(unicode) {
//    }
//};
//
//struct sliceENTERED_CHAR_WITH_MODS : slice {
//    using input_type = std::integral_constant<InputType, InputType::ENTERED_CHAR_WITH_MODS>;
//    unsigned int unicode;
//    ModifierKeyFlag mods;
//    constexpr sliceENTERED_CHAR_WITH_MODS() = default;
//    explicit constexpr sliceENTERED_CHAR_WITH_MODS(unsigned int unicode, ModifierKeyFlag mods)
//        : unicode(unicode)
//        , mods(mods) {
//    }
//};
//
//struct sliceFILE_DROP : slice {
//    using input_type = std::integral_constant<InputType, InputType::FILE_DROP>;
//    int path_count;
//    const char** paths[];
//    constexpr sliceFILE_DROP() = default;
//    constexpr sliceFILE_DROP(int path_count, const char** paths)
//        : path_count(path_count)
//        , paths{ paths } {
//    }
//};
//
//struct sliceJOYSTICK_CONFIG : slice {
//    using input_type = std::integral_constant<InputType, InputType::JOYSTICK_CONFIG>;
//    JoystickId jid;
//    JoystickConfigState state;
//    constexpr sliceJOYSTICK_CONFIG() = default;
//    constexpr sliceJOYSTICK_CONFIG(JoystickId jid, JoystickConfigState state)
//        : jid(jid)
//        , state(state) {
//    }
//};
//
////    //using KeyboardKeySlice = slice<InputType::KEYBOARD_KEY>;
////    //using KeyboardCharSlice = slice<InputType::ENTERED_CHAR>;
////    //using KeyboardModedCharSlice = slice<InputType::ENTERED_CHAR_WITH_MODS>;
////    //using MouseButtonSlice = slice<InputType::MOUSE_BUTTON>;
////    //using MousePositionSlice = slice<InputType::CURSOR_POSITION>;
////    //using MouseEnterSlice = slice<InputType::CURSOR_ENTER>;
////    //using MouseScrollSlice = slice<InputType::SCROLL_MOVE>;
////    //using FileDropSlice = slice<InputType::FILE_DROP>;
////    //using JoystickConfigSlice = slice<InputType::JOYSTICK_CONFIG>;
////    template<InputType INPUT_TYPE>
////    using SliceVector = std::vector<std::pair<gtl::StdMicrosecondsD,slice<INPUT_TYPE>>>;
//
//struct KeyboardState {
//    using state_bitset = std::bitset<GLA_EVENT_KEY_COUNT()>;
//    state_bitset state; /// True if pressed, false if released.
//    state_bitset fired_state; /// True if key was triggered, false otherwise.
//    state_bitset repeated_state; /// True if repeated, false otherwise.
//    state_bitset pressed_state; /// True if pressed, false otherwise.
//    state_bitset released_state; /// True if released, false otherwise.
//    state_bitset clicked_state; /// True if pressed then released, false otherwise.
//
//    /// <method:wasFired>
//    /// Returns true if the passed key was fired this frame.
//    [[nodiscard]] bool wasFired(KeyboardKeyId id) const {
//        return fired_state[static_cast<int>(id)];
//    }
//
//    /// <method:wasPressed>
//    /// Returns true if the passed key was pressed this frame.
//    [[nodiscard]] bool wasPressed(KeyboardKeyId id) const {
//        return pressed_state[static_cast<int>(id)];
//    }
//
//    /// <method:wasPressed>
//    /// Returns true if the passed key was pressed this frame.
//    [[nodiscard]] bool wasReleased(KeyboardKeyId id) const {
//        return released_state[static_cast<int>(id)];
//    }
//
//    /// <method:wasClicked>
//    /// Returns true if the passed key was clicked this frame.
//    [[nodiscard]] bool wasClicked(KeyboardKeyId id) const {
//        return clicked_state[static_cast<int>(id)];
//    }
//
//    /// <method:wasClicked>
//    /// Returns true if the passed key was held down until repeated this frame.
//    [[nodiscard]] bool wasRepeated(KeyboardKeyId id) const {
//        return repeated_state[static_cast<int>(id)];
//    }
//
//    /// <method:isReleased>
//    /// Returns true if the final state of the passed key is released.
//    [[nodiscard]] bool isReleased(KeyboardKeyId id) const {
//        return !state[static_cast<int>(id)];
//    }
//
//    /// <method:isPressed>
//    /// Returns true if the final state of the passed key is pressed.
//    [[nodiscard]] bool isPressed(KeyboardKeyId id) const {
//        return state[static_cast<int>(id)];
//    }
//
//};
//
//struct MouseState {
//    using state_bitset = std::bitset<GLA_EVENT_BUTTON_COUNT()>;
//    double x_position{}; /// Last knows x position of the mouse.
//    double y_position{}; /// Last known y position of the mouse.
//    double x_scroll{}; /// Scroll wheel offset on x axis.
//    double y_scroll{}; /// Scroll wheel offset on y axis.
//    bool is_inside{}; /// True if mouse is inside a window.
//    state_bitset state; /// True if pressed, false if released.
//    state_bitset fired_state; /// True if key was triggered, false otherwise.
//    state_bitset repeated_state; /// True if repeated, false otherwise.
//    state_bitset pressed_state; /// True if pressed, false otherwise.
//    state_bitset released_state; /// True if released, false otherwise.
//    state_bitset clicked_state; /// True if pressed then released, false otherwise.
//
//    /// <method:wasFired>
//    /// Returns true if the passed key was fired this frame.
//    [[nodiscard]] bool wasFired(MouseKeyId id) const {
//        return fired_state[static_cast<int>(id)];
//    }
//
//    /// <method:wasPressed>
//    /// Returns true if the passed key was pressed this frame.
//    [[nodiscard]] bool wasPressed(MouseKeyId id) const {
//        return pressed_state[static_cast<int>(id)];
//    }
//
//    /// <method:wasReleased>
//    /// Returns true if the passed key was pressed this frame.
//    [[nodiscard]] bool wasReleased(MouseKeyId id) const {
//        return released_state[static_cast<int>(id)];
//    }
//
//    /// <method:wasClicked>
//    /// Returns true if the passed key was clicked this frame.
//    [[nodiscard]] bool wasClicked(MouseKeyId id) const {
//        return clicked_state[static_cast<int>(id)];
//    }
//
//    /// <method:wasClicked>
//    /// Returns true if the passed key was held down until repeated this frame.
//    [[nodiscard]] bool wasRepeated(MouseKeyId id) const {
//        return repeated_state[static_cast<int>(id)];
//    }
//
//    /// <method:isInside>
//    /// Returns true if the mouse is within the window.
//    [[nodiscard]] bool isInside(MouseKeyId id) const {
//        return is_inside;
//    }
//
//    /// <method:isReleased>
//    /// Returns true if the final state of the passed key is released.
//    [[nodiscard]] bool isReleased(MouseKeyId id) const {
//        return !state[static_cast<int>(id)];
//    }
//
//    /// <method:isPressed>
//    /// Returns true if the final state of the passed key is pressed.
//    [[nodiscard]] bool isPressed(MouseKeyId id) const {
//        return state[static_cast<int>(id)];
//    }
//
//    /// <method:lastMousePos>
//    /// Returns the last known mouse cursor position.
//    [[nodiscard]] std::pair<double, double> lastMousePosition() {
//        return std::make_pair(x_position, y_position);
//    }
//
//    /// <method:lastWheelDelta>
//    /// Returns the last scroll wheel offset.
//    [[nodiscard]] std::pair<double, double> lastWheelDelta() {
//        return std::make_pair(x_position, y_position);
//    }
//};
//
//struct ModifierState {
//    using state_bitset = std::bitset<GLA_EVENT_MODIFIER_COUNT()>;
//    state_bitset state; /// True if is activated, false if deactivated.
//
//    [[nodiscard]] bool isOn(ModifierKeyFlag mod) {
//        return state[static_cast<int>(mod)];
//    }
//};
//
//struct State {
//    KeyboardState keyboard_state;
//    MouseState mouse_state;
//    ModifierState modifier_state;
//};
//
//struct UniqueSlicePtr {
//    size_t index;
//    gtl::StdMicrosecondsD distance_from_last_slice;
//    InputType type;
//    std::unique_ptr<slice> uptr;
//
//};
//
//struct PackedBuffer {
//    gtl::Timer slice_timer_;
//    State current;
//    State previous;
//    std::vector<UniqueSlicePtr> slices_;
//    std::vector<UniqueSlicePtr*> keyboard_key_slices_;
//    std::vector<UniqueSlicePtr*> keyboard_char_slices_;
//    std::vector<UniqueSlicePtr*> keyboard_modded_char_slices_;
//    std::vector<UniqueSlicePtr*> mouse_button_slices_;
//    std::vector<UniqueSlicePtr* > mouse_position_slices_;
//    std::vector<UniqueSlicePtr*> mouse_enter_slices_;
//    std::vector<UniqueSlicePtr*> mouse_scroll_slices_;
//    std::vector<UniqueSlicePtr*> file_drop_slices_;
//    std::vector<UniqueSlicePtr*> joystick_config_slices_;
//
//    /// Keyboard
//    std::vector<UniqueSlicePtr*> keyboard_key_repeated;
//    std::vector<UniqueSlicePtr*> keyboard_key_pressed;
//    std::vector<UniqueSlicePtr*> keyboard_key_released;
//    //std::vector<KeyboardKeySlice*> keyboard_key_clicked;
//
//    //std::vector<KeyboardKeySlice*> keyboard_mod_activated;
//    //std::vector<KeyboardCharSlice*> accumulated_text;
//    //std::vector<KeyboardModedCharSlice*> modded_accumulated_text;
//
//    ///// Mouse
//    //std::vector<MouseButtonSlice*> mouse_button_repeated;
//    //std::vector<MouseButtonSlice*> mouse_button_pressed;
//    //std::vector<MouseButtonSlice*> mouse_button_released;
//    //std::vector<MouseButtonSlice*> mouse_button_clicked;
//
//    //std::vector<MousePositionSlice*> mouse_position_path;
//    //std::vector<MouseScrollSlice*> mouse_scroll_path;
//    //std::vector<MouseEnterSlice*> mouse_entered_path;
//
//    ///// Joystick
//    //std::vector<JoystickConfigSlice*> joystick_configured;
//    ///// Other
//    //std::vector<FileDropSlice*> file_paths_dropped;
//
//    constexpr void CallbackKeyboardKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
//        slices_.push_back({ slices_.size() - 1,slice_timer_.reset(),InputType::KEYBOARD_KEY,std::make_unique<slice>(
//            slice_keyboard_key(static_cast<KeyState>(action)
//                                 , static_cast<KeyboardKeyId>(key)
//                                 , static_cast<ModifierKeyFlag>(mods)
//                                 , scancode)) }
//        );
//        auto new_slice_ptr = &slices_.back();
//        keyboard_key_slices_.push_back(new_slice_ptr);
//
//        if (action == static_cast<int>(KeyState::PRESSED)) {
//            keyboard_key_pressed.push_back(new_slice_ptr);
//            current.keyboard_state.state[key] = true;
//            current.keyboard_state.fired_state[key] = true;
//            current.keyboard_state.pressed_state[key] = true;
//        }
//        else if (action == static_cast<int>(KeyState::RELEASED)) {
//            keyboard_key_released.push_back(new_slice_ptr);
//            current.keyboard_state.state[key] = false;
//            current.keyboard_state.fired_state[key] = true;
//            current.keyboard_state.released_state[key] = true;
//            if (previous.keyboard_state.pressed_state[key]) {
//                current.keyboard_state.clicked_state[key] = true;
//            }
//        }
//        else if (action == static_cast<int>(KeyState::REPEATED)) {
//            keyboard_key_repeated.push_back(new_slice_ptr);
//            current.keyboard_state.state[key] = true;
//            current.keyboard_state.fired_state[key] = true;
//            current.keyboard_state.pressed_state[key] = true;
//            current.keyboard_state.repeated_state[key] = true;
//        }
//    }
//
//    //template<InputType INPUT_TYPE>
//    //const SliceVector<INPUT_TYPE> & get() {}
//    //template<> const SliceVector<InputType::KEYBOARD_KEY>& get() { return keyboard_key_slices_; }
//    //template<> const std::vector<slice<InputType::KEYBOARD_KEY>>& get() { return keyboard_key_slices_; }
//    //template<> const std::vector<slice<InputType::KEYBOARD_KEY>>& get() { return keyboard_key_slices_; }
//    //template<> const std::vector<slice<InputType::KEYBOARD_KEY>>& get() { return keyboard_key_slices_; }
//    //template<> const std::vector<slice<InputType::KEYBOARD_KEY>>& get() { return keyboard_key_slices_; }
//    //template<> const std::vector<slice<InputType::KEYBOARD_KEY>>& get() { return keyboard_key_slices_; }
//    //template<> const std::vector<slice<InputType::KEYBOARD_KEY>>& get() { return keyboard_key_slices_; }
//    //template<> const std::vector<slice<InputType::KEYBOARD_KEY>>& get() { return keyboard_key_slices_; }
//    //template<> const std::vector<slice<InputType::KEYBOARD_KEY>>& get() { return keyboard_key_slices_; }
//
//    //auto push(auto new_slice) {
//    //    slices_.push_back(UniqueSlicePtr());
//    //    slices_.back().uptr = std::make_unique<slice>(new_slice);
//    //    slices_.back().distance_from_last_slice = slice_timer_.reset();
//    //    slices_.back().index = slices_.size()-1;
//    //    slices_.back().type = new_slice.type();
//    //    return slices_.back();
//    //}
//
//    //void clear() {
//    //    keyboard_key_slices_.clear();
//    //    keyboard_char_slices_.clear();
//    //    keyboard_modded_char_slices_.clear();
//    //    mouse_button_slices_.clear();
//    //    mouse_position_slices_.clear();
//    //    mouse_enter_slices_.clear();
//    //    mouse_scroll_slices_.clear();
//    //    file_drop_slices_.clear();
//    //    joystick_config_slices_.clear();
//    //}
//};
//
////class Buffer {
////    PackedBuffer packed_slices_;
////public:
////    void push(slice_keyboard_key slice) {
////        packed_slices_.push(slice);
////    }
//
////    //template<InputType INPUT_TYPE>
////    //std::vector<slice<INPUT_TYPE>> get() {
////    //    return packed_slices_.get<INPUT_TYPE>();
////    //}
//
////    //void clear() {
////    //    packed_slices_.clear();
////    //}
////};
//
//class PtrBuffer {
//    void read_buffer(const PackedBuffer& buffer_) {
//        for (auto& s : buffer_.slices_)
//        {
//            switch (s.type)
//            {
//            case(InputType::KEYBOARD_KEY):
//                auto* slice_ptr = dynamic_cast<slice_keyboard_key*>(s.uptr.get());
//
//                if (slice_ptr->state == KeyState::PRESSED) {
//                    keyboard_key_pressed.push_back(slice_ptr);
//                }
//                else if (slice_ptr->state == KeyState::RELEASED) {
//                    keyboard_key_released.push_back(slice_ptr);
//                }
//                else if (slice_ptr->state == KeyState::REPEATED) {
//                    keyboard_key_repeated.push_back(slice_ptr);
//                }
//            default:
//                break;
//            }
//        }
//    }
//    /// Keyboard
//    std::vector<slice_keyboard_key*> keyboard_key_repeated;
//    std::vector<slice_keyboard_key*> keyboard_key_pressed;
//    std::vector<slice_keyboard_key*> keyboard_key_released;
//    //std::vector<KeyboardKeySlice*> keyboard_key_clicked;
//
//    //std::vector<KeyboardKeySlice*> keyboard_mod_activated;
//    //std::vector<KeyboardCharSlice*> accumulated_text;
//    //std::vector<KeyboardModedCharSlice*> modded_accumulated_text;
//
//    ///// Mouse
//    //std::vector<MouseButtonSlice*> mouse_button_repeated;
//    //std::vector<MouseButtonSlice*> mouse_button_pressed;
//    //std::vector<MouseButtonSlice*> mouse_button_released;
//    //std::vector<MouseButtonSlice*> mouse_button_clicked;
//
//    //std::vector<MousePositionSlice*> mouse_position_path;
//    //std::vector<MouseScrollSlice*> mouse_scroll_path;
//    //std::vector<MouseEnterSlice*> mouse_entered_path;
//
//    ///// Joystick
//    //std::vector<JoystickConfigSlice*> joystick_configured;
//    ///// Other
//    //std::vector<FileDropSlice*> file_paths_dropped;
//
//};
//
//
//
////    class Frame {
////        const Buffer& source_buffer;
////        State state;
////        PtrBuffer buffer;
////    };
//
////    class OperatingSystemEvents {
////        Buffer& os_event_buffer;
////    public:
////        explicit OperatingSystemEvents(Buffer& os_event_buffer)
////            : os_event_buffer(os_event_buffer) {
////        }
//
////        void poll() {
////            /* Allow GLFW to poll events into the os buffer through callback functions.*/
////            glfwPollEvents(); // pushes the appropriate slice into the buffer with callbacks
////        }
//
////        void clear() {
////            /* Clear all messages from os event buffer.*/
////            os_event_buffer.clear();
////        }
//
////        // GLFW CALLBACK FUNCTIONS
////        constexpr void glfwCallbackKeyboardKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
////            os_event_buffer.push(KeyboardKeySlice(static_cast<KeyState>(action)
////                , static_cast<KeyboardKeyId>(key)
////                , static_cast<ModifierKeyFlag>(mods)
////                , scancode)
////            );
////        }
//
////        constexpr void glfwCallbackCharacterEntered(GLFWwindow* window, unsigned int codepoint) {
////            os_event_buffer.push(KeyboardCharSlice(codepoint));
////        }
//
//
////        constexpr void glfwCallbackMousePosition(GLFWwindow* window, double x_pos, double y_pos) {
////            os_event_buffer.push(MousePositionSlice(x_pos, y_pos));
////        }
//
////        constexpr void glfwCallbackMouseScrolled(GLFWwindow* window, double x_offset, double y_offset) {
////            os_event_buffer.push(MouseScrollSlice(x_offset, y_offset));
////        }
//
////        constexpr void glfwCallbackMouseEntered(GLFWwindow* window, int is_inside_window) {
////            os_event_buffer.push(MouseEnterSlice(static_cast<MouseWindowState>(is_inside_window)));
////        }
//
////        constexpr void glfwCallbackMouseButton(GLFWwindow* window, int button, int action, int mods) {
////            os_event_buffer.push(MouseButtonSlice(static_cast<KeyState>(action)
////                , static_cast<MouseKeyId>(button)
////                , static_cast<ModifierKeyFlag>(mods))
////            );
////        }
//
////        constexpr void glfwCallbackKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
////            // Action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
////            // scancode is unique for every key, regardless of whether it has a key token.
////            // query the scancode for any named key on the current platform with glfwGetKeyScancode.
////            os_event_buffer.push(KeyboardKeySlice(static_cast<KeyState>(action)
////                , static_cast<KeyboardKeyId>(key)
////                , static_cast<ModifierKeyFlag>(mods)
////                , scancode
////            )
////            );
////        }
//
////        constexpr void glfwCallbackPathDrop(GLFWwindow* window, int path_count, const char* paths[]) {
////            os_event_buffer.push(FileDropSlice(path_count, paths));
////        }
//
////        constexpr void glfwCallbackJoystickConfig(int jid, int event) {
////            os_event_buffer.push(JoystickConfigSlice(static_cast<JoystickId>(jid)
////                , static_cast<JoystickConfigState>(event))
////            );
////        }
//
////    };
////}
//struct Event {
//    virtual bool get() {
//        return true;
//    }
//};
//struct KeyEvent : Event {
//    const State& source_state;
//    KeyState state;
//    KeyboardKeyId id;
//    ModifierKeyFlag mods;
//    KeyEvent(const State& source_state,
//        KeyState state = KeyState::RELEASED,
//        KeyboardKeyId id = KeyboardKeyId::UNKNOWN,
//        ModifierKeyFlag mods = ModifierKeyFlag::NONE)
//        : source_state(source_state)
//        , state(state)
//        , id(id)
//        , mods(mods) {
//    }
//    bool get() override {
//        bool event_occured = false;
//        if (state == KeyState::PRESSED) {
//            if (source_state.keyboard_state.wasPressed(id))
//                event_occured = true;
//        }
//        else if (state == KeyState::RELEASED) {
//            if (source_state.keyboard_state.wasReleased(id))
//                event_occured = true;
//        }
//        else if (state == KeyState::REPEATED) {
//            if (source_state.keyboard_state.wasRepeated(id))
//                event_occured = true;
//        }
//
//        if (!source_state.modifier_state.state[static_cast<size_t>(mods)]) {
//            event_occured = false;
//        }
//
//        return event_occured;
//    }
//};
//
//struct EventSet {
//    template<typename ...T>
//    explicit EventSet(T...input) :events({ &input... }) {
//    }
//    std::vector<Event*> events;
//    bool get() {
//        bool retval = true;
//        for (auto e : events) {
//            if (!e->get())
//                retval = false;
//        }
//        return retval;
//    }
//};
//
//template <typename R, typename ... Types>
//constexpr std::integral_constant<unsigned, sizeof ...(Types)> getArgumentCount(R(*f)(Types ...))
//{
//    return std::integral_constant<unsigned, sizeof ...(Types)>{};
//}
//
//template <typename R, typename ... Types>
//constexpr auto getArgumentTuple(R(*f)(Types ...))
//{
//    return std::tuple<Types...>();
//}
//
//template<typename EventT, typename FuncT>
//auto onEvent(EventT&& event, FuncT&& func, decltype(getArgumentTuple(func)) args) {
//    if (event.get())
//        return std::apply(func, args);
//}
//
//template<typename EventT, typename FuncT>
//auto onEvent(EventT&& event, FuncT&& func) {
//    if (event.get())
//        return std::invoke(func);
//}




//RenderText(text_shader_program, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
//RenderText(text_shader_program, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));


// Render Imgui 
// 
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


// ------------------------------------------------------------------------
 /*   glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);*/

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //// Setup Dear ImGui context
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    //// Setup Platform/Renderer bindings
    //ImGui_ImplGlfw_InitForOpenGL(main_window.getGLFWWinPtr(), true);
    //ImGui_ImplOpenGL3_Init("#version 330");
    //// Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    // 
    //// Start the Dear ImGui frame
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplGlfw_NewFrame();
    //ImGui::NewFrame();

    //ImGui::Render();

    // build and compile our shader program
      // ------------------------------------
      // vertex shader
      //unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
      //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
      //glCompileShader(vertexShader);
      //// check for shader compile errors
      //int success;
      //char infoLog[512];
      //glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
      //if (!success)
      //{
      //    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      //    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      //}
      // fragment shader
      //unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
      //glCompileShader(fragmentShader);
      //// check for shader compile errors
      //glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
      //if (!success)
      //{
      //    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      //    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      //}
      // link shaders
      //unsigned int shaderProgram = glCreateProgram();
      //glAttachShader(shaderProgram, vertexShader);
      //glAttachShader(shaderProgram, fragmentShader);
      //glLinkProgram(shaderProgram);
      //// check for linking errors
      //glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
      //if (!success) {
      //    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      //    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      //}
      //glDeleteShader(vertexShader);
      //glDeleteShader(fragmentShader);


    //void apply_layout(Vertux* vtx, float scalex, float scaley) {
    //    vtx->transform = vtx->parent->transform;
    //    vtx->transform.scaley *= scaley;
    //    // Top Anchor = parent Translate Y by (parent scale  - Scale Y)
    //    vtx->transform.translatey = vtx->parent->transform.translatey + (vtx->parent->transform.scaley - vtx->transform.scaley);
    //}
    //
    //void apply_grid_layout(Vertux* vtx, float gridx, float gridy, int position) {
    //    vtx->transform = vtx->parent->transform;
    //    vtx->transform.scalex /= gridx;
    //    vtx->transform.scaley /= gridy;
    //    // Top Anchor = parent Translate Y by (parent scale  - Scale Y)
    //    vtx->transform.translatey = vtx->parent->transform.translatey + (vtx->parent->transform.scaley - vtx->transform.scaley);
    //    // Left Anchor
    //    vtx->transform.translatex = vtx->parent->transform.translatex + (vtx->parent->transform.scalex - vtx->transform.scalex);
    //
    //    // Top Left is position 0, or [ 0, 0 ]
    //    vtx->transform.translatex += position * (vtx->parent->transform.scalex / gridx);
    //    vtx->transform.translatey += position * (vtx->parent->transform.scaley / gridy);
    //}

    //// note that we read the matrix multiplication from right to left
    //const char* text_vertexShaderSource = "#version 330 core\n"
    //"layout (location = 0) in vec4 vertex;\n"
    //"out vec2 TexCoords;\n"
    //"uniform mat4 projection; \n"
    //"void main()\n"
    //"{\n"
    //"   gl_Position =  projection * vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    //"   TexCoords = vertex.z;\n"
    //"}\0";
    //const char* text_fragmentShaderSource = "#version 330 core\n"
    //"in vec2 TexCoords;\n"
    //"out vec4 color;\n"
    //"uniform sampler2D text;\n"
    //"uniform vec3 textColor;\n"
    //"void main()\n"
    //"{\n"
    //"   vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
    //"   color = vec4(textColor, 1.0) * sampled;\n"
    //"}\n\0";

    //
    //struct Vertux {
    //    gtl::vec2<float> origin{ 0.f,0.f };
    //    Interface transform;
    //
    //    Vertux* parent{ nullptr };
    //    std::vector<Vertux> children;
    //
    //    Vertux& add_new_child() {
    //        children.push_back(Vertux());
    //        auto& child = children.back();
    //        child.parent = this;
    //        child.transform = transform;
    //        child.origin = origin;
    //        return child;
    //    }
    //};


    //// Text stuff
    //
    //struct Character {
    //    unsigned int TextureID;  // ID handle of the glyph texture
    //    glm::ivec2   Size;       // Size of glyph
    //    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    //    unsigned int Advance;    // Offset to advance to next glyph
    //};
    //std::map<char, Character> Characters;
    //gla::VertexArrayObject* text_vaop;
    //gla::VertexBufferObject* text_vbop;
    //
    //// render line of text
    //// -------------------
    //void RenderText(gla::ShaderProgram& shader, std::string text, float x, float y, float scale, glm::vec3 color)
    //{
    //    // activate corresponding render state	
    //    shader.use();
    //    glUniform3f(glGetUniformLocation(shader.get(), "textColor"), color.x, color.y, color.z);
    //    glActiveTexture(GL_TEXTURE0);
    //    text_vaop->bind();
    //
    //    // iterate through all characters
    //    std::string::const_iterator c;
    //    for (c = text.begin(); c != text.end(); c++)
    //    {
    //        Character ch = Characters[*c];
    //
    //        float xpos = x + ch.Bearing.x * scale;
    //        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
    //
    //        float w = ch.Size.x * scale;
    //        float h = ch.Size.y * scale;
    //        // update VBO for each character
    //        float vertices[6][4] = {
    //            { xpos,     ypos + h,   0.0f, 0.0f },
    //            { xpos,     ypos,       0.0f, 1.0f },
    //            { xpos + w, ypos,       1.0f, 1.0f },
    //
    //            { xpos,     ypos + h,   0.0f, 0.0f },
    //            { xpos + w, ypos,       1.0f, 1.0f },
    //            { xpos + w, ypos + h,   1.0f, 0.0f }
    //        };
    //        // render glyph texture over quad
    //        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    //        // update content of VBO memory
    //        text_vbop->bind();
    //        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
    //
    //        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //        // render quad
    //        glDrawArrays(GL_TRIANGLES, 0, 6);
    //        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    //        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    //    }
    //    glBindVertexArray(0);
    //    glBindTexture(GL_TEXTURE_2D, 0);
    //};
        //FT_Library ft;
        //if (FT_Init_FreeType(&ft))
        //{
        //    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        //    return -1;
        //}

        //FT_Face face;
        //if (FT_New_Face(ft, "Arial.ttf", 0, &face))
        //{
        //    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        //    return -1;
        //}

        //if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        //{
        //    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        //    return -1;
        //}

        //glEnable(GL_CULL_FACE);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        ///* Build and Complie text_ Shader Program */
        //gla::VertexShader text_vert_shader;
        //text_vert_shader.source(text_vertexShaderSource);
        //text_vert_shader.compile();
        //text_vert_shader.checkCompilation();
        //gla::FragmentShader text_frag_shader;
        //text_frag_shader.source(text_fragmentShaderSource);
        //text_frag_shader.compile();
        //text_frag_shader.checkCompilation();
        //gla::ShaderProgram text_shader_program;
        //text_shader_program.attachVertexShader(text_vert_shader);
        //text_shader_program.attachFragmentShader(text_frag_shader);
        //text_shader_program.link();
        //text_shader_program.checkLink();

        //text_shader_program.use();
        //glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(temp_global_width), 0.0f, static_cast<float>(temp_global_width));
        //glUniformMatrix4fv(glGetUniformLocation(text_shader_program.get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        //FT_Set_Pixel_Sizes(face, 0, 48);

        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

        //for (unsigned char c = 0; c < 128; c++)
        //{
        //    // load character glyph 
        //    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        //    {
        //        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        //        continue;
        //    }
        //    // generate texture
        //    unsigned int texture;
        //    glGenTextures(1, &texture);
        //    glBindTexture(GL_TEXTURE_2D, texture);
        //    glTexImage2D(
        //        GL_TEXTURE_2D,
        //        0,
        //        GL_RED,
        //        face->glyph->bitmap.width,
        //        face->glyph->bitmap.rows,
        //        0,
        //        GL_RED,
        //        GL_UNSIGNED_BYTE,
        //        face->glyph->bitmap.buffer
        //    );
        //    // set texture options
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //    // now store character for later use
        //    Character character = {
        //        texture,
        //        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        //        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        //        face->glyph->advance.x
        //    };
        //    Characters.insert(std::pair<char, Character>(c, character));
        //}

        //FT_Done_Face(face);
        //FT_Done_FreeType(ft);

        // configure VAO/VBO for texture quads
    // -----------------------------------
        //    ///* Set up vertex data (and buffer(s)) and configure vertex attributes */
        //gla::VertexArrayObject text_vao;
        //gla::VertexBufferObject text_vbo;
        //text_vaop = &text_vao;
        //text_vbop = &text_vbo;
        //text_vao.bind();
        //text_vbo.bind();
        //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        //glEnableVertexAttribArray(0);
        //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        ////glBindBuffer(GL_ARRAY_BUFFER, 0);
        ////glBindVertexArray(0);
        //text_vao.unbind();
        //text_vbo.unbind();


            ////ImGui::ShowDemoWindow();
            //// Imgui interface
            //ImGui::Begin("DEBUG Interface");
            //ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
            //ImGui::BulletText("Main Canvas Transformation");
            //ImGui::DragFloat("1.Translate X", &main_canvas.transform.translatex, 0.005f);
            //ImGui::DragFloat("2.Translate Y", &main_canvas.transform.translatey, 0.005f);
            //ImGui::DragFloat("3.Translate Z", &main_canvas.transform.translatez, 0.005f);
            //ImGui::DragFloat("4.rotate X", &main_canvas.transform.rotatex, 0.005f);
            //ImGui::DragFloat("5.rotate Y", &main_canvas.transform.rotatey, 0.005f);
            //ImGui::DragFloat("6.rotate Z", &main_canvas.transform.rotatez, 0.005f);
            //ImGui::DragFloat("7.rotate angle", &main_canvas.transform.angle, 0.005f);
            //ImGui::DragFloat("8.scale X", &main_canvas.transform.scalex, 0.005f);
            //ImGui::DragFloat("9.scale Y", &main_canvas.transform.scaley, 0.005f);
            //ImGui::DragFloat("10.scale Z", &main_canvas.transform.scalez, 0.005f);
            //ImGui::BulletText("Top Bar Transformation");
            //ImGui::DragFloat("11.Translate X", &top_bar.transform.translatex, 0.005f);
            //ImGui::DragFloat("12.Translate Y", &top_bar.transform.translatey, 0.005f);
            //ImGui::DragFloat("13.Translate Z", &top_bar.transform.translatez, 0.005f);
            //ImGui::DragFloat("14.rotate X", &top_bar.transform.rotatex, 0.005f);
            //ImGui::DragFloat("15.rotate Y", &top_bar.transform.rotatey, 0.005f);
            //ImGui::DragFloat("16.rotate Z", &top_bar.transform.rotatez, 0.005f);
            //ImGui::DragFloat("17.rotate angle", &top_bar.transform.angle, 0.005f);
            //ImGui::DragFloat("18.scale X", &top_bar.transform.scalex, 0.005f);
            //ImGui::DragFloat("19.scale Y", &top_bar.transform.scaley, 0.005f);
            //ImGui::DragFloat("20.scale Z", &top_bar.transform.scalez, 0.005f);









        // set up vertex data (and buffer(s)) and configure vertex attributes
         //------------------------------------------------------------------

        //unsigned int /*VBO*//*, VAO*//*,*/ EBO;
        ////glGenVertexArrays(1, &VAO);
        ////glGenBuffers(1, &VBO);
        //glGenBuffers(1, &EBO);
        //// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        ////glBindVertexArray(vao.get());

        ////glBindBuffer(GL_ARRAY_BUFFER, vbo.get());
        ////glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        //glEnableVertexAttribArray(0);

        //// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        //// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        ////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        //// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        //// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        //glBindVertexArray(0);


        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

        //apply_layout(&top_bar, 1, 0.2f);
        //    // create transformations
        //tform.identity(); // make sure to initialize matrix to identity matrix first
        //tform.translate(top_bar.transform.translatex, top_bar.transform.translatey, top_bar.transform.translatez);
        //tform.scale(top_bar.transform.scalex, top_bar.transform.scaley, top_bar.transform.scalez);
        //tform.rotate(top_bar.transform.angle, top_bar.transform.rotatex, top_bar.transform.rotatey, top_bar.transform.rotatez);
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, tform.value_ptr());

        //// draw our second triangle
        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        ////glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------

        // Controller stores id,search action.
        // Controller = EventSet + Target Methods
        // State = Did a click happen ? Yes.a
        // BufferPointer = When and where in the buffer did it happen ? Give me the slices where a click started and ended.
        //
        // Event Set <Press,Release> = Click;
        // 
        // onEvent(Press[MouseR],&draw_select_box(Press[MouseR].position, mouse_current_position),Release[MouseR],&make_selection(Press[MouseR].position,Release[MouseR].position))
        //gla::onEvent(gla::KeyEvent(dummy_event_state, gla::KeyState::PRESSED, gla::KeyboardKeyId::A), &test);
        //gla::onEvent(gla::EventSet( gla::KeyEvent(dummy_event_state, gla::KeyState::PRESSED, gla::KeyboardKeyId::A),
        //                            gla::KeyEvent(dummy_event_state, gla::KeyState::PRESSED, gla::KeyboardKeyId::B)), 
        //    &test);


//void SetupGfxPipeline_Primitive(gla::ShaderProgram& shader_program, unsigned int& texture1, unsigned int& texture2,gla::VertexArrayObject& vao,gla::VertexBufferObject& vbo, gla::ElementBufferObject& ebo) {
//    // Set up primitive graphics pipeline
//
///* Build and Complie Shader Program */
//    shader_program.makeFromFile("primitive.vert", "primitive.frag");
//    shader_program.setUniformInt("ourTexture", 0);// THIS FUNCTION TELLS THE SHADER PROGRAM THAT OUR TEXTURE CORRESPONDS TO glActiveTexture(GL_TEXTURE0);
//        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//
//    //// load and create a texture 
//    //// -------------------------
//    //// texture 1
//    //// ---------
//    //glGenTextures(1, &texture1);
//    //glBindTexture(GL_TEXTURE_2D, texture1);
//    //// set the texture wrapping parameters
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    //// set texture filtering parameters
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //// load image, create texture and generate mipmaps
//    //int width, height, nrChannels;
//    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//    //// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//    //unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//    //if (data)
//    //{
//    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//    //    glGenerateMipmap(GL_TEXTURE_2D);
//    //}
//    //else
//    //{
//    //    std::cout << "Failed to load texture" << std::endl;
//    //}
//    //stbi_image_free(data);
//    //glBindTexture(GL_TEXTURE_2D, 0);
//    //// texture 2
//    //// ---------
//    //glGenTextures(1, &texture2);
//    //glBindTexture(GL_TEXTURE_2D, texture2);
//    //// set the texture wrapping parameters
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    //// set texture filtering parameters
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //// load image, create texture and generate mipmaps
//    //data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
//    //if (data)
//    //{
//    //    // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//    //    glGenerateMipmap(GL_TEXTURE_2D);
//    //}
//    //else
//    //{
//    //    std::cout << "Failed to load texture" << std::endl;
//    //}
//    //stbi_image_free(data);
//    //glBindTexture(GL_TEXTURE_2D, 0);
//
//    ///* Set up vertex data (and buffer(s)) and configure vertex attributes */
//
//    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//    vao.bind();
//    vbo.bind();
//    vbo.setData(debug_interface.cube_vertices, sizeof(debug_interface.cube_vertices), GL_STATIC_DRAW);
//    //ebo.bind();
//    //ebo.setData(indices, sizeof(indices), GL_STATIC_DRAW);
//    // Set up attribute pointers
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    // color attribute 1 
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    // texture coord attribute 2
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//    vbo.unbind();
//    vao.unbind();
//    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//     //                You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//     //VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//    //note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex 
//     //attribute's bound vertex buffer object so afterwards we can safely unbind
//
//};
//int SetupGfxPipeline_Text(gla::ShaderProgram& text_shader,gla::VertexArrayObject& tvao,gla::VertexBufferObject& tvbo) {
//
//    //setup text rendering pipeline
////     // OpenGL state
//// ------------
///*  glEnable(GL_CULL_FACE);
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
//  // compile and setup the shader
//  // ----------------------------
//
//    text_shader.makeFromFile("text.vert", "text.frag");
//    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(debug_interface.temp_global_width), 0.0f, static_cast<float>(debug_interface.temp_global_height));
//    text_shader.use();
//    glUniformMatrix4fv(glGetUniformLocation(text_shader.get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//    // FreeType
//    // --------
//    FT_Library ft;
//    // All functions return a value different than 0 whenever an error occurred
//    if (FT_Init_FreeType(&ft))
//    {
//        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//        return -1;
//    }
//
//    // find path to font
//    std::string font_name = "Arial.ttf";
//    if (font_name.empty())
//    {
//        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
//        return -1;
//    }
//
//    // load font as face
//    FT_Face face;
//    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
//        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//        return -1;
//    }
//    else {
//        // set size to load glyphs as
//        FT_Set_Pixel_Sizes(face, 0, 48);
//
//        // disable byte-alignment restriction
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//        // load first 128 characters of ASCII set
//        for (unsigned char c = 0; c < 128; c++)
//        {
//            // Load character glyph 
//            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//            {
//                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//                continue;
//            }
//            // generate texture
//            unsigned int texture;
//            glGenTextures(1, &texture);
//            glBindTexture(GL_TEXTURE_2D, texture);
//            glTexImage2D(
//                GL_TEXTURE_2D,
//                0,
//                GL_RED,
//                face->glyph->bitmap.width,
//                face->glyph->bitmap.rows,
//                0,
//                GL_RED,
//                GL_UNSIGNED_BYTE,
//                face->glyph->bitmap.buffer
//            );
//            // set texture options
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//            // now store character for later use
//            Character character = {
//                texture,
//                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//                static_cast<unsigned int>(face->glyph->advance.x)
//            };
//            Characters.insert(std::pair<char, Character>(c, character));
//        }
//        glBindTexture(GL_TEXTURE_2D, 0);
//    }
//    // destroy FreeType once we're finished
//    FT_Done_Face(face);
//    FT_Done_FreeType(ft);
//    // configure VAO/VBO for texture quads
//    // -----------------------------------
//
//    tvao.bind();
//    tvbo.bind();
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
//    tvao.unbind();
//    tvbo.unbind();
//    return 0;
//};
//void RenderText(gla::VertexBufferObject& tvbo,gla::VertexArrayObject& tvao,gla::ShaderProgram & text_shader, std::string text, float x, float y, float scale, glm::vec3 color)
//{
//    // render line of text
//// -------------------
//// OpenGL state
//// ------------
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    // activate corresponding render state	
//    text_shader.use();
//    glUniform3f(glGetUniformLocation(text_shader.get(), "textColor"), color.x, color.y, color.z);
//    glActiveTexture(GL_TEXTURE0);
//    tvao.bind();
//
//    // iterate through all characters
//    std::string::const_iterator c;
//    for (c = text.begin(); c != text.end(); c++)
//    {
//        Character ch = Characters[*c];
//
//        float xpos = x + ch.Bearing.x * scale;
//        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//        float w = ch.Size.x * scale;
//        float h = ch.Size.y * scale;
//        // update VBO for each character
//        float vertices[6][4] = {
//            { xpos,     ypos + h,   0.0f, 0.0f },
//            { xpos,     ypos,       0.0f, 1.0f },
//            { xpos + w, ypos,       1.0f, 1.0f },
//
//            { xpos,     ypos + h,   0.0f, 0.0f },
//            { xpos + w, ypos,       1.0f, 1.0f },
//            { xpos + w, ypos + h,   1.0f, 0.0f }
//        };
//        // render glyph texture over quad
//        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//        // update content of VBO memory
//        tvbo.bind();
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
//        tvbo.unbind();
//        // render quad
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
//    }
//    tvao.unbind();
//    glBindTexture(GL_TEXTURE_2D, 0);
//    // OpenGL state
//    // ------------
//    glDisable(GL_CULL_FACE);
//    glDisable(GL_BLEND);
//};
//void RenderPrimitives(gla::VertexArrayObject& vao, gla::ShaderProgram& shader_program,gla::gl_uint texture1, gla::gl_uint texture2) {
//    glEnable(GL_DEPTH_TEST);         // Enable depth test
//    glDepthFunc(GL_LESS);        // Accept fragment if it closer to the camera than the former one
//
//    // bind textures on corresponding texture units
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//
//    // create transformations
//    shader_program.use();
//    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 view = glm::mat4(1.0f);
//    glm::mat4 projection = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    view = glm::lookAt(debug_interface.cameraPos, debug_interface.cameraPos + debug_interface.cameraFront, debug_interface.cameraUp);
//    projection = glm::perspective(glm::radians(debug_interface.fov), (float)debug_interface.temp_global_width / (float)debug_interface.temp_global_height, 0.1f, 100.0f);
//    // retrieve the matrix uniform locations
//    auto modelLoc = shader_program.getUniformLoc("model");
//    unsigned int viewLoc = shader_program.getUniformLoc("view");
//    unsigned int projectionLoc = shader_program.getUniformLoc("projection");
//    // get matrix's uniform location and set matrix
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//
//
//    vao.bind();// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//    for (unsigned int i = 0; i < 10; i++)
//    {
//        if (i % 2) {
//            glBindTexture(GL_TEXTURE_2D, texture1);
//        }
//        else {
//            glBindTexture(GL_TEXTURE_2D, texture2);
//        }
//        // calculate the model matrix for each object and pass it to shader before drawing
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, debug_interface.cubePositions[i]);
//        float angle = 20.0f * i;
//        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//        glDrawArrays(GL_TRIANGLES, 0, 80);
//    }
//    glDisable(GL_DEPTH_TEST);         // Enable depth test
//
//};


///// Holds all state information relevant to a character as loaded using FreeType
//struct Character {
//    unsigned int TextureID; // ID handle of the glyph texture
//    glm::ivec2   Size;      // Size of glyph
//    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
//    unsigned int Advance;   // Horizontal offset to advance to next glyph
//};
//std::map<GLchar, Character> Characters;

/*
* Geometry of the vertux
*
*   #0 (-1.0,1.0) +--------------+  (1.0,1.0)  #3
*               |              |
*               |              |
*               |      .(0,0)  |
*               |              |
*               |              |
*   #1(-1.0,-1.0) +--------------+  (1.0,-1.0) #2
*/
//struct FrameMap {
//    gtl::vec2<float> image_size{ 0.f,0.f };
//    struct Frame {
//        gtl::vec2<float> frame_pos{ 0,115 };
//        gtl::vec2<float> frame_size{ 150,250 };
//    };
//    std::vector<Frame> frames;

//    std::array<gtl::vec2<float>, 4> get_gl_texture_coords(int framei) {
//        auto this_frame = frames.at(framei);
//        return {
//            {{(this_frame.frame_size.x + this_frame.frame_pos.x) / image_size.x,
//            ((this_frame.frame_pos.y + this_frame.frame_size.y) / image_size.y)},

//            {(this_frame.frame_size.x + this_frame.frame_pos.x) / image_size.x,
//           ((this_frame.frame_pos.y) / image_size.x)},

//           {this_frame.frame_pos.x / image_size.x,
//           ((this_frame.frame_pos.y) / image_size.y)},

//           {this_frame.frame_pos.x / image_size.x,
//           ((this_frame.frame_pos.y + this_frame.frame_size.y) / image_size.y)},
//        } };
//    }
//};


//
//struct RGBA {
//    char r, g, b, a;
//};
//
//struct Point {
//    int x, y;
//};
//
//struct BoundingBox {
//    int x, y, width, height;
//};
//
//void findContours(const std::vector<RGBA>& binaryImage, int width, int height, std::vector<std::vector<Point>>& contours) {
//    std::vector<bool> visited(width * height, false);
//
//    for (int i = 0; i < height; ++i) {
//        for (int j = 0; j < width; ++j) {
//            if (binaryImage[i * width + j].r == 255 && !visited[i * width + j]) {
//                contours.push_back({});
//                Point current = { j, i };
//
//                // Perform contour tracing
//                do {
//                    visited[current.y * width + current.x] = true;
//                    contours.back().push_back(current);
//
//                    // Check 8-connected neighbors
//                    const int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
//                    const int dy[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
//
//                    bool found = false;
//                    for (int k = 0; k < 8; ++k) {
//                        int nx = current.x + dx[k];
//                        int ny = current.y + dy[k];
//
//                        if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
//                            binaryImage[ny * width + nx].r == 255 && !visited[ny * width + nx]) {
//                            current = { nx, ny };
//                            found = true;
//                            break;
//                        }
//                    }
//
//                    if (!found) {
//                        break;
//                    }
//
//                } while (current.x != j || current.y != i);
//            }
//        }
//    }
//}
//
//BoundingBox getBoundingBox(const std::vector<Point>& contour) {
//    BoundingBox boundingBox = { std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), 0, 0 };
//
//    for (const auto& point : contour) {
//        boundingBox.x = std::min(boundingBox.x, point.x);
//        boundingBox.y = std::min(boundingBox.y, point.y);
//        boundingBox.width = std::max(boundingBox.width, point.x - boundingBox.x);
//        boundingBox.height = std::max(boundingBox.height, point.y - boundingBox.y);
//    }
//
//    return boundingBox;
//}
//
//RGBA grayscale(RGBA rgba) {
//    // Calculate grayscale intensity using the luminance formula: 0.299*R + 0.587*G + 0.114*B
//    char grayscale = static_cast<char>(0.299 * rgba.r + 0.587 * rgba.g + 0.114 * rgba.b);
//
//    // Set the same value for R, G, and B to make it grayscale
//    rgba.r = rgba.g = rgba.b = grayscale;
//
//    return rgba;
//};
//
//char otsuThreshold(const std::vector<RGBA>& grayscaleImage, int width, int height) {
//    // Compute histogram
//    std::vector<int> histogram(256, 0);
//    for (int i = 0; i < width * height; ++i) {
//        ++histogram[static_cast<unsigned char>(grayscaleImage[i].r)];
//    }
//
//    // Total number of pixels
//    int totalPixels = width * height;
//
//    // Compute probabilities
//    std::vector<double> probabilities(256, 0.0);
//    for (int i = 0; i < 256; ++i) {
//        probabilities[i] = static_cast<double>(histogram[i]) / totalPixels;
//    }
//
//    // Compute cumulative probabilities
//    std::vector<double> cumulativeProbabilities(256, 0.0);
//    cumulativeProbabilities[0] = probabilities[0];
//    for (int i = 1; i < 256; ++i) {
//        cumulativeProbabilities[i] = cumulativeProbabilities[i - 1] + probabilities[i];
//    }
//
//    // Compute means
//    std::vector<double> means(256, 0.0);
//    for (int i = 0; i < 256; ++i) {
//        means[i] = i * probabilities[i];
//    }
//
//    // Compute cumulative means
//    std::vector<double> cumulativeMeans(256, 0.0);
//    cumulativeMeans[0] = means[0];
//    for (int i = 1; i < 256; ++i) {
//        cumulativeMeans[i] = cumulativeMeans[i - 1] + means[i];
//    }
//
//    // Compute between-class variance
//    std::vector<double> betweenClassVariances(256, 0.0);
//    for (int i = 0; i < 256; ++i) {
//        double term1 = cumulativeProbabilities[i] * (1.0 - cumulativeProbabilities[i]);
//        double term2 = cumulativeMeans[i] / cumulativeProbabilities[i] - cumulativeMeans[i];
//        betweenClassVariances[i] = term1 * term2 * term2;
//    }
//
//    // Find the optimal threshold (maximum between-class variance)
//    int optimalThreshold = 0;
//    double maxBetweenClassVariance = betweenClassVariances[0];
//    for (int i = 1; i < 256; ++i) {
//        if (betweenClassVariances[i] > maxBetweenClassVariance) {
//            maxBetweenClassVariance = betweenClassVariances[i];
//            optimalThreshold = i;
//        }
//    }
//
//    return static_cast<char>(optimalThreshold);
//}
//
//void convertToBinary(const std::vector<RGBA>& grayscaleImage, int width, int height, char threshold, std::vector<RGBA>& binaryImage) {
//    binaryImage.resize(width * height);
//
//    for (int i = 0; i < width * height; ++i) {
//        // Apply thresholding
//        binaryImage[i].r = (grayscaleImage[i].r > threshold) ? 255 : 0;
//        binaryImage[i].g = binaryImage[i].b = binaryImage[i].r;
//        binaryImage[i].a = grayscaleImage[i].a;
//    }
//}
//
//void dilate(std::vector<RGBA>& binaryImage, int width, int height) {
//    std::vector<RGBA> result(binaryImage.begin(), binaryImage.end());
//
//    // Dilation operation
//    for (int i = 1; i < height - 1; ++i) {
//        for (int j = 1; j < width - 1; ++j) {
//            if (binaryImage[i * width + j].r == 255 ||
//                binaryImage[(i - 1) * width + j].r == 255 ||
//                binaryImage[(i + 1) * width + j].r == 255 ||
//                binaryImage[i * width + (j - 1)].r == 255 ||
//                binaryImage[i * width + (j + 1)].r == 255) {
//                result[i * width + j].r = 255;
//                result[i * width + j].g = result[i * width + j].b = result[i * width + j].r;
//            }
//        }
//    }
//
//    binaryImage = result;
//}
//
//void erode(std::vector<RGBA>& binaryImage, int width, int height) {
//    std::vector<RGBA> result(binaryImage.begin(), binaryImage.end());
//
//    // Erosion operation
//    for (int i = 1; i < height - 1; ++i) {
//        for (int j = 1; j < width - 1; ++j) {
//            if (binaryImage[i * width + j].r == 0 ||
//                binaryImage[(i - 1) * width + j].r == 0 ||
//                binaryImage[(i + 1) * width + j].r == 0 ||
//                binaryImage[i * width + (j - 1)].r == 0 ||
//                binaryImage[i * width + (j + 1)].r == 0) {
//                result[i * width + j].r = 0;
//                result[i * width + j].g = result[i * width + j].b = result[i * width + j].r;
//            }
//        }
//    }
//
//    binaryImage = result;
//}
//
//void performClosing(std::vector<RGBA>& binaryImage, int width, int height, int dilationSize, int erosionSize) {
//    // Perform closing (Dilation followed by Erosion)
//    for (int i = 0; i < dilationSize; ++i) {
//        dilate(binaryImage, width, height);
//    }
//
//    for (int i = 0; i < erosionSize; ++i) {
//        erode(binaryImage, width, height);
//    }
//}
//
//std::vector<BoundingBox> processImage(const std::vector<RGBA>& image, int width, int height) {
//    // Step 1: Convert image to grayscale
//    std::vector<RGBA> grayscaleImage(image.size());
//    for (size_t i = 0; i < image.size(); ++i) {
//        grayscaleImage[i] = grayscale(image[i]);
//    }
//
//    // Step 2: Otsu's threshold to obtain binary image
//    char threshold = otsuThreshold(grayscaleImage, width, height);
//
//    std::vector<RGBA> binaryImage;
//    convertToBinary(grayscaleImage, width, height, threshold, binaryImage);
//
//    // Step 3: Perform morphological transformations to smooth image
//    int dilationSize = 1;
//    int erosionSize = 1;
//    performClosing(binaryImage, width, height, dilationSize, erosionSize);
//
//    // Step 4: Find contours
//    std::vector<std::vector<Point>> contours;
//    findContours(binaryImage, width, height, contours);
//
//    // Step 5: Iterate through contours to get bounding rectangles
//    std::vector<BoundingBox> boundingBoxes;
//    for (const auto& contour : contours) {
//        BoundingBox boundingBox = getBoundingBox(contour);
//        boundingBoxes.push_back(boundingBox);
//    }
//
//    return boundingBoxes;
//}
//
//class ResourceManager {
//    struct Resource {
//        std::string name;
//        std::string ext;
//        std::string path;
//
//    };
//
//    // { {"name", "ext","path"}, "tag"}
//    std::map<Resource,std::string> resources = {
//    {{"","",""},""},
//    {{"","",""},""}
//    };
//
//    void load_file_folder(const std::string& path, const std::string& tag, const std::string& extension) {
//        for (const auto& entry : std::filesystem::directory_iterator(path)) { // Iterate over directory
//            int index = 0;
//            if (std::filesystem::is_regular_file(entry)) { // For each regular file
//                if (entry.path().extension().string() == extension) // If file has the requested extension load it
//                { // Add index number to the tag name
//                    resources.insert(
//                        { {entry.path().filename().string(),entry.path().extension().string(),entry.path().string()},tag + std::to_string(index)});
//                    // Increment index
//                    index++;
//                }
//                // else do nothing
//            }
//        }
//    }
//
//    void load_file(const std::string& fileName, const std::string& tag) {
//        if (std::filesystem::exists(fileName)) {
//            auto entry = std::filesystem::path(fileName);
//            resources.insert(
//                { {entry.filename().string(),entry.extension().string(),entry.string()},tag });
//        }
//        else {
//            std::cout << "File not found: " << fileName << std::endl;
//        }
//    }
//};

//
//class Sprite
//{
//    struct Frame {
//        gtl::vec2<float> pos{ 0.f,0.f };
//        gtl::vec2<float> size{ 0.f,0.f };
//    };
//
//private:
//    std::vector<std::vector<size_t>> animations_; // A list animations
//    std::vector<Frame> frames_; // Pos and size of frame on the texture map
//    gtl::vec2<float> map_size_{ 0.f,0.f };
//    size_t active_frame_;
//    size_t active_animation_;
//    size_t init_frame_ = 0; // Initial frame of active animation, loop restarts from this frame, 0(first frame) by default
//    // Returns the texture co-ordinates to be used by OpenGl to render the sub texture.
//    constexpr std::array<gtl::Vec2f, 4> get_frame_uv(const Frame& frame) {
//        return {
//            // Top Right of Texture Bounds
//            gtl::Vec2f{(frame.size.x + frame.pos.x) / map_size_.x,(frame.pos.y + frame.size.y) / map_size_.y} 
//            // Bottom Right of Texture Bounds
//            ,gtl::Vec2f{(frame.size.x + frame.pos.x) / map_size_.x,frame.pos.y / map_size_.x} 
//            // Bottom Left of Texture Bounds
//            ,gtl::Vec2f{frame.pos.x / map_size_.x,frame.pos.y / map_size_.y} 
//            // Top Left of Texture Bounds
//            ,gtl::Vec2f{frame.pos.x / map_size_.x,(frame.pos.y + frame.size.y) / map_size_.y} }; 
//    }
//    constexpr std::array<float, 8> get_frame_uv_raw(const Frame& frame) {
//        return {
//            // Top Right of Texture Bounds
//            (frame.size.x + frame.pos.x) / map_size_.x,
//            (frame.pos.y + frame.size.y) / map_size_.y,
//            // Bottom Right of Texture Bounds
//            (frame.size.x + frame.pos.x) / map_size_.x,
//            frame.pos.y / map_size_.x,
//            // Bottom Left of Texture Bounds
//            frame.pos.x / map_size_.x,
//            frame.pos.y / map_size_.y,
//            // Top Left of Texture Bounds
//            frame.pos.x / map_size_.x,
//            (frame.pos.y + frame.size.y) / map_size_.y};
//    }
//    constexpr gtl::vec2<float> get_aspect_ratio(const Frame & frame) {
//        return frame.size.normalized(); // Get the unit vector of the sprite size
//    }
//public:
//    void addFrame(gtl::vec2<float> pos, gtl::vec2<float> size) { frames_.push_back({ pos,size }); }
//    void addAnimation(std::vector<size_t> frame_indices) { animations_.push_back({ frame_indices }); }
//    void setMapSize(gtl::Vec2f size) { map_size_ = size; };
//    void setActiveAnimation(size_t anim_idx, size_t init_frame) {
//        active_frame_ = init_frame;
//        active_animation_ = anim_idx;
//    };
//    void setActiveFrame(size_t active_frame) {
//        active_frame_ = active_frame;
//    };
//    std::array<gtl::Vec2f, 4> getActiveUV(){ return get_frame_uv(frames_.at(active_frame_)); }
//    std::array<float, 8>  getActiveUVRaw() { return get_frame_uv_raw(frames_.at(active_frame_)); };
//    constexpr gtl::vec2<float> getActiveAspect() {
//        return frames_.at(active_frame_).size.normalized(); // Get the unit vector of the sprite size
//    }
//    void NextFrame() {
//        if (active_frame_ >= animations_.at(active_animation_).size()) {
//            active_frame_ = init_frame_; // Reset back to init frame after last frame
//        }
//        else {
//            active_frame_++; // Active frame is the next one
//        }
//    };
//};
