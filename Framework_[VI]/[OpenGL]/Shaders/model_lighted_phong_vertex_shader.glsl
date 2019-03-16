uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
attribute vec3 Positions;
attribute vec3 TextureCoords;
attribute vec3 Normals;

varying vec2 TextureCoordsOut;
varying vec3 NormalsOut;
varying vec3 EyeOut;



void main(void) {
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Positions[0], Positions[1], Positions[2], 1.0);
    
    TextureCoordsOut = vec2(TextureCoords[0], TextureCoords[1]);
    
    mat4 ModelViewReset = ModelViewMatrix;
    //ModelViewReset[3][0] = 0.0;
    //ModelViewReset[3][1] = 0.0;
    //ModelViewReset[3][2] = 0.0;
    //ModelViewReset[3][3] = 1.0;
    
    
    
    vec4 NormalCorrected4 = ModelViewMatrix * vec4(Normals[0], Normals[1], Normals[2], 1.0);
    NormalsOut = normalize(vec3(NormalCorrected4[0], NormalCorrected4[1], NormalCorrected4[2]));
    
    //NormalsOut = normalize(vec3(ModelViewReset * vec4(Normals[0], Normals[1], Normals[2], 1.0)));
    
    
    vec4 EyeCorrected4 = ModelViewMatrix * vec4(Positions[0], Positions[1], Positions[2], 1.0);
    EyeOut = normalize(vec3(EyeCorrected4[0], EyeCorrected4[1], EyeCorrected4[2]));
    
}
