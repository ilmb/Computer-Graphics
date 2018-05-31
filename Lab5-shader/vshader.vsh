attribute vec4 a_position;
attribute vec2 a_textcoord0;

uniform mat4 MVPMatrix;
uniform float time;

varying vec2 qt_TexCoord0;
varying vec3 qt_CoordVer;

void main(void)
{
    vec4 newPos = vec4(a_position);
    if(newPos.z >-3.0)
    {
        newPos.z = sin((newPos.x+time) * 10.0) / 5.0;
    }
    gl_Position = MVPMatrix * newPos;

    qt_TexCoord0 = a_textcoord0;
    qt_CoordVer = newPos.xyz;
}
