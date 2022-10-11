in vec4 pos_vert; // IN de 4 valores (X Y Z W)

uniform sampler2D textura;	// textura de la imagen
uniform bool tieneTextura;
uniform vec2 luz;			// vector de 2

void main()
{
	// Luz ambiente
		vec4 ambiente = vec4(0.02, 0.02, 0.02, 1.0);						// vector de 4

	// Luz a coordenadas de vista
		vec2 posLuz = (gl_ModelViewProjectionMatrix * vec4(luz, 0, 1)).xy;	// vector de 2

	// Calcula el vector desde luz a pixels en forma circular
		vec2 luzAFrag = posLuz - pos_vert.xy;								// vector de 2
		luzAFrag.y = luzAFrag.y / 1.7;

	// Distancia (longitud del vector)
		float longVector = clamp(length(luzAFrag) * 2, 0, 1); // Agrandar o achicar el circulo de ilumnacion

	// pixel en la textura
		vec4 pixel = texture2D(textura, gl_TexCoord[0].xy);					// vector de 4

	// multiplicando por el color y la luz
		if(tieneTextura == true)		// si hay textura, define el color
		{
			gl_FragColor = gl_Color * pixel * (clamp(ambiente + vec4(1-longVector, 1-longVector, 1-longVector, 1), 0, 1));
		} 
		else 
		{								// si no hay textura, usa la predeterminada
			gl_FragColor = gl_Color;
		}
}