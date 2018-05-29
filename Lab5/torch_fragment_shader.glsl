uniform vec4 color;
varying vec4 vtx;
uniform vec3 torch_position;
uniform vec4 torch_first_color;
uniform vec4 torch_second_color;
uniform vec3 normal;
uniform bool lighting;
uniform float time;

void main() {
    if (lighting) {
    
    	float t = (sin(time) + 1.0) / 2.0;
    	vec4 light_color = t * torch_first_color + (1.0 - t) * torch_second_color;
    
    
        vec3 dir = torch_position - vec3(vtx);
        float intensity = dot(normalize(normal), normalize(dir));
        if (intensity < 0.0) intensity = 0.0;
        intensity = intensity / length(dir) / 2.0;
        gl_FragColor = color + (light_color - color) * intensity;
    }
    else gl_FragColor = color;

}
