/*
TUGAS BESAR PRAKTIKUM GKV lab D1
KELOMPOK 9 : 
1. Ardy Hasan Rona Akhmad	(24060122130053)
2. Dimas Yudha Saputra		(24060122120025)
3. Yahya Ilham Riyadi		(24060122130069)

*/
#include <GL/glut.h>
#include <cstdlib> // Untuk fungsi rand()
#include <cmath> // Untuk fungsi sin, cos

// Posisi dan orientasi mobil
float carX = 0.0f; // Posisi X mobil
float carZ = -101.0f; // Posisi Z mobil
float carSpeed = 0.1f; // Kecepatan mobil

// Variabel untuk garis putus-putus
float lineOffset = 0.0f;
float lineSpeed = -0.1f; // Kecepatan pergerakan garis

// Variabel untuk pohon
const int numTrees = 40; // Jumlah pohon di setiap sisi
float treePositions[numTrees]; // Posisi Z pohon

// Variabel untuk kamera
float camX = 0.0f, camY = 1.0f, camZ = -95.0f; // Posisi kamera
float camYaw = 4.7f; // Yaw kamera
float camPitch = 0.0f; // Pitch kamera
bool perspective = true; // Jenis kamera

// Variabel untuk panning dan zoom
float panX = 0.0f, panY = 0.0f, zoom = 1.0f;

// Variabel untuk mobil
float carRotation = 0.0f; // Nilai rotasi mobil
float carScale = 1.0f; // Nilai skala mobil
bool carVisible = false;

// Variabel untuk toggle shadow dan lighting
bool showShadows = false;
bool lightingEnabled = false;

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
	GLfloat lightPos[] = { carX, 4.0f, carZ - 3.0f, 1.0f }; // Posisi baru sumber cahaya
    GLfloat lightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f  }; // Cahaya ambient yang lebih tinggi
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Cahaya diffuse yang lebih cerah
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Cahaya specular yang lebih intens
	

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Inisialisasi posisi pohon
    for (int i = 0; i < numTrees; ++i) {
        treePositions[i] = -150.0f + (i * 4.0f); // Menempatkan pohon dengan jarak tertentu
    }
}

void drawShadow(float x, float z) {
	if (!showShadows) return; // Jika bayangan dinonaktifkan, keluar dari fungsi
	
    glPushMatrix();
    glTranslatef(x, -0.99f, z + 0.45f); // Posisi bayangan
    glColor4f(0.1f, 0.1f, 0.1f, 0.5f); // Warna dan transparansi bayangan

    // Gambar bayangan datar (flat shadow)
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glEnd();

    glPopMatrix();
}

void drawTree(float x, float z) {
    glPushMatrix();
    glTranslatef(x, -0.5f, z);

    // Menggambar batang pohon
    glPushMatrix();
    glColor3f(0.545f, 0.271f, 0.075f); // Warna coklat
    glScalef(0.3f, 2.0f, 0.3f); // Sesuaikan proporsi batang pohon
    glutSolidCube(1.0);
    glPopMatrix();

    // Menggambar daun pohon
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f); // Warna hijau
    glTranslatef(0.0f, 1.5f, 0.0f); // Sesuaikan posisi daun
    glutSolidSphere(0.6, 20, 20); // Menggunakan bentuk sferis untuk daun
    glPopMatrix();

    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    glTranslatef(carX, -0.5f, carZ); // Posisikan mobil

    // Terapkan rotasi
    glRotatef(carRotation, 0.0f, 1.0f, 0.0f);

    // Terapkan skala
    glScalef(carScale, carScale, carScale);

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
    glTranslatef(-4.0f, 4.0f, -110.0f);
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



void setCamera() {
    float camXRot = cos(camYaw) * cos(camPitch);
    float camYRot = sin(camPitch);
    float camZRot = sin(camYaw) * cos(camPitch);

    gluLookAt(camX, camY, camZ, 
              camX + camXRot, camY + camYRot, camZ + camZRot, 
              0.0, 1.0, 0.0);
}

void display() {
    // Membersihkan layar dan Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Mengatur kamera
    setCamera();
    
    
	if (lightingEnabled) {
        glEnable(GL_LIGHTING);
    } else {
        glDisable(GL_LIGHTING);
    }
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
        drawShadow(-3.0f, treePositions[i]+1.0f);
    }

    // Menggambar pohon di kanan jalan
    for (int i = 0; i < numTrees; ++i) {
        drawTree(3.0f, treePositions[i]);
        drawShadow(3.0f, treePositions[i]);
    }

    // Menggambar matahari
    drawSun();

    // Menggambar mobil
	if (carVisible) {
        drawCar();
        drawShadow(carX, carZ);
    }
    
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
        if (treePositions[i] > -40.0f) {
            treePositions[i] -= 110.0f; // Mengulang posisi pohon ke depan
        }
    }

    glutPostRedisplay(); // Meminta display untuk di-refresh
    glutTimerFunc(16, timer, 0); // Mengatur timer untuk animasi (sekitar 60 FPS)
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0f * w / h;

    // Mengatur viewport
    glViewport(0, 0, w, h);

    // Mengatur perspektif proyeksi
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspective) {
        gluPerspective(45, ratio, 1, 1000);
    } else {
        glOrtho(-10.0 * ratio, 10.0 * ratio, -10.0, 10.0, 1.0, 1000.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
void moveCamera(float speed) {
    float camXRot = cos(camYaw) * cos(camPitch);
    float camYRot = sin(camPitch);
    float camZRot = sin(camYaw) * cos(camPitch);

    // Hitung vektor pergerakan maju mundur
    float moveX = camXRot * speed;
    float moveY = camYRot * speed;
    float moveZ = camZRot * speed;

    // Terapkan pergerakan ke posisi kamera
    camX += moveX;
    camY += moveY;
    camZ += moveZ;
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
        case 'q':
        case 'Q':
            carRotation += 5.0f; // Putar mobil berlawanan arah jarum jam
            break;
        case 'e':
        case 'E':
            carRotation -= 5.0f; // Putar mobil searah jarum jam
            break;
        case 'r':
        case 'R':
            carScale += 0.1f; // Perbesar mobil
            break;
        case 't':
        case 'T':
            carScale -= 0.1f; // Perkecil mobil
            break;
        case 'i':
        case 'I':
            moveCamera(-0.1f); // Gerakkan kamera ke maju
            break;
        case 'k':
        case 'K':
            moveCamera(0.1f); // Gerakkan kamera ke mundur
            break;
        
    }

    // Check if the new car position is within the road boundaries
    if (newCarX >= -1.5f && newCarX <= 1.5f) {
        // Update the car position if it's within the road boundaries
        carX = newCarX;
    }

    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            camYaw -= 0.03f; // Rotate camera left
            break;
        case GLUT_KEY_RIGHT:
            camYaw += 0.03f; // Rotate camera right
            break;
        case GLUT_KEY_UP:
            camPitch += 0.03f; // Tilt camera up
            break;
        case GLUT_KEY_DOWN:
            camPitch -= 0.03f; // Tilt camera down
            break;
        case GLUT_KEY_PAGE_UP:
            camY += 0.03f; // Move camera up
            break;
        case GLUT_KEY_PAGE_DOWN:
            camY -= 0.03f; // Move camera down
            break;
    }

    glutPostRedisplay();
}

void menu(int option) {
    switch (option) {
        case 1:
            carVisible = !carVisible;
            break;
        case 2: // Toggle shadow
            showShadows = !showShadows;
            break;
        case 3: // Toggle lighting
            lightingEnabled = !lightingEnabled;
            break;
        case 4:
            // Toggle between perspective and orthogonal projection
            perspective = !perspective;
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
    }
    glutPostRedisplay();
}
void createMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("Toggle Car", 1);
    glutAddMenuEntry("Toggle Shadow", 2);
    glutAddMenuEntry("Toggle Lighting", 3);
    glutAddMenuEntry("Toggle Camera", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
    glutSpecialFunc(specialKeys);
	createMenu();
    // Enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}
