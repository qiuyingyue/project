uniform vec3 rf,ambient;//diffuse,ambient
uniform float roughness;
uniform int lightNum;
varying vec3 normal;
varying vec4 ecPos; 
//varying vec3 eyedir;

vec3 xdot(vec3 a, vec3 b, float Distance){
	vec3 c;
	c.x = a.x*b.x;
	c.y = a.y*b.y;
	c.z = a.z*b.z;
	float constant = 1;
	float linear = 0.05;
	float expo = 0.05;
	float Attenuation = constant + linear*Distance + expo*Distance*Distance; 
	c /= Attenuation;
	return c;
}

vec3 CTbrdf(vec3 n, vec3 l, vec3 v){
	if(dot(n,l)<0.0)
		return vec3(0.0,0.0,0.0);
	vec3 F,h,brdf,unit;
	float D,Den,G;
	float a = pow(roughness,2.0);//roughness;
	float ndotv,ndoth,ndotl,vdoth,ldoth;
	unit = vec3(1.0,1.0,1.0);
	h = normalize(v+l);
	ndotv = max(dot(n,v),0.0);
	ndoth = max(dot(n,h),0.0);
	ndotl = max(dot(n,l),0.0);
	vdoth = max(dot(v,h),0.0);
	ldoth = max(dot(l,h),0.0);
	Den = 4.0*ndotv;//*ndotl
	if(Den==0.0) Den=1.0;
	//Cook-Torrance
	if(vdoth!=0.0)
		G =min(1.0, min(2.0*ndoth*ndotv/vdoth,2.0*ndoth*ndotl/vdoth));
	else
		G = 1.0;
	//GGX
	if(ndoth!=0.0)
		D = pow((a/(pow(ndoth,2.0)*(a*a-1.0)+1.0)),2.0)/3.1415926;
	else
		D = 1.0;
    //Schilick Approximation
    F = rf + pow((1.0-ldoth),5.0)*(unit - rf);
    if(ndotv==0.0) brdf = vec3(1.0,1.0,1.0);
    else brdf = D*G/Den*F;//*ndotl
    return brdf;
}

void main(){
	vec3 view,norm;
    vec3 cf;
    float af,distance;
    int i;
    vec3 brdf;//result 
    vec3 aux,lightDir;
    norm = normalize(normal);
	//view = vec3(0.0,0.0,1.0);
	view = normalize(vec3(vec4(0.0,0.0,0.0,1.0)-ecPos));
	//view = eyedir;
    cf = vec3(0.0,0.0,0.0);
    for(i=0;i<=lightNum;i++){
    	aux = vec3(gl_LightSource[i].position-ecPos); 
    	distance = length(aux);
    	lightDir = normalize(aux); 
		brdf = CTbrdf(norm,lightDir,view);
    	cf += xdot(brdf, gl_LightSource[i].diffuse.xyz,distance);
    }
    cf += gl_LightSource[0].ambient.xyz;
    //if(cf.x>1) cf.x=1;
    //if(cf.y>1) cf.y=1;
    //if(cf.z>1) cf.z=1;
    af = 1.0;
    gl_FragColor = vec4(cf, af); 
}
