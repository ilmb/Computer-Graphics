attribute vec4 vertex;
uniform mat4 mvp;
varying vec4 vtx;
void main() {
    gl_Position = mvp * vertex;
    vtx = vertex;

}
