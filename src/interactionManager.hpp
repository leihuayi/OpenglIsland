extern float xrot;
extern float yrot;
extern float zoom;

void createMenu();
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void menu(int num);
void updateCameraSpeed(void);