## Name: Zeinab Walid <br> Section : 1   <br>    B.N: 34

# Task Three

## Implementation: 
1- Add the full body of assignment 2.<br>
2-Add the keyboard function with the cases of assignmnet 2 .<br>
3- Implement the forward and backward movements.<br>
4- Implement the vertical rotation (Left & Right functions).<br>
5- Implement the horizontal rotation (Up & Down functions) .<br>
6- Edit the mouse and motion funcions to control the left &right movement.<br>
 ```cpp
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
 ```

 ```cpp
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
 ```
  ```cpp
  void Left()

{
   rotatePoint(up,0.1,eye);
}

  ```

  ```cpp
  void Right()
{
     rotatePoint(up,-0.1,eye);
}
  ```
  ```cpp
  void Up()

{   look[0] = center[0] - eye[0];
	look[1] = center[1] - eye[1];
	look[2] = center[2] - eye[2];
    crossProduct(up,look,direction_hor);
    normalize(direction_hor);
     rotatePoint(direction_hor,0.1,up);
     rotatePoint(direction_hor,0.1,eye);

}
  ```

  ```cpp
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
  ```

  ```cpp
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

  ```
## Results: <br>
### Mouse Control for Left & Right Movement.<br>

![picture](left_mouse.png) 
<br>

![picture](right_mouse.png) 
<br>

### Arrows Control: <br>
#### 1- Left &  Right . <br>
![picture](left_arrow.png) 
<br>

![picture](right_arrow.png) 
<br>

#### 2- Up &  Down . <br>
![picture](up_arrow.png) 
<br>

![picture](down_arrow.png) 
<br>

## Problems:<br>
1- I Can not control the left & right movement with same button (left click button).<br>
2- some commands in the code template, I do not know their usage in code.



## Solution: <br>
1- I tried to use the Left click and right click buttons to control left & right movement .<br>


