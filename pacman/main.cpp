#define GLEW_STATIC
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Cube.hpp>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include <vector>

#include <glimac/Creature.hpp>
#include <glimac/Board.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    GLuint width = 1280;
    GLuint height = 720;
    // Initialize SDL and open a window
    SDLWindowManager windowManager(width, height, "Pacman 3D");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    Board board;
    std::cout << "*** Board ***" << std::endl;
    std::cout << "m = " << board.getM() << std::endl;
    std::cout << "n = " << board.getN() << std::endl;

    FilePath applicationPath(argv[0]);

    std::string VS = "shaders/3D.vs.glsl";
    std::string FS = "shaders/normals.fs.glsl";

#if __APPLE__
    Program program = loadProgram(VS, FS);
#else
    Program program = loadProgram(applicationPath.dirPath() + VS,
                                      applicationPath.dirPath() + FS);
#endif
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    /**
    * Uniform Variable
    */
    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    // Active test de profondeur du GPU
    glEnable(GL_DEPTH_TEST);

    /**
    * Calcul des matrices de Transformation
    */
    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;

    Sphere sphere(1, 32, 16);
    Cube cube;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount()*sizeof(float), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (const GLvoid*) (0*sizeof(GLfloat)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (const GLvoid*) (0*sizeof(GLfloat)));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), (const GLvoid*) (0*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Application loop
    bool loop = true;

    while(loop) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                loop = false; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MVMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        MVMatrix = glm::rotate(MVMatrix, -windowManager.getTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        ProjMatrix = glm::perspective(glm::radians(70.0f), (float)width/height, 0.1f, 100.0f);
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glBindVertexArray(vao);

        /* START DRAWING THE EARTH */
            glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

            MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
            MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
            MVMatrix = glm::translate(MVMatrix, glm::vec3(-2, 0, 0));
            MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2));

            glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        /* END DRAWING THE EARTH */

        /* START DRAWING THE MOON */
            glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
        /* END DRAWING */

        glBindVertexArray(0);


        // Update the display
        windowManager.swapBuffers();
    }

    for (int i = 0; i < board.getM(); i++) {
        for (int j = 0; j < board.getN(); j++) {
            if(board.getTab()[i][j] == 1)
                std::cout << "!";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
