#version 460 core

out vec4 FragColor;

uniform mat4 u_Transform;
uniform mat4 u_RayRotation;
uniform float u_Var;

float SphereSDF(vec3 rayPos, vec3 center, float radius) {
    return distance(rayPos, center) - radius;
}

float DE(vec3 pos) {
    int Power = 8;
    int Iterations = 100;
    float Bailout = 2;
	vec3 z = pos;
	float dr = 1.0;
	float r = 0.0;
	for (int i = 0; i < Iterations ; i++) {
		r = length(z);
		if (r>Bailout) break;
		
		// convert to polar coordinates
		float theta = acos(z.z/r) + u_Var;
		float phi = atan(z.y,z.x) + u_Var;
		dr =  pow( r, Power-1.0)*Power*dr + 1.0;
		
		// scale and rotate the point
		float zr = pow( r,Power);
		theta = theta*Power;
		phi = phi*Power;
		
		// convert back to cartesian coordinates
		z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
		z+=pos;
	}
	return 0.5*log(r)*r/dr;
}

float PolynomialSMin( float a, float b, float k )
{
    float h = max( k-abs(a-b), 0.0 )/k;
    return min( a, b ) - h*h*k*(1.0/4.0);
}

float IntersectSDF(float distA, float distB) {
    return max(distA, distB);
}

float UnionSDF(float distA, float distB) {
    return min(distA, distB);
}

float DifferenceSDF(float distA, float distB) {
    return max(distA, -distB);
}

float SceneSDF(vec3 rayPos) {
    return //DE(rayPos);
    PolynomialSMin(SphereSDF(rayPos, vec3(0.0, 0.0, 0.0), 1.0), SphereSDF(rayPos, vec3(1.0, 0.0, 0.0), 1.5), 0.2);
}

vec3 EstimateNormal(vec3 ray) {
    float epsilon = 0.01;
    return normalize(vec3(
        SceneSDF(vec3(ray.x + epsilon, ray.y, ray.z)) - SceneSDF(vec3(ray.x - epsilon, ray.y, ray.z)),
        SceneSDF(vec3(ray.x, ray.y + epsilon, ray.z)) - SceneSDF(vec3(ray.x, ray.y - epsilon, ray.z)), 
        SceneSDF(vec3(ray.x, ray.y, ray.z + epsilon)) - SceneSDF(vec3(ray.x, ray.y - epsilon, ray.z))
    ));
}


void main()
{
    vec3 lightAPos = vec3(0.0);

    vec3 eye = ( u_RayRotation * u_Transform * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    vec3 viewCoord = vec3((gl_FragCoord.xy / 1050) * 2.0 - vec2(1680.0/1050.0,1.0), 5.0) / 2.5;

    int MAX_ITERATION = 30;
    float collisionThreshold = 0.0001;
    float maxRayDist = 20.0;

    vec3 ray = (u_RayRotation * vec4(viewCoord , 1.0)).xyz ;
    vec3 rayDir = normalize(ray);

    bool hit = true;

    int iterations = 0;
    float dist = SceneSDF(ray);
    while (dist > collisionThreshold && iterations <= MAX_ITERATION) {
        ray += rayDir * dist;

        if (distance(ray, eye) >= maxRayDist) {
            hit = false;
            break;
        }

        dist = SceneSDF(eye + ray);
        iterations++;
    }

    if (hit) {
        float itRatio = (float(iterations))/MAX_ITERATION;
        float AmbientOcclusion = 1 - itRatio;
        vec3 normal = EstimateNormal(eye + ray)/2.0 + 0.5;
        float lightDensity = dot(normal,normalize(eye + ray - lightAPos));
        FragColor = vec4((vec3( (AmbientOcclusion * AmbientOcclusion ), 0.8, 0.2 + itRatio)) * AmbientOcclusion ,1.0);//vec4(0.8, 0.7, 0.2,1.0);
    } else {
        FragColor = vec4(0.11, 0.09, 0.1,1.0);
    }
} 