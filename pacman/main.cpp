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
    FreeflyCamera camera = FreeflyCamera();
    //TrackballCamera camera = TrackballCamera();

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
    //bool key[4] = {false, false, false, false};

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

            if (windowManager.isKeyPressed(SDLK_z))
                key = 'z';
            if (windowManager.isKeyPressed(SDLK_s))
                key = 's';
            if (windowManager.isKeyPressed(SDLK_q))
                key = 'q';
            if (windowManager.isKeyPressed(SDLK_d))
                key = 'd';
            /*
            if (windowManager.isKeyPressed(SDLK_z))
                camera.moveFront(0.001);
            if (windowManager.isKeyPressed(SDLK_s))
                camera.moveFront(-0.001);
            if (windowManager.isKeyPressed(SDLK_q))
                camera.moveLeft(0.001);
            if (windowManager.isKeyPressed(SDLK_d))
                camera.moveLeft(-0.001);
                */
        }

        pacman.move(key);

        std::cout << pacman.getCoord_x() << " - " << pacman.getCoord_y() << " - " << board->getLevel()[pacman.getCoord_x()][pacman.getCoord_y()] << std::endl;
        if (pacman.getDir() != pacman.getDirOld())
            std::cout << pacman.getDir() << " - " << std::endl;

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* On récupère la ViewMatrix de la caméra à chaque tour de boucle */
        glm::mat4 globalMVMatrix = camera.getViewMatrix();

        MVMatrix = glm::translate(globalMVMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
        MVMatrix = glm::rotate(MVMatrix, -windowManager.getTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glBindVertexArray(vao);

        /* START DRAWING THE EARTH */
        glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
        /* END DRAWING THE EARTH */

        MVMatrix = glm::translate(globalMVMatrix, glm::vec3(0, 0, -5)); // Translation
        MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
        MVMatrix = glm::translate(MVMatrix, glm::vec3(-2, 0, 0));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2));

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        /* START DRAWING THE MOON */
        glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
        /* END DRAWING */

        for (int i = 0; i < board->getLevelHeight(); i++) { // Parcours des lignes
            MVMatrix = glm::translate(globalMVMatrix, glm::vec3(-8, -3, -10)); // réinit MVMAtrix puis translate général
            MVMatrix = glm::scale(MVMatrix, glm::vec3(0.15, 0.15, 0.15)); // Scale général
            MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, i*0.5f)); // Translate en profondeur en fonction du numéro de ligne
            for (int j = 0; j < board->getLevelWidth(); j++) { // Parcours des colonnes
                if(board->getLevel()[i][j] == 4) {
                    MVMatrix = glm::translate(MVMatrix, glm::vec3(i*0.5f, 0, 0)); // On translate en x, pour afficher le cube à droite

                    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
                }
                else {
                    MVMatrix = glm::translate(MVMatrix, glm::vec3(i*0.5f, 0, 0)); // On translate mais on affiche pas le cube (car c'est vide)
                }

            }
        }

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
