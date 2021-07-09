#version 330 core
out vec4  color;
in vec3	  fragmentColor;
//in vec2	  fragmentTexCoord;
in vec3	  pos;


void main(){
	color = vec4(fragmentColor, 1.0);
}


// https://habr.com/ru/post/343876/
