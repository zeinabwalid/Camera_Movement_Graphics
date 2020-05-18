#include<windows.h>
#include <GL/glut.h>
#include <math.h>

static int head=0,body = 0 ,shoulder1 = 0,shoulder2 = 0,shoulder3 = 0, elbow1 = 0, thigh10 =0 ,thigh11=0, leg1 =0,thigh20 =0 ,thigh21=0, leg2 =0;
int movingl,movingr;


float speed = 0.2;
double eye[] = { 0, 0, -20 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };
double look[]={0,0,0};
double direction[]={0,0,0};
double direction_hor[]={0,0,0};


void init(void)
{
    glMatrixMode(GL_PROJECTION);
	gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);
	 glShadeModel(GL_FLAT);
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];

}

void Left()

{
   rotatePoint(up,0.1,eye);
}

void Right()
{
     rotatePoint(up,-0.1,eye);
}

void Up()

{   look[0] = center[0] - eye[0];
	look[1] = center[1] - eye[1];
	look[2] = center[2] - eye[2];
    crossProduct(up,look,direction_hor);
    normalize(direction_hor);
     rotatePoint(direction_hor,0.1,up);
     rotatePoint(direction_hor,0.1,eye);

}

void Down()
{
    look[0] = center[0] - eye[0];
	look[1] = center[1] - eye[1];
	look[2] = center[2] - eye[2];
    crossProduct(up,look,direction_hor);
    normalize(direction_hor);
     rotatePoint(direction_hor,-0.1,up);
     rotatePoint(direction_hor,-0.1,eye);
}

void moveForward()
{  //vector between eye and center
    direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	//location updates of eye & center
	eye[0] += direction[0] * speed;
	eye[1] += direction[1] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;
}

void moveBack()
{
    //vector between eye and center
    direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	//location updates of eye & center
	eye[0] -= direction[0] * speed;
	eye[1] -= direction[1] * speed;
	eye[2] -= direction[2] * speed;

	center[0] -= direction[0] * speed;
	center[1] -= direction[1] * speed;
	center[2] -= direction[2] * speed;
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
   	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	// full body
    glPushMatrix();

    ///////head
   glPushMatrix();
   glTranslatef (-0.5, 2.5, 0.0);
   glRotatef ((GLfloat) head, 0.0, 0.0, 1.0);
   glTranslatef (0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 1.0, 1.0);
   glutWireSphere(0.6,10,10);
   glPopMatrix();
   glPopMatrix();
   /////body
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) body, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 3.0, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   //// arm 1
   glPushMatrix();
   glTranslatef (1.2, 1.3, 0.0);
   glRotatef ((GLfloat) shoulder3, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) shoulder2, 1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder1, 0.0, 0.0, 1.0);
   glTranslatef (0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.4, 0.5);
   glutWireCube (1.0);
   glPopMatrix();

   glTranslatef (0.5, 0.0, 0.0);
   glRotatef ((GLfloat) elbow1, 0.0, 1.0, 0.0);
   glTranslatef (0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.4, 0.5);
   glutWireCube (1.0);
   glPopMatrix();
   //Draw finger flang 1
   glTranslatef(0.65, 0.15, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 1
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   //Draw finger flang 2
   glTranslatef(-0.15, 0.0, 0.2);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 2
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   //Draw finger flang 3
   glTranslatef(-0.15, 0.0, -0.4);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 3
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
    //Draw finger flang 4
   glTranslatef(-0.15, -0.3, 0.4);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 4
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();
   ////// arm2
   glPushMatrix();
   glTranslatef (-1.2, 1.3, 0.0);
   glRotatef ((GLfloat) shoulder3, 0.0, 0.0, -1.0);
   glRotatef ((GLfloat) shoulder2, -1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder1, 0.0, 0.0,- 1.0);
   glTranslatef (-0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.4, 0.5);
   glutWireCube (1.0);
   glPopMatrix();

   glTranslatef (-0.5, 0.0, 0.0);
   glRotatef ((GLfloat) elbow1, 0.0, 1.0, 0.0);
   glTranslatef (-0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.4, 0.5);
   glutWireCube (1.0);
   glPopMatrix();
   //Draw finger flang 1
   glTranslatef(-0.8, 0.15, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 1
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   //Draw finger flang 2
   glTranslatef(-0.15, 0.0, 0.2);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 2
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   //Draw finger flang 3
   glTranslatef(-0.15, 0.0, -0.4);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 3
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   //Draw finger flang 4
   glTranslatef(-0.15, -0.3, 0.4);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();

   //Draw finger flang 4
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.1);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();
   ////thigh1
   glPushMatrix();
   glTranslatef (0.2, -2.5, 0.0);
   glRotatef ((GLfloat) thigh11, 0.0, 0.0, 1.0);
   glTranslatef (0.4, 1.0, 0.0);
   glRotatef ((GLfloat) thigh10, 1.0, 0.0, 0.0);
   glTranslatef (0.0, -1.0, 0.0);
   glPushMatrix();
   glScalef (0.8, 2.0, 0.5);
   glutWireCube (1.0);
   glPopMatrix();
   /////leg1
   glTranslatef (0.0, -1.0, 0.0);
   glRotatef ((GLfloat) leg1, 1.0, 0.0, 0.0);
   glTranslatef (0.0, -1.0, 0.0);
   glPushMatrix();
   glScalef (0.8, 2.0, 0.5);
   glutWireCube (1.0);
   glPopMatrix();
   ////foot1
   glTranslatef (0.0, -1.15,0.35);
   glPushMatrix();
   glScalef (0.8, 0.3, 1.2);
   glutSolidCube (1.0);
   glPopMatrix();
   glPopMatrix();
   ////thigh2
   glPushMatrix();
   glTranslatef (-0.2, -2.5, 0.0);
   glRotatef ((GLfloat) thigh21, 0.0, 0.0, 1.0);
   glTranslatef (-0.4, 1.0, 0.0);
   glRotatef ((GLfloat) thigh20, 1.0, 0.0, 0.0);
   glTranslatef (0.0, -1.0, 0.0);
   glPushMatrix();
   glScalef (0.8, 2.0, 0.5);
   glutWireCube (1.0);
   glPopMatrix();
   /////leg2
   glTranslatef (0.0, -1.0, 0.0);
   glRotatef ((GLfloat) leg2, 1.0, 0.0, 0.0);
   glTranslatef (0.0, -1.0, 0.0);
   glPushMatrix();
   glScalef (0.8, 2.0, 0.5);
   glutWireCube (1.0);
   glPopMatrix();
   ////foot2
   glTranslatef (0.0, -1.15, 0.35);
   glPushMatrix();
   glScalef (0.8, 0.3, 1.2);
   glutSolidCube (1.0);
   glPopMatrix();
   glPopMatrix();

    glPopMatrix();
	// draw trunck
	// call the robotic body draw function here
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: Left(); break;
	case GLUT_KEY_RIGHT: Right(); break;
	case GLUT_KEY_UP:    Up(); break;
	case GLUT_KEY_DOWN:  Down(); break;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	// List all youe keyboard keys from assignment two her for body movement
	switch (key)
	{
	case 'f':
		moveForward();
		glutPostRedisplay();
		break;
	case 'b':
		moveBack();
		glutPostRedisplay();
		break;

   ////////////arms
   case 's':
       if (shoulder1 < 90){
      shoulder1 = (shoulder1 + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'S':
       if(shoulder1 > -90){
      shoulder1 = (shoulder1 - 5) % 360;
      glutPostRedisplay();}
      break;
    case 'a':
        if(shoulder2<180 ){
      shoulder2 = (shoulder2 + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'A':
        if(shoulder2>-180){
      shoulder2 = (shoulder2 - 5) % 360;
      glutPostRedisplay();}
      break;

      case 'z':
          if(shoulder3<90){
      shoulder3 = (shoulder3 + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'Z':
         if(shoulder3>-90){
      shoulder3 = (shoulder3 - 5) % 360;
      glutPostRedisplay();}
      break;

   case 'e':
       if(elbow1<90){
      elbow1 = (elbow1 + 5) % 360;
      glutPostRedisplay();}
      break;

   case 'E':
        if(elbow1>-120){
      elbow1 = (elbow1 - 5) % 360;
      glutPostRedisplay();}
      break;


    //////////thigh1 & leg1
    case 't':
        if(thigh10 <90){
      thigh10 = (thigh10 + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'T':
       if(thigh10 >-90){
      thigh10 = (thigh10 - 5) % 360;
      glutPostRedisplay();}
      break;
      case 'y':
          if (thigh11 <90){
      thigh11 = (thigh11 + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'Y':
        if(thigh11> 0){
      thigh11 = (thigh11 - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'u':
       if(leg1 <180){
      leg1 = (leg1 + 5) % 360;
      glutPostRedisplay();}
      break;

   case 'U':
        if(leg1 >0){
      leg1 = (leg1 - 5) % 360;
      glutPostRedisplay();}
      break;

      //////////thigh2 & leg2
    case 'i':
        if(thigh20<90){
      thigh20 = (thigh20 + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'I':
        if(thigh20>-90){
      thigh20 = (thigh20 - 5) % 360;
      glutPostRedisplay();}
      break;
    case 'o':
        if(thigh21>-90){
      thigh21 = (thigh21 - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'O':
       if(thigh21<0){
      thigh21 = (thigh21 + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'p':
        if(leg2<180){
      leg2 = (leg2 + 5) % 360;
      glutPostRedisplay();}
      break;

   case 'P':
        if(leg2>0){
      leg2 = (leg2 - 5) % 360;
      glutPostRedisplay();}
      break;

   case 27:
      exit(0);
      break;
   default:
      break;
   }
}
static void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
            Left();
            movingl =1;
    }
    if (state == GLUT_UP) {

      movingl = 0;
    }
  }
  else if (button == GLUT_RIGHT_BUTTON){
    if (state == GLUT_DOWN) {
            Right();
            movingr =1;
    }
    if (state == GLUT_UP) {

      movingr = 0;
    }
  }
}
static void motion(int x, int y)
{
  if (movingl==1) {
        Left();
        glutPostRedisplay();
  }
  if(movingr==1){
     Right();
     glutPostRedisplay();
  }
  }


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("body");
	init();
	glutDisplayFunc(display);
    	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
    glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}

