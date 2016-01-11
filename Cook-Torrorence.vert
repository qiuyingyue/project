//uniform vec3 lightPos;
uniform vec4 eyepos;
varying vec3 normal;
varying vec4 ecPos; //lightDir
  
void main()  
{  
    /* these are the new lines of code to compute the light's direction */  
    ecPos = gl_ModelViewMatrix * gl_Vertex;  
    normal = normalize(gl_NormalMatrix * gl_Normal);
    //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();  
    //vec4 veyePos = (gl_ModelViewMatrix * eyepos);
    //vec4 pos = ecPos / ecPos.w;
    //eyedir  = normalize(veyePos.xyz - pos.xyz);
}  
