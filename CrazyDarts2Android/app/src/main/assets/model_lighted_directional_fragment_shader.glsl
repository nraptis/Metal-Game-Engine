varying mediump vec3 N;
varying mediump vec3 v;

uniform lowp vec4 ModulateColor;
varying lowp vec2 TextureCoordsOut;
uniform sampler2D Texture;

//r, g, b, [ambient intensity]
uniform lowp vec4 Ambient;

//dirX, dirY, dirZ, [diffuse intensity]
uniform lowp vec4 Diffuse;

//Shininess, Specular Intensity
uniform lowp vec2 Specular;

void main (void) {
    
    mediump vec3 Direction = vec3(-Diffuse[0], -Diffuse[1], -Diffuse[2]);
    //highp vec3 SpotlightPosition = vec3(Specular[0], Specular[1], Specular[2]);
    
    //highp vec3 L = normalize(SpotlightPosition - v);
    mediump vec3 L = Direction;//normalize(SpotlightPosition - v);
    
    mediump vec3 E = normalize(v); // we are in Eye Coordinates, so EyePos is (0,0,0)
    mediump vec3 R = normalize(-reflect(L,N));
    
    //calculate Diffuse Term:
    lowp float Idiff = max(dot(N,L), 0.0) * Diffuse[3];
    Idiff = clamp(Idiff, 0.0, 1.0);
    
    // calculate Specular Term:
    lowp float Ispec = pow(max(dot(R, E), 0.0), Specular[0]) * Specular[1];
    Ispec = clamp(Ispec, 0.0, 100.0);
    
    lowp float Ilight = Ambient[3] + Idiff + Ispec;
    
    
    gl_FragColor = vec4(Ilight, Ilight, Ilight, 1.0);
    
    
}


/*highp vec4 Color = vec4(ModulateColor[0] * Ambient[0] * Ilight,
 ModulateColor[1] * Ambient[1] * Ilight,
 ModulateColor[2] * Ambient[2] * Ilight,
 ModulateColor[3]);
 
 gl_FragColor = Color * texture2D(Texture, TextureCoordsOut);
 */

/*
void main(void) {
    
    mediump vec3 DiffuseDirection = vec3(Diffuse[0], Diffuse[1], Diffuse[2]);
    
    lowp float DiffuseFactor = max(0.0, dot(NormalsOut, DiffuseDirection));
    
    lowp float DiffuseIntensity = Diffuse[3] * DiffuseFactor;
    lowp float AmbientIntensity = Ambient[3];
    
    lowp float LightIntensity = AmbientIntensity + DiffuseIntensity;
    
    lowp vec4 Color = vec4(ModulateColor[0] * Ambient[0] * LightIntensity,
                           ModulateColor[1] * Ambient[1] * LightIntensity,
                           ModulateColor[2] * Ambient[2] * LightIntensity,
                           ModulateColor[3]);
    
    gl_FragColor = Color * texture2D(Texture, TextureCoordsOut);
}
*/
