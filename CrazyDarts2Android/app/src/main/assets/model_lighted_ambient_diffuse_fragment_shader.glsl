uniform lowp vec4 ModulateColor;
varying mediump vec2 TextureCoordsOut;
uniform sampler2D Texture;
uniform lowp vec4 Ambient;

//dirx, diry, dirz, diff_intensity...
uniform lowp vec4 Diffuse;

varying mediump vec3 NormalsOut;


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
