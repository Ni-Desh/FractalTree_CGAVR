#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

#define PI 3.14159265

int maxDepth = 10;
int currentDepth = 0;

void delay(int ms) {
    usleep(ms * 1000);
}

void drawBranch(float x1, float y1, float angle, int depth) {
    if (depth == 0) return;

    float length = 0.15 * depth;  // Shorter branches at deeper levels
    float x2 = x1 + length * cos(angle * PI / 180.0);
    float y2 = y1 + length * sin(angle * PI / 180.0);

    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    glFlush();
    delay(200);  // Add delay to visualize progressive growth

    // Recurse for left and right branches
    drawBranch(x2, y2, angle + 25, depth - 1);
    drawBranch(x2, y2, angle - 25, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2, 0.5, 0.2); // Tree color

    // Start from bottom center
    drawBranch(0.0, -0.9, 90, currentDepth);

    if (currentDepth < maxDepth) {
        currentDepth++;
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0); // Default color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1); // Adjust view so tree fits
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Recursive Fractal Tree with Animation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

