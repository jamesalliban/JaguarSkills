#version 110

uniform sampler2D tex0;
uniform sampler2D texDepthMap;

varying vec3 v;
varying vec3 N;
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform float shinyness;
uniform float shadowIntensity;
uniform int isBumpMapActive;
uniform float bumpMapStrength;

varying vec4 v_col;

void main()
{	
	vec3 L = normalize(gl_LightSource[0].position.xyz - v);
	vec3 E = normalize(-v); 
	vec3 R = normalize(-reflect(L,N));
    
    if (gl_FrontFacing)  // the mesh seems to be facing the worng way.
        L *= -1.0;
    
    // bump map
    //vec3 bumpNormal = normalize(texture2D(texDepthMap, gl_TexCoord[0].st).rgb * 2.0 - 1.0) * 0.9;
    vec3 bumpNormal = ((texture2D(texDepthMap, gl_TexCoord[0].st).rgb - 1.0) * 2.0) * bumpMapStrength;
    
	// ambient term 
	vec4 Iamb = ambient;

	// diffuse term
	vec4 Idiff = texture2D( tex0, gl_TexCoord[0].st) * diffuse;
	
    if (isBumpMapActive == 1)
        Idiff *= max(dot(N * bumpNormal, L), shadowIntensity);     // if bumpmap used
	else
        Idiff *= max(dot(N,L), shadowIntensity);
	
    Idiff = clamp(Idiff, 0.0, diffuse.a);

	// specular term
	vec4 Ispec = specular; 
	Ispec *= pow(max(dot(R,E),0.0), shinyness);
	Ispec = clamp(Ispec, 0.0, 1.0); 

	// final color 
    vec4 finalCol = Iamb + Idiff + Ispec;
    
    float alpha = 1.0;
    
	gl_FragColor = vec4(finalCol.rgb, alpha);
}
