# Dokumentation

## Szenengraph

-> Planet
--> Raumstation
---> Solarpanele
---> Sensorarray
---> Sensoren

## Ordnerstruktur

- docs - Dokumentation
- Include - freeglut und andere dependencies
- Texturen - Textur für die Solarpanele

## Zusammenfassung

In meinem Projekt erstellte ich eine Raumstation, Modell angelehnt an die Internationale Raumstation ISS (Referenz iss.jpg), die um den Planeten Erde rotiert. Teile der Station sind steuerbar,
wie z.B. die Solarpanele oder Sensorarrays, welche rotiert werden können. Alle steuerbaren Elemente sind in der internen Hilfe (Taste "h") sichtbar und auch im Screenshot hilfe.png dokumentiert.

Weiterhin ist es möglich die Distanz zur Erde zu verändern, um welche die Station im Orbit rotiert. Mit z kann zwischen 3 verschiedenen Kameramodi gewechselt werden. Im Standard ist der Planet im Vordergrund und die Station im Orbit. Der zweite Kameramodus folgt dem Orbit und zeigt die Station aus einem bestimmten Winkel. Im dritten Modus kann man die Raumstation sehr nah in Detailansicht betrachten.

## Steuerung

h, H - Hilfeseite anzeigen

### Grundlegende Steuerung
linke Maus Taste      - Kamerabewegung
mittlere Maus Taste   - Zoom
rechte Maus Taste     - Kontextmenü

### Steuerungen Raumstation
a,A    - Rotation Solarpanele (links)
d,D    - Rotation Solarpanele (rechts)
y,Y    - Rotation Sensorarray (links)
c,C    - Rotation Sensorarray (rechts)
x,X    - Rotation Sensoren (links)
v,V    - Rotation Sensoren (rechts)
o,O    - Distanz Erde - Station verringern
p,P    - Distanz Erde - Station inkrementieren

### Grafikoptionen
f,F    - Framerate (An/Aus)
l,L    - Licht global (An/Aus)
h,H,F1 - Hilfe (An/Aus)
w,W    - WireFrame (An/Aus)
k,K    - Koordinatensystem (An/Aus)
b,B    - Backfaceculling (An/Aus)

### Steuerung Kamera
z, Z   - Kameramodus wechseln (Standard | Orbit folgen | Detailansicht)
u,U    - Geschwindigkeit an FPS anpassen (an/ aus)
ESC    - Beenden
