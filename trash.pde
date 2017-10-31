boolean squareVisible = true;
int x = 50;
int y = 50;
int w = 100;
int h = 100;
import processing.serial.*;
Serial port;
int val;

void setup() {
    size(200, 200);
    noStroke();
    fill(255, 0, 0);
    rect(x, y, w, h);

    port = new Serial(this, 9600);
}

void draw() {
    background(255);
    if (squareVisible) {
        fill(40, 80, 90);
    } else {
        fill(255, 0, 0);
    }
    rect(x, y, w, h); // Draw a square
}


void mousePressed() {
    if (((mouseX > x) && (mouseX < x + w) &&
            (mouseY > y) && (mouseY < y + h))) {
        // if mouse clicked inside square
        squareVisible = !squareVisible;  // toggle square visibility
    }
}

void mouseMoved() {
    if (((mouseX > x) && (mouseX < x + w) &&
            (mouseY > y) && (mouseY < y + h))) {
        port.write("H");                 // send an H to indicate mouse is over square
    }
}
