in vec4 pos_vert;

uniform sampler2D textura;
uniform bool tieneTextura;
uniform vec2 luz;

void main()
{
	// Luz ambiente
	vec4 ambiente = vec4(0.02, 0.02, 0.02, 1.0);

	// Luz a coordenadas de vista
	vec2 posLuz = (gl_ModelViewProjectionMatrix * vec4(luz, 0, 1)).xy;

	// Calcula el vector desde luz a pixels en forma circular
	vec2 luzAFrag = posLuz - pos_vert.xy;
	luzAFrag.y = luzAFrag.y / 1.7;

	// Distancia (longitud del vector)
	float longVector = clamp(length(luzAFrag) * 2, 0, 1);

	// pixel en la textura
	vec4 pixel = texture2D(textura, gl_TexCoord[0].xy);

	// multiplicando por el color y la luz
	if(tieneTextura == true)
	{
		gl_FragColor = gl_Color * pixel * (clamp(ambiente + vec4(1-longVector, 1-longVector, 1-longVector, 1), 0, 1));
	} 
	else 
	{
		gl_FragColor = gl_Color;
	}
}