#pragma once
#include <iostream>
#include <string_view>
#include <string>
#include <map>
#include <array>
#include <iostream>
#include <filesystem>
#include <string>

#include "external.hpp" // GL,GLM,GLEW,GLFW,IMGUI,FREETYPE
#include "timer.hpp"
#include "gla.hpp"
#include "gla_globject.hpp"
#include "caf.hpp"

//<summary>
//GLFW Callback Functions
//</summary>/*
//This modification uses regular member functions instead of lambdas in the CallbackManager class, 
//and it also employs static dispatcher functions for GLFW callbacks. 
//The dispatcher functions retrieve the CallbackManager instance from the window user pointer 
//and delegate the call to the appropriate member function.
//
//*/
//gla::slice_buffer default_event_buffer;
//
//    namespace GLFWCallbacks {
//        static void keyCallbackDispatcher(GLFWwindow* w, int key, int scancode, int action, int mods) {
//            default_event_buffer.push(gla::Slice_keyboard_key(static_cast<gla::KeyState>(action),
//                 static_cast<gla::KeyboardKeyId>(key),
//                 static_cast<gla::ModifierKeyFlag>(mods),
//                 scancode));
//        }
//
//        static void characterEnteredCallbackDispatcher(GLFWwindow* w, unsigned int codepoint) {
//            default_event_buffer.push(gla::SliceENTERED_CHAR(codepoint));
//        }
//
//        static void mousePositionCallbackDispatcher(GLFWwindow* w, double x_pos, double y_pos) {
//            default_event_buffer.push(gla::Slice_CURSOR_POSITION(x_pos, y_pos));
//        }
//
//        static void mouseScrolledCallbackDispatcher(GLFWwindow* w, double x_offset, double y_offset) {
//            default_event_buffer.push(gla::SliceSCROLL_MOVE(x_offset, y_offset));
//        }
//
//        static void mouseEnteredCallbackDispatcher(GLFWwindow* w, int is_inside_window) {
//            default_event_buffer.push(gla::Slice_CURSOR_ENTER(static_cast<gla::MouseWindowState>(is_inside_window)));
//        }
//
//        static void mouseButtonCallbackDispatcher(GLFWwindow* w, int button, int action, int mods) {
//            default_event_buffer.push(gla::Slice_MOUSE_BUTTON(static_cast<gla::KeyState>(action),
//                static_cast<gla::MouseKeyId>(button),
//                static_cast<gla::ModifierKeyFlag>(mods)));
//        }
//
//        static void pathDropCallbackDispatcher(GLFWwindow* w, int path_count, const char* paths[]) {
//            default_event_buffer.push(gla::SliceFILE_DROP(path_count, paths));
//        }
//
//        static void joystickConfigCallbackDispatcher(int jid, int event) {
//            default_event_buffer.push(gla::SliceJOYSTICK_CONFIG(static_cast<gla::JoystickId>(jid),
//                                static_cast<gla::JoystickConfigState>(event)));
//        }
//
//        static void setCallbacks(GLFWwindow* window_) {
//
//        glfwSetKeyCallback(window_, &GLFWCallbacks::keyCallbackDispatcher);
//        glfwSetCharCallback(window_, &GLFWCallbacks::characterEnteredCallbackDispatcher);
//        glfwSetCursorPosCallback(window_, &GLFWCallbacks::mousePositionCallbackDispatcher);
//        glfwSetScrollCallback(window_, &GLFWCallbacks::mouseScrolledCallbackDispatcher);
//        glfwSetCursorEnterCallback(window_, &GLFWCallbacks::mouseEnteredCallbackDispatcher);
//        glfwSetMouseButtonCallback(window_, &GLFWCallbacks::mouseButtonCallbackDispatcher);
//        glfwSetDropCallback(window_, &GLFWCallbacks::pathDropCallbackDispatcher);
//        glfwSetJoystickCallback(&GLFWCallbacks::joystickConfigCallbackDispatcher);
//    };
//};

// CAF Components
// 1. Debug Logger
caf::logger debug_log;

// 2. Resource Manager
caf::resource_manager resources;

// 3. Event System
//gla::slice_buffer event_buffer;
//gla::Frame event_frame{event_buffer};
//gla::Events events{event_frame};

struct system_vertux {
    gla::ShaderProgram shader;
    gla::VertexArrayObject vao;
    gla::VertexBufferObject vbo;
    gla::ElementBufferObject ebo;
    gla::Texture texture1;

    glm::mat4 projection;
    gtl::vec2<float> canvas_size = { 1000,1000 };

    float vertux_vertices[20] = {
        // Position  //ZOrder  // Texture Co-Ords
         0.5f,  0.5f, 0.0f,     1.f,  1.f,  // top right 
         0.5f, -0.5f, 0.0f,     1.f, 0.f,  // bottom right
        -0.5f, -0.5f, 0.0f,    0.f, 0.f,  // bottom left
        -0.5f,  0.5f, 0.0f,    0.f,  1.f,  // top left 
    };

    gtl::vec2<float*> texture_indices[4] = {
        {&vertux_vertices[3],&vertux_vertices[4]},// top right 
        {&vertux_vertices[8],&vertux_vertices[9]},// bottom right
        {&vertux_vertices[13],&vertux_vertices[14]},// bottom left
        {&vertux_vertices[18], &vertux_vertices[19]},// top left 
    };

    unsigned int vertux_indices[6] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    void SetupGfxPipeline() {
        // compile and setup the shader
        shader.makeFromFile("vertux.vert", "vertux.frag");

        // Load textures
        texture1.load("resources/images/side_adventurer/adventurer-v1.5-Sheet.png", GL_RGBA);


        // Update Projection
        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, canvas_size.x, canvas_size.y, 0.0f, -1.0f, 1.0f); ;
        glUniformMatrix4fv(glGetUniformLocation(shader.get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        ///* Set up vertex data (and buffer(s)) and configure vertex attributes */
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        vao.bind();
        vbo.bind();
        vbo.setData(vertux_vertices, sizeof(vertux_vertices), GL_STATIC_DRAW);
        ebo.bind();
        ebo.setData(vertux_indices, sizeof(vertux_indices), GL_STATIC_DRAW);
        // Set up attribute pointers
        // Attribute 1: vec3<float> : x-pos, y-pos, z-order | stridde 3
        // Attrubute 2: vec2<float> : x-tex-pos, y-tex-pos | stride 2
        // Total Stride: 5
        

        // Attribute 0: vert_pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // Attribute 1: vert_tex_pos
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        ebo.unbind();
        vbo.unbind();
        vao.unbind();
    };

    void Draw(glm::vec3 color
        , glm::vec2 position
        , glm::vec2 size
        , float rotate
        , gtl::vec2<float> frame_pos
        , gtl::vec2<float> frame_size) {
        glEnable(GL_DEPTH_TEST);         // Enable depth test
        glDepthFunc(GL_LESS);        // Accept fragment if it closer to the camera than the former one

        // Set Active Texture
        glActiveTexture(GL_TEXTURE0);
        texture1.bind();
        // Position of first rollo frame: 0,115
        // Size of first Rollo Frame: 150,250
        gtl::vec2<float> image_size{ texture1.size.x,texture1.size.y };

        // //Convert to texture co-ords
        //frame_pos = {frame_pos.x / image_size.x, 1-(frame_pos.y / image_size.y)};
        //frame_size = {frame_size.x / image_size.x, 1-(frame_size.y / image_size.y) };

        // Offset texture coordinates
        (*texture_indices[0].x) = (frame_pos.x + frame_size.x) / image_size.x;
        (*texture_indices[0].y) = (frame_pos.y + frame_size.y) / image_size.y;

        (*texture_indices[1].x) = (frame_pos.x + frame_size.x) / image_size.x;
        (*texture_indices[1].y) = frame_pos.y / image_size.y;

        (*texture_indices[2].x) = frame_pos.x / image_size.x;
        (*texture_indices[2].y) = frame_pos.y / image_size.y;

        (*texture_indices[3].x) = frame_pos.x / image_size.x;
        (*texture_indices[3].y) = (frame_pos.y + frame_size.y) / image_size.y;

        // create transformations
        shader.use();
        glm::mat4 model = glm::mat4(1.0f);

        //// Scale Vertices to Match Aspect Ratio of Frame
        //glm::vec2 new_size = size * glm::vec2(frame_size.x / frame_size.y, 1.0f);
        //model = glm::scale(model, glm::vec3(frame_size.x / frame_size.y, 1.0f, 1.0f));

        model = glm::translate(model, glm::vec3(size/2.f, 0.0f)); // Offset Position by half the quad size on x and y axis (0,0) is top left corner

        model = glm::translate(model, glm::vec3(position, 0.0f)); // Do Translations

        //model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
        //model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

        model = glm::scale(model, glm::vec3(size, 1.0f));

        glUniformMatrix4fv(glGetUniformLocation(shader.get(), "model"),1,0, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(shader.get(), "frag_base_color"), color.x, color.y, color.z);
        vao.bind();// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized 
        vbo.bind();
        vbo.setData(vertux_vertices, sizeof(vertux_vertices), GL_STATIC_DRAW); // Update the vertex data each draw call for the texture-co-ords
        vbo.unbind();
        ebo.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        vao.unbind();
        texture1.unbind();
        glDisable(GL_DEPTH_TEST);         // Enable depth test 
    };
};
struct system_font {

    gla::ShaderProgram text_shader;
    gla::VertexArrayObject tvao;
    gla::VertexBufferObject tvbo;
    gtl::vec2<float> window_size = {1000,1000};

    /// Holds all state information relevant to a character as loaded using FreeType
    struct Character {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2   Size;      // Size of glyph
        glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };
    std::map<GLchar, Character> characters_;

    int SetupGfxPipeline_Text() {

        //setup text rendering pipeline
    //     // OpenGL state
    // ------------
    /*  glEnable(GL_CULL_FACE);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
      // compile and setup the shader
      // ----------------------------

        text_shader.makeFromFile("text.vert", "text.frag");
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window_size.x), 0.0f, static_cast<float>(window_size.y));
        text_shader.use();
        glUniformMatrix4fv(glGetUniformLocation(text_shader.get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // FreeType
        // --------
        FT_Library ft;
        // All functions return a value different than 0 whenever an error occurred
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            return -1;
        }

        // find path to font
        std::string font_name = "Arial.ttf";
        if (font_name.empty())
        {
            std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
            return -1;
        }

        // load font as face
        FT_Face face;
        if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return -1;
        }
        else {
            // set size to load glyphs as
            FT_Set_Pixel_Sizes(face, 0, 48);

            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // load first 128 characters of ASCII set
            for (unsigned char c = 0; c < 128; c++)
            {
                // Load character glyph 
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                    continue;
                }
                // generate texture
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );
                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // now store character for later use
                Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
                };
                characters_.insert(std::pair<char, Character>(c, character));
            }
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        // configure VAO/VBO for texture quads
        // -----------------------------------

        tvao.bind();
        tvbo.bind();
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        tvao.unbind();
        tvbo.unbind();
        return 0;
    };

    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
    {
        // render line of text
    // -------------------
    // OpenGL state
    // ------------
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // activate corresponding render state	
        text_shader.use();
        glUniform3f(glGetUniformLocation(text_shader.get(), "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        tvao.bind();

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = characters_[*c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            tvbo.bind();
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
            tvbo.unbind();
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        tvao.unbind();
        glBindTexture(GL_TEXTURE_2D, 0);
        // OpenGL state
        // ------------
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
    };
};
struct Interface {
    float translatex = 0.f;
    float translatey = 0.f;
    float translatez = 0.f;
    float scalex = 1.f;
    float scaley = 1.f;
    float scalez = 1.f;
    float rotatex = 0.f;
    float rotatey = 0.f;
    float rotatez = 1.f;
    float angle = glm::radians(0.0f);
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
    float fov = 45.0f;

    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;
    int temp_global_width = 1000;
    int temp_global_height = 1000;


    glm::vec3 cubePositions[10] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    float triangle_vertices[32] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int triangle_indices[6] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    float cube_vertices[288] = {
    -0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,1.0f, 0.0f, 0.0f,  0.0f, 1.0f
    };
};
Interface debug_interface;

void temp_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    debug_interface.temp_global_width = width;
    debug_interface.temp_global_height = height;
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (debug_interface.firstMouse)
    {
        debug_interface.lastX = xpos;
        debug_interface.lastY = ypos;
        debug_interface.firstMouse = false;
    }

    float xoffset = xpos - debug_interface.lastX;
    float yoffset = debug_interface.lastY - ypos; // reversed since y-coordinates go from bottom to top
    debug_interface.lastX = xpos;
    debug_interface.lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    debug_interface.yaw += xoffset;
    debug_interface.pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (debug_interface.pitch > 89.0f)
        debug_interface.pitch = 89.0f;
    if (debug_interface.pitch < -89.0f)
        debug_interface.pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(debug_interface.yaw)) * cos(glm::radians(debug_interface.pitch));
    front.y = sin(glm::radians(debug_interface.pitch));
    front.z = sin(glm::radians(debug_interface.yaw)) * cos(glm::radians(debug_interface.pitch));
    debug_interface.cameraFront = glm::normalize(front);
};
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    debug_interface.fov -= (float)yoffset;
    if (debug_interface.fov < 1.0f)
        debug_interface.fov = 1.0f;
    if (debug_interface.fov > 45.0f)
        debug_interface.fov = 45.0f;
};
void processInput(GLFWwindow* window) {

    // Assume this function is called right after call to glfwPollEvents
    // Assume GLFW has called all the callback functions
    // Assume Callback functions are bound to push slices into the event_buffer
    //event_frame.update();// update this event frame (this reads the slices in event buffer for use with events.
    //// Sample using gla event
    //if (event_frame.current_state.mouse_state.wasFired(gla::MouseKeyId::MOUSE_LEFT)) {
    //    glfwSetWindowShouldClose(window, true);
    //}
    //if (onEvent(gla::KeyboardKeyId::ESCAPE, gla::KeyState::PRESSED)) {
    //    glfwSetWindowShouldClose(window, true);
    //}
    //onEvent(Press[MouseR], &draw_select_box(Press[MouseR].position, mouse_current_position))
    //    onEvent(Release[MouseR], &make_selection(Press[MouseR].position, Release[MouseR].position))


    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * debug_interface.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        debug_interface.cameraPos += cameraSpeed * debug_interface.cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        debug_interface.cameraPos -= cameraSpeed * debug_interface.cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        debug_interface.cameraPos -= glm::normalize(glm::cross(debug_interface.cameraFront, debug_interface.cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        debug_interface.cameraPos += glm::normalize(glm::cross(debug_interface.cameraFront, debug_interface.cameraUp)) * cameraSpeed;
};

bool TEST_GLA_BASIC() {
    debug_log.log_print("Hello this a DEBUG message called from test_gla_basic. Hi, How are you ?");
    debug_log.store("debug_info.txt");

    resources.load_file("resources/images/side_adventurer/adventurer-v1.5-Sheet.png", "sprite1");
    resources.load_folder("resources/images/icons_food/", "food", ".png");
    resources.load_file("vertux.frag", "shader_frag_vertux");
    resources.load_file("vertux.vert", "shader_vert_vertux");

    ///* Initialize GLA library */
    auto isInit = gla::init();
    std::cout << isInit.what();

    /* Create a windowed mode window and its OpenGL context */
    std::vector<gla::ContextHint> context_hints = {
            { GLFW_SAMPLES, 4},                 // 4x antialiasing
            { GLFW_CONTEXT_VERSION_MAJOR, 3 },  // We want OpenGL 3.3
            { GLFW_CONTEXT_VERSION_MINOR, 3 },
            { GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE },  // To make MacOS happy; should not be needed.
            { GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE }   // We don't want the old OpenGL.
    };
    auto main_window = gla::Subcontext();
    main_window.init(context_hints, 1000, 1000, "TEST_GLA_BASIC");
    main_window.makeCurrent();

    //GLFWCallbacks::setCallbacks(main_window.getGLFWWinPtr());
    //gla::callback_manager.setTargetBuffer(event_buffer);
    //gla::callback_manager.setTargetWindow(main_window.getGLFWWinPtr());
    //gla::setCallbacks(main_window.getGLFWWinPtr());

    //glfwSetFramebufferSizeCallback(main_window.getGLFWWinPtr(), temp_framebuffer_size_callback); // Temporary buffer size callback
    //glfwSetCursorPosCallback(main_window.getGLFWWinPtr(), mouse_callback);
    //glfwSetScrollCallback(main_window.getGLFWWinPtr(), scroll_callback);
    // glfwSetInputMode(main_window.getGLFWWinPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // tell GLFW to capture our mouse


    system_font sys_font;
    system_vertux sys_vertux;
    // Set up graphics pipeline
    gla::ShaderProgram shader_program;
    gla::VertexArrayObject vao;
    gla::VertexBufferObject vbo;
    gla::ElementBufferObject ebo;
    unsigned int texture1, texture2;

    gla::ShaderProgram t_shader;
    gla::VertexArrayObject t_vao;
    gla::VertexBufferObject t_vbo;

    /*SetupGfxPipeline_Primitive(shader_program, texture1, texture2, vao, vbo, ebo);*/
    //sys_font.SetupGfxPipeline_Text(/*t_shader, t_vao, t_vbo*/);
    sys_vertux.SetupGfxPipeline();

    // uncomment this call to draw in wireframe polygons.
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int frame_i = 0; // start at frame 0
    gtl::Timer anim_timer;
    /* Loop until the user closes the window */
    while (!main_window.isShouldClose()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        debug_interface.deltaTime = currentFrame - debug_interface.lastFrame;
        debug_interface.lastFrame = currentFrame;
        processInput(main_window.getGLFWWinPtr());

        // Events
        // 1. Query the events
        //default_event_buffer.printSizes(); // for example
        // 2. Clear the event buffer
        //default_event_buffer.clear();

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //RenderPrimitives(vao, shader_program, texture1, texture2);
        //sys_font.RenderText(/*t_vbo, t_vao, t_shader,*/ "BigTeeny!", 100, 100, 1, glm::vec3(0.5, 0.8f, 0.2f));
        // Offset current frame by frame index
        sys_vertux.Draw({ 0.0f,0.0f,0.0f }, { 0,0 }, { (385 / 7) * 10 ,(592 / 16) * 10 }, 0.f
            , { static_cast<float>(0 + (51*(frame_i%7))),static_cast<float>((592 / 16)* ((frame_i/7) % 16)) }
            , { 51, (592 / 16) }
        );

        if (anim_timer.elapsedTime().count() > 1000000.0/12.0) { // Render 60 frames per second
            // iterate frames of sprite
            if (frame_i < 7*16) // Iterate over all sprite frames
            {
                frame_i++;
                anim_timer.reset();
            }
            else { // Loop Animation back to start -> or finish animation
                frame_i = 0;
                anim_timer.reset();
            }
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(main_window.getGLFWWinPtr());

        /* Poll for and process events */
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:

    return true;
};


int main(void) {
    TEST_GLA_BASIC();
};
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

//namespace gla {
//    class CallbackManager {
//    public:
//        CallbackManager() = default;
//        CallbackManager(GLFWwindow* window, slice_buffer& buffer)
//            : window_(window), buffer_(&buffer) {}
//        void setTargetWindow(GLFWwindow* win_ptr) {
//            window_ = win_ptr;
//        }
//        void setTargetBuffer(slice_buffer& bufr) {
//            buffer_ = &bufr;
//        }
//    private:
//        GLFWwindow* window_;
//        slice_buffer* buffer_;
//
//    public:
//        void keyboardKeyCallback(GLFWwindow* w, int key, int scancode, int action, int mods) {
//            buffer_->push(Slice_keyboard_key(static_cast<KeyState>(action),
//                static_cast<KeyboardKeyId>(key),
//                static_cast<ModifierKeyFlag>(mods),
//                scancode));
//        }
//
//        void characterEnteredCallback(GLFWwindow* w, unsigned int codepoint) {
//            buffer_->push(SliceENTERED_CHAR(codepoint));
//        }
//
//        void mousePositionCallback(GLFWwindow* w, double x_pos, double y_pos) {
//            buffer_->push(Slice_CURSOR_POSITION(x_pos, y_pos));
//        }
//
//        void mouseScrolledCallback(GLFWwindow* w, double x_offset, double y_offset) {
//            buffer_->push(SliceSCROLL_MOVE(x_offset, y_offset));
//        }
//
//        void mouseEnteredCallback(GLFWwindow* w, int is_inside_window) {
//            buffer_->push(Slice_CURSOR_ENTER(static_cast<MouseWindowState>(is_inside_window)));
//        }
//
//        void mouseButtonCallback(GLFWwindow* w, int button, int action, int mods) {
//            buffer_->push(Slice_MOUSE_BUTTON(static_cast<KeyState>(action),
//                static_cast<MouseKeyId>(button),
//                static_cast<ModifierKeyFlag>(mods)));
//        }
//
//        void pathDropCallback(GLFWwindow* w, int path_count, const char* paths[]) {
//            buffer_->push(SliceFILE_DROP(path_count, paths));
//        }
//
//        void joystickConfigCallback(int jid, int event) {
//            buffer_->push(SliceJOYSTICK_CONFIG(static_cast<JoystickId>(jid),
//                static_cast<JoystickConfigState>(event)));
//        }
//
//    }callback_manager;
//
//    namespace CallbackManagerCallbacks {
//        static void keyCallbackDispatcher(GLFWwindow* w, int key, int scancode, int action, int mods) {
//            callback_manager.keyboardKeyCallback(w, key, scancode, action, mods);
//        }
//
//        static void characterEnteredCallbackDispatcher(GLFWwindow* w, unsigned int codepoint) {
//            callback_manager.characterEnteredCallback(w, codepoint);
//        }
//
//        static void mousePositionCallbackDispatcher(GLFWwindow* w, double x_pos, double y_pos) {
//            callback_manager.mousePositionCallback(w, x_pos, y_pos);
//        }
//
//        static void mouseScrolledCallbackDispatcher(GLFWwindow* w, double x_offset, double y_offset) {
//            callback_manager.mouseScrolledCallback(w, x_offset, y_offset);
//        }
//
//        static void mouseEnteredCallbackDispatcher(GLFWwindow* w, int is_inside_window) {
//            callback_manager.mouseEnteredCallback(w, is_inside_window);
//        }
//
//        static void mouseButtonCallbackDispatcher(GLFWwindow* w, int button, int action, int mods) {
//            callback_manager.mouseButtonCallback(w, button, action, mods);
//        }
//
//        static void pathDropCallbackDispatcher(GLFWwindow* w, int path_count, const char* paths[]) {
//            callback_manager.pathDropCallback(w, path_count, paths);
//        }
//
//        static void joystickConfigCallbackDispatcher(int jid, int event) {
//            callback_manager.joystickConfigCallback(jid, event);
//        }
//    };
//
//    void setCallbacks(GLFWwindow* window_) {
//
//        glfwSetKeyCallback(window_, &CallbackManagerCallbacks::keyCallbackDispatcher);
//        glfwSetCharCallback(window_, &CallbackManagerCallbacks::characterEnteredCallbackDispatcher);
//        glfwSetCursorPosCallback(window_, &CallbackManagerCallbacks::mousePositionCallbackDispatcher);
//        glfwSetScrollCallback(window_, &CallbackManagerCallbacks::mouseScrolledCallbackDispatcher);
//        glfwSetCursorEnterCallback(window_, &CallbackManagerCallbacks::mouseEnteredCallbackDispatcher);
//        glfwSetMouseButtonCallback(window_, &CallbackManagerCallbacks::mouseButtonCallbackDispatcher);
//        glfwSetDropCallback(window_, &CallbackManagerCallbacks::pathDropCallbackDispatcher);
//        glfwSetJoystickCallback(&CallbackManagerCallbacks::joystickConfigCallbackDispatcher);
//    };
//}

//        void keyboardKeyCallback(GLFWwindow* w, int key, int scancode, int action, int mods) {
//            buffer_->push(Slice_keyboard_key(static_cast<KeyState>(action),
//                static_cast<KeyboardKeyId>(key),
//                static_cast<ModifierKeyFlag>(mods),
//                scancode));
//        }
//
//        void characterEnteredCallback(GLFWwindow* w, unsigned int codepoint) {
//            buffer_->push(SliceENTERED_CHAR(codepoint));
//        }
//
//        void mousePositionCallback(GLFWwindow* w, double x_pos, double y_pos) {
//            buffer_->push(Slice_CURSOR_POSITION(x_pos, y_pos));
//        }
//
//        void mouseScrolledCallback(GLFWwindow* w, double x_offset, double y_offset) {
//            buffer_->push(SliceSCROLL_MOVE(x_offset, y_offset));
//        }
//
//        void mouseEnteredCallback(GLFWwindow* w, int is_inside_window) {
//            buffer_->push(Slice_CURSOR_ENTER(static_cast<MouseWindowState>(is_inside_window)));
//        }
//
//        void mouseButtonCallback(GLFWwindow* w, int button, int action, int mods) {
//            buffer_->push(Slice_MOUSE_BUTTON(static_cast<KeyState>(action),
//                static_cast<MouseKeyId>(button),
//                static_cast<ModifierKeyFlag>(mods)));
//        }
//
//        void pathDropCallback(GLFWwindow* w, int path_count, const char* paths[]) {
//            buffer_->push(SliceFILE_DROP(path_count, paths));
//        }
//
//        void joystickConfigCallback(int jid, int event) {
//            buffer_->push(SliceJOYSTICK_CONFIG(static_cast<JoystickId>(jid),
//                static_cast<JoystickConfigState>(event)));
//        }
//
//    }callback_manager;
//
