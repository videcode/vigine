#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;
// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 2) in vec3 vertexColor;
// texture coordinates from C++
//layout (location = 2) in vec2 texCoord;


// Values that stay constant for the whole mesh.
uniform mat4 MVP;
out vec3 fragmentColor;
out vec3 pos;
//out vec2 fragmentTexCoord;

void main(){

  gl_Position = MVP * vec4(vertexPosition_modelspace,1);
  //gl_Position =  vec4(vertexPosition_modelspace, 1);
  pos = vec3(vertexPosition_modelspace);

  // The color of each vertex will be interpolated
  // to produce the color of each fragment
  fragmentColor = vertexColor;
  //fragmentTexCoord	= texCoord;


}

