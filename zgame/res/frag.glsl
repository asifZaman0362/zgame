#version 330 core

out vec4 frag;

in vec2 TexCoord;
uniform sampler2D ourTexture;

void main() {
    frag = texture(ourTexture, TexCoord); //* vec4(ourColor, 1.0f);
}
