/* Computer Graphics and Game Technology, Assignment Box2D game
 *
 * Student name .... Manuel Overdijk & Youp Uylings
 * Student email ... manuel.overdijk@gmail.com  & juylings@hotmail.com
 * Collegekaart .... 10374582 & --- --- ---
 * Date ............ March 2014
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <cstdio>

#include <GL/gl.h>
#include <GL/glut.h>
#include <Box2D/Box2D.h>

#include "levels.h"


void drawCircle(unsigned int level);



unsigned int reso_x = 800, reso_y = 600; // Window size in pixels
const float world_x = 8.f, world_y = 6.f; // Level (world) size in meters

int last_time;
int frame_count;

// Information about the levels loaded from files will be available in these.
unsigned int num_levels;
level_t *levels;

b2World *world;
b2Body *ball;


/*
 * Load a given world, i.e. read the world from the `levels' data structure and
 * convert it into a Box2D world.
 */
void load_world(unsigned int level)
{
    if (level >= num_levels)
    {
        // Note that level is unsigned but we still use %d so -1 is shown as
        // such.
        printf("Warning: level %d does not exist.\n", level);
        return;
    }

    // Create a Box2D world and populate it with all bodies for this level
    //gravity
    // (including the ball).

    //gravity
    b2Vec2 gravity(0.0f, -10.0f);

    //create our b2World
    world = new b2World(gravity);

    // //create a single static body
    // b2BodyDef groundBodyDef;
    // groundBodyDef.position.Set(0.0f, -10.0f);
    // b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // b2PolygonShape groundBox;
    // groundBox.SetAsBox(50.0f, 10.0f);
    // groundBody->CreateFixture(&groundBox, 0.0f);
    
    //create a single dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    //ball = new b2Body* body;
    ball = world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 0.4;
    

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    ball->CreateFixture(&fixtureDef);

}


/*
 * Called when we should redraw the scene (i.e. every frame).
 * It will show the current framerate in the window title.
 */
void draw(void)
{
    int time = glutGet(GLUT_ELAPSED_TIME);
    int frametime = time - last_time;
    frame_count++;

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    // Clear the buffer
    glColor3f(0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);


    world->Step(timeStep, velocityIterations, positionIterations);

    b2Vec2 position = ball->GetPosition();
    float32 angle = ball->GetAngle();
    //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    //drawCircle(position.x, position.y,angle);
    //
    // Do any logic and drawing here.
    //
    // Show rendered frame
    glutSwapBuffers();

    // Display fps in window title.
    if (frametime >= 1000)
    {
        char window_title[128];
        snprintf(window_title, 128,
                "Box2D: %f fps, level %d/%d",
                frame_count / (frametime / 1000.f), -1, num_levels);
        glutSetWindowTitle(window_title);
        last_time = time;
        frame_count = 0;
    }

}

void drawCircle(b2CircleShape *circle, b2Vec2 position){

    float32 x = position.x;
    float32 y = position.y;
    float32 r = circle->m_radius;

    //give color->red
    glColor3f(1.0,0.0,0.0)
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for( unsigned int i = 0.0f; i <= subdivs; ++i ) {
        float angle = i * ((2.0f * 3.14159f) / subdivs);
        glVertex2f(x + r * cos(angle), y + r * sin(angle) );
    }

    glEnd();
}

/*
 * Called when window is resized. We inform OpenGL about this, and save this
 * for future reference.
 */
void resize_window(int width, int height)
{
    glViewport(0, 0, width, height);
    reso_x = width;
    reso_y = height;
}

/*
 * Called when the user presses a key.
 */
void key_pressed(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: // Esc
        case 'q':
            exit(0);
            break;
        // Add any keys you want to use, either for debugging or gameplay.
        default:
            break;
    }
}

/*
 * Called when the user clicked (or released) a mouse buttons inside the window.
 */
void mouse_clicked(int button, int state, int x, int y)
{

}

/*
 * Called when the mouse is moved to a certain given position.
 */
void mouse_moved(int x, int y)
{

}


int main(int argc, char **argv)
{
    // Create an OpenGL context and a GLUT window.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(reso_x, reso_y);
    glutCreateWindow("Box2D");

    // Bind all GLUT events do callback function.
    glutDisplayFunc(&draw);
    glutIdleFunc(&draw);
    glutReshapeFunc(&resize_window);
    glutKeyboardFunc(&key_pressed);
    glutMouseFunc(&mouse_clicked);
    glutMotionFunc(&mouse_moved);
    glutPassiveMotionFunc(&mouse_moved);

    // Initialise the matrices so we have an orthogonal world with the same size
    // as the levels, and no other transformations.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, world_x, 0, world_y, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Read the levels into a bunch of structs.
    num_levels = load_levels(&levels);
    printf("Loaded %d levels.\n", num_levels);

    // Load the first level (i.e. create all Box2D stuff).
    load_world(0);

    last_time = glutGet(GLUT_ELAPSED_TIME);
    frame_count = 0;
    glutMainLoop();

    return 0;
}
