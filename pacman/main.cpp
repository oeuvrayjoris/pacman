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

    Geometry pacman_obj;
    if(!pacman_obj.loadOBJ("../../assets/models/pacman.obj", "../../assets/models/pacman.mtl", false))
        std::cout << "Error loading pacman.obj" << std::endl;

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
    Sphere sphere(1, 32, 16);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount()*sizeof(float), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vbo2;
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vbo_pacman;
    glGenBuffers(1, &vbo_pacman);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_pacman);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pacman_obj.getVertexCount()*sizeof(Geometry::Vertex), pacman_obj.getVertexBuffer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint ibo_pacman;
    glGenBuffers(1, &ibo_pacman);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_pacman);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pacman_obj.getIndexCount()*sizeof(Geometry::Vertex), pacman_obj.getIndexBuffer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(float), (const GLvoid*) (0*sizeof(GLfloat)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float), (const GLvoid*) (0*sizeof(GLfloat)));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(float), (const GLvoid*) (0*sizeof(GLfloat)));
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

    GLuint vao_pacman;
    glGenVertexArrays(1, &vao_pacman);
    glBindVertexArray(vao_pacman);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_pacman);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pacman);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid*) offsetof(Geometry::Vertex, m_Position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid*) offsetof(Geometry::Vertex, m_Normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid*) offsetof(Geometry::Vertex, m_TexCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Application loop
    bool loop = true;

    glm::ivec2 previousMousePosition = windowManager.getMousePosition();
    glm::ivec2 mousePosition = windowManager.getMousePosition();


    Board *board = new Board;
    Pacman pacman(board);

    pacman.setDir('q');
    pacman.setDirOld('q');
    pacman.setCoord_x(19);
    pacman.setCoord_y(12);
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

        pacman.move(dir);
        
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* On récupère la ViewMatrix de la caméra à chaque tour de boucle */
        glm::mat4 globalMVMatrix = camera.getViewMatrix();

        //NormalMatrix = glm::transpose(glm::inverse(globalMVMatrix));


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
                        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
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
                        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
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
                        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                        glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
                        glBindVertexArray(0);
                        break;
                    case 10:
                        // Pacman
                        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.25, 0.25, 0.25));
                        MVMatrix = glm::rotate(MVMatrix, 0.f, glm::vec3(0, 1, 0));

                        switch(pacman.getDir()) {
                            case 'z':
                                MVMatrix = glm::rotate(MVMatrix, 180.f, glm::vec3(0, 1, 0));
                                break;
                            case 'q':
                                MVMatrix = glm::rotate(MVMatrix, -90.f, glm::vec3(0, 1, 0));
                                break;
                            case 'd':
                                MVMatrix = glm::rotate(MVMatrix, 90.f, glm::vec3(0, 1, 0));
                                break;
                        }

                        glBindVertexArray(vao_pacman);
                        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                        glDrawElements(GL_TRIANGLES, pacman_obj.getIndexCount(), GL_UNSIGNED_INT, 0);
                        glBindVertexArray(0);

                        switch(pacman.getDir()) {
                            case 'z':
                                MVMatrix = glm::rotate(MVMatrix, -180.f, glm::vec3(0, 1, 0));
                                break;
                            case 'q':
                                MVMatrix = glm::rotate(MVMatrix, 90.f, glm::vec3(0, 1, 0));
                                break;
                            case 'd':
                                MVMatrix = glm::rotate(MVMatrix, -90.f, glm::vec3(0, 1, 0));
                                break;
                        }

                        MVMatrix = glm::scale(MVMatrix, glm::vec3(4, 4, 4));
                        break;
                    case 11:
                        // Ghost 1
                        glBindVertexArray(vao2);
                        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        break;
                    case 12:
                        // Ghost 2
                        glBindVertexArray(vao2);
                        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        break;
                    case 13:
                        // Ghost 3
                        glBindVertexArray(vao2);
                        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                        glBindVertexArray(0);
                        break;
                    case 14:
                        // Ghost 4
                        glBindVertexArray(vao2);
                        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
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

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glDeleteBuffers(1, &vbo2);
    glDeleteVertexArrays(1, &vao2);

    glDeleteBuffers(1, &vbo_pacman);
    glDeleteVertexArrays(1, &vao_pacman);

    return EXIT_SUCCESS;
}
