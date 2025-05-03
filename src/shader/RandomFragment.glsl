#version 330
uniform uint u_seed;
uniform float u_time;
in vec2 fragCoord;
out vec4 fragColor;

float randcore(uint seed){
    seed = (seed ^ 61u) ^ (seed >> 16u);
    seed *= 9u;
    seed = seed ^ (seed >> 4u);
    seed *= 0x27d4eb2du;
    u_seed = seed ^ (seed >> 15u);
    return float(u_seed) / 4294967296.0;
}
float rand(){
    return randcore(u_seed);
}
void main(){
    u_seed = uint(float(69557857) * (fragCoord.x * fragCoord.y)) * u_seed;
    if(distance(fragCoord, vec2(0.5)) < 0.4){
        fragColor = vec4(rand(), rand(), rand(), 1.0);
    }
    else{
        fragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}