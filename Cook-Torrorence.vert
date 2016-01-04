uniform vec3 lightPos;
varying vec3 lightDir,normal;
  
void main()  
{  
    vec4 ecPos;  
    vec3 aux;  
    normal = normalize(gl_NormalMatrix * gl_Normal);  
    /* these are the new lines of code to compute the light's direction */  
    ecPos = gl_ModelViewMatrix * gl_Vertex;  
    aux = vec3(gl_LightSource[0].position-ecPos);  
    lightDir = normalize(aux);  
	gl_Position = ftransform();  
    //lightDir = normalize(lp-gl_Position.xyz);
    //lightDir = normalize(lightPos);
    //vec3 lp = gl_NormalMatrix * (gl_LightSource[0].position - gl_Vertex).xyz;
    //lightDir = normalize(lp); 
}  
