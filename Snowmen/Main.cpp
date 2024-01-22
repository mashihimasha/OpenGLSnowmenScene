#include <glut.h>  
#include <math.h>

float snowmanRotation = 0.0;

double objR = 0.0;
double sceneX = 0.0;
double sceneZ = 0.0;
double rotateSceneY = 0.0;

//variables to move the camera
float camX = 0.0f;
float camY = 0.0f;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void drawAxes() {

    glBegin(GL_LINES);

    glLineWidth(1.5);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-40, 0, 0);
    glVertex3f(40, 0, 0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -40, 0);
    glVertex3f(0, 40, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, -40);
    glVertex3f(0, 0, 40);

    glEnd();
}
void drawGrid() {
    GLfloat ext = 40.0f;
    GLfloat step = 1.0f;
    GLfloat yGrid = -1.4f;
    GLint line;

    glBegin(GL_LINES);
    for (line = -ext; line <= ext; line += step) {
        glVertex3f(line, yGrid, ext);
        glVertex3f(line, yGrid, -ext);

        glVertex3f(ext, yGrid, line);
        glVertex3f(-ext, yGrid, line);
    }
    glEnd();
}
//
//void drawHead() {
//    //eye1
//    glPushMatrix();
//    glTranslated(0.3, 2.6, 0.95);
//    glColor3f(0.0, 0.0, 0.0);
//    glutSolidSphere(0.1f, 60, 60);
//    glPopMatrix();
//
//    //eye2
//    glPushMatrix();
//    glTranslated(-0.3, 2.6, 0.95);
//    glColor3f(0.0, 0.0, 0.0);
//    glutSolidSphere(0.1f, 60, 60);
//    glPopMatrix();
//
//    //nose
//    glPushMatrix();
//    glTranslated(0.0, 2.3, 0.95);
//    glColor3f(0.9, 0.41, 0.17);
//    glutSolidCone(0.18, 1.0, 70, 12);
//    glPopMatrix();
//
//    //head
//    glPushMatrix();
//    glTranslated(0.0, 2.3, 0.0);
//    glColor3f(1.0, 1.0, 1.0);
//    glutSolidSphere(1.0f, 60, 60);
//    glPopMatrix();
//
//}
//void drawBody() {
//
//    glPushMatrix();
//    glTranslated(0.0, 1.8, 0.0);
//    glRotated(-90, 1.0, 0.0, 0.0);
//    glColor3f(1.0, 0.0, 0.0);
//    glutSolidTorus(0.3, 0.8, 10, 50);
//    glPopMatrix();
//
//
//    glColor3f(1.0, 1.0, 1.0);
//    glutSolidSphere(2.0f, 60, 60);
//
//    //button1
//    glPushMatrix();
//    glTranslated(0.0, 1.4, 1.4);
//    glColor3f(0.0, 0.0, 0.0);
//    glutSolidSphere(0.09f, 60, 60);
//    glPopMatrix();
//
//    //button2
//    glPushMatrix();
//    glTranslated(0.0, 1.2, 1.6);
//    glColor3f(0.0, 0.0, 0.0);
//    glutSolidSphere(0.09f, 60, 60);
//    glPopMatrix();
//
//    //button3
//    glPushMatrix();
//    glTranslated(0.0, 1.0, 1.7);
//    glColor3f(0.0, 0.0, 0.0);
//    glutSolidSphere(0.09f, 60, 60);
//    glPopMatrix();
//
//}
//
//void drawObject() {
//
//    glPushMatrix();
//
//    glColor3f(1.0, 1.0, 1.0);
//    glRotated(90, 0.0, 1.0, 0.0);
//    drawHead();
//    drawBody();
//
//    glPopMatrix();
//}

//set lighting
void setLighting() {
    // Lighting set up
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // Set lighting intensity and color
    GLfloat qaAmbientLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat qaDiffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };


    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    // Set the light position
    GLfloat qaLightPosition[] = { 100.0, -2.0, 100.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

    //set light 1
    glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);
    GLfloat qaLightPosition1[] = { 0.0, 0.0, 100.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);

}

//draw object with lighting
void drawObjectWithLighting() {

    // Set material properties
    GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat qaWhite[] = { 1.0,1.0,1.0,1.0 };
    GLfloat qaSnowWhite[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat qaOrange[] = { 0.9, 0.41, 0.17, 1.0 };
    GLfloat qaLowAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat qaFullAmbient[] = { 1.0, 1.0, 1.0, 1.0 };

    //Set, ambient, diffuse and specular lighting. Set ambient to 20%.
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaWhite);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaWhite);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 80);
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaLowAmbient);
    glLightfv(GL_LIGHT1, GL_AMBIENT, qaLowAmbient);

    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);

    glPushMatrix();

    //rotate object
    glRotated(90, 0.0, 1.0, 0.0);

    ////eye lighting
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaBlack);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBlack);

    //eye1
    glPushMatrix();
    glTranslated(0.3, 2.6, 0.95);
    glColor3f(0.0, 0.0, 0.0);
    glNormal3f(0.0, 0.0, 1.0);
    glutSolidSphere(0.1f, 60, 60);
    glPopMatrix();

    //eye2
    glPushMatrix();
    glTranslated(-0.3, 2.6, 0.95);
    glColor3f(0.0, 0.0, 0.0);
    glNormal3f(0.0, 0.0, 1.0);
    glutSolidSphere(0.1f, 60, 60);
    glPopMatrix();

    ////nose lighting

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaOrange);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaOrange);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    //flat shade nose
    glShadeModel(GL_FLAT);

    //nose
    glPushMatrix();
    glTranslated(0.0, 2.3, 0.95);
    glColor3f(0.9, 0.41, 0.17);
    glutSolidCone(0.18, 1.0, 70, 12);
    glPopMatrix();

    ////head lighting

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaSnowWhite);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaSnowWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
    glShadeModel(GL_SMOOTH);

    //head
    glPushMatrix();
    glTranslated(0.0, 2.3, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0.0, 1.0, 1.0);
    glutSolidSphere(1.0f, 60, 60);
    glPopMatrix();

    ////red shawl lighting

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaRed);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaRed);

    //red shawl
    glPushMatrix();
    glTranslated(0.0, 1.8, 0.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(0.0, 0.0, 1.0);
    glutSolidTorus(0.3, 0.8, 10, 50);
    glPopMatrix();

    ////bottom body sphere lighting

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaSnowWhite);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaSnowWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

    //bottom body sphere
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(2.0f, 60, 60);

    ////button lighting
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaBlack);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBlack);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

    //button1
    glPushMatrix();
    glTranslated(0.0, 1.4, 1.4);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.09f, 60, 60);
    glPopMatrix();

    //button2
    glPushMatrix();
    glTranslated(0.0, 1.2, 1.6);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.09f, 60, 60);
    glPopMatrix();

    //button3
    glPushMatrix();
    glTranslated(0.0, 1.0, 1.7);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.09f, 60, 60);
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_LIGHTING);

}

//draw scene using snowman with lighting and shading
void drawNineSnowMen() {
    double x;
    double z;
    for (x = -30.0; x <= 30.0; x += 30.0) {
        for (z = -30.0; z <= 30.0; z += 30.0) {

            if (x == 0.0 && z == 0.0)
            {
                glPushMatrix();
                glTranslated(0.0, 3.6, 0.0);
                glRotatef(snowmanRotation, 0.0, 1.0, 0.0);
                glRotated(objR, 0.0, 1.0, 0.0);
                glScaled(2.5, 2.5, 2.5);
                //drawObject();
                drawObjectWithLighting();
                glPopMatrix();
                continue;
            }
            else {

                glPushMatrix();
                glTranslated(x, 1.0, z);
                //drawObject();
                drawObjectWithLighting();
                glPopMatrix();
            }

        }
    }
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(35.0 + camX, 4.0 + camY, 0.0, 0, 0, 0, 0, 1.0, 0);
    glTranslated(sceneX, 0.0, sceneZ);
    glRotated(rotateSceneY, 0.0, 1.0, 0.0);

    glColor3f(0.8, 0.8, 0.8);
    drawGrid();
    drawAxes();

    setLighting();

    glPushMatrix();
    drawNineSnowMen();
    glPopMatrix();

    glutSwapBuffers();

}

void keyboardSpecial(int key, int x, int y) {
    //camera around x clockwise
    if (key == GLUT_KEY_UP)
        camX += 0.5;

    //camera around x anti-clockwise
    if (key == GLUT_KEY_DOWN)
        camX -= 0.5;

    //translate to left
    if (key == GLUT_KEY_LEFT)
        sceneX += 0.5;

    //translate to right
    if (key == GLUT_KEY_RIGHT)
        sceneX -= 0.5;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

    //obj rotate clockwise
    if (key == 'l') {
        objR++;
    }
    //obj rotate anti-clockwise
    if (key == 'r') {
        objR--;
    }

    if (key == 'z') {
        sceneZ++;
    }
    if (key == 'Z') {
        sceneZ--;
    }

    if (key == 'y') {
        camY++;
    }
    if (key == 'Y') {
        camY--;
    }

    if (key == 'v') {
        rotateSceneY++;
    }
    if (key == 'V') {
        rotateSceneY--;
    }


    glutPostRedisplay();

}

void Timer(int x) {
    snowmanRotation += snowmanRotation >= 360.0 ? -snowmanRotation : 2;
    glutPostRedisplay();

    glutTimerFunc(60, Timer, 1);
}

void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Define the Perspective projection frustum
    // (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
    gluPerspective(120.0, aspect_ratio, 1.0, 100.0);

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Rotating Snowman");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // keyboard function activation
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    glutTimerFunc(60.0, Timer, 1);
    init();
    glutMainLoop();


    return 0;
}