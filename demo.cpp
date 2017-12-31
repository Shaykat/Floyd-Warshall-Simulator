
#include<bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glu.h>
using namespace std;
vector<pair<int,int> > grid;
int n,m,g,gu;

void Grid()
{

    cin >> n;
    g = (n-2)/2+2;
    if(g%2 == 0) g++;

    m = g/2+1;
    gu = 500/g;
    int  p,q;
    for(int i = 0; i < m; i++){
        p = (m-i)*gu;
        q = (g-i)*gu;
        grid.push_back(make_pair(p,q));
    }

    for(int i = m-2; i >= 0; i--){
        p = (m-i)*gu;
        q = (i+1)*gu;
        cout << i << " if" << endl;
        grid.push_back(make_pair(p,q));
    }

    for(int i = m+1; i <= g; i++){
        p = i*gu;
        q = (i-m+1)*gu;
        cout << i << "  is" << endl;
        grid.push_back(make_pair(p,q));
    }

    for(int i = 1; i < m; i++){
        p = (g-i)*gu;
        q = (m+i)*gu;
        cout << i << " if" << endl;
        grid.push_back(make_pair(p,q));
    }
}
void DrawNodes(){
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3ub(0,255,0);
    glPointSize(1.0);
    glLineWidth(3);

    float p = 300,q = 500,r = 300,s = 100,t = 200,u = 300,x,y,t1=300,t2=500;

    glBegin(GL_LINES);
    for(float i = .001; i < 10; i+=.005){
        x = (1.0-i)*(1.0-i)*p + 2.0*(1.0-i)*i*t+(i*i)*r;
        y = (1.0-i)*(1.0-i)*q + 2.0*(1.0-i)*i*u+(i*i)*s;


        cout << y << " " << 500 << " " << 100 << " " << x << " " << 300 << " " << 200 << endl;
        if(y>=100 && y <= 500 && x >=  200 && x <= 300)
        {
            //cout << y << " " << 500 << " " << 100 << " " << x << " " << 300 << " " << 200 << endl;
            glVertex3f(x,y,0);
            glVertex3f(t1,t2,0);
        }

        t1 = x;
        t2 = y;
    }
    glEnd();



    /*glPushMatrix(); //Save the current state of transformations

    glTranslatef(400, 350, 0.0); //Move to the center of the triangle
    //glRotatef(0.0, 0.0, 0.0, 1.0); //Rotate about the the vector (1, 2, 3)

    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    for(int i=0;i<100;i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/100;
        float r=50;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();
    glPopMatrix();*/

    glFlush ();
}


void myDisplay(void)
{
    DrawNodes();
}

void myInit (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3ub(0,255,0);
    glPointSize(10.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 600.0, 0.0, 600.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (100, 150);
    glutCreateWindow ("my first attempt");
    glutDisplayFunc(myDisplay);
    myInit ();
    //glutFullScreen();
    glutMainLoop();




    return EXIT_SUCCESS;
}
