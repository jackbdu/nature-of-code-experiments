OF_GLSL_SHADER_HEADER

#define MAX_PARTICLES_NUM 200

uniform float uTime;
uniform vec2 uWindowSize;
uniform vec4 uParticles[MAX_PARTICLES_NUM];

void main()
{
  const float baseIntensity = 1.8;

  float windowWidth = uWindowSize.x;
  float windowHeight = uWindowSize.y;

  vec3 outColor = vec3(0.);
    
  for (int i = 0; i < MAX_PARTICLES_NUM; i++) {
    vec2 position = vec2(uParticles[i].x, windowHeight - uParticles[i].y);
    float lifespan = uParticles[i].z;
    float flickerFrequency = uParticles[i].w;
    float intensity = baseIntensity * abs(sin(lifespan * flickerFrequency)) * lifespan;
    // float intensity = 1.4 * lifespan; // no flickering
    float dist = distance(position, gl_FragCoord.xy);

    vec3 color = vec3(sin(lifespan + 3 + uTime),
                              sin(lifespan + 2),
                              sin(lifespan + 1));
    color *= pow(1. / dist, 1. / intensity);
    outColor.rgb += color;
  }

	gl_FragColor = vec4(sqrt(outColor), 1.);
}
