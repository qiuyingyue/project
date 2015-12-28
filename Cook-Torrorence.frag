uniform vec3 diffuse,ambient,rf;
uniform float roughness;
varying vec3 normal,lightDir;

vec3 xdot(vec3 a, vec3 b){
	vec3 c;
	c.x = a.x*b.x;
	c.y = a.y*b.y;
	c.z = a.z*b.z;
	return c;
}
vec3 CTbrdf(vec3 n, vec3 l, vec3 v){
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
	Den = 4.0*ndotl*ndotv;
	//Cook-Torrance
	G =min(1.0, min(2.0*ndoth*ndotv/vdoth,2.0*ndoth*ndotl/vdoth));
	//GGX
	D = pow(a,2.0)/(3.1415926*pow(
    		(pow(ndoth,2.0)*(a*a-1.0)+1.0)
        	,2.0));
    //Schilick Approximation
    F = rf + pow((1.0-ldoth),5.0)*(unit - rf);
    brdf = D*G*ndotl/Den*F;
    return brdf;
}

void main(){
	vec3 view,norm;
    vec3 cf;
    float af;
    vec3 brdf;//result
    norm = normalize(normal);
    view = vec3(0.0,0.0,1.0);
	if(dot(normal,lightDir)<0.0)
		brdf = vec3(0.0,0.0,0.0);
	else
		brdf = CTbrdf(norm,lightDir,view);
    cf = xdot(brdf,diffuse) + ambient;
    af = 1.0;
    gl_FragColor = vec4(cf, af); 
}
