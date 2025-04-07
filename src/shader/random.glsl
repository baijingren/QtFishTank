#version 330
uniform uint u_seed;
uniform float u_time;

float randcore(uint seed){
    seed = (seed ^ 61u) ^ (seed >> 16u);
    seed *= 9u;
    seed = seed ^ (seed >> 4u);
    seed *= 0x27d4eb2du;
    u_seed = seed ^ (seed >> 15u);
    return float(u_seed) / 4294967296.0;
}
float rand(float x){
    return randcore(u_seed);
}