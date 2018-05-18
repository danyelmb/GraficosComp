#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <SOIL.h>

void ejes();
void initFunc();

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
void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);
void funKeyboard(int key, int x, int y);

using namespace std;
//GLfloat M_PI=3.14;
// Variables globales
int w = 600;
int h = 600;
unsigned char light='0';
 //Mente
bool mind=0;
GLfloat desZ = 0.0f;
GLfloat rotY_green =  0.0f;
GLfloat rotX_green =  0.0f;
GLfloat rotZ_green =  0.0f;
GLfloat luz_r=  0.0f;    
GLfloat luz_v =  0.0f;
GLfloat luz_b =  0.0f;

 //Cubos
GLfloat Lp =  0.0f;
GLfloat rotY_base =  0.0f;
GLfloat rotX_base =  0.0f;
GLfloat rotZ_base =  0.0f;
             
 //Camara
GLfloat fovy= 60.0f;
GLfloat Y_camera =  0.0f;
GLfloat X_camera =  4.0f;
GLfloat Z_camera =  0.0f;
GLfloat  zoom = 0;
int xO,yO;

float deltaAngle = 0.0f;
int xOrigin = -1;
float angle = 60.0f;

GLfloat DL0[] = { -1.0f, 0.0f, 1.0f, 0.0f };
GLfloat PL1[] = {1.5f, 2.0f,0.0f, 1.0f };

#define NT 1
GLuint  objTexture[NT];
GLfloat old_y=2,old_x=-3;



void time(){
    
    GLfloat Kq[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat K2[] = { 0.0f, 0.3f, 0.0f, 1.0f };
    GLfloat Kz[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Kq);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , K2);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Kz);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
     glutSolidSphere(0.5,50,50);
    }

void reality(){
  
    GLfloat Kp[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kl[] = { 0.5f, 0.0f, 0.0f, 1.0f };
    GLfloat Km[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Kp);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kl);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Km);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
              glutSolidSphere(0.5,50,50);  
}

void space(){
    
    GLfloat Ku[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kj[] = { 0.3f, 0.3f, 0.6f, 1.0f };
    GLfloat Kn[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ku);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kj);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Kn);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
              glutSolidSphere(0.5,50,50);
}

void soul(){
    
    GLfloat Kw[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat K1[] = { 0.5f, 0.2f, 0.01f, 1.0f };
    GLfloat Kx[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Kw);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , K1);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Kx);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
              glutSolidSphere(0.5,50,50);
}

void power(){
    
    GLfloat Kc[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kf[] = { 0.5f, 0.0f, 0.5f, 1.0f };
    GLfloat Kv[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Kc);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kf);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Kv);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
               glutSolidSphere(0.5,50,50);
}

void ejes(){
    glEnable (GL_LINE_STIPPLE);
    glLineStipple(1,255);
    glLineWidth(2.0f);
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_LINES);
    glVertex3f(-10,0,0);
    glVertex3f(10,0,0);
   
    glVertex3f(0,-10,0);
    glVertex3f(0,10,0);
    
    glVertex3f(0,0,-10);
    glVertex3f(0,0,10);
    glEnd();
    
glDisable (GL_LINE_STIPPLE);

    glLineWidth(1.0f);
}


int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Thanos");
    
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
    glPolygonOffset(1.0,1.0);

 // Modelo de Iluminación
    glEnable(GL_LIGHTING);
    
 // Parámetros de la Luz ambiental global
    GLfloat IA[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
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
    GLfloat Id3[] = { 1.0f, 0.0f, 0.5f, 1.0f };
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
    const char *fileName[NT] = {"common/img/pokeball2.bmp"};
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

 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (CÃ¡mara)
    GLfloat eye[3]    = {   3.0f*(GLfloat)cos(X_camera*M_PI/180.0f)*(GLfloat)sin(Y_camera*M_PI/180.0f),
                            3.0f*(GLfloat)sin(Y_camera*M_PI/180.0f),
                            3.0f*(GLfloat)cos(Y_camera*M_PI/180.0f)*(GLfloat)cos(X_camera*M_PI/180.0f)};
    GLfloat center[3] = {0.0,  0.0, 0.0};
    GLfloat up[3]     = {0.0,  1.0,  0.0};
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                   up[0],     up[1],     up[2]);

            glColor3f(0.0f, 0.0f, 0.0f);
            glPushMatrix();
            
            glRotatef(Lp,0,1,0);
            glTranslatef( 1.5f, 2.0f,0.0f );
           
    // Definimos el material del objeto
    GLfloat Ke[] = { luz_r,luz_v,luz_b,1};
    GLfloat Kr[] = {luz_r,luz_v,luz_b,1};
    GLfloat Kt[] = { luz_r,luz_v,luz_b,1};
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ke);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kr);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Kt);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
            glutSolidSphere(0.05,50,50);
            glPopMatrix();
    ejes();
    drawLights();
    /*
    glPushMatrix();
    glTranslatef(0,0,2);
    glColor3f(0.6f,0.6f,0.3f);
    glutSolidSphere(0.25,50,50);
    glScalef(1.0,1.0,0.25);
    glPopMatrix();
    */
    
    glPushMatrix();
    
    glTranslatef(-1,0,0);
    glRotatef(rotY_base,1,1,1);
    glTranslatef(1,0,0);
    
    glScalef(0.25,0.25,0.25);
    drawCube();
    glPopMatrix();
    glPushMatrix();
    
    glRotatef(rotY_base,-1,-1,-1);
    glTranslatef(1,0,0);
    
    glScalef(0.25,0.25,0.25);
    drawCube();
    glPopMatrix();
     glPushMatrix();
    
    glRotatef(rotY_base,-1,-1,-1);
    glTranslatef(1,0,0);
    
    glScalef(0.25,0.25,0.25);
    drawCube();
    glPopMatrix();
   // Intercambiamos los buffers
    glutSwapBuffers();
    
}
void drawCube() {
    
 // Definimos el material del cubo
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 1,1,1, 1.0f };
    GLfloat Ks[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
        
 // Definimos el cubo
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, objTexture[0]);
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
        glBegin(GL_QUADS);
     // CARA IZQUIERDA (x = -1)
        glNormal3f(-1.0f,  0.0f,  0.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
     // CARA SUPERIOR (y = 1)
        glNormal3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f); 
        glVertex3f(-1.0f,  1.0f,  1.0f);
     // CARA INFERIOR (y = -1)
        glNormal3f( 0.0f, -1.0f,  0.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);    
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);    
        glVertex3f( 1.0f, -1.0f, -1.0f);
     // CARA DELANTERA (z = 1)
        glNormal3f( 0.0f,  0.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
     // CARA TRASERA (z = -1)
        glNormal3f( 0.0f,  0.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);  
        glVertex3f( 1.0f, -1.0f, -1.0f);
    glEnd();
    
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
            break;
        case GLUT_KEY_DOWN:
            
           
             glDisable(GL_LIGHT2);
              glEnable(GL_LIGHT3);
               luz_r -= 5.0f;
             if(luz_r>=0){
                luz_r=0;
            }
            break;
        case GLUT_KEY_RIGHT:
            
             glDisable(GL_LIGHT3);
              glEnable(GL_LIGHT4);
            rotY_green += 5.0f;
             if(rotY_green>=+130){
                rotY_green=+130;
            }
            break;
        case GLUT_KEY_LEFT:
            
             glDisable(GL_LIGHT4);
              glEnable(GL_LIGHT5);
             rotY_green -= 5.0f;
             if(rotY_green<=-130){
                rotY_green=-130;
            }
           
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
        
    }
    else
    {
        // Zoom out
       
        zoom+=1;
         if ( zoom<10.25f   ){
        zoom = 10.25f;
        }
    }

   glutPostRedisplay();
}
void funIdle() {
    
  
    
}
void repeat(int t){
    //Sleep(10);
    if(mind){
        rotY_base+=5;
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
              glDisable(GL_LIGHT1);break;
        case '2': 
              glDisable(GL_LIGHT2);break;
        case '3': 
              glDisable(GL_LIGHT3);break;
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
        
        
        case 'p':
           Lp -= 3.5;
        break;
        case 'l': if(luz_a){
            luz_a=0;
              glDisable(GL_LIGHT0);
        }else{ luz_a=1;
          glEnable(GL_LIGHT0);}
        break;
        case 'r': rotY_base += 5; break;
        case 'R': rotY_base -= 5; break; break;
        case 'S': rotY_base -= 5; break; break;
        case 's': rotY_base -= 5; break; break;
        
        case 'M': mind=1;
        turnoff(light);
        light='1';
        glEnable(GL_LIGHT1);
        break;
        case 'd': desZ-=0.01;if(desZ<=-0.5){
            desZ=-0.5;}break;
        case 'D': desZ+=0.01;
        if(desZ>=0){ 
            desZ=0;}break;
    }
    glutPostRedisplay();
    
}

void mouseButton(int button, int state, int x, int y) {
	// only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

    // when the button is released
        if (state == GLUT_UP) {
            xOrigin = -1;
        } else {// state = GLUT_DOWN
            xOrigin = x;
            xO=x;
            yO=y;
        }
    }
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down	  
    if (xOrigin != -1) {
    // update camera's direction
    X_camera =(xO-x)/5 ;

    Y_camera =(yO-y)/5 ;
    }
   glutPostRedisplay();
}