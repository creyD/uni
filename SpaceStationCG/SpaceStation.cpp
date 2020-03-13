#define _CRT_SECURE_NO_WARNINGS
#define __EXPORT_HELP

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "Include/freeglut.h"
#include "Include/glext.h"
#include "help.h"
#include "window.h"
#include "wavefront.h"
#include "input.h"
#include "light.h"

void setCamera();		// Kamera platzieren, siehe Maus-Callbacks
void drawScene();		// Zeichnet die Szene im Weltkoordinatensystem
void loadObjects();		// Laedt externe Objektdateien

// Globale Variablen zur Steuerung der Raumstation
float GLOBAL_STATIONPOS[3] = { 0, 0, 0 };
float GLOBAL_STATIONSPEED = (float)0.05;
float GLOBAL_STATIONDISTANCE = 13;
float GLOBAL_SPACESTATIONROTATION = 0;
float GLOBAL_SOLAR_ROTATION = 0;
float GLOBAL_SENSOR_GENERAL_ROTATION = 0;
float GLOBAL_SENSORS_ROTATION = 45;

float GLOBAL_EARTHROTATION = 0;

// Kameramodi (0 = Standard, 1 = Follow Orbit, 2 = Close Up)
int GLOBAL_CAM_MODE = 0;

// FPS Mode (false = Absolute Geschwindigkeit, true = Relative Geschwindigkeit)
int FPS_MODE = false;

// Slices und Stacks global fuer alle Zylinder und Kugelformen definieren
float SLICES = 100;
float STACKS = 100;


/////////////////////////////////////////////////////////////////////////////////
//	Externe Objekte und Texturen
/////////////////////////////////////////////////////////////////////////////////
// Externe Objekte und Texturpfade definieren
#define num_objects 1
const char* objects_dir = "./Texturen/";
const char* objects_paths[num_objects] = { "solar.obj" };
cg_object3D objects[num_objects];

enum {
	SOLARPANEL = 0
};

void loadObjects() {
	// alle Objekte Laden, wenn der Pfad verfuegbar ist
	for (int i = 0; i < num_objects; i++)
		if (strlen(objects_paths[i]) > 0)
		{
			char filename[255] = "";
			strcat(filename, objects_dir);
			strcat(filename, objects_paths[i]);
			objects[i].load(filename, true);
		}

	// Materialeigenschaften fuer Solarpanele setzen
	objects[SOLARPANEL].setMaterial(0.1, 0.1, 0.8, 0.9, 0.5, 80, 0);
}

/////////////////////////////////////////////////////////////////////////////////
//	Kamerafunktion
/////////////////////////////////////////////////////////////////////////////////
void setCamera() {
	cg_mouse mouse;
	// Ansichtstransformationen setzen,
	// SetCamera() zum Beginn der Zeichenfunktion aufrufen
	double x, y, z, The, Phi;
	static double radius = 25;
	// Maus abfragen
	if (cg_mouse::buttonState(GLUT_LEFT_BUTTON))
	{
		cg_globState::cameraHelper[0] += mouse.moveX();
		cg_globState::cameraHelper[1] += mouse.moveY();
	}
	if (cg_mouse::buttonState(GLUT_MIDDLE_BUTTON))
	{
		radius += 0.1 * mouse.moveY();
		if (radius < 1.0) radius = 1.0;
	}
	Phi = 0.2 * cg_globState::cameraHelper[0] / cg_globState::screenSize[0] * M_PI + M_PI * 0.5;
	The = 0.2 * cg_globState::cameraHelper[1] / cg_globState::screenSize[1] * M_PI;
	x = radius * cos(Phi) * cos(The);
	y = radius * sin(The);
	z = radius * sin(Phi) * cos(The);
	int Oben = (The <= 0.5 * M_PI || The > 1.5 * M_PI) * 2 - 1;

	if (GLOBAL_CAM_MODE == 0)
	{
		gluLookAt(x, y, z, 0, 0, 0, 0, Oben, 0);
	}
	else if (GLOBAL_CAM_MODE == 1) {
		double offset[3] = { 5, 5, 5 };
		gluLookAt(
			GLOBAL_STATIONPOS[0] + offset[0], GLOBAL_STATIONPOS[1] + offset[1], GLOBAL_STATIONPOS[2] + offset[2],
			GLOBAL_STATIONPOS[0], GLOBAL_STATIONPOS[1], GLOBAL_STATIONPOS[2],
			0, Oben, 0
		);
	}
	else if (GLOBAL_CAM_MODE == 2) {
		gluLookAt(
			GLOBAL_STATIONPOS[0] - 2, GLOBAL_STATIONPOS[1] - 2, GLOBAL_STATIONPOS[2] - 2,
			GLOBAL_STATIONPOS[0], GLOBAL_STATIONPOS[1], GLOBAL_STATIONPOS[2],
			0, Oben, 0
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////
//	Anfang des OpenGL Programmes
/////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	init(argc, argv);

	// Laedt die externen Objektdateien und Texturen
	loadObjects();

	// Die Hauptschleife starten
	glutMainLoop();
	return 0;
}

void displayFunc() {
	// Hilfe-Instanzen
	cg_help help;
	cg_globState globState;
	cg_key key;

	// Tastatur abfragen
	// Achtung: einmaliges Betaetigen funktioniert so nur mit glutIgnoreKeyRepeat(true) (siehe main)
	if (key.keyState(27))
	{
		exit(0); // Escape -> Programm beenden
	}
	else if (1 == key.keyState('f') || 1 == key.keyState('F'))
	{
		help.toggleFps();	// Framecounter on/off
	}
	else if (1 == key.keyState('h') || 1 == key.keyState('H') || 1 == key.specialKeyState(GLUT_KEY_F1))
	{
		help.toggle();	// Hilfetext on/off
	}
	else if (1 == key.keyState('k') || 1 == key.keyState('K'))
	{
		help.toggleKoordsystem();	// Koordinatensystem on/off
	}
	else if (1 == key.keyState('w') || 1 == key.keyState('W'))
	{
		globState.drawMode = (globState.drawMode == GL_FILL) ? GL_LINE : GL_FILL; // Wireframe on/off
	}
	else if (1 == key.keyState('l') || 1 == key.keyState('L'))
	{
		globState.lightMode = !globState.lightMode;	// Beleuchtung on/off
	}
	else if (1 == key.keyState('b') || 1 == key.keyState('B'))
	{
		globState.cullMode = !globState.cullMode; // Backfaceculling on/off
	}
	else if (1 == key.keyState('i') || 1 == key.keyState('I'))
	{
		globState.cameraHelper[0] = 0;	// Initialisierung der Kamera
		globState.cameraHelper[1] = 0;
	}
	// Steuerungen der Solarplatten
	else if (key.keyState('A') || key.keyState('a'))
	{
		GLOBAL_SOLAR_ROTATION -= 0.125;
	}
	else if (key.keyState('D') || key.keyState('d'))
	{
		GLOBAL_SOLAR_ROTATION += 0.125;
	}
	// Steuerung des Sensorarrays
	else if (key.keyState('Y') || key.keyState('y'))
	{
		if (GLOBAL_SENSOR_GENERAL_ROTATION <= 30) {
			GLOBAL_SENSOR_GENERAL_ROTATION += 0.125;
		}
	}
	else if (key.keyState('C') || key.keyState('c'))
	{
		if (GLOBAL_SENSOR_GENERAL_ROTATION >= -30) {
			GLOBAL_SENSOR_GENERAL_ROTATION -= 0.125;
		}
	}
	// Steuerung der Sensoren
	else if (key.keyState('X') || key.keyState('x'))
	{
		GLOBAL_SENSORS_ROTATION -= 0.125;
	}
	else if (key.keyState('V') || key.keyState('v'))
	{
		GLOBAL_SENSORS_ROTATION += 0.125;
	}
	// Kamerasetting Folgen (An/ Aus)
	else if (1 == key.keyState('Z') || 1 == key.keyState('z'))
	{
		if (GLOBAL_CAM_MODE == 2) {
			GLOBAL_CAM_MODE = 0;
		}
		else {
			GLOBAL_CAM_MODE++;
		}
	}
	else if (key.keyState('p') || key.keyState('P'))
	{
		GLOBAL_STATIONDISTANCE += (float)0.05;
	}
	else if (key.keyState('o') || key.keyState('O'))
	{
		if (!(GLOBAL_STATIONDISTANCE <= 12))
		{
			GLOBAL_STATIONDISTANCE -= (float)0.05;
		}
	}
	// FPS Modi umschalten
	else if (1 == key.keyState('u') || 1 == key.keyState('U')) {
		if (FPS_MODE) {
			FPS_MODE = false;
		}
		else {
			FPS_MODE = true;
		}
	}

	// Szene zeichnen: CLEAR, SETCAMERA, DRAW_SCENE
	// Back-Buffer neu initialisieren
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Kamera setzen (spherische Mausnavigation)
	setCamera();

	// Koordinatensystem zeichnen
	help.drawKoordsystem(-8, 10, -8, 10, -8, 10);

	// Zeichenmodus einstellen (Wireframe on/off)
	glPolygonMode(GL_FRONT_AND_BACK, globState.drawMode);

	// Backface Culling on/off);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	if (globState.cullMode) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	// Auswahl Farbmodus oder Beleuchtungsmodus
	if (globState.lightMode == GL_TRUE) // Beleuchtung aktivieren
	{
		float m_amb[4] = { 0.2, 0.2, 0.2, 1.0 };
		float m_diff[4] = { 0.2, 0.2, 0.6, 1.0 };
		float m_spec[4] = { 0.8, 0.8, 0.8, 1.0 };
		float m_shine = 32.0;
		float m_emiss[4] = { 0.0, 0.0, 0.0, 1.0 };

		SetMaterial(GL_FRONT_AND_BACK, m_amb, m_diff, m_spec, m_shine, m_emiss);

		SetLights();

		glEnable(GL_LIGHTING);
	} else {  // Zeichnen im Farbmodus
		glDisable(GL_LIGHTING);
		glColor4f(0.2, 0.2, 0.6, 1.0);
	}

	// Geometrie zeichnen /////////////////!!!!!!!!!!!!!!!!!!!!!!!!///////////////////////
	drawScene();

	// Hilfetext zeichnen
	help.draw();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);

	glFlush();				// Daten an Server (fuer die Darstellung) schicken
	glutSwapBuffers();		// Buffers wechseln
}


void solarPanel() {
	glPushMatrix();
		glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glScalef(0.5, 0.5, 0.5);
			objects[SOLARPANEL].draw();
		glDisable(GL_CULL_FACE);
	glPopMatrix();
}


void solarConnector() {
	glPushMatrix();
			glColor3f(0.8, 0.8, 0.8);
			glScalef(0.25, 0.25, 3);
			glutSolidCube(1);
	glPopMatrix();
}


// Zeichnet einen Solararm mit zwei verbundenen Panelen mit der gegebenen Rotation
void solarArm(float x, float y, float z, float rotation) {
	glPushMatrix();
		glColor3f(0.169, 0.169, 0.169);
		glTranslatef(x, y - 0.375, z);
		glRotatef(-90, 1, 0, 0);
		glutSolidCylinder(0.25, 0.25, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(rotation, 0, 1, 0);

		glPushMatrix();
			glTranslatef(0, 8.25, 0);
			solarConnector();
		glPopMatrix();

		solarConnector();
		glTranslatef(0, 4.125, 1);
		solarPanel();

		glTranslatef(0, 0, -2);
		solarPanel();
	glPopMatrix();
}

// Zeichnet das kleine Sensorarray
void sensorArrayKlein(float x, float y, float z, float skalierung_x, float skalierung_y, float skalierung_z, int zacken) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(skalierung_x, skalierung_y, skalierung_z);
		glRotatef(90, 1, 0, 0);
		glColor3f(1, 1, 1);

		for (int i = 0; i < zacken; i++)
		{
			int grad = 45;
			glPushMatrix();
				glTranslatef(0, i * 0.265, 0);
			
				if (!(i % 2 == 0))
				{
					grad *= -1;
				}

				glRotatef(grad, 1, 0, 0);
				glScalef(4, 0.5, 0.125);
				glutSolidCube(1);
			glPopMatrix();
		}
		
	glPopMatrix();
}

// Zeichnet das grosse Sensorarray
void sensorArrayGross(float x, float y, float z, float general_rotation, float sensor_rotation, float skalierung) {
	glPushMatrix();
		// Verschiebe das Sensorarray zur benoetigten Stelle
		glTranslatef(x, y, z);
		// Setze die Skalierung des Objekts
		glScalef(skalierung, skalierung, skalierung);
		// Verbinder zu anderen Objekten
		glRotatef(general_rotation, 0, 0, 1);
		glPushMatrix();
			glColor3f(0.55,0.55,0.55);
			glutSolidCylinder(0.5, 0.5, SLICES, STACKS);
			glTranslatef(0, 0, 0.75);
			glScalef(12, 1, 0.5);
			glutSolidCube(1);
		glPopMatrix();

		// Array der Sensoren
		glPushMatrix();
			glColor3f(1, 1, 1);
			for (int i = 0; i < 12; i++)
			{
				glPushMatrix();
					double x = -4;
					double z = 3 + 4 * i * 0.7;
					if (i >= 4)
					{
						x = 0;
						z = 3 + 4 * (i - 4) * 0.7;
					}
					if (i >= 8)
					{
						x = 4;
						z = 3 + 4 * (i - 8) * 0.7;
					}
					glTranslatef(x, 0, z);
					glRotatef(sensor_rotation, 1, 0, 0);
					glScalef(3, 2, 0.25);
					glutSolidCube(1);
				glPopMatrix();
			}
		glPopMatrix();

		// Rahmen um und zwischen den Sensoren
		for (int i = 0; i < 6; i++)
		{
			glPushMatrix();
				glColor3f(0.123, 0.5, 1);
				double x = 0;
				if (i == 0) {
					x = -2.375 - 3.25;
				}
				if (i == 1) {
					x = -2.375;
				}
				if (i == 2) {
					x = -1.625;
				}
				if (i == 3) {
					x = -1.625 + 3.25;
				}
				if (i == 4) {
					x = 2.375;
				}
				if (i == 5) {
					x = 2.375 + 3.25;
				}
				glTranslatef(x, 0, 6.25);
				glScalef(0.25, 0.25, 10.5);
				glutSolidCube(1);
			glPopMatrix();
		}
	glPopMatrix();
}


void wing(float x, float y, float z, float rotation, float skalierung) {
	glPushMatrix();
		// Gegebene Skalierung anwenden
		glScalef(skalierung, skalierung, skalierung);

		// Traeger
		glPushMatrix();
			glColor3f(0.211, 0.211, 0.211);
			glTranslatef(x + 1.5, y, z);
			glScalef(12, 1, 1);
			glutSolidCube(1);
		glPopMatrix();


		// Obere Seite 3 Solarpanele
		for (int i = -1; i <= 1; i++)
		{
			solarArm(x + 3.25 * i, y + 0.875, z, rotation);
		}

		// Untere Seite 3 Solarpanele
		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		for (int i = -1; i <= 1; i++)
		{
			solarArm(x + 3.25 * i, y + 0.875, z, -rotation);
		}
		glPopMatrix();

		// Verbindungsstueck zur Basis der Station
		glPushMatrix();
			glColor3f(0.123, 0.123, 0.211);
			glTranslatef(x + 7.5, y, z);
			glRotatef(90, 0, 1, 0);
			glutSolidCylinder(1, 1, SLICES, STACKS);
		glPopMatrix();

		// 2 Sensorarrays (90 Grad zu den Solarpanelen)
		sensorArrayKlein(x - 2, y, z + 0.725, 0.5, 1, 3, 8);
		sensorArrayKlein(x + 4, y, z + 0.725, 0.5, 1, 3, 8);
	glPopMatrix();
}


// Hauptkoerper der Raumstation
void base(float x, float y, float z) {
	// Grundkoerper der Station
	glPushMatrix();
		glColor3f(0.134, 0.211, 0.211);
		glTranslatef(x, y, z);
		glScalef(30, 3, 3);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(x, y - 3, z);
		glScalef(5, 3, 3);
		glutSolidCube(1);
	glPopMatrix();

	// 2 Bewegbare Sensor Arrays Front
	sensorArrayGross(x + 10, y, z + 1.5, GLOBAL_SENSOR_GENERAL_ROTATION, GLOBAL_SENSORS_ROTATION, 1);
	sensorArrayGross(x - 10, y, z + 1.5, GLOBAL_SENSOR_GENERAL_ROTATION, GLOBAL_SENSORS_ROTATION, 1);
}


void base2() {
	glPushMatrix();
		glEnable(GL_CULL_FACE);
			// Nur Aussenseite des Zylinders rendern
			glCullFace(GL_BACK);
			glTranslatef(0, -1.5, -2.5);
			// Verbindungsstueck zwischen Base und Base 2 
			glutSolidCone(3, 2, SLICES, STACKS);
			glRotatef(180, 1, 0, 0);
			// Base 2 Hauptteil
			glutSolidCylinder(3, 20, SLICES, STACKS);
		glDisable(GL_CULL_FACE);
	glPopMatrix();
}


struct SpaceStation {
	float position[3];
	float scale;
	float rotation;
	float speed;

	SpaceStation()
	{
		position[0] = GLOBAL_STATIONPOS[0];
		position[1] = GLOBAL_STATIONPOS[1];
		position[2] = GLOBAL_STATIONPOS[2];
		rotation = GLOBAL_SPACESTATIONROTATION;
		scale = (float)0.05;
		speed = GLOBAL_STATIONSPEED;
	}

	void update()
	{
		position[0] = GLOBAL_STATIONPOS[0];
		position[1] = GLOBAL_STATIONPOS[1];
		position[2] = GLOBAL_STATIONPOS[2];
		rotation = GLOBAL_SPACESTATIONROTATION;
	}

	void draw()
	{
		glPushMatrix();
			glRotatef(rotation, 0, 1, 0);
			glTranslatef(position[0], position[1], position[2]);
			glScalef(scale, scale, scale);
			glPushMatrix();
				wing(-18.5, 0, 0, GLOBAL_SOLAR_ROTATION, 1.5);
				base(0, 0, 0);
				base2();
				glRotatef(-180, 0, 0, 1);
				wing(-18.5, 0, 0, -GLOBAL_SOLAR_ROTATION, 1.5);
			glPopMatrix();
		glPopMatrix();
	}
};

struct Earth {
	float rotation;
	float position[3];

	Earth ()
	{
		rotation = GLOBAL_EARTHROTATION;
		position[0] = 0;
		position[1] = 0;
		position[2] = 0;
	}

	void update()
	{
		rotation = GLOBAL_EARTHROTATION;
	}

	void draw()
	{
		glPushMatrix();
			glRotatef(rotation, 0, 1, 0);
			glColor3f(0, 0, 1);
			glutSolidSphere(10, SLICES, STACKS);
		glPopMatrix();
	}
};

void drawLights() {
	// Erstellen 8er Lichter, die permanent die Station beleuchten
	static cg_light test[7] = { 1 , 2 , 3, 4, 5, 6, 7 };
	for (int i = 0; i < 7; i++)
	{
		float offset_x = 5;
		float offset_y = 5;
		float offset_z = 5;

		// Offset pro Lichtquelle bestimmen: In jedem Quadranten eine Lichtquelle
		switch (i) {
			case 0:
				break;
			case 1:
				offset_x *= -1;
				break;
			case 2:
				offset_y *= -1;
				break;
			case 3:
				offset_z *= -1;
				break;
			case 4:
				offset_x *= -1;
				offset_y *= -1;
				break;
			case 5:
				offset_x *= -1;
				offset_z *= -1;
				break;
			case 6:
				offset_y *= -1;
				offset_z *= -1;
				break;
			case 7:
				offset_x *= -1;
				offset_y *= -1;
				offset_z *= -1;
				break;
		}

		// Erstelle eine Lichtquelle mit dem Offset offset zur Station
		float offset[3] = { offset_x, offset_y, offset_z };
		float position[3] = { GLOBAL_STATIONPOS[0] + offset[0], GLOBAL_STATIONPOS[1] + offset[1], GLOBAL_STATIONPOS[2] + offset[2] };
		test[i].setPosition(position[0], position[1], position[2], 0);
		test[i].setAmbient(0.1, 0.1, 0.1, 1.0);
		test[i].setDiffuse(0.5, 1.0, 0.3, 1.0);
		test[i].setSpecular(1.0, 1.0, 0.3, 1.0);
		test[i].setAttentuation(1.0, 0.05, 0.0);
		test[i].enable();
		test[i].draw();
	}
}

void drawScene() {	
	cg_globState globState;
	// Zeichnet die Szene 1x im Weltkoordinatensystem
	// Festlegen der Geschwindigkeit der Erdrotation
	GLOBAL_EARTHROTATION += (float)0.01;

	// Festlegen des Pfades und der Geschwindigkeit der Rotation der Raumstation um den Planeten
	// GLOBAL_STATIONDISTANCE bestimmt den Abstand der Station von der Erde
	// GLOBAL_STATIONSPEED bestimmt die Geschwindigkeit des Orbits
	if (FPS_MODE == 0) {
		GLOBAL_STATIONPOS[0] = GLOBAL_STATIONDISTANCE * sin(GLOBAL_EARTHROTATION * GLOBAL_STATIONSPEED);
		GLOBAL_STATIONPOS[1] = GLOBAL_STATIONDISTANCE * cos(GLOBAL_EARTHROTATION * GLOBAL_STATIONSPEED);
	}
	else {
		// 60 ist der Faktor um den die normale Geschwindigkeit multipliziert wird, um moeglichst gleiche Geschwindigkeiten zwischen den Modi zu erzielen
		GLOBAL_STATIONPOS[0] = GLOBAL_STATIONDISTANCE * sin(GLOBAL_EARTHROTATION * ((GLOBAL_STATIONSPEED * 60) / (MAX(1, cg_help::getFps()))));
		GLOBAL_STATIONPOS[1] = GLOBAL_STATIONDISTANCE * cos(GLOBAL_EARTHROTATION * ((GLOBAL_STATIONSPEED * 60) / (MAX(1, cg_help::getFps()))));
		GLOBAL_STATIONPOS[2] = 0;
	}	
	
	// Objekte instanziieren (Erde und Raumstation)
	static Earth myEarth;
	myEarth.update();
	myEarth.draw();

	static SpaceStation mySpacestation;
	mySpacestation.update();
	mySpacestation.draw();

	// Im Falle der Beleuchtung, wird das Modell der Station von 8 Lichtquellen (in jedem "Oktanten" eine) beleuchtet
	if (globState.lightMode == GL_TRUE) {
		drawLights();
	}
}
