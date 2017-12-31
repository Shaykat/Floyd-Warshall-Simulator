#include<bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glu.h>
using namespace std;
#define GLUT_BITMAP_HELVETICA_20	((void*)12)
vector<pair<int,int> > grid; // pair of cordinates of nodes stored in grid
vector<int> Graph[100]; // graph stored in Graph
vector<pair<int,int> > Edges; // pair of nodes of edges stored in Edges
vector<int> cost[100];   // cost of edges stored in cost
vector<pair<float,float> > curvepoints[200]; // store every points of  curves in curvePoints to redraw during simulation
vector<pair<int, int> > midPoint[200];
map<pair<int, int>, int> EdgeIndex; //map the indexes of edges
map<pair<int,int>, int> edgeCost; // map cost of edges
map<pair<int,int> ,int> nodeRegion; // map nodes with it's quadrant Region
int flag[200];
int node,edge,m,g,gu,startNode,endNode;
string ToString(int n) { string s; stringstream convert; convert << n; s = convert.str(); return s; }


void PrintText(int x, int y, int n)
{
    string S;
    int I, len;

	if(n != -1)
    {
        S = ToString(n);
    }

    string temp = ToString(n);

    len = S.length(); 			// See how many characters are in text string.


    glColor3f(0.0, 0.0, 1.0);

    glRasterPos2f( x, y); 		// Location to start printing text
    for(I = 0; I < len; I++) 			// Loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, S[I]);
    }

}

//------------------------------------------------------------------------------------------------------------------------------

pair<float, float> midlePointSet(pair<int, int> pr)
{
    float tp1,tp2;
    float p, q, r, s, t, u, v, w, x, y, tx1, ty1, tx2, ty2, t1, t2;

    int ni = EdgeIndex[make_pair(pr.first, pr.second)];
    p = grid[pr.first-1].first;
    q = grid[pr.first-1].second;

    r = grid[pr.second-1].first;
    s = grid[pr.second-1].second;

    v = nodeRegion[make_pair(p,q)];
    w = nodeRegion[make_pair(r,s)];

    if(p == r)
    {
        u = (q+s)/2;
        if(flag[ni] == 0)
        {
            t = p - 100;
            cout << "hogai dukse " << p << " " << r << endl;
            flag[ni] = 1;
            flag[EdgeIndex[make_pair(pr.second,pr.first)]]=1;
        }
        else
        {
            t = p + 100;
        }
    }
    else if(q == s)
    {
        t = (p+q)/2;
        if(flag[ni] == 0)
        {
            u = q + 100;

            flag[ni] = 1;
            flag[EdgeIndex[make_pair(pr.second,pr.first)]]=1;
        }
        else
        {
            u = q - 100;
        }
    }
    else
    {
        if(v == 1 && w == 1 && flag[ni] == 0)
        {
            t = max(p,r);
            u = max(q,s);
            flag[ni] = 1;
            flag[EdgeIndex[make_pair(pr.second,pr.first)]]=1;
            cout<<v<<" paici na "<<w<<endl;
        }
        else if(v == 1 && w == 1 && flag[ni])
        {
            t = min(p,r);
            u = min(q,s);
            cout<<v<<" paici na "<<w<<endl;

        }
        else if(v == 3 && w == 3 && flag[ni] == 0)
        {
            t = max(p,r);
            u = max(q,s);
            flag[ni] = 1;
            flag[EdgeIndex[make_pair(pr.second,pr.first)]]=1;
            cout<<v<<" paici na "<<w<<endl;
        }

        else if(v == 3 && w == 3 && flag[ni])
        {
            t = min(p,r);
            u = min(q,s);
            cout<<v<<" paici na "<<w<<endl;
        }

        else if(v == 2 && w == 2 && flag[ni] == 0)
        {
            t = min(p,r);
            u = max(q,s);
            flag[ni] = 1;
            flag[EdgeIndex[make_pair(pr.second,pr.first)]]=1;
            cout<<v<<" paici na "<<w<<endl;
        }

        else if(v == 2 && w == 2 && flag[ni])
        {
            t = max(p,r);
            u = min(q,s);
            cout<<v<<" paici na "<<w<<endl;
        }

        else if (v == 4 && w == 4 && flag[ni] == 0)
        {
            t = min(p,r);
            u = max(q,s);
            flag[ni] = 1;
            flag[EdgeIndex[make_pair(pr.second,pr.first)]]=1;
            cout<<v<<" paici "<<w<<" "<<ni<<" "<<flag[ni]<<endl;
        }

        else if (v == 4 && w == 4 && flag[ni])
        {
            t = max(p,r);
            u = min(q,s);
            cout<<v<<" paici na "<<w<<" "<<ni<<" "<<flag[ni]<<endl;
        }

        else if((v == 3 && w == 2) || (v == 4 && w == 2) || (v == 4 && w == 3))
        {
            t = max(p,r);
            u = max(q,s);
            cout<<v<<" paici na "<<w<<endl;
        }

        else if((v == 2 && w == 3) || (v == 2 && w == 4) || (v == 3 && w == 4))
        {
            cout<<v<<" paici "<<w<<endl;
            t = min(p,r);
            u = min(q,s);
        }

        else if((v == 1 && w == 2) || (v == 1 && w == 3) || (v == 1 && w == 4))
        {
            t = min(p,r);
            u = max(q,s);
            cout<<v<<" paici na "<<w<<endl;
        }

        else if((v == 2 && w == 1) || (v == 3 && w == 1) || (v == 4 && w == 1))
        {
            t = max(p,r);
            u = min(q,s);
            cout<<v<<" paici na "<<w<<endl;
        }
    }

    midPoint[ni].push_back(make_pair(t,u));
    return make_pair(t,u);
}

//------------------------------------------------------------------------------------------------------------------------------

void Grid()
{

    //cin >> node;

    g = (node-2)/2+2;
    if(g%2 == 0) g++;

    m = g/2+1;
    gu = 1000/g;
    int  p,q;
    for(int i = 0; i < m; i++){
        p = (m-i)*gu;
        q = (g-i)*gu;
        grid.push_back(make_pair(p,q));
        if(p >= m*gu && q >= m*gu) nodeRegion[make_pair(p,q)] = 1;
        else if(p < m*gu && q >= m*gu) nodeRegion[make_pair(p,q)] = 2;
        else if(p < m*gu && q < m*gu) nodeRegion[make_pair(p,q)] = 3;
        else if(p >= m*gu && q < m*gu) nodeRegion[make_pair(p,q)] = 4;
    }

    for(int i = m-2; i >= 0; i--){
        p = (m-i)*gu;
        q = (i+1)*gu;
        //cout << i << " if" << endl;
        grid.push_back(make_pair(p,q));
        if(p >= m*gu && q >= m*gu) nodeRegion[make_pair(p,q)] = 1;
        else if(p < m*gu && q >= m*gu) nodeRegion[make_pair(p,q)] = 2;
        else if(p < m*gu && q < m*gu) nodeRegion[make_pair(p,q)] = 3;
        else if(p >= m*gu && q < m*gu) nodeRegion[make_pair(p,q)] = 4;
    }

    for(int i = m+1; i <= g; i++){
        p = i*gu;
        q = (i-m+1)*gu;
        //cout << i << "  is" << endl;
        grid.push_back(make_pair(p,q));
        if(p >= m*gu && q >= m*gu) nodeRegion[make_pair(p,q)] = 1;
        else if(p < m*gu && q >= m*gu) nodeRegion[make_pair(p,q)] = 2;
        else if(p < m*gu && q < m*gu) nodeRegion[make_pair(p,q)] = 3;
        else if(p >= m*gu && q < m*gu) nodeRegion[make_pair(p,q)] = 4;
    }

    for(int i = 1; i < m; i++){
        p = (g-i)*gu;
        q = (m+i)*gu;
        //cout << i << " if" << endl;
        grid.push_back(make_pair(p,q));
        if(p >= m*gu && q >= m*gu) nodeRegion[make_pair(p,q)] = 1;
        else if(p < m*gu && q >= m*gu) nodeRegion[make_pair(p,q)] = 2;
        else if(p < m*gu && q < m*gu) nodeRegion[make_pair(p,q)] = 3;
        else if(p >= m*gu && q < m*gu) nodeRegion[make_pair(p,q)] = 4;
    }
}


//------------------------------------------------------------------------------------------------------------------------------


void Graph_Input()
{
    cout << "Enter Number of node you want to input: ";
    cin >> node;
    cout << "Enter Number of edge you want to input: ";
    cin >> edge;
    cout << "Graph Input with cost: " << endl;

    Grid(); ///////// Create Grid according to Number of Node

    for(int i = 0; i < edge; i++)
    {
        int x,y,c;
        cin >> x >> y >> c;

        Graph[x].push_back(y);
        //Graph[y].push_back(x);

        cost[x].push_back(c);
        //cost[y].push_back(c);

        Edges.push_back(make_pair(x,y));

        EdgeIndex[make_pair(x,y)] = i+1;
        //EdgeIndex[make_pair(y,x)] = i+1;

        edgeCost[make_pair(x,y)] = c;
        //edgeCost[make_pair(y,x)] = c;

    }

    cout << "Start Node: ";
    cin >> startNode;
    cout << "End Node: ";
    cin >> endNode;
}


////----------------------------------------------------------------------------------------------------

void drawLine(pair<int,int> p1, pair<int,int> p2, pair<float, float> mp, int edi,int n1,int n2)
{
    //Baizer curve algorithm
    float tp1,tp2;
    float p = p1.first,q = p1.second,r = p2.first,s = p2.second,t,u,x,y,tx1,ty1,tx2,ty2,t1,t2;

    tx1 = max(p,r);
    ty1 = max(q,s);

    tx2 = min(p,r);
    ty2 = min(q,s);

    t = mp.first;
    u = mp.second;

    if(p == r)
    {
        cout << p << " " << r << endl;
        tx1 = p;
        tx2 = t;
    }

    if(p == r)
    {
        if(flag[edi] != 2)
        {
            tx1 = p;
            tx2 = t;
            flag[edi] = 2;
            flag[EdgeIndex[make_pair(n2,n1)]]=2;
        }
        else
        {
            tx1 = t;
            tx2 = p;
        }
    }
    else if(q == s)
    {
        if(flag[edi] != 2)
        {
            ty1 = u;
            ty2 = q;
            flag[edi] = 2;
            flag[EdgeIndex[make_pair(n2,n1)]]=2;
        }
        else
        {
            ty1 = q;
            ty2 = u;
        }
    }



    //cout << "curbe: " <<" "<<n1<<" "<<n2<<" "<< p << " " << q << " " << r << " " << s << " " << t << " " << u << " " << tx1 << " " << tx2 << " " << ty1 << " " << ty2 << endl;

    glPushMatrix(); //Save the current state of transformations
    glColor3f(0,1,0);
    glLineWidth(3);
    glBegin(GL_LINES);
    t1=p,t2=q;
    for(float i = .001; i < 10; i+=.005)
    {
        x = (1.0-i)*(1.0-i)*p + 2.0*(1.0-i)*i*t+(i*i)*r;
        y = (1.0-i)*(1.0-i)*q + 2.0*(1.0-i)*i*u+(i*i)*s;

        //cout << n1 << " " << n2 << " " << y << " " << ty2 << " " << ty1 << " " << x << " " << tx2 << " " << tx1 << endl;
        if(y>=ty2 && y <= ty1 && x >=  tx2 && x <= tx1)
        {
            //cout << p << "hogar bal " << r << endl;
            glVertex3f(t1,t2,0);
            glVertex3f(x,y,0);

            t1 = x;
            t2 = y;
            curvepoints[edi].push_back(make_pair(x,y));
        }

    }
    glEnd();
    glPopMatrix();

    glFlush();
}


void NodeConnector()
{
    int l = grid.size(),p,q,x,y,tmp;
    //cout << l << endl;
    tmp = l-node;
    l = l-tmp;

    pair<int,int> pr;
    int b = 1;
    for(int j = 0; j < Edges.size(); j++)
    {
        pr = Edges[j];
        cout << pr.first << " node number " << pr.second << endl;
        pair<float, float> mp;
        mp = midlePointSet(pr);

        p = grid[pr.first-1].first;
        q = grid[pr.first-1].second;

        x = grid[pr.second-1].first;
        y = grid[pr.second-1].second;
        //cout << "points: " << i << " " << j << " " << tp << endl;

        drawLine(make_pair(p,q), make_pair(x,y), mp, j+1,pr.first,pr.second);

    }
    //PrintText(300,500,5);
    glFlush ();

}

void DrawNodes()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3ub(0,255,0);
    glPointSize(1.0);
    glLineWidth(10);

    int l = grid.size(),p,q,tmp;
    cout << l << endl;
    tmp = l-node;
    l = l-tmp;

    for(int j = 0; j < l; j++){
        p = grid[j].first;
        q = grid[j].second;

        //cout << p << " " << q << endl;

        glPushMatrix(); //Save the current state of transformations
        glTranslatef(p, q, 0.0); //Move to the center of the triangle
        //glRotatef(0.0, 0.0, 0.0, 1.0); //Rotate about the the vector (1, 2, 3)

        glBegin(GL_POLYGON);
        glColor3f(1,0,0);
        for(int i=0;i<100;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/100;
            float r=30;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix(); //Undo the move to the center of the triangle
        PrintText(p,q,j+1);
    }

    glFlush ();
}


void myDisplay(void)
{
    //Graph_Input();
    DrawNodes();
    NodeConnector();
}

void myInit (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3ub(0,255,0);
    glPointSize(10.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1200.0, 0.0, 1200.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (1200, 1200);
    glutInitWindowPosition (100, 150);
    glutCreateWindow ("my first attempt");
    Graph_Input();
    //Grid();
    glutDisplayFunc(myDisplay);
    myInit ();
    //glutFullScreen();
    glutMainLoop();
    //Graph_Input();

    return EXIT_SUCCESS;
}



/*
8
19
1 2 3
2 1 3
1 4 4
4 1 5
1 3 4
1 8 5
2 3 4
2 6 5
2 8 3
3 4 6
3 8 2
4 5 2
4 7 2
4 8 5
5 6 8
6 7 5
7 6 5
7 8 4
8 1 7
1
7



8
20
1 2 3
2 1 3
2 3 3
3 2 3
3 4 3
4 3 3
4 5 3
5 4 3
5 6 3
6 5 3
6 7 3
7 6 3
7 8 3
8 7 3
8 1 3
1 8 3
2 8 6
2 6 8
1 5 7
5 1 7
1
8

*/
