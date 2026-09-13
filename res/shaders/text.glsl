#type vertex
#version 330 core
layout (location = 0) in vec4 vertex;

uniform mat4 model;
uniform mat4 projection;

out vec2 texCoord;

void main()
{
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
    texCoord = vertex.zw;
}

#type fragment
#version 330 core

in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D text;
uniform vec4 textColor;

void main()
{
    float alpha = texture(text, texCoord).r;
    FragColor = vec4(textColor.rgb, textColor.a * alpha);
}