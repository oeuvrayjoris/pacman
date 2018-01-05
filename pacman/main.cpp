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
#include <glimac/Geometry.hpp>

using namespace glimac;

struct TexProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    TexProgram(const FilePath& applicationPath) {
        std::string VS = "shaders/3D.vs.glsl";
        std::string FS = "shaders/tex3D.fs.glsl";
        #if __APPLE__
            m_Program = loadProgram(VS, FS);
        #else
            m_Program = loadProgram(applicationPath.dirPath() + VS,
                                              applicationPath.dirPath() + FS);
        #endif
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

struct NormalProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    NormalProgram(const FilePath& applicationPath) {
        std::string VS = "shaders/3D.vs.glsl";
        std::string FS = "shaders/normals.fs.glsl";
#if __APPLE__
        m_Program = loadProgram(VS, FS);
#else
        m_Program = loadProgram(applicationPath.dirPath() + VS,
                                              applicationPath.dirPath() + FS);
#endif
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
    }
};

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

    // Chargement des shaders
    FilePath applicationPath(argv[0]);
    TexProgram texProgram(applicationPath);
    NormalProgram normalProgram(applicationPath);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // Active test de profondeur du GPU
    glEnable(GL_DEPTH_TEST);

    /*Geometry pacman_obj;
    if(!pacman_obj.loadOBJ("../../assets/models/pacman.obj", "../../assets/models/pacman.mtl", false))
        std::cout << "Error loading pacman.obj" << std::endl;
    */

    // Cameras
    //FreeflyCamera camera = FreeflyCamera();
    TrackballCamera camera = TrackballCamera();


    /**
     * Textures
     */

    std::unique_ptr<Image> pImageEdge = loadImage("../../assets/textures/EdgeMap.jpg");
    if(pImageEdge == NULL)
        std::cout << "EdgeMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageSpace = loadImage("../../assets/textures/SpaceMap.jpg");
    if(pImageSpace == NULL)
        std::cout << "SpaceMap == NULL" << std::endl;

    GLuint edgeTexture;
    glGenTextures(1, &edgeTexture);

    GLuint spaceTexture;
    glGenTextures(1, &spaceTexture);

    glBindTexture(GL_TEXTURE_2D, edgeTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageEdge->getWidth(), pImageEdge->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageEdge->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, spaceTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageSpace->getWidth(), pImageSpace->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageSpace->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    /**
    * Calcul des matrices de Transformation
    */

    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;

    ProjMatrix = glm::perspective(glm::radians(70.f), (float) width / height, 0.1f, 100.f);

    Cube cube(1.0);
    Sphere sphere(1, 32, 16);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount()*sizeof(ShapeVertex), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vbo2;
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
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
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint vao2;
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Application loop
    bool loop = true;

    glm::ivec2 previousMousePosition = windowManager.getMousePosition();
    glm::ivec2 mousePosition = windowManager.getMousePosition();


    Board *board = new Board;
    board->launchGame();
    char dir = 'q';

    while(loop) {
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e)) {
            switch(e.type) {
                case SDL_QUIT:
                    loop = false;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                        case SDLK_q:
                            dir = 'q';
                            break;
                        case SDLK_d:
                            dir = 'd';
                            break;
                        case SDLK_z:
                            dir = 'z';
                            break;
                        case SDLK_s:
                            dir = 's';
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }

            if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
                mousePosition = windowManager.getMousePosition();
                if (mousePosition.x < previousMousePosition.x) {
                    camera.rotateLeft(1);
                }
                else if (mousePosition.x > previousMousePosition.x) {
                    camera.rotateLeft(-1);
                }
                if (mousePosition.y < previousMousePosition.y) {
                    camera.rotateUp(1);
                }
                else if (mousePosition.y > previousMousePosition.y) {
                    camera.rotateUp(-1);
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

        board->getPacman()->move(dir);
        board->checkForDeath();
        board->moveGhosts();
        board->checkForDeath();
        
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* On récupère la ViewMatrix de la caméra à chaque tour de boucle */
        glm::mat4 globalMVMatrix = camera.getViewMatrix();

        /* Sol */
        MVMatrix = glm::translate(globalMVMatrix, glm::vec3(0, 0, 0));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(30, 0.01, 30));

        glBindVertexArray(vao);

        texProgram.m_Program.use();
        glUniform1i(texProgram.uTexture, 0);

        glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, spaceTexture);

        glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

        /* Plateau de jeu */

        for (int i = 0; i < board->getLevelHeight(); i++) {
            MVMatrix = glm::translate(globalMVMatrix, glm::vec3(-3.9, 6.5, 0));
            MVMatrix = glm::scale(MVMatrix, glm::vec3(0.15, 0.15, 0.15));
            MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, 2*i));

            for (int j = 0; j < board->getLevelWidth(); j++) {
                MVMatrix = glm::translate(MVMatrix, glm::vec3(2, 0, 0));

                switch(board->getLevel()[i][j]) {
                    case 0:
                        // Empty case
                        break;
                    case 1:
                        // Dot case
                        MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
                        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.25, 0.25, 0.25));
                        glBindVertexArray(vao2);
                        normalProgram.m_Program.use();
                        glUniformMatrix4fv(normalProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(normalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(normalProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        MVMatrix = glm::scale(MVMatrix, glm::vec3(4.0, 4.0, 4.0));
                        MVMatrix = glm::rotate(MVMatrix, -windowManager.getTime(), glm::vec3(0, 1, 0));
                        break;
                    case 2:
                        // Pellet case
                        MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
                        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.5, 0.5, 0.5));
                        glBindVertexArray(vao2);
                        normalProgram.m_Program.use();
                        glUniformMatrix4fv(normalProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(normalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(normalProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        MVMatrix = glm::scale(MVMatrix, glm::vec3(2.0, 2.0, 2.0));
                        MVMatrix = glm::rotate(MVMatrix, -windowManager.getTime(), glm::vec3(0, 1, 0));
                        break;
                    case 3:
                        // Bonus fruit case
                        break;
                    case 4:
                        // Edge
                        glBindVertexArray(vao);
                        normalProgram.m_Program.use();
                        glUniformMatrix4fv(normalProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(normalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(normalProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
                        glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
                        glBindVertexArray(0);
                        /*
                        glBindVertexArray(vao);

                        texProgram.m_Program.use();
                        glUniform1i(texProgram.uTexture, 0);

                        glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D, edgeTexture);

                        glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D, 0);

                        glBindVertexArray(0);*/
                        break;
                    case 10:
                        // Pacman
                        glBindVertexArray(vao2);
                        normalProgram.m_Program.use();
                        glUniformMatrix4fv(normalProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(normalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(normalProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        break;
                    case 11:
                        // Ghost 1
                        glBindVertexArray(vao2);
                        normalProgram.m_Program.use();
                        glUniformMatrix4fv(normalProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(normalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(normalProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        break;
                    case 12:
                        // Ghost 2
                        glBindVertexArray(vao2);
                        normalProgram.m_Program.use();
                        glUniformMatrix4fv(normalProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(normalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(normalProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        break;
                    case 13:
                        // Ghost 3
                        glBindVertexArray(vao2);
                        normalProgram.m_Program.use();
                        glUniformMatrix4fv(normalProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(normalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(normalProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        break;
                    case 14:
                        // Ghost 4
                        glBindVertexArray(vao2);
                        normalProgram.m_Program.use();
                        glUniformMatrix4fv(normalProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(normalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(normalProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        break;
                    default:
                        break;
                }
            }
        }

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteTextures(1, &edgeTexture);
    glDeleteTextures(1, &spaceTexture);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glDeleteBuffers(1, &vbo2);
    glDeleteVertexArrays(1, &vao2);

    return EXIT_SUCCESS;
}
