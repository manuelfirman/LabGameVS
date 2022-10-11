#version 130
out vec4 pos_vert; // 4 valores: X Y Z W (W siempre = 1)

void main() // GRAPHICS PIPELINE (OpenGL)
{
	// transforma la posicion del vertice (cuadrado = 2 triangulos)
		pos_vert = gl_ModelViewProjectionMatrix * gl_Vertex;		// toma la posicion y la transforma en una posicion en el mundo
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;		// define la posicion del vertice

	// transforma las coordenadas de textura
		gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;	// elige un pixel de la textura

	// reenviar el color del vertice
		gl_FrontColor = gl_Color;
}