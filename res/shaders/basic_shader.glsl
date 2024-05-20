#shader vertex
#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexColor;

out vec2 uv;
out vec3 fragmentColor;

uniform mat4 u_mvp;

void main() {
  gl_Position =  u_mvp * vec4(vertexPosition_modelspace,1);
  uv = vertexUV;
  fragmentColor = vertexColor;
}

#shader fragment
#version 330 core

in vec2 uv;
in vec3 fragmentColor;

out vec3 color;

uniform sampler2D u_myTexture;
uniform int u_viewMode;

void main() {

  if (u_viewMode == 0) {
    color = fragmentColor;
  } else {
    color = texture( u_myTexture, uv ).rgb; 
  }
}