struct BasicVertexUniforms {
    mat4 projectionMatrix;
    mat4 modelViewMatrix;
};

uniform BasicVertexUniforms VertexUniforms;

attribute vec4 Position;
attribute vec4 SourceColor;

varying vec4 DestinationColor;


attribute vec2 TexCoordIn;
varying vec2 TexCoordOut;

void main(void) {
    DestinationColor = SourceColor;
    gl_Position = VertexUniforms.projectionMatrix * VertexUniforms.modelViewMatrix * Position;
    TexCoordOut = TexCoordIn;
}
