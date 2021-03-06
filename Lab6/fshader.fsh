uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower;

varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;

vec2 SineWave( vec2 p )
{
    float tx=0.3477;
    float ty=0.7812;

    // convert Vertex position <-1,+1> to texture coordinate <0,1> and some shrinking so the effect dont overlap screen
    p.x=( 0.55*p.x)+0.5;
    p.y=(-0.55*p.y)+0.5;
    // wave distortion
    float x = sin( 25.0*p.y + 30.0*p.x + 6.28*tx) * 0.05;
    float y = sin( 25.0*p.y + 30.0*p.x + 6.28*ty) * 0.05;
    return vec2(p.x+x, p.y+y);
}

void main(void)
{
    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 diffuseMaterialColor = texture2D(u_texture, v_texcoord);
    vec3 eyeVector = normalize(v_position.xyz - eyePosition.xyz);
    vec3 lightVector = normalize(v_position.xyz - u_lightPosition.xyz);
    vec3 reflectLight = normalize(reflect(lightVector, v_normal));
    float len = length(v_position.xyz - eyePosition.xyz);
    float specularFactor = 50.0;
    float ambientFactor = 0.1;

    vec4 diffuseColor = diffuseMaterialColor * u_lightPower * max(0.0, dot(v_normal, -lightVector)); // / (1.0 + 0.25 * len * len);
    resultColor += diffuseColor;

    vec4 ambientColor = ambientFactor * diffuseMaterialColor;
    resultColor += ambientColor;

    vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0) * u_lightPower * pow(max(0.0, dot(reflectLight, -eyeVector)), specularFactor); // / (1.0 + 0.25 * len * len);
    resultColor += specularColor;

    // добавляем волны
    //resultColor += texture2D(u_texture, SineWave(v_texcoord));

    //float luminance = resultColor.r * 0.299 + resultColor.g * 0.587 + resultColor.b * 0.114;

    // черно - белая картинка
    //resultColor = vec4(luminance, luminance, luminance, 1.0);

    gl_FragColor = resultColor;
}
