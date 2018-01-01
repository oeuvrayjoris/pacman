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

#include <glimac/Board.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Pacman.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    GLuint width = 854;//1280;
    GLuint height = 480; //720;
    // Initialize SDL and open a window
    SDLWindowManager windowManager(width, height, "Pacman 3D");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

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
    * Caméra
    */
    //FreeflyCamera camera = FreeflyCamera();
    TrackballCamera camera = TrackballCamera();

    /**
    * Calcul des matrices de Transformation
    */

    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;

    ProjMatrix = glm::perspective(glm::radians(70.f), (float) width / height, 0.1f, 100.f);

    Cube cube(1.0);

    Board *board = new Board;
    std::cout << "*** Board ***" << std::endl;
    std::cout << "m = " << board->getLevelHeight() << std::endl;
    std::cout << "n = " << board->getLevelWidth() << std::endl;

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

    glm::ivec2 previousMousePosition = windowManager.getMousePosition();
    glm::ivec2 mousePosition = windowManager.getMousePosition();

    Pacman pacman(board);

    pacman.setDir('z');
    pacman.setDirOld('x');
    pacman.setCoord_x(12);
    pacman.setCoord_y(12);

    while(loop) {

        char key;

        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e)) {
            if (e.type == SDL_QUIT) {
                loop = false; // Leave the loop after this iteration
            }

            if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
                mousePosition = windowManager.getMousePosition();
                if (mousePosition.x < previousMousePosition.x) {
                    camera.rotateLeft(0.5);
                }
                else if (mousePosition.x > previousMousePosition.x) {
                    camera.rotateLeft(-0.5);
                }
                if (mousePosition.y < previousMousePosition.y) {
                    camera.rotateUp(0.5);
                }
                else if (mousePosition.y > previousMousePosition.y) {
                    camera.rotateUp(-0.5);
                }
            }
            else if (windowManager.isMouseButtonPressed(SDL_BUTTON_MIDDLE)) {
                // On récupére la position de la souris
                mousePosition = windowManager.getMousePosition();
                if (mousePosition.y < previousMousePosition.y)
                {
                    camera.moveFront(-0.05);
                }
                else if (mousePosition.y > previousMousePosition.y)
                {
                    camera.moveFront(0.05);
                }
            }

        }

        previousMousePosition = mousePosition;

        pacman.move(key);

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* On récupère la ViewMatrix de la caméra à chaque tour de boucle */
        glm::mat4 globalMVMatrix = camera.getViewMatrix();

        glBindVertexArray(vao);

        for (int i = 0; i < board->getLevelHeight(); i++) {
            MVMatrix = glm::translate(globalMVMatrix, glm::vec3(-3.9, 6, 0));
            MVMatrix = glm::scale(MVMatrix, glm::vec3(0.15, 0.15, 0.15));
            MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, 2*i));

            for (int j = 0; j < board->getLevelWidth(); j++) {
                MVMatrix = glm::translate(MVMatrix, glm::vec3(2, 0, 0));

                switch(board->getLevel()[i][j]) {
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                        glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
                        break;
                }
            }
        }

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
