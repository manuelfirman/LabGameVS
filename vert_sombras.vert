#version 330

out vec4 pos_vert;

void main()
{
	// transforma la posicion del vertice
	pos_vert = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// transforma las coordenadas de textura
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	// reenviar el color del vertice
	gl_FrontColor = gl_Color;
}