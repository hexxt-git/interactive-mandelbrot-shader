#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform vec2 screenDims;
uniform vec2 offset;
uniform float zoom;

const int MAX_ITERATIONS = 3000;

vec2 ComplexSquare(vec2 z){
    return vec2(
        z.x * z.x - z.y * z.y,
        z.x * z.y * 2.0
    );
}


void main() {
    
    float greater = float(screenDims.x);
    if(screenDims.y > screenDims.x){
        greater = float(screenDims.y);
    }

    vec2 z0 = vec2(
        (fragTexCoord.x - 0.5 ) * screenDims.x / greater / zoom + offset.x,
        (fragTexCoord.y - 0.5 ) * screenDims.y / greater / zoom + offset.y
    );

    vec2 z = z0;

    int iterations = 0;
    for (iterations = 0; iterations < MAX_ITERATIONS; iterations++){
        z = ComplexSquare(z) + z0;
        if (abs(z.x+z.y) > 4.0) break;
    }

    float smoothVal = float(iterations) + 1.0 - (log(log(length(z))) / log(2.0));
    float norm = pow(smoothVal / float(MAX_ITERATIONS), 0.5);
    if (iterations == MAX_ITERATIONS) finalColor = vec4(0.0, 0.0, 0.0, 1.0);
    else finalColor = vec4(norm, norm, norm, 1.0);
}