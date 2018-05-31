uniform sampler2D qt_Texture0;

uniform float time;


varying vec2 qt_TexCoord0;
varying vec3 qt_CoordVer;

vec3 point = vec3(time*5.0,0.0,0.0);

void main(void)
{
    vec4 col = texture2D(qt_Texture0, qt_TexCoord0);
    gl_FragColor = col;

}
