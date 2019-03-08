struct ModulateFragmentUniforms {
    lowp float r;
    lowp float g;
    lowp float b;
    lowp float a;
};

uniform ModulateFragmentUniforms FragmentUniforms;

varying lowp vec4 DestinationColor;

varying lowp vec2 TexCoordOut;
uniform sampler2D Texture;

void main(void) {
    lowp vec4 modulate = vec4(FragmentUniforms.r, FragmentUniforms.g, FragmentUniforms.b, FragmentUniforms.a);
    gl_FragColor = DestinationColor * modulate * texture2D(Texture, TexCoordOut);
}
