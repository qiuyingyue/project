uniform vec3 rf,ambient;//diffuse,ambient
uniform float roughness;
uniform int lightNum;
uniform sampler2D tex;
uniform sampler2D env_brdf;
uniform float density;
varying vec3 normal;
varying vec4 ecPos; 


vec3 xdot(vec3 a, vec3 b, float Distance){
	vec3 c;
	c = a*b;
	float constant = 1;
	float linear = 0.5;
	float expo = 0.5;
	float Attenuation = constant + linear*Distance + expo*Distance*Distance; 
	c /= Attenuation;
	return c;
}

vec3 CTbrdf(vec3 n, vec3 l, vec3 v){
	if(dot(n,l)<0.0)
		return vec3(0.0,0.0,0.0);
	vec3 F,h,brdf,unit;
	float D,Den,G,GD;
	float a = roughness*roughness;//roughness;
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
	if(ndotv!=0.0)
		GD = G/Den;
	else
		GD = ndoth/vdoth/2.0;
	//GGX
	if(ndoth!=0.0)
		D = pow((a/(pow(ndoth,2.0)*(a*a-1.0)+1.0)),2.0)/3.1415926;
	else
		D = 1.0;
    //Schilick Approximation
    F = rf + pow((1.0-ldoth),5.0)*(unit - rf);
    brdf = D*GD*F;//*ndotl
    return brdf;
}

void main(){
	vec3 view,norm;
    vec3 cf,ct;
    float af,at,distance;
    int i;
    vec3 brdf;//result 
    vec3 aux,lightDir;
    vec4 texel;

    norm = normalize(normal);
	//view = vec3(0.0,0.0,1.0);
	view = normalize(vec3(vec4(0.0,0.0,0.0,1.0)-ecPos));
    cf = vec3(0.0,0.0,0.0);
    for(i=0;i<=lightNum;i++){
    	aux = vec3(gl_LightSource[i].position-ecPos); 
    	distance = length(aux);
    	lightDir = normalize(aux); 
        //lightDir = vec3(0.0,0.0,1.0);
		brdf = CTbrdf(norm,lightDir,view);
    	cf += xdot(brdf, gl_LightSource[i].diffuse.rgb,distance);
    }

    float NoV = min(0.99,max(dot(norm,view),0.01));//1.0/256.0);
    vec4 ibl =  texture2D(env_brdf, vec2(1.0-NoV,roughness/1.5));
    cf += density*(ibl.r*rf + ibl.g);
    //Texture
    texel = texture2D(tex,vec2(gl_TexCoord[0].s,gl_TexCoord[0].t));
    ct = texel.rgb;  
    at = texel.a;
    af = 1.0; 
    gl_FragColor = vec4(ct,at); //
    gl_FragColor = vec4(cf*ct, af); 
    //gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}

/*vec3 ImportanceSampleGGX(vec2 Xi, float Roughness, vec3 N){
    float a = Roughness * Roughness;
    float Phi = 2.0 * 3.1415926 * Xi.x;
    float CosTheta = sqrt( (1.0 - Xi.y) / ( 1.0 + (a*a - 1.0) * Xi.y ) );
    float SinTheta = sqrt( 1.0 - CosTheta * CosTheta );
    vec3 H;
    H.x = SinTheta * cos( Phi );
    H.y = SinTheta * sin( Phi );
    H.z = CosTheta;
    vec3 UpVector = abs(N.z) < 0.999 ? vec3(0.0,0.0,1.0) : vec3(1.0,0.0,0.0);
    vec3 TangentX = normalize( cross( UpVector , N ) );
    vec3 TangentY = cross( N, TangentX );
    // Tangent to world space
    return TangentX * H.x + TangentY * H.y + N * H.z;
}

float saturate(float f){
    return min(1.0,max(0.0,f));
}

vec2 Hammersley(int i, int N){
    vec2 Xi;
    Xi.x = i*1.0/N;
    Xi.y = 0.0;
    float base = 2.0;
    float next= i;
    float inv_base = 1.0/base;
    float f = inv_base;//Base is 2
    while(next>0.0){
        Xi.y += f*mod(next,2);
        next = floor(next/base);
        f *= inv_base;
    }
    return Xi;
}

vec2 IntegrateBRDF(float NoV, vec3 N){
    vec3 V;
    V.x = sqrt( 1.0f - NoV * NoV ); // sin
    V.y = 0.0;
    V.z = NoV; // cos
    float A = 0.0;
    float B = 0.0;
    int NumSamples = 1024;
    for(int i = 0; i < NumSamples; i++ ){
        vec2 Xi = Hammersley( i, NumSamples );
        vec3 H = ImportanceSampleGGX( Xi, roughness , N );
        vec3 L = 2.0 * dot( V, H ) * H - V;
        float NoL = saturate( L.z );
        float NoH = saturate( H.z );
        float VoH = saturate( dot( V, H ) );
        if( NoL > 0.0 ){
            float G = (VoH==0)?1.0:min(1.0, min(2.0*NoH*NoV/VoH,2.0*NoH*NoL/VoH));
            float G_Vis = G * VoH / (NoH * NoV);
            float Fc = pow( 1.0 - VoH, 5.0 );
            A += (1.0 - Fc) * G_Vis;
            B += Fc * G_Vis;
        }
    }
    return vec2( A, B ) / NumSamples;
}

vec3 ApproximateSpecularIBL(vec3 N, vec3 V){
    float NoV = saturate(dot(N,V));
    vec2 EnvBRDF = IntegrateBRDF( NoV , N);
    return ( EnvBRDF.x*rf + EnvBRDF.y );
}
*/