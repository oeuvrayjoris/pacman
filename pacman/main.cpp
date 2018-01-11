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
#include <glimac/Camera3.hpp>
#include <glimac/Camera1.hpp>
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

    // Cameras
    //FreeflyCamera camera = FreeflyCamera();
    TrackballCamera camera = TrackballCamera();
    Camera3 camera3 = Camera3();
    Camera1 camera1 = Camera1();
    int camera_choice = 1;

    /**
     * Textures
     */

#if __APPLE__
    std::unique_ptr<Image> pImageSpace = loadImage("../../assets/textures/SpaceMap.jpg");
    if(pImageSpace == NULL)
        std::cout << "SpaceMap == NULL" << std::endl;

    std::unique_ptr<Image> pImagePacman = loadImage("../../assets/textures/NovelliMap.jpg");
    if(pImagePacman == NULL)
        std::cout << "PacmanMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageBlinky = loadImage("../../assets/textures/BlinkyMap.jpg");
    if(pImageBlinky == NULL)
        std::cout << "BlinkyMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageClyde = loadImage("../../assets/textures/ClydeMap.jpg");
    if(pImageClyde == NULL)
        std::cout << "ClydeMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageInky = loadImage("../../assets/textures/InkyMap.jpg");
    if(pImageInky == NULL)
        std::cout << "InkyMap == NULL" << std::endl;

    std::unique_ptr<Image> pImagePinky = loadImage("../../assets/textures/PinkyMap.jpg");
    if(pImagePinky == NULL)
        std::cout << "PinkyMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageCoeur = loadImage("../../assets/textures/CoeurMap.png");
    if(pImageCoeur == NULL)
        std::cout << "CoeurMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageMenu1 = loadImage("../../assets/textures/Menu1Map.jpg");
    if(pImageMenu1 == NULL)
        std::cout << "Menu1Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageMenu2 = loadImage("../../assets/textures/Menu2Map.jpg");
    if(pImageMenu2 == NULL)
        std::cout << "Menu2Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageMenu3 = loadImage("../../assets/textures/Menu3Map.jpg");
    if(pImageMenu3 == NULL)
        std::cout << "Menu3Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageEchap1 = loadImage("../../assets/textures/Echap1Map.jpg");
    if(pImageEchap1 == NULL)
        std::cout << "Echap1Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageEchap2 = loadImage("../../assets/textures/Echap2Map.jpg");
    if(pImageEchap2 == NULL)
        std::cout << "Echap2Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageEchap3 = loadImage("../../assets/textures/Echap3Map.jpg");
    if(pImageEchap3 == NULL)
        std::cout << "Echap3Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageOver1 = loadImage("../../assets/textures/Over1Map.jpg");
    if(pImageOver1 == NULL)
        std::cout << "Over1Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageOver2 = loadImage("../../assets/textures/Over2Map.jpg");
    if(pImageOver2 == NULL)
        std::cout << "Over2Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageOver3 = loadImage("../../assets/textures/Over3Map.jpg");
    if(pImageOver3 == NULL)
        std::cout << "Over3Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageDot = loadImage("../../assets/textures/DotMap.jpg");
    if(pImageDot == NULL)
        std::cout << "DotMap == NULL" << std::endl;
#else
    std::unique_ptr<Image> pImageSpace = loadImage(applicationPath.dirPath() + "../assets/textures/SpaceMap.jpg");
    if(pImageSpace == NULL)
        std::cout << "SpaceMap == NULL" << std::endl;

    std::unique_ptr<Image> pImagePacman = loadImage(applicationPath.dirPath() +"../assets/textures/PacmanMap.jpg");
    if(pImagePacman == NULL)
        std::cout << "PacmanMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageBlinky = loadImage(applicationPath.dirPath() +"../assets/textures/BlinkyMap.jpg");
    if(pImageBlinky == NULL)
        std::cout << "BlinkyMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageClyde = loadImage(applicationPath.dirPath() +"../assets/textures/ClydeMap.jpg");
    if(pImageClyde == NULL)
        std::cout << "ClydeMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageInky = loadImage(applicationPath.dirPath() +"../assets/textures/InkyMap.jpg");
    if(pImageInky == NULL)
        std::cout << "InkyMap == NULL" << std::endl;

    std::unique_ptr<Image> pImagePinky = loadImage(applicationPath.dirPath() +"../assets/textures/PinkyMap.jpg");
    if(pImagePinky == NULL)
        std::cout << "PinkyMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageCoeur = loadImage(applicationPath.dirPath() +"../assets/textures/CoeurMap.png");
    if(pImageCoeur == NULL)
        std::cout << "CoeurMap == NULL" << std::endl;

    std::unique_ptr<Image> pImageMenu1 = loadImage(applicationPath.dirPath() + "../assets/textures/Menu1Map.jpg");
    if(pImageCoeur == NULL)
        std::cout << "Menu1Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageMenu2 = loadImage(applicationPath.dirPath() + "../assets/textures/Menu2Map.jpg");
    if(pImageMenu2 == NULL)
        std::cout << "Menu2Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageMenu3 = loadImage(applicationPath.dirPath() + "../assets/textures/Menu3Map.jpg");
    if(pImageMenu3 == NULL)
        std::cout << "Menu3Map == NULL" << std::endl;

        std::unique_ptr<Image> pImageEchap1 = loadImage(applicationPath.dirPath() + "../assets/textures/Echap1Map.jpg");
    if(pImageEchap1 == NULL)
        std::cout << "Echap1Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageEchap2 = loadImage(applicationPath.dirPath() + "../assets/textures/Echap2Map.jpg");
    if(pImageEchap2 == NULL)
        std::cout << "Echap2Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageEchap3 = loadImage(applicationPath.dirPath() + "../assets/textures/Echap3Map.jpg");
    if(pImageEchap3 == NULL)
        std::cout << "Echap3Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageOver1 = loadImage(applicationPath.dirPath() + "../assets/textures/Over1Map.jpg");
    if(pImageOver1 == NULL)
        std::cout << "Over1Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageOver2 = loadImage(applicationPath.dirPath() + "../assets/textures/Over2Map.jpg");
    if(pImageOver2 == NULL)
        std::cout << "Over2Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageOver3 = loadImage(applicationPath.dirPath() + "../assets/textures/Over3Map.jpg");
    if(pImageOver3 == NULL)
        std::cout << "Over3Map == NULL" << std::endl;

    std::unique_ptr<Image> pImageDot = loadImage(applicationPath.dirPath() + "../assets/textures/DotMap.jpg");
    if(pImageDot == NULL)
        std::cout << "DotMap == NULL" << std::endl;
#endif

    GLuint spaceTexture;
    glGenTextures(1, &spaceTexture);

    GLuint pacmanTexture;
    glGenTextures(1, &pacmanTexture);

    GLuint blinkyTexture;
    glGenTextures(1, &blinkyTexture);

    GLuint clydeTexture;
    glGenTextures(1, &clydeTexture);

    GLuint inkyTexture;
    glGenTextures(1, &inkyTexture);

    GLuint pinkyTexture;
    glGenTextures(1, &pinkyTexture);

    GLuint coeurTexture;
    glGenTextures(1, &coeurTexture);

    GLuint menu1Texture;
    glGenTextures(1, &menu1Texture);

    GLuint menu2Texture;
    glGenTextures(1, &menu2Texture);

    GLuint menu3Texture;
    glGenTextures(1, &menu3Texture);

    GLuint echap1Texture;
    glGenTextures(1, &echap1Texture);

    GLuint echap2Texture;
    glGenTextures(1, &echap2Texture);

    GLuint echap3Texture;
    glGenTextures(1, &echap3Texture);

    GLuint over1Texture;
    glGenTextures(1, &over1Texture);

    GLuint over2Texture;
    glGenTextures(1, &over2Texture);

    GLuint over3Texture;
    glGenTextures(1, &over3Texture);

    GLuint dotTexture;
    glGenTextures(1, &dotTexture);

    glBindTexture(GL_TEXTURE_2D, spaceTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageSpace->getWidth(), pImageSpace->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageSpace->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, pacmanTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImagePacman->getWidth(), pImagePacman->getHeight(), 0, GL_RGBA, GL_FLOAT, pImagePacman->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, blinkyTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageBlinky->getWidth(), pImageBlinky->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageBlinky->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, clydeTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageClyde->getWidth(), pImageClyde->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageClyde->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, inkyTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageInky->getWidth(), pImageInky->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageInky->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, pinkyTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImagePinky->getWidth(), pImagePinky->getHeight(), 0, GL_RGBA, GL_FLOAT, pImagePinky->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, coeurTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageCoeur->getWidth(), pImageCoeur->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageCoeur->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, menu1Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageMenu1->getWidth(), pImageMenu1->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageMenu1->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, menu2Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageMenu2->getWidth(), pImageMenu2->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageMenu2->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, menu3Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageMenu3->getWidth(), pImageMenu3->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageMenu3->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, echap1Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageEchap1->getWidth(), pImageEchap1->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageEchap1->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, echap2Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageEchap2->getWidth(), pImageEchap2->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageEchap2->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, echap3Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageEchap3->getWidth(), pImageEchap3->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageEchap3->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, over1Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageOver1->getWidth(), pImageOver1->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageOver1->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, over2Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageOver2->getWidth(), pImageOver2->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageOver2->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, over3Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageOver3->getWidth(), pImageOver3->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageOver3->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, dotTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageDot->getWidth(), pImageDot->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageDot->getPixels());
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
    bool pause = false;
    int menu_choice = 3;
    int step = 0; // 0 = menu, 1 = game, 2 = echap, 3 = game over
    float degree = 0;
    float pi = 3.14159265359;

    char dir = 'q';

    for (int numLevel = 1; numLevel < 100; numLevel++) {

        board->load();
        while (loop && board->getPacman()->getLeftDots() != 0) {
            // Event loop:
            SDL_Event e;
            while (windowManager.pollEvent(e)) {
                switch (e.type) {
                    case SDL_QUIT:
                        loop = false;
                        break;
                    case SDL_KEYDOWN:
                        switch (e.key.keysym.sym) {
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
                            case SDLK_c:
                                if (camera_choice == 1)
                                    camera_choice = 3;
                                else
                                    camera_choice = 1;
                                break;
                            case SDLK_ESCAPE:
                                pause = !pause;
                                if(step == 2) {
                                    step = 1;
                                }
                                else {
                                    step = 2;
                                }
                                break;
                            case SDLK_UP:
                                degree += 0.1;
                                //std::cout << degree << std::endl;
                                    if(menu_choice < 2)
                                        menu_choice += 1;
                                break;
                            case SDLK_DOWN:
                                degree -= 0.1;
                                //std::cout << degree << std::endl;
                                if (menu_choice > 1)
                                        menu_choice -= 1;
                                break;
                            case SDLK_KP_ENTER:
                                if(step == 0 || step == 2) {
                                    if(menu_choice == 2) {
                                        step = 1; // On entre dans le jeu
                                        pause = false;
                                        menu_choice = 3; // reinit
                                    }

                                    else
                                        return EXIT_SUCCESS; // On quitte le jeu
                                }
                                else if(step == 3) { // Game over
                                    if(menu_choice == 2) {
                                        step = 0; // On revient au menu
                                        menu_choice = 3; // reinit
                                    }
                                    else
                                        return EXIT_SUCCESS; // On quitte le jeu
                                }
                                break;
                            case SDLK_RETURN:
                                if(step == 0 || step == 2) {
                                    if(menu_choice == 2) {
                                        step = 1; // On entre dans le jeu
                                        pause = false;
                                        menu_choice = 3; // reinit
                                    }

                                    else
                                        return EXIT_SUCCESS; // On quitte le jeu
                                }
                                else if(step == 3) { // Game over
                                    if(menu_choice == 2) {
                                        step = 0; // On revient au menu
                                        menu_choice = 3; // reinit
                                    }
                                    else
                                        return EXIT_SUCCESS; // On quitte le jeu
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }

            previousMousePosition = mousePosition;

            if(!pause) {
                board->getPacman()->move(dir);
                board->checkForDeath();
                if (!board->getPacman()->getLives()) {
                    step = 3;
                }
                board->moveGhosts();
                board->checkForDeath();
                if (!board->getPacman()->getLives()) {
                    step = 3;
                }
                if (!loop)
                    break;
                board->handleModes();
            }

            /*********************************
             * HERE SHOULD COME THE RENDERING CODE
             *********************************/

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            switch(step) {
                case 0: {
                    // Menu
                    MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0.2));
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(16 / 9, 1, 1));
                    MVMatrix = glm::rotate(MVMatrix, pi/2, glm::vec3(0, 1, 0));
                    MVMatrix = glm::rotate(MVMatrix, pi/2, glm::vec3(1, 0, 0));

                    glBindVertexArray(vao);

                    texProgram.m_Program.use();
                    glUniform1i(texProgram.uTexture, 0);

                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                    glActiveTexture(GL_TEXTURE0);
                    switch (menu_choice) {
                        case 3:
                            glBindTexture(GL_TEXTURE_2D, menu1Texture);
                            break;
                        case 2:
                            glBindTexture(GL_TEXTURE_2D, menu2Texture);
                            break;
                        case 1:
                            glBindTexture(GL_TEXTURE_2D, menu3Texture);
                            break;
                        default:
                            break;
                    }

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);
                    break;
                }
                case 1: {
                    // Game

                    // Nombre de vies
                    MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-3.2,-1.7,-3));
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2));
                    MVMatrix = glm::rotate(MVMatrix, pi/2, glm::vec3(1, 0, 0));

                    glBindVertexArray(vao);

                    for (int i=0; i<board->getPacman()->getLives(); i++) {
                        texProgram.m_Program.use();
                        glUniform1i(texProgram.uTexture, 0);

                        glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                           glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                        glActiveTexture(GL_TEXTURE0);

                        glBindTexture(GL_TEXTURE_2D, coeurTexture);

                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D, 0);

                        MVMatrix = glm::translate(MVMatrix, glm::vec3(2.2,0,0));
                    }

                    glBindVertexArray(0);

                    /* On récupère la ViewMatrix de la caméra à chaque tour de boucle */
                    glm::mat4 globalMVMatrix;
                    if (camera_choice == 1)
                        globalMVMatrix = camera1.getViewMatrix();
                    else
                        globalMVMatrix = camera3.getViewMatrix();

                    /* Environment */

                    MVMatrix = glm::translate(globalMVMatrix, glm::vec3(0, 0, 0));
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(30, 30, 30));

                    glBindVertexArray(vao2);

                    texProgram.m_Program.use();
                    glUniform1i(texProgram.uTexture, 0);

                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, spaceTexture);

                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);

                    /* Plateau de jeu */

                    for (int i = 0; i < board->getLevelHeight(); i++) {
                        MVMatrix = glm::scale(globalMVMatrix, glm::vec3(0.15, 0.15, 0.15));
                        MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, 2 * i));

                        for (int j = 0; j < board->getLevelWidth(); j++) {
                            MVMatrix = glm::translate(MVMatrix, glm::vec3(2, 0, 0));

                            switch (board->getLevel()[i][j]) {
                                case 0:
                                    // Empty case
                                    break;
                                case 1:
                                    // Dot case
                                    MVMatrix = glm::scale(MVMatrix, glm::vec3(0.25, 0.25, 0.25));
                                    glBindVertexArray(vao2);

                                    texProgram.m_Program.use();
                                    glUniform1i(texProgram.uTexture, 0);

                                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(ProjMatrix * MVMatrix));
                                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, dotTexture);

                                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, 0);

                                    glBindVertexArray(0);
                                    MVMatrix = glm::scale(MVMatrix, glm::vec3(4.0, 4.0, 4.0));
                                    break;
                                case 2:
                                    // Pellet case
                                    MVMatrix = glm::scale(MVMatrix, glm::vec3(0.5, 0.5, 0.5));

                                    glBindVertexArray(vao2);

                                    texProgram.m_Program.use();
                                    glUniform1i(texProgram.uTexture, 0);

                                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(ProjMatrix * MVMatrix));
                                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, dotTexture);

                                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, 0);

                                    glBindVertexArray(0);
                                    MVMatrix = glm::scale(MVMatrix, glm::vec3(2.0, 2.0, 2.0));
                                    break;
                                case 3:
                                    // Bonus fruit case
                                    break;
                                case 4:
                                    // Edge
                                    glBindVertexArray(vao);
                                    normalProgram.m_Program.use();
                                    glUniformMatrix4fv(normalProgram.uMVPMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(ProjMatrix * MVMatrix));
                                    glUniformMatrix4fv(normalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                                    glUniformMatrix4fv(normalProgram.uNormalMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
                                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
                                    glBindVertexArray(0);
                                    break;
                                case 10:
                                    // Pacman

                                    camera3.setX(j * -0.325);
                                    camera3.setY(0.20 + i * 0.205);
                                    camera3.setZ(-2 + i * -0.29);

                                    glBindVertexArray(vao2);

                                    switch (board->getPacman()->getDir()) {
                                        case 's':
                                            MVMatrix = glm::rotate(MVMatrix, pi, glm::vec3(0, 1, 0));
                                            break;
                                        case 'q':
                                            MVMatrix = glm::rotate(MVMatrix, pi/2, glm::vec3(0, 1, 0));
                                            break;
                                        case 'd':
                                            MVMatrix = glm::rotate(MVMatrix, -pi/2, glm::vec3(0, 1, 0));
                                            break;
                                    }

                                    texProgram.m_Program.use();
                                    glUniform1i(texProgram.uTexture, 0);

                                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(ProjMatrix * MVMatrix));
                                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, pacmanTexture);

                                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, 0);

                                    switch (board->getPacman()->getDir()) {
                                        case 's':
                                            MVMatrix = glm::rotate(MVMatrix, -pi, glm::vec3(0, 1, 0));
                                            break;
                                        case 'q':
                                            MVMatrix = glm::rotate(MVMatrix, -pi/2, glm::vec3(0, 1, 0));
                                            break;
                                        case 'd':
                                            MVMatrix = glm::rotate(MVMatrix, pi/2, glm::vec3(0, 1, 0));
                                            break;
                                    }

                                    glBindVertexArray(0);
                                    break;
                                case 11:
                                    // Ghost Blinky
                                    glBindVertexArray(vao2);

                                    texProgram.m_Program.use();
                                    glUniform1i(texProgram.uTexture, 0);

                                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(ProjMatrix * MVMatrix));
                                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, blinkyTexture);

                                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, 0);

                                    glBindVertexArray(0);
                                    break;
                                case 12:
                                    // Ghost Pinky
                                    glBindVertexArray(vao2);

                                    texProgram.m_Program.use();
                                    glUniform1i(texProgram.uTexture, 0);

                                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(ProjMatrix * MVMatrix));
                                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, pinkyTexture);

                                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, 0);

                                    glBindVertexArray(0);
                                    break;
                                case 13:
                                    // Ghost Inky
                                    glBindVertexArray(vao2);

                                    texProgram.m_Program.use();
                                    glUniform1i(texProgram.uTexture, 0);

                                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(ProjMatrix * MVMatrix));
                                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, inkyTexture);

                                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, 0);

                                    glBindVertexArray(0);
                                    break;
                                case 14:
                                    // Ghost Clyde
                                    glBindVertexArray(vao2);

                                    texProgram.m_Program.use();
                                    glUniform1i(texProgram.uTexture, 0);

                                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(ProjMatrix * MVMatrix));
                                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, clydeTexture);

                                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                                    glActiveTexture(GL_TEXTURE0);
                                    glBindTexture(GL_TEXTURE_2D, 0);

                                    glBindVertexArray(0);
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                    break;
                }
                case 2: {
                    // Echap
                    MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0.2));
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(16 / 9, 1, 1));
                    MVMatrix = glm::rotate(MVMatrix, pi / 2, glm::vec3(0, 1, 0));
                    MVMatrix = glm::rotate(MVMatrix, pi / 2, glm::vec3(1, 0, 0));

                    glBindVertexArray(vao);

                    texProgram.m_Program.use();
                    glUniform1i(texProgram.uTexture, 0);

                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                    glActiveTexture(GL_TEXTURE0);
                    switch (menu_choice) {
                        case 3:
                            glBindTexture(GL_TEXTURE_2D, echap1Texture);
                            break;
                        case 2:
                            glBindTexture(GL_TEXTURE_2D, echap2Texture);
                            break;
                        case 1:
                            glBindTexture(GL_TEXTURE_2D, echap3Texture);
                            break;
                        default:
                            break;
                    }

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);
                    break;
                }
                case 3: {
                    // Game over
                    MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0.2));
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(16 / 9, 1, 1));
                    MVMatrix = glm::rotate(MVMatrix, pi / 2, glm::vec3(0, 1, 0));
                    MVMatrix = glm::rotate(MVMatrix, pi / 2, glm::vec3(1, 0, 0));

                    glBindVertexArray(vao);

                    texProgram.m_Program.use();
                    glUniform1i(texProgram.uTexture, 0);

                    glUniformMatrix4fv(texProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glUniformMatrix4fv(texProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(texProgram.uNormalMatrix, 1, GL_FALSE,
                                       glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

                    glActiveTexture(GL_TEXTURE0);
                    switch (menu_choice) {
                        case 3:
                            glBindTexture(GL_TEXTURE_2D, over1Texture);
                            break;
                        case 2:
                            glBindTexture(GL_TEXTURE_2D, over2Texture);
                            break;
                        case 1:
                            glBindTexture(GL_TEXTURE_2D, over3Texture);
                            break;
                        default:
                            break;
                    }

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);
                    break;
                }
                default:
                    break;
            }

            // Update the display
            windowManager.swapBuffers();
        }
    }

    glDeleteTextures(1, &spaceTexture);
    glDeleteTextures(1, &pacmanTexture);
    glDeleteTextures(1, &blinkyTexture);
    glDeleteTextures(1, &clydeTexture);
    glDeleteTextures(1, &inkyTexture);
    glDeleteTextures(1, &pinkyTexture);
    glDeleteTextures(1, &coeurTexture);
    glDeleteTextures(1, &menu1Texture);
    glDeleteTextures(1, &menu2Texture);
    glDeleteTextures(1, &menu3Texture);
    glDeleteTextures(1, &echap1Texture);
    glDeleteTextures(1, &echap2Texture);
    glDeleteTextures(1, &echap3Texture);
    glDeleteTextures(1, &over1Texture);
    glDeleteTextures(1, &over2Texture);
    glDeleteTextures(1, &over3Texture);
    glDeleteTextures(1, &dotTexture);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glDeleteBuffers(1, &vbo2);
    glDeleteVertexArrays(1, &vao2);

    delete board;

    return EXIT_SUCCESS;
}
