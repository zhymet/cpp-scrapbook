#pragma once

#include "external.hpp"

#include <stdexcept>
#include <type_traits>
#include <concepts>
#include <functional>
#include <cassert>
#include <iostream>
#include <fstream>

namespace gla {

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

    using gl_bool = GLboolean;
    using gl_int = GLint;
    using gl_uint = GLuint;
    using gl_enum = GLenum;
    using gl_sizei = GLsizei;
    using gl_char = GLchar;

    template<typename T>
    concept GlCreateFunc_ = std::is_invocable_r_v<gl_uint, T>;

    template<typename T>
    concept GlDeleteFunc_ = std::is_invocable_r_v<void, T, gl_uint>;

    template<typename T>
    concept GlIsFunc_ = std::is_invocable_r_v<gl_bool, T, gl_uint>;


    template<GlCreateFunc_  GlCreateFuncT, GlCreateFuncT CREATE_FUNC,
            GlDeleteFunc_ GlDeleteFuncT, GlDeleteFuncT DELETE_FUNC,
            GlIsFunc_ GlIsFuncT, GlIsFuncT IS_FUNC>
    class GlObject {
    protected:
        const GlCreateFuncT& gl_create = CREATE_FUNC;
        const GlDeleteFuncT& gl_delete = DELETE_FUNC;
        const GlIsFuncT& gl_valid = IS_FUNC;
    private:
        gl_uint id_;
    public:
        explicit GlObject() : id_(gl_create()) {}
        constexpr ~GlObject() {
            assert(valid() == GL_TRUE && "wglObjectPtr : Destructor called on an invalid object.");
            gl_delete(id_);
        }
        constexpr const inline gl_uint& get() { return id_; }
        constexpr gl_bool valid() { return gl_valid(id_); }
    };


        template<typename T>
    class GlObjectPtr {
        T *ptr_;
    public:
        constexpr GlObjectPtr() : ptr_(nullptr)  {}
        constexpr GlObjectPtr &operator=(const GlObjectPtr &rhs) {
            ptr_ = rhs.ptr_;
            return *this;
        }
        constexpr GlObjectPtr &operator=(GlObjectPtr &&rhs) {
            ptr_ = std::move(rhs.ptr_);
            return *this;
        }
        constexpr explicit GlObjectPtr(T &gl_obj) {
            if (gl_obj->valid() == GL_TRUE)
                ptr_ = &gl_obj;
#if NTSDK_DEBUG == 1
            else
                throw "Attempting to construct GlObjectPtr with invalid GlObject."; // TODO: Create exception for this error.
#else
            else
                    ptr_ = nullptr;
#endif
            return this;
        }
        constexpr GlObjectPtr &operator=(T &gl_obj) {
            if (gl_obj->valid() == GL_TRUE)
                ptr_ = &gl_obj;
#if NTSDK_DEBUG == 1
            else
                throw "Attempting to assign an invalid GlObject to a GlObjectPtr."; // TODO: Create exception for this error.
#else
            else
                    ptr_ = nullptr;
#endif
            return this;
        }
        constexpr T &get() {
            return *ptr_;
        }
        constexpr gl_bool valid() {
            return ptr_->valid();
        }
    };

    // Vertex & Fragment Shader Bindings
    namespace bind::gl {
        constexpr  static auto const CreateShader
            = [](gl_enum shader_type) { return glCreateShader(shader_type); };

        constexpr  static auto const CreateVertexShader
            = []() { return glCreateShader(GL_VERTEX_SHADER); };

        constexpr  static auto const CreateFragmentShader
            = []() { return glCreateShader(GL_FRAGMENT_SHADER); };

        constexpr  static auto const DeleteShader
            = [](gl_uint i) { return glDeleteShader(i); };

        constexpr  static auto const IsShaderType
            = [](gl_uint i, gl_enum shader_type) {
            gl_int shader_type_result;
            glGetShaderiv(i, GL_SHADER_TYPE, &shader_type_result);
            if (glIsShader(i) && (shader_type_result == shader_type))
                return GL_TRUE;
            else
                return GL_FALSE;
        };

        constexpr  static auto const IsVertexShader
            = [](gl_uint i) { return IsShaderType(i, GL_VERTEX_SHADER); };

        constexpr  static auto const IsFragmentShader
            = [](gl_uint i) { return IsShaderType(i, GL_FRAGMENT_SHADER); };

        constexpr static auto ShaderSource
            = [](int i, char const* source_code) { glShaderSource(i, 1, &source_code, NULL); };

        constexpr static auto CompileShader
            = [](gl_uint i) { glCompileShader(i); };

        constexpr static auto GetShaderiv
            = [](gl_uint i, gl_enum n, gl_int* p) { glGetShaderiv(i, n, p); };

        constexpr static auto GetShaderInfoLog
            = [](gl_int i, gl_sizei ml, gl_sizei* l, gl_char* il) { glGetShaderInfoLog(i, ml, l, il); };
    }

    // Vertex Shader Object
    using VertexShaderOBJ = GlObject<
        decltype(bind::gl::CreateVertexShader), bind::gl::CreateVertexShader
        , decltype(bind::gl::DeleteShader), bind::gl::DeleteShader
        , decltype(bind::gl::IsVertexShader), bind::gl::IsVertexShader
    >;

    struct VertexShader : public VertexShaderOBJ {
        gl_int info_log_length_{ 0 };
    public:
        VertexShader() : VertexShaderOBJ() {}
        constexpr void source(char const* source_code) {
            bind::gl::ShaderSource(get(), source_code);
        }
        void sourceFromFile(char const* file) {
            std::ifstream shader_file(file);
            std::string shader_file_raw((std::istreambuf_iterator<char>(shader_file)), (std::istreambuf_iterator<char>()));
            bind::gl::ShaderSource(get(), shader_file_raw.c_str());
        }
        constexpr void compile() {
            bind::gl::CompileShader(get());
        }
        constexpr gl_int checkCompilation() {
            // If result is not 0 then an error occured
            // Check the vertex shader's compilation status. GL_TRUE if successful, GL_FALSE otherwise.
            gl_int result_type = GL_FALSE;
            auto id = get();
            bind::gl::GetShaderiv(id, GL_COMPILE_STATUS, &result_type);
            bind::gl::GetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length_);
            if (info_log_length_ == 0) {
                result_type = GL_TRUE;
                return result_type;
            }
            else {
                return result_type;
            }
        }
        void printCompilationErrors() {
            // If errors occured print error log.
            // TODO: better error reporting method.
            if (info_log_length_ > 0) {
                std::vector<char> error_msg(info_log_length_ + 1);
                bind::gl::GetShaderInfoLog(get(), info_log_length_, NULL, &error_msg[0]);
                printf("%s\n", &error_msg[0]);
            }
            else {
                printf("%s\n", "No compilation errors in shader program.");
            }
        }
    };

    // Fragment Shader Object
    using FragmentShaderOBJ = GlObject<
        decltype(bind::gl::CreateFragmentShader), bind::gl::CreateFragmentShader,
        decltype(bind::gl::DeleteShader), bind::gl::DeleteShader
        , decltype(bind::gl::IsFragmentShader), bind::gl::IsFragmentShader
    >;

    struct FragmentShader : public FragmentShaderOBJ {
        gl_int info_log_length_{ 0 };
    public:
        FragmentShader() : FragmentShaderOBJ() {}
        void sourceFromFile(char const* file) {
            std::ifstream shader_file(file);
            std::string shader_file_raw((std::istreambuf_iterator<char>(shader_file)),(std::istreambuf_iterator<char>()));
            bind::gl::ShaderSource(get(), shader_file_raw.c_str());
        }
        constexpr void source(char const* source_code) {
            bind::gl::ShaderSource(get(), source_code);
        }
        constexpr void compile() {
            bind::gl::CompileShader(get());
        }
        constexpr gl_int checkCompilation() {
            // If result is not 0 then an error occured
            // Check the Fragment shader's compilation status. GL_TRUE if successful, GL_FALSE otherwise.
            gl_int result_type = GL_FALSE;
            auto id = get();
            bind::gl::GetShaderiv(id, GL_COMPILE_STATUS, &result_type);
            bind::gl::GetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length_);
            if (info_log_length_ == 0) {
                result_type = GL_TRUE;
                return result_type;
            }
            else {
                return result_type;
            }
        }
        void printCompilationErrors() {
            // If errors occured print error log.
            // TODO: better error reporting method.
            if (info_log_length_ > 0) {
                std::vector<char> error_msg(info_log_length_ + 1);
                bind::gl::GetShaderInfoLog(get(), info_log_length_, NULL, &error_msg[0]);
                printf("%s\n", &error_msg[0]);
            }
            else {
                printf("%s\n", "No compilation errors in shader program.");
            }
        }
    };
    
    // ShaderProgram bindings
    namespace bind::gl {
        constexpr static auto const CreateProgram = []() { return glCreateProgram(); };
        constexpr static auto const DeleteProgram = [](gl_uint i) { return glDeleteProgram(i); };
        constexpr static auto const IsProgram = [](gl_uint i) { return glIsProgram(i); };
        constexpr static auto const AttachShader = [](gl_uint p_i, gl_uint s_i) { glAttachShader(p_i, s_i); };
        constexpr static auto const DetachShader = [](gl_uint p_i, gl_uint s_i) { glDetachShader(p_i, s_i); };
        constexpr static auto const LinkProgram = [](gl_uint i) { glLinkProgram(i); };
        constexpr static auto const GetProgramiv = [](gl_uint i, gl_enum n, gl_int* p) {return glGetProgramiv(i, n, p); };
    };

    // Shader Program Object
    using ShaderProgramOBJ = GlObject<
        decltype(bind::gl::CreateProgram), bind::gl::CreateProgram
        , decltype(bind::gl::DeleteProgram), bind::gl::DeleteProgram
        , decltype(bind::gl::IsProgram), bind::gl::IsProgram
    >;

    class ShaderProgram : public ShaderProgramOBJ {
        gl_int info_log_length_{ 0 };
        gl_int link_state_;
    public:
        ShaderProgram() : ShaderProgramOBJ() {}
        auto makeFromFile(const char * vert_file, const char * frag_file) {
            /* Build and Complie Shader Program */
            gla::VertexShader vert_shader;
            vert_shader.sourceFromFile(vert_file);
            vert_shader.compile();
            vert_shader.checkCompilation();
            gla::FragmentShader frag_shader;
            frag_shader.sourceFromFile(frag_file);
            frag_shader.compile();
            frag_shader.checkCompilation();
            attachVertexShader(vert_shader);
            attachFragmentShader(frag_shader);
            link();
            return checkLink();
        }
        constexpr gl_int getUniformLoc(const char * name) { return glGetUniformLocation(get(),name); }
        constexpr void attachVertexShader(VertexShader& vertex_shader) {
            bind::gl::AttachShader(get(), vertex_shader.get());
        }
        constexpr void detachVertexShader(VertexShader& vertex_shader) {
            bind::gl::DetachShader(get(), vertex_shader.get());
        }
        constexpr void attachFragmentShader(FragmentShader& fragment_shader) {
            bind::gl::AttachShader(get(), fragment_shader.get());
        }
        constexpr void detachFragmentShader(FragmentShader& fragment_shader) {
            bind::gl::DetachShader(get(), fragment_shader.get());
        }
        constexpr void link() {
            bind::gl::LinkProgram(get());
        }
        constexpr gl_int checkLink() {
            gl_int result_type = GL_FALSE;
            auto id = get();
            bind::gl::GetProgramiv(get(), GL_LINK_STATUS, &result_type);
            bind::gl::GetProgramiv(get(), GL_INFO_LOG_LENGTH, &info_log_length_);

            if (info_log_length_ == 0) {
                result_type = GL_TRUE;
                link_state_ = true;
                return result_type;
            }
            else {
                return result_type;
            }
        }
        void printLinkErrors() {
            // TODO: better error reporting method.
            if (info_log_length_ > 0) {
                std::vector<char> ProgramErrorMessage(info_log_length_ + 1);
                glGetProgramInfoLog(get(), info_log_length_, NULL, &ProgramErrorMessage[0]);
                printf("%s\n", &ProgramErrorMessage[0]);
            }
            else {
                printf("%s\n", "No link errors in shader program.");
            }
        }
        void use() {
            glUseProgram(get());
        }

        void setUniformInt(const char * name, gl_int value) {
            use();
            glUniform1i(glGetUniformLocation(get(), name), value);
        }


    };

    // Vertex Array Buffer Object Bindings
    namespace bind::gl {
        constexpr auto const GenBuffers = [](gl_sizei size) {
            gl_uint id;
            glGenBuffers(size, &id);
            return id;
        };

        constexpr auto const GenVertexArrays = [](gl_sizei size) {
            gl_uint id;
            glGenVertexArrays(size, &id);
            return id;
        };

        constexpr auto const CreateVertexBuffer = []() {
            return GenBuffers(1);
        };

        constexpr auto const CreateElementBuffer = []() {
            return GenBuffers(1);
        };

        constexpr static auto const DeleteBuffer
            = [](gl_uint i) { return glDeleteBuffers(1,&i); };
        
        constexpr static auto const CreateVertexArray = []() {
            return GenVertexArrays(1);
        };

        constexpr static auto const DeleteVertexArray
            = [](gl_uint i) { return glDeleteVertexArrays(1, &i); };


        constexpr static auto const IsVertexArray = [](gl_uint i) {
            return glIsVertexArray(i);
        };

        constexpr static auto const IsBuffer = [](gl_uint i) {
            // TODO: FIX - currently says buffer is not a buffer?
            //return glIsBuffer(i);
            return true;
        };
        //From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) will be used to configure the currently bound buffer,
        constexpr static auto const BindVertexBuffer = [](gl_uint id) { glBindBuffer(GL_ARRAY_BUFFER,id); };
        constexpr static auto const BindElementBuffer = [](gl_uint id) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); };
        constexpr static auto const UnbindVertexBuffer = []() { glBindBuffer(GL_ARRAY_BUFFER, 0); };
        constexpr static auto const UnbindElementBuffer = []() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };



        //From that point on we should bind/configure the corresponding VBO(s) and attribute pointer(s)
        //and then unbind the VAO for later use. As soon as we want to draw an object, we simply bind
        //the VAO with the preferred settings before drawing the object and that is it. 
        constexpr static auto const BindVertexArray = [](gl_uint id) { glBindVertexArray(id); };
        constexpr static auto const UnbindVertexArray = []() { glBindVertexArray(0); ; };

        //copies the previously defined vertex data into the currently bound buffer's memory
        //The fourth parameter specifies how we want the graphics card to manage the given data.This can take 3 forms:
        //GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
        //GL_STATIC_DRAW : the data is set only once and used many times.
        //GL_DYNAMIC_DRAW : the data is changed a lot and used many times.
        constexpr static auto const SetArrayBufferData = [](const void* data, gl_sizei size, GLenum usage) { glBufferData(GL_ARRAY_BUFFER, size, data, usage); };
        constexpr static auto const SetElementBufferData = [](const void* data, gl_sizei size, GLenum usage) { glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage); };


        /*
        The first parameter specifies which vertex attribute we want to configure. 
        Remember that we specified the location of the position vertex attribute in the vertex shader with layout (location = 0).
        This sets the location of the vertex attribute to 0 and since we want to pass data to this vertex attribute, we pass in 0.
        */
        /*
        The next argument specifies the size of the vertex attribute. The vertex attribute is a vec3 so it is composed of 3 values.
        */
        /*
        The third argument specifies the type of the data which is GL_FLOAT (a vec* in GLSL consists of floating point values).
        */
        /*
        The next argument specifies if we want the data to be normalized. 
        If we're inputting integer data types (int, byte) and we've set this to GL_TRUE, 
        the integer data is normalized to 0 (or -1 for signed data) and 1 when converted to float. 
        This is not relevant for us so we'll leave this at GL_FALSE.*/
        /*The fifth argument is known as the stride and tells us the space between consecutive vertex attributes. 
        Since the next set of position data is located exactly 3 times the size of a float away we specify that value as the stride. 
        Note that since we know that the array is tightly packed (there is no space between the next vertex attribute value) w
        e could've also specified the stride as 0 to let OpenGL determine the stride (this only works when values are tightly packed). 
        Whenever we have more vertex attributes we have to carefully define the spacing between each vertex 
        attribute but we'll get to see more examples of that later on.*/
        /*The last parameter is of type void* and thus requires that weird cast.
        This is the offset of where the position data begins in the buffer.
        Since the position data is at the start of the data array this value is just 0.
        We will explore this parameter in more detail later on*/
        constexpr static auto const SetVertexAttribPtr = [](gl_uint id) { 
            glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(id);
        };
    };

    // Vertex Buffer Object
    using VertexBufferOBJ = GlObject<
        decltype(bind::gl::CreateVertexBuffer), bind::gl::CreateVertexBuffer
        , decltype(bind::gl::DeleteBuffer), bind::gl::DeleteBuffer
        , decltype(bind::gl::IsBuffer), bind::gl::IsBuffer
    >;

    struct VertexBufferObject : public VertexBufferOBJ {
        VertexBufferObject() : VertexBufferOBJ() {}
        void bind() { bind::gl::BindVertexBuffer(get()); };
        void unbind() { bind::gl::UnbindVertexBuffer(); }
        void setData(const void* data, gl_sizei size, GLenum usage) { bind::gl::SetArrayBufferData(data,size,usage); }
    };

    // Element Buffer Object
    using ElementBufferOBJ = GlObject<
        decltype(bind::gl::CreateElementBuffer), bind::gl::CreateElementBuffer
        , decltype(bind::gl::DeleteBuffer), bind::gl::DeleteBuffer
        , decltype(bind::gl::IsBuffer), bind::gl::IsBuffer
    >;

    struct ElementBufferObject : public ElementBufferOBJ {
        ElementBufferObject() : ElementBufferOBJ() {}
        void bind() { bind::gl::BindElementBuffer(get()); };
        void unbind() { bind::gl::UnbindElementBuffer(); }
        void setData(const void* data, gl_sizei size, GLenum usage) { bind::gl::SetElementBufferData(data,size, usage); }
    };


    // Vertex Array Object
    using VertexArrayOBJ = GlObject<
        decltype(bind::gl::CreateVertexArray), bind::gl::CreateVertexArray
        , decltype(bind::gl::DeleteVertexArray), bind::gl::DeleteVertexArray
        , decltype(bind::gl::IsVertexArray), bind::gl::IsVertexArray
    >;

    struct VertexArrayObject : public VertexArrayOBJ {
        VertexArrayObject() : VertexArrayOBJ() {}
        void bind() { bind::gl::BindVertexArray(get()); }
        void unbind() { bind::gl::UnbindVertexArray(); }
    };

    // Texture Object Bindings
    namespace bind::gl {
        constexpr static auto const CreateTexture
            = []() { gl_uint i; glGenTextures(1, &i); return i; };

        constexpr static auto const BindTexture = [](gl_uint id) { glBindTexture(GL_TEXTURE_2D, id); };

        constexpr static auto const DeleteTexture
            = [](gl_uint i) { glDeleteTextures(1, &i); };


        constexpr static auto const IsTexture = [](gl_uint i) {
            return glIsTexture(i);
        };
    };

    // Element Buffer Object
    using TextureOBJ = GlObject<
        decltype(bind::gl::CreateTexture), bind::gl::CreateTexture
        , decltype(bind::gl::DeleteTexture), bind::gl::DeleteTexture
        , decltype(bind::gl::IsTexture), bind::gl::IsTexture
    >;

    // Requires stbi_image
    struct Texture : public TextureOBJ {
        Texture() : TextureOBJ() {}
        gtl::vec2<float> size{0.f,0.f};
        void load(const char * name,gl_enum type = GL_RGB) {
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glBindTexture(GL_TEXTURE_2D, get());
            // set the texture wrapping parameters
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // load image, create texture and generate mipmaps
            int width, height, nrChannels;
            //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
            // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
            unsigned char* data = stbi_load(name, &width, &height, &nrChannels, 0);
            if (data)
            {
                size = {static_cast<float>(width),static_cast<float>(height)};
                glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
            glBindTexture(GL_TEXTURE_2D, 0);
        };

        // Binds for editing texture, for use must be bound after call to the active texture glActiveTexture(GL_TEXTURE0) or another number
        void bind() { glBindTexture(GL_TEXTURE_2D, get()); };
        void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
    };
};
//
//void example() {
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//        float vertices[] = {
//             1.0f,  1.0f, 0.0f,  // top right
//             1.0f, -1.0f, 0.0f,  // bottom right
//            -1.0f, -1.0f, 0.0f,  // bottom left
//            -1.0f,  1.0f, 0.0f   // top left 
//    };
//    unsigned int indices[] = {  // note that we start from 0!
//        0, 1, 3,  // first Triangle
//        1, 2, 3   // second Triangle
//    };
//    gla::VertexArrayObject vao;
//    gla::VertexBufferObject vbo;
//    gla::ElementBufferObject ebo;
//
//    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//    vao.bind();
//
//    vbo.bind();
//    vbo.setData(vertices, GL_STATIC_DRAW);
//
//    ebo.bind();
//    ebo.setData(indices, GL_STATIC_DRAW);
//
//    gla::bind::gl::SetVertexAttribPtr(0); // Corresponds to postion layout = 0 in the Vertex Shader
//
//    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex 
//    // attribute's bound vertex buffer object so afterwards we can safely unbind
//    vbo.unbind();
//
//    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//
//        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//    vao.unbind();
//}
///*
//* EXAMPLE USE
//*     // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//         1.0f,  1.0f, 0.0f,  // top right
//         1.0f, -1.0f, 0.0f,  // bottom right
//        -1.0f, -1.0f, 0.0f,  // bottom left
//        -1.0f,  1.0f, 0.0f   // top left 
//    };
//    unsigned int indices[] = {  // note that we start from 0!
//        0, 1, 3,  // first Triangle
//        1, 2, 3   // second Triangle
//    };
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//    glBindVertexArray(0);
//
//*/