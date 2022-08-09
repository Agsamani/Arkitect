#version 460 core

out vec4 FragColor;

uniform mat4 u_Transform;
uniform mat4 u_RayRotation;
uniform float u_Var;
uniform int u_Power;

uniform vec3 u_GlowColor;
uniform vec3 u_BGColor;
uniform vec3 u_AColor;
uniform vec3 u_BColor;


float SphereSDF(vec3 rayPos, vec3 center, float radius) {
    return distance(rayPos, center) - radius;
}

float DE(vec3 pos) {
    int Power = u_Power;
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
    
    return DE(rayPos);
    //min(SphereSDF(rayPos, vec3(0.0, 0.0, 0.0), 0.7), SphereSDF(rayPos, vec3(1.5, 0.0, 0.0), 1.0));
}

vec3 EstimateNormal(vec3 ray) {
    float epsilon = 0.001;
    return normalize(vec3(
        SceneSDF(vec3(ray.x + epsilon, ray.y, ray.z)) - SceneSDF(vec3(ray.x - epsilon, ray.y, ray.z)),
        SceneSDF(vec3(ray.x, ray.y + epsilon, ray.z)) - SceneSDF(vec3(ray.x, ray.y - epsilon, ray.z)), 
        SceneSDF(vec3(ray.x, ray.y, ray.z + epsilon)) - SceneSDF(vec3(ray.x, ray.y - epsilon, ray.z))
    ));
}


void main()
{
    vec3 lightPos = vec3(5.0, 0.0, 0.0);
    vec3 sunLightDir = normalize(vec3(-1.0));
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec2 screenCoord = (gl_FragCoord.xy / 1280.0) * 2.0 - vec2(2048.0/1280.0,1.0);
    float planeDist = 3.0;

    vec3 eye = (u_RayRotation * u_Transform * vec4(0.0, 0.0, 0.0, 1.0)).xyz; // u_RayRotation * 

    int MAX_ITERATION = 200;
    float collisionThreshold = 0.00005;
    float maxRayDist = 20.0;

    vec3 ray = vec3(0.0);//vec3(vec3(screenCoord, planeDist)) / 4.0; // u_RayRotation * 
    vec3 rayDir = (u_RayRotation * normalize(vec4(screenCoord, planeDist, 1.0))).xyz;
    //ray = vec3(0.0);

    bool hit = true;

    int iterations = 0;
    float dist = SceneSDF(eye + ray);
    while (dist > collisionThreshold && iterations <= MAX_ITERATION) {
        ray += rayDir * dist;

        if (length(ray) >= maxRayDist) {
            hit = false;
            break;
        }


        dist = SceneSDF(eye + ray);
        iterations++;
    }

    vec3 normal = EstimateNormal(eye + ray);
    //////////////////////////////////////

    vec3 hitPos = eye + ray;
    rayDir = sunLightDir;//normalize(lightPos - hitPos);//reflect(rayDir, normal);
    ray = rayDir * (collisionThreshold * 100.0);

    bool hit2 = true;
    int iterations2 = 0;
    dist = SceneSDF(hitPos + ray);
    
    float minAngle = 3.14/ 2.0;
    float minDist = dist;
    while (dist > collisionThreshold && iterations2 <= MAX_ITERATION) {
        float angle = asin(dist/length(ray));
        minAngle = min(minAngle, angle);

        ray += rayDir * dist;

        if (length(ray) >= maxRayDist) {
            hit2 = false;
            break;
        }
        

        dist = SceneSDF(hitPos + ray);
        minDist = min(minDist, dist);
        iterations2++;
    }

    

    float itRatio = (float(iterations))/MAX_ITERATION;
    float AmbientOcclusion = 1 - itRatio;
    if (hit) {
        
        vec3 baseColor = vec3(u_AColor.x * AmbientOcclusion + u_BColor.y, u_AColor.y, u_AColor.z * itRatio + u_BColor.z);//mix(u_AColor, u_BColor, (itRatio * itRatio)) ;
        vec3 oColor = baseColor * AmbientOcclusion;
        
        float shadowDensity = u_BColor.x;
        if(hit2) {
            oColor *= 1.0 * shadowDensity;
        } else {
            oColor *= sin(min(minAngle, 3.14/2.0)) * (1 - shadowDensity) + shadowDensity ;
        }
        
        FragColor = vec4(oColor, 1.0);
    } else {
        FragColor = vec4(mix(u_BGColor, u_GlowColor, pow(itRatio, 2)), 1.0);
    }

    float gamma = 2.2;
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
} 