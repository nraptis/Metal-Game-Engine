uniform lowp vec4 ModulateColor;
varying mediump vec2 TextureCoordsOut;
uniform sampler2D Texture;
uniform lowp vec4 Ambient;
uniform lowp vec4 Diffuse;
uniform lowp vec4 Specular;


varying mediump vec3 NormalsOut;
varying mediump vec3 EyeOut;

void main(void) {
    
    mediump vec3 DiffuseDirection = vec3(Diffuse[0], Diffuse[1], Diffuse[2]);
    
    mediump float DiffuseFactor = max(0.0, dot(NormalsOut, DiffuseDirection));
    mediump float SpecularFactor = pow(max(0.0, dot(DiffuseDirection, EyeOut)), Specular[1]); //3
    mediump float AmbientIntensity = Ambient[3];
    mediump float DiffuseIntensity = DiffuseFactor; //Diffuse[3] * 
    mediump float SpecularIntensity = Specular[0] * SpecularFactor;
    
    mediump float LightIntensity = AmbientIntensity + DiffuseIntensity;// + SpecularIntensity;
    
    //LightIntensity = 1.0;
    
    lowp vec4 Color = vec4(ModulateColor[0] * Ambient[0] * LightIntensity,
                           ModulateColor[1] * Ambient[1] * LightIntensity,
                           ModulateColor[2] * Ambient[2] * LightIntensity,
                           ModulateColor[3]);
    
    gl_FragColor = Color * texture2D(Texture, TextureCoordsOut);
}
