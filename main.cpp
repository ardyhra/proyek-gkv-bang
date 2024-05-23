#include <GL/glut.h>
#include <cstdlib> // Untuk fungsi rand()

// Posisi dan orientasi mobil
float carX = 0.0f; // Posisi X mobil
float carZ = -1.0f; // Posisi Z mobil
float carSpeed = 0.1f; // Kecepatan mobil

// Variabel untuk garis putus-putus
float lineOffset = 0.0f;
float lineSpeed = -0.1f; // Kecepatan pergerakan garis

// Variabel untuk pohon
const int numTrees = 1000; // Jumlah pohon di setiap sisi
float treePositions[numTrees]; // Posisi Z pohon

void init() {
    // Set warna background
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f); // Warna langit
    // Mengaktifkan Depth Buffer
    glEnable(GL_DEPTH_TEST);
    // Mengaktifkan pencahayaan
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    // Atur posisi dan properti cahaya
    GLfloat lightPos[] = { -4.0f, 4.0f, -10.0f, 1.0f }; // Posisi matahari
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Inisialisasi posisi pohon
    for (int i = 0; i < numTrees; ++i) {
        treePositions[i] = -20.0f + (i * 4.0f); // Menempatkan pohon dengan jarak tertentu
    }
}

void drawTree(float x, float z) {
    glPushMatrix();
    glTranslatef(x, -0.5f, z);

    // Menggambar batang pohon
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f); // Warna coklat
    glScalef(0.1f, 0.5f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Menggambar daun pohon
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f); // Warna hijau
    glTranslatef(0.0f, 0.5f, 0.0f);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    glTranslatef(carX, -0.5f, carZ); // Posisikan mobil di belakang

    // Menggambar badan utama mobil
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glScalef(1.0f, 0.5f, 2.0f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Menggambar atap mobil
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.25f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Menggambar roda
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.5f, -0.4f, 0.5f);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, -0.4f, -0.5f);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, -0.4f, 0.5f);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, -0.4f, -0.5f);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

void drawSun() {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(-4.0f, 4.0f, -10.0f);
    glutSolidSphere(1.0, 50, 50);
    glPopMatrix();
}

void drawDashedLines() {
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih untuk garis
    glPushMatrix();
    glTranslatef(0.0f, -0.9f, 4.5f-lineOffset); // Menggeser garis ke depan

    for (int i = 0; i < 10000; ++i) {
        glBegin(GL_QUADS);
        glVertex3f(-0.1f, 0.0f, -5.0f - i * 2.0f);
        glVertex3f(0.1f, 0.0f, -5.0f - i * 2.0f);
        glVertex3f(0.1f, 0.0f, -4.5f - i * 2.0f);
        glVertex3f(-0.1f, 0.0f, -4.5f - i * 2.0f);
        glEnd();
    }

    glPopMatrix();
}

void display() {
    // Membersihkan layar dan Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Mengatur kamera
    gluLookAt(0.0, 0.75, 5.0,  // posisi kamera
              0.0, 0.0, 0.0,  // target
              0.0, 1.0, 0.0); // arah atas

    // Menggambar jalanan
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-2.0f, -1.0f, -1000.0f);
    glVertex3f(2.0f, -1.0f, -1000.0f);
    glVertex3f(2.0f, -1.0f, 3.0f);
    glVertex3f(-2.0f, -1.0f, 3.0f);
    glEnd();
    
    // Menggambar rumput di kiri jalan
    glColor3f(0.35f, 0.74f, 0.35f);
    glBegin(GL_QUADS);
    glVertex3f(-1000.0f, -1.0f, -1000.0f);
    glVertex3f(-2.0f, -1.0f, -1000.0f);
    glVertex3f(-2.0f, -1.0f, 2.0f);
    glVertex3f(-10.0f, -1.0f, 2.0f);
    glEnd();

    // Menggambar rumput di kanan jalan
    glBegin(GL_QUADS);
    glVertex3f(2.0f, -1.0f, -1000.0f);
    glVertex3f(1000.0f, -1.0f, -1000.0f);
    glVertex3f(10.0f, -1.0f, 2.0f);
    glVertex3f(2.0f, -1.0f, 2.0f);
    glEnd();

    // Menggambar garis putus-putus
    drawDashedLines();

    // Menggambar pohon di kiri jalan
    for (int i = 0; i < numTrees; ++i) {
        drawTree(-3.0f, treePositions[i]+1.0f);
    }

    // Menggambar pohon di kanan jalan
    for (int i = 0; i < numTrees; ++i) {
        drawTree(3.0f, treePositions[i]);
    }

    // Menggambar matahari
    drawSun();

    // Menggambar mobil
    drawCar();

    // Swap buffer
    glutSwapBuffers();
}

void timer(int value) {
    // Update offset garis untuk animasi
    lineOffset += lineSpeed;
    if (lineOffset >= 2.0f) {
        lineOffset -= 2.0f;
    }

    // Update posisi pohon untuk animasi
    for (int i = 0; i < numTrees; ++i) {
        treePositions[i] -= lineSpeed;
        if (treePositions[i] > 10.0f) {
            treePositions[i] -= 40.0f; // Mengulang posisi pohon ke depan
        }
    }

    glutPostRedisplay(); // Meminta display untuk di-refresh
    glutTimerFunc(16, timer, 0); // Mengatur timer untuk animasi (sekitar 60 FPS)
}

void keyboard(unsigned char key, int x, int y) {
	float newCarX = carX; // Store the current car position

    switch (key) {
        case 'a':
        case 'A':
            newCarX -= carSpeed; // Move the car left
            break;
        case 'd':
        case 'D':
            newCarX += carSpeed; // Move the car right
            break;
        case 'w':
        case 'W':
            carZ -= carSpeed; // Move the car forward
            break;
        case 's':
        case 'S':
            carZ += carSpeed; // Move the car backward
            break;
    }

    // Check if the new car position is within the road boundaries
    if (newCarX >= -1.5f && newCarX <= 1.5f) {
        // Update the car position if it's within the road boundaries
        carX = newCarX;
    }

    glutPostRedisplay();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0f * w / h;

    // Mengatur viewport
    glViewport(0, 0, w, h);

    // Mengatur perspektif proyeksi
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    // Inisialisasi GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Animasi Mobil 3D");

    init();

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);

    // Enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}
