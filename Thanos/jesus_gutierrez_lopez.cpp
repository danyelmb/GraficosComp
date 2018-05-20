#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <SOIL.h>

void gaunlet();
void ejes();
void initFunc();
void ironman();

void drawObject(GLfloat s, GLint c);
void myMesh(GLfloat r, GLint Ni, GLint Nj);
void myVbo();
void destroyFunc();
void funReshape(int w, int h);
void funDisplay();
void funIdle();
void drawCube();
void repeat(int time);
void drawLights();
void drawTriangulo(char color);
void MyKeyboardFunc(unsigned char Key, int x, int y);
void mouseWheel(int,int ,int ,int);
void funKeyboard(int key, int x, int y);

using namespace std;

typedef struct {
    vector<GLfloat>  vCoords;
    vector<GLfloat>  nCoords;
    vector<GLfloat>  tCoords;
    vector<GLushort> iCoords;
} Tmesh;
Tmesh createMesh(GLfloat r, GLint Ni, GLint Nj);
GLsizei meshSize;
        
//GLfloat M_PI=3.14;
// Variables globales
int w = 600;
int h = 600;
unsigned char light='0';
bool mind=0;
GLfloat desZ = 0.0f;
GLfloat rotY_green =  0.0f;
GLfloat rotX_green =  0.0f;
GLfloat rotZ_green =  0.0f;
GLfloat luz_r=  0.0f;    
GLfloat luz_v =  0.0f;
GLfloat luz_b =  0.0f;

GLfloat Lp =  0.0f;
GLfloat rotY_base =  0.0f;
GLfloat rotX_base =  0.0f;
GLfloat rotZ_base =  0.0f;
GLfloat fovy= 60.0f;
GLfloat Y_camera =  0.0f;
GLfloat X_camera =  0.0f;
GLfloat Z_camera =  0.0f;
float deltaAngle = 0.0f;
int xOrigin = -1;
float angle = 60.0f;
int soul=0;


GLfloat scale =  1.0f;
GLfloat tele1 = 0.0f;
GLfloat tele2 = 0.0f;
GLfloat tele3 = 0.0f;
GLfloat translateX =  0.0f;
GLfloat translateY =  0.0f;
GLfloat translateZ =  0.0f;
GLfloat DL0[] = { 1.0f, 0.0f, -1.0f, 0.0f };
GLfloat PL1[] = {0,0.2,2.3,1.0f};
int xO,yO;
#define NT 6
GLuint  objTexture[NT];

#define NB 4

GLuint  myDisplayList;
GLuint  VBO[NB];
void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	// only start motion if the left button is pressed
if (button == GLUT_LEFT_BUTTON) {

// when the button is released
if (state == GLUT_UP) {
xOrigin = -1;
}
else {// state = GLUT_DOWN
xOrigin = x;
xO=x;
yO=y;
}
}
}
GLfloat old_y=2,old_x=-3;

 

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	  
if (xOrigin != -1) {
		// update camera's direction
		X_camera =(xO-x)/5 ;

		Y_camera =(yO-y)/5 ;
}

   glutPostRedisplay();

}


void base(){
       GLfloat Ka[] = { 1,1,1, 0.6f };	
   GLfloat Kd[] = { 1,1,1 ,0.6f }; 
   GLfloat Ks[] = { 1,1,1, 0.6f };
     glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);	     
     glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);	    
     glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);	     
             glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glBindTexture(GL_TEXTURE_2D, objTexture[0]);
    glDepthMask(GL_FALSE);
      glutSolidCylinder(0.5,0.2,50,50);  
     glDepthMask(GL_TRUE);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_2D);
   
}
int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 4");
    
 // Inicializamos GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) printf("Error: %s\n", glewGetErrorString(err));
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    printf("This system supports OpenGL Version: %s\n", oglVersion);
    
 // Inicializaciones especÃ­ficas
    initFunc();
    
 // ConfiguraciÃ³n CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutSpecialFunc(funKeyboard);
    glutMouseWheelFunc(mouseWheel);
    glutMouseFunc(mouseButton);
    glutMotionFunc (mouseMove);
    glutTimerFunc(10, repeat, 0);
    
    glutKeyboardFunc(MyKeyboardFunc);
  //  glutIdleFunc(funIdle);
 // Bucle principal
    glutMainLoop();
    
    return 0;
}

void initFunc() {
  
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);

 // Modelo de Iluminación
    glEnable(GL_LIGHTING);
    
 // Parámetros de la Luz ambiental global
    GLfloat IA[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, IA);

 // Parámetros de la Luz 0 (direccional=sol)
    GLfloat Ia0[] = { 0.1f, 0.1f, 0.1f, 0.1f };
    GLfloat Id0[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    GLfloat Is0[] = { 0.3f, 0.3f, 0.3f, 0.3f };
    glLightfv(GL_LIGHT0, GL_AMBIENT , Ia0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , Id0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Is0);
    glEnable(GL_LIGHT0);

 
   // 1==> MIND
    GLfloat Ia11[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id1[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    GLfloat Is1[] = { 0.9f, 0.9f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT , Ia11);
    glLightfv(GL_LIGHT1, GL_DIFFUSE , Id1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Is1);
    glEnable(GL_LIGHT1);
  // 2==> TIME
    GLfloat Ia2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id2[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    GLfloat Is2[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightfv(GL_LIGHT2, GL_AMBIENT , Ia2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE , Id2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, Is2);
  
      // Parámetros de la Luz 2 (Spotligth=foco)
    GLfloat Ia3[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id3[] = { 1.0f, 0.5f, 0.0f, 1.0f };
    GLfloat Is3[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightfv(GL_LIGHT3, GL_AMBIENT , Ia3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE , Id3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, Is3);
    
      // Parámetros de la Luz 2 (Spotligth=foco)
    GLfloat Ia4[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id4[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat Is4[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightfv(GL_LIGHT4, GL_AMBIENT , Ia4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE , Id4);
    glLightfv(GL_LIGHT4, GL_SPECULAR, Is4);
      // Parámetros de la Luz 2 (Spotligth=foco)
    GLfloat Ia5[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id5[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat Is5[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightfv(GL_LIGHT5, GL_AMBIENT , Ia5);
    glLightfv(GL_LIGHT5, GL_DIFFUSE , Id5);
    glLightfv(GL_LIGHT5, GL_SPECULAR, Is5);
      // Parámetros de la Luz 2 (Spotligth=foco)
    GLfloat Ia6[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id6[] = { 1.0f, 0.0f, 1.0f, 1.0f };
    GLfloat Is6[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightfv(GL_LIGHT6, GL_AMBIENT , Ia6);
    glLightfv(GL_LIGHT6, GL_DIFFUSE , Id6);
    glLightfv(GL_LIGHT6, GL_SPECULAR, Is6);
    
 // Modelo de Sombreado
    glShadeModel(GL_SMOOTH);
    
 // Normalizado de coordenadas normales
    glEnable(GL_NORMALIZE);
     
 // Texturas
    glGenTextures(NT,objTexture);
    const char *fileName[NT] = {"common/img/galaxia.bmp","common/img/orange2.bmp","common/img/ironman.bmp","common/img/vision.bmp","common/img/spidy.bmp","common/img/scarlet.bmp"};
    for(unsigned i=0; i<NT; i++) {
     // Seleccionamos la textura a configurar
        glBindTexture(GL_TEXTURE_2D, objTexture[i]);
     // Cargamos la textura (SOIL)
        int textureW, textureH;
        unsigned char* texture = SOIL_load_image(fileName[i], &textureW, &textureH, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureW, textureH, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(texture); 
     // Configuramos la textura
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

 // Transparencia
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    // Display Lists para almacenar los objetos una vez creados
    myDisplayList = glGenLists(1);
    glNewList(myDisplayList, GL_COMPILE);
        myMesh(2.0f,200,200);
    glEndList();

 // VBO's para almacenar los objetos una vez creados y dejarlos en la GPU
    Tmesh mesh = createMesh(2.0f,200,200);
    meshSize = mesh.iCoords.size();
    glGenBuffers(NB,VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh.vCoords.size(), &(mesh.vCoords.front()), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh.nCoords.size(), &(mesh.nCoords.front()), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh.tCoords.size(), &(mesh.tCoords.front()), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*mesh.iCoords.size(), &(mesh.iCoords.front()), GL_STATIC_DRAW);

    
}

void destroyFunc() {
    
    glDeleteTextures(NT,objTexture);
    
}
 
void funReshape(int wnew, int hnew) {
    
 // ConfiguraciÃ³n del Viewport
    glViewport(0, 0, wnew, hnew);

 // Captura de w y h
    w = wnew;
    h = hnew;
    
}
GLfloat  zoom = 0;
void funDisplay() {
    
 // Borramos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
 // Para configurar la matriz matriz P
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
 // Matriz de ProyecciÃ³n P (CÃ¡mara)
  GLfloat fovy = 60, aspectRatio = (GLfloat)w/(GLfloat)h, nplane = 0.1f, fplane = 20.0f;
  gluPerspective(fovy+zoom,aspectRatio,nplane,fplane);
  // Or whatever you want the step to be
 // You had GL_MODELVIEW
//glOrtho(-1.5 + zoom, 1.0 - zoom, -2.0 + zoom, 0.5 - zoom, -1.0, 3.5)
    // GLfloat left = -1.0f, right = 1.0f, bottom = -1.0f, top = 1.0f;
  // glOrtho(left+zoom,right-zoom,bottom+zoom,top-zoom,nplane,fplane);	
//glFrustum(left,right,bottom,top,nplane,fplane);
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
     
        light='1';
      // Matriz de Vista V (CÃ¡mara)
    GLfloat eye[3]    = {   3.0f*cos(X_camera*M_PI/180.0f)*sin(Y_camera*M_PI/180.0f),
                            3.0f*sin(Y_camera*M_PI/180.0f),
                            3.0f*cos(Y_camera*M_PI/180.0f)*cos(X_camera*M_PI/180.0f)};
    GLfloat center[3] = {0.0f,  0.0f, 0.0f};
    GLfloat up[3]     = {0.0f,  1.0f,  0.0f};
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                   up[0],     up[1],     up[2]);

          
            glTranslatef( 0,-0.5,+2);
    // Definimos el material del objeto
  
    glPushMatrix();
    glRotatef(30,1,0,0);
    glScalef(0.25,0.25,0.25);
    gaunlet();
    glPopMatrix();
            //glutSolidSphere(0.05,50,50);
    glPopMatrix();
    drawLights();
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);  glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glBindTexture(GL_TEXTURE_2D, objTexture[soul]);
    glPushMatrix();
        
    //glScalef(-1,-1,-1);
    glutSolidSphere(10.0f, 50,50);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_2D);
         glPushMatrix();
         
    glTranslatef(-1,1,-2);
    glRotatef(rotY_base,1,1,1);
    glTranslatef(1,0,0);
    
    glScalef(0.25,0.25,0.25);
    glTranslatef(translateX,translateY,translateZ);
    glScalef(scale,scale,scale);
    drawObject(1,1);
    glPopMatrix();
   
   // Intercambiamos los buffers
    glutSwapBuffers();
    
}
void drawCube() {
    
 // Definimos el cubo
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, objTexture[4]);
    
    glBegin(GL_QUADS);
     // CARA DERECHA (x = 1)
        glNormal3f( 1.0f,  0.0f,  0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f); 
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f); 
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f); 
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);   
            glEnd();
            
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, objTexture[4]);
    
        glBegin(GL_QUADS);
     // CARA IZQUIERDA (x = -1)
        glNormal3f(-1.0f,  0.0f,  0.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
            glEnd();
    
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, objTexture[4]);
    
        glBegin(GL_QUADS);
     // CARA SUPERIOR (y = 1)
        glNormal3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f); 
        glVertex3f(-1.0f,  1.0f,  1.0f);
            glEnd();
    
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, objTexture[4]);
    
        glBegin(GL_QUADS);
     // CARA INFERIOR (y = -1)
        glNormal3f( 0.0f, -1.0f,  0.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);    
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);    
        glVertex3f( 1.0f, -1.0f, -1.0f);
            glEnd();
    
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, objTexture[2]);
    
        glBegin(GL_QUADS);
     // CARA DELANTERA (z = 1)
        glNormal3f( 0.0f,  0.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
            glEnd();
    
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, objTexture[4]);
    
        glBegin(GL_QUADS);
     // CARA TRASERA (z = -1)
        glNormal3f( 0.0f,  0.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);  
        glVertex3f( 1.0f, -1.0f, -1.0f);
            glEnd();
    
        glDisable(GL_TEXTURE_2D);
}
void funKeyboard(int key, int x, int y) {
    
    switch(key) {
        case GLUT_KEY_UP:
            luz_r+= 0.1;
            glDisable(GL_LIGHT1);
            glEnable(GL_LIGHT2);
            if(luz_r<=+1){
               luz_r=+1;
            }
            translateY+=1.0f;
            break;
        case GLUT_KEY_DOWN:
            glDisable(GL_LIGHT2);
            glEnable(GL_LIGHT3);
            luz_r -= 5.0f;
            if(luz_r>=0){
               luz_r=0;
            }
            translateY-=1.0f;
            break;
        case GLUT_KEY_RIGHT:
             glDisable(GL_LIGHT3);
              glEnable(GL_LIGHT4);
            rotY_green += 5.0f;
             if(rotY_green>=+130){
                rotY_green=+130;
            }
            translateX+=5.0f;
            break;
        case GLUT_KEY_LEFT: 
            glDisable(GL_LIGHT4);
             glEnable(GL_LIGHT5);
            rotY_green -= 5.0f;
            if(rotY_green<=-130){
               rotY_green=-130;
            }translateX-=5.0f;
           
            break;
      
    }
    
    glutPostRedisplay();
      
}
void mouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
        // Zoom in
        zoom-=1;
           if (zoom>-10.25f){
        zoom = 10.25f;
        }
    }else{
        // Zoom out
        zoom+=1;
        if (zoom<10.25f){
            zoom = 10.25f;
        }
    }

   glutPostRedisplay();
}
void funIdle() {
    
  
    
}
bool r=false;
void repeat(int t){
    //Sleep(10);
    if(mind){
        rotY_base+=5;
    }
    if(r){
       Lp+=1;
       if(Lp>=90){
           r=false;
           Lp=90;
        }
    }else{
        Lp-=1;
        if(Lp<=-90){
            r=true;
            Lp=-90;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(30, repeat, 0);
 
}

void drawLights() {
    
 // Luz 0: Direccional
    glLightfv(GL_LIGHT0, GL_POSITION, DL0);
    
    glPushMatrix();
 // Luz 1: Posicional
    glRotatef(Lp,0,1,0);
    
    glLightfv(GL_LIGHT1, GL_POSITION, PL1);
    
    glLightfv(GL_LIGHT2, GL_POSITION, PL1);
    
    glLightfv(GL_LIGHT3, GL_POSITION, PL1);
    
    glLightfv(GL_LIGHT4, GL_POSITION, PL1);
    
    glLightfv(GL_LIGHT5, GL_POSITION, PL1);
    
    glLightfv(GL_LIGHT6, GL_POSITION, PL1);
    
    glPopMatrix();

}
int luz_p=1,luz_f=1,luz_a=1;

void turnoff(unsigned char Key){
      switch(Key) {
        
        case '1':
              glDisable(GL_LIGHT1); break;
        case '2': 
              glDisable(GL_LIGHT2); break;
        case '3': 
              glDisable(GL_LIGHT3); break;
        case '4': 
              glDisable(GL_LIGHT4); break; 
        case '5': 
              glDisable(GL_LIGHT5); break;
        case '6': 
              glDisable(GL_LIGHT6); break;
    }
    glutPostRedisplay();
}
void MyKeyboardFunc(unsigned char Key, int x, int y){
    
    switch(Key) {
        
        case 'a':
            turnoff(light);
            break;
        
        case 'A':
            turnoff(light);
            break;
          
        case 'o':
            turnoff(light);
            light='3';
            glEnable(GL_LIGHT3);
            soul=1;
            break;
        case 'O':
            turnoff(light);
            soul=0;
            break;
            
        case 'P':
            turnoff(light);
            light='6';
            glEnable(GL_LIGHT6);
            desZ+=1;
            if(desZ<=+50){
                desZ=+50;
            }
            break;
            
        case 'p':
            turnoff(light);
            light='6';
            glEnable(GL_LIGHT6);
            desZ-=1;
            if(desZ<=-50){
                desZ=-50;
            }
            break;
            
        case 'l': 
            if(luz_a){
                luz_a=0;
                glDisable(GL_LIGHT0);
            }else{ 
                luz_a=1;
                glEnable(GL_LIGHT0);}
            break;
            
        case 'r': 
            mind=0;
            turnoff(light);
            light='4';
            glEnable(GL_LIGHT4);
            if(scale<3.0f){
                scale +=  0.1f;
            }
            if(scale<1.0f){
                scale += 0.1f;
            }
            break;
            
        case 'R': 
            mind=0;
            turnoff(light);
            light='4';
            glEnable(GL_LIGHT4);
            if(scale>0.1f){
                scale -= 0.1f;
            }
            if(scale>1.0f){
                scale -= 0.1f;
            } 
            break;
            
        case 's':  
            mind=0;
            turnoff(light);
            light='5';
            glEnable(GL_LIGHT5); 
            tele1 += 11.25;
            tele2 += 11.25;
            tele3 += 11.25;
            break;
            
        case 'S':  
            mind=0;
            turnoff(light);
            light='5';
            glEnable(GL_LIGHT5);
            tele1 -= 11.25;
            tele2 -= 11.25;
            tele3 -= 11.25;
            
            break;
        
        case 'm': 
            mind=1;
            turnoff(light);
            light='1';
            glEnable(GL_LIGHT1);
            break;
            
        case 'M': 
            mind=1;
            turnoff(light);
            light='1';
            glEnable(GL_LIGHT1);
            break;
       
        case 't': 
            desZ=0;
            soul=0;
            mind=0;
            turnoff(light);
            light='2';
            glEnable(GL_LIGHT2);
            scale=1;
            break;
        
        case 'z':
            if(desZ>-50){
                desZ=desZ-3;
            }
            break;
            
        case'Z':
            if(desZ<50){
                desZ=desZ+3;
            }
            break;
            
    }
    glutPostRedisplay();
    
}
//Gemas
void realityGem(){
     glPushMatrix();
     glTranslatef(-0.8,0,-0.5);
     glRotatef(30,0,1,0);
    GLUquadricObj *obj = gluNewQuadric();
    glutSolidSphere(0.3,50,50);
     glTranslatef(0,0,-0.63);
    gluCylinder(obj, 0.2, 0.27, 0.5, 100, 100);
    glRotatef(desZ,1,0,0);
    glutSolidSphere(0.2,50,50);
       glTranslatef(0,0,-0.50);
    gluCylinder(obj, 0.1, 0.17, 0.4, 100, 100);
    glutSolidSphere(0.1,50,50);
       glTranslatef(0,0,-0.20);
    gluCylinder(obj, 0.01, 0.1, 0.2, 100, 100);
    glPopMatrix();
}
void powerGem(){
      glPushMatrix();
     glTranslatef(-0.3,0,-0.8);
     glRotatef(10,0,1,0);
    GLUquadricObj *obj = gluNewQuadric();
    glutSolidSphere(0.3,50,50);
     glTranslatef(0,0,-0.63);
    gluCylinder(obj, 0.2, 0.27, 0.5, 100, 100);
    glRotatef(desZ,1,0,0);
   
    glutSolidSphere(0.2,50,50);
       glTranslatef(0,0,-0.50);
    gluCylinder(obj, 0.1, 0.17, 0.4, 100, 100);
    glutSolidSphere(0.1,50,50);
       glTranslatef(0,0,-0.20);
    gluCylinder(obj, 0.01, 0.1, 0.2, 100, 100);
     glPopMatrix();
}
void spaceGem(){
      glPushMatrix();
     glTranslatef(0.3,0,-1);
    GLUquadricObj *obj = gluNewQuadric();
    glutSolidSphere(0.3,50,50);
     glTranslatef(0,0,-0.63);
    
   gluCylinder(obj, 0.2, 0.27, 0.5, 100, 100);
   
      glRotatef(desZ,1,0,0);
    glutSolidSphere(0.2,50,50);
       glTranslatef(0,0,-0.50);
    gluCylinder(obj, 0.1, 0.17, 0.4, 100, 100);
    glutSolidSphere(0.1,50,50);
       glTranslatef(0,0,-0.20);
    gluCylinder(obj, 0.01, 0.1, 0.2, 100, 100);
     glPopMatrix();
}
void soulGem(){
  glPushMatrix();
     glTranslatef(0.8,0,-0.6);
     glRotatef(-30,0,1,0);
   
    GLUquadricObj *obj = gluNewQuadric();
    glutSolidSphere(0.3,50,50);
     glTranslatef(0,0,-0.63);
    gluCylinder(obj, 0.2, 0.27, 0.5, 100, 100);
     glRotatef(desZ,1,0,0);
   
    glutSolidSphere(0.2,50,50);
       glTranslatef(0,0,-0.50);
    gluCylinder(obj, 0.1, 0.17, 0.4, 100, 100);
    glutSolidSphere(0.1,50,50);
       glTranslatef(0,0,-0.20);
    gluCylinder(obj, 0.01, 0.1, 0.2, 100, 100);
     glPopMatrix();
}
void timeGem(){
      glPushMatrix();
     glTranslatef(0.6,0.3,0);
     
    glRotatef(-75,0,1,0);

    GLUquadricObj *obj = gluNewQuadric();
    glutSolidSphere(0.3,50,50);
     glTranslatef(0,0,-0.63);
    
    gluCylinder(obj, 0.2, 0.27, 0.5, 100, 100);
      glRotatef(30,0,1,0);
    glutSolidSphere(0.2,50,50);
       glTranslatef(0,0,-0.50);
    gluCylinder(obj, 0.01, 0.17, 0.4, 100, 100);
      glPopMatrix();
   
}
void gem(){
      GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 1,1, 1.0f, 1.0f };
    GLfloat Ks[] = { 1,1,1, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
              glutSolidSphere(0.5,50,50);
              
               GLfloat Kc[] = {  0.24725f, 0.2245f, 0.0645f, 1.0f };
    GLfloat Kf[] = { 0.34615f, 0.3143f, 0.0903f, 1.0f };
    GLfloat Kv[] = {0.797357f, 0.723991f, 0.208006f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Kc);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kf);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Kv);
    glMaterialf (GL_FRONT, GL_SHININESS, 83.2f);
}
void mindGem(){ 
     glutSolidSphere(1,50,50); 
     glPushMatrix();
     glTranslatef(0,0.9,0);
     
 // Luz 2: Foco
     glScalef(0.5,0.35,0.5);
     gem();
     glPopMatrix();
     
     glRotatef(30,1,0,0);
     glRotatef(desZ,1,0,0);
     timeGem();
     
    
     soulGem();
     
    
     spaceGem();
     
 
     realityGem();
     
   
     powerGem();
     
     
 
}

//Guante
void gaunlet(){
    
    GLfloat Kc[] = {  0.24725f, 0.2245f, 0.0645f, 1.0f };
    GLfloat Kf[] = { 0.34615f, 0.3143f, 0.0903f, 1.0f };
    GLfloat Kv[] = {0.797357f, 0.723991f, 0.208006f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Kc);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kf);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Kv);
    glMaterialf (GL_FRONT, GL_SHININESS, 83.2f);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 0.8, 1, 2, 100, 100);
    glPushMatrix();
     glScalef(1,0.8,1);
     
    mindGem();
    glPopMatrix();
//    //gluCylinder(obj, 1.0, 1, 3, 30, 30);
}

//Esferas
void iron(){
    // Definimos el material del objeto
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
     glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, objTexture[2]);
   
    glPushMatrix();
        glTranslatef(-4.0f, 0.0f, -5.0f);
   
        glRotatef(90,0,1,0);

      
        myVbo();
    glPopMatrix();
}
void vision(){
// Definimos el material del objeto
    GLfloat Kf[] = { 0.2f, 0.2f, 0.2f, 0.5f };
    GLfloat Kg[] = { 0.9f, 0.9f, 0.9f, 0.5f };
    GLfloat Kh[] = { 0.9f, 0.9f, 0.9f, 0.5f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Kf);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kg);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Kh);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objTexture[3]);
   
    glPushMatrix();
        glTranslatef(2.0f, 0.0f, 0.0f);
        glRotatef(90,0,1,0);
      
        myVbo();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void spidy(){
    // Definimos el material del objeto
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 0.0f, 0.0f, 0.9f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, objTexture[4]);
    glPushMatrix();
        glTranslatef(0,4,-2.5);
        glRotatef(Lp,0,0,1);
        glTranslatef(0,-4,0);
        glScalef(0.25,0.25,0.25);
        myVbo();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}
void witch(){
    // Definimos el material del objeto
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 0.9f, 0.0f, 0.9f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, objTexture[5]);
    glPushMatrix();
        glTranslatef(2.0f, 0.0f, -5.0f);
        glRotatef(90,0,1,0);
        myVbo();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}
void drawObject(GLfloat s, GLint c) {
    
 
    
 // Definimos el objeto
    glPushMatrix();
        glTranslatef(1.0f, 0.0f, 0.0f);
        glRotatef(tele1,1,0,0);
        glRotatef(tele2,0,1,0);
        glRotatef(tele3,0,0,1);
        glTranslatef(-1.0f, 0.0f, 0.0f);
        iron();
    glPopMatrix();
    
    
    glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.0f);
        glRotatef(tele1,1,1,0);
        glRotatef(tele2,0,1,1);
        glRotatef(tele3,0,1,0);
        glTranslatef(0.0f, -1.0f, 0.0f);
        witch();
    glPopMatrix();
    
    spidy();
    
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.0f);
        glRotatef(tele1,0,0,1);
        glRotatef(tele2,1,1,1);
        glRotatef(tele3,1,0,0);
        glTranslatef(0.0f, 0.0f, -1.0f);
        vision();
    glPopMatrix();

}

void myMesh(GLfloat r, GLint Ni, GLint Nj) {
    
    Tmesh mesh = createMesh(r,Ni,Nj);
    
    glBegin(GL_TRIANGLES);
        for(unsigned i=0; i<mesh.iCoords.size(); i++) {
            GLushort v = mesh.iCoords[i];
            glNormal3fv  (&mesh.nCoords[3*v]);
            glTexCoord2fv(&mesh.tCoords[2*v]);
            glVertex3fv  (&mesh.vCoords[3*v]);
        }
    glEnd();
    
}


void myVbo() {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); glVertexPointer  (3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); glNormalPointer  (   GL_FLOAT, 0, 0);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]); glTexCoordPointer(2, GL_FLOAT, 0, 0);
        
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[3]);
    glDrawElements (GL_TRIANGLES, meshSize, GL_UNSIGNED_SHORT, 0);
        
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
}
Tmesh createMesh(GLfloat r, GLint Ni, GLint Nj) {
    
    Tmesh mesh;
      
    for(GLint i=0; i<=Ni; i++) {
        GLfloat theta = M_PI*(GLfloat)i/(GLfloat)Ni;
        for(GLint j=0; j<=Nj; j++) {
            GLfloat phi = 2*M_PI*(GLfloat)j/(GLfloat)Nj;
            GLfloat x = r*sin(theta)*cos(phi);
            GLfloat y = r*cos(theta);
            GLfloat z = r*sin(theta)*sin(phi);
            mesh.vCoords.push_back(x);
            mesh.vCoords.push_back(y);
            mesh.vCoords.push_back(z);
            mesh.nCoords.push_back(x/r);
            mesh.nCoords.push_back(y/r);
            mesh.nCoords.push_back(z/r);
            GLfloat s = 1.0 - (GLfloat)j/(GLfloat)Nj;
            GLfloat t = 1.0 - (GLfloat)i/(GLfloat)Ni;
            mesh.tCoords.push_back(s);
            mesh.tCoords.push_back(t);
        }
    }  

    for(GLint i=0; i<Ni; i++) {
        for(GLint j=0; j<Nj; j++) {
            
            GLushort v1 = (Nj+1)*i     + j;
            GLushort v2 = (Nj+1)*(i+1) + j;
            
            mesh.iCoords.push_back(v1+1);
            mesh.iCoords.push_back(v2+1);
            mesh.iCoords.push_back(v2);

            mesh.iCoords.push_back(v1+1);
            mesh.iCoords.push_back(v2);
            mesh.iCoords.push_back(v1);
            
        }
    }
    
    return mesh;     
}