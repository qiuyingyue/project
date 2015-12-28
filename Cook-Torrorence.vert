uniform vec3 lightPos;
varying vec3 lightDir,normal;
  
void main()  
{  
    normal = normalize(gl_NormalMatrix * gl_Normal);
	gl_Position = ftransform();  
    //lightDir = normalize(lp-gl_Position.xyz);
    lightDir = normalize(vec3(gl_LightSource[0].position)); 
    //lightDir = normalize(lightPos);
}  
