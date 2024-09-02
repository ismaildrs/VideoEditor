#include "../include/shader_class.hpp"


Shader::Shader() {
    std::ifstream vertexFile, fragFile;
    std::string vertexSource, fragSource;

    // Reading vertex shader file
    vertexFile.open(VERTEX_SHADER_PATH);
    if (!vertexFile.is_open()) {
        #ifdef TEST_VERSION
            std::cerr << "Failed to open file: " << VERTEX_SHADER_PATH << std::endl;
        #endif
        exit(EXIT_FAILURE);  // Corrected exit syntax
    }

    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();  // Read file buffer into stream
    vertexSource = vertexStream.str();   // Convert stream into string

    vertexFile.close();  // Close the file

    // Reading fragment shader file
    fragFile.open(FRAG_SHADER_PATH);
    if (!fragFile.is_open()) {
        #ifdef TEST_VERSION
            std::cerr << "Failed to open file: " << FRAG_SHADER_PATH << std::endl;
        #endif
        exit(EXIT_FAILURE);  // Corrected exit syntax
    }

    std::stringstream fragStream;
    fragStream << fragFile.rdbuf();  // Read file buffer into stream
    fragSource = fragStream.str();   // Convert stream into string

    fragFile.close();  // Close the file

    // Convert string to C-string
    const char* vertexCstSource = vertexSource.c_str();
    const char* fragCstSource = fragSource.c_str();

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCstSource, nullptr);
    glCompileShader(vertexShader);

    // Check for compilation errors in vertex shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        #ifdef TEST_VERSION
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        #endif
        exit(EXIT_FAILURE);
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragCstSource, nullptr);
    glCompileShader(fragmentShader);

    // Check for compilation errors in fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        #ifdef TEST_VERSION
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        #endif
        exit(EXIT_FAILURE);
    }

    // Link shaders to the program
    ID = glCreateProgram();  // Assign the created program to ID
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Check for linking errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Clean up: delete shaders as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);  // Use the shader program
}

void Shader::setUniform(const std::string &name, int unit) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), unit);
}