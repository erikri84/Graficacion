

#include "Plane.h"

Plane::Plane() : Object3D(),
					size(0),
					normals(NULL),
					plane(NULL),
					textureCoords(NULL),
					mTransform(glm::mat4(1.0)),
					aRotations(0.0f, 0.0f, 0.0f),
					side(0)
{
}



void Plane::createPlane(int side)
{
	float gs = 50.0; //geometry size (longitud total del plano)
	this->side = side;
	int TS = 2 * 3 * 2;	//2 triangulos de 3 vertices con 2 coords 
	int VS = 2 * 3 * 4; //2 triangulos de 3 vertices con 4 coords 

	int px = this->side, pz = this->side;
	size = px * VS * pz;
	int textureSize = px * TS * pz;

	plane = (GLfloat*)malloc(size * sizeof(GLfloat)); // 4 coordenadas homogeneas
	textureCoords = (GLfloat*)malloc(textureSize * sizeof(GLfloat));

	//calculo de coordenadas segun pantalla
	//GLfloat dx = px / 2.0, dz = pz / 2.0, len = 2.0 / (float)side;
	GLfloat len = gs / (float)side,
		dx = len / 2.0,
		dz = len / 2.0;

	int colNorm = 0;
	int col = 0;
	int texCol = 0;
	for (int j = 0; j < pz; ++j)
		for (int i = 0; i < px; ++i, col += VS, texCol += TS)
		{
			GLfloat x = i * len - (gs / 2.0),
				z = j * len - (gs / 2.0);

			//triangulo 1 V1 arriba-izq
			plane[col] = x;	//x
			plane[col + 1] = 0.0;				//y
			plane[col + 2] = z;	//z
			plane[col + 3] = 1.0;				//w
			textureCoords[texCol] = (float)i / (float)px;
			textureCoords[texCol + 1] = (float)j / (float)pz;

			//triangulo 1 V2 abajo-izq
			plane[col + 4] = x;	//x
			plane[col + 5] = 0.0;				//y
			plane[col + 6] = z + len;	//z
			plane[col + 7] = 1.0;				//w
			textureCoords[texCol + 2] = (float)i / (float)px;
			textureCoords[texCol + 3] = ((float)j + 1) / (float)pz;// *len / (float)pz;

																   //triangulo 1 V3 arriba-der
			plane[col + 8] = x + len;	//x
			plane[col + 9] = 0.0;				//y
			plane[col + 10] = z;	//z
			plane[col + 11] = 1.0;				//w
			textureCoords[texCol + 4] = ((float)i + 1) / (float)px;// *len / (float)pz;
			textureCoords[texCol + 5] = (float)j / (float)pz;

			///////////////////////////////////////////////
			///////////////////////////////////////////////
			//triangulo 2 V1 abajo-izq
			plane[col + 12] = x;
			plane[col + 13] = 0.0;			//y
			plane[col + 14] = z + len;
			plane[col + 15] = 1.0;			//w
			textureCoords[texCol + 6] = (float)i / (float)px;
			textureCoords[texCol + 7] = ((float)j + 1) / (float)pz;// *len / (float)pz;

																   //triangulo 2 V3 abajo-der
			plane[col + 16] = x + len;	//x
			plane[col + 17] = 0.0;				//y
			plane[col + 18] = z + len;	//z
			plane[col + 19] = 1.0;				//w
			textureCoords[texCol + 8] = ((float)i + 1) / (float)pz;// *len / (float)pz;
			textureCoords[texCol + 9] = ((float)j + 1) / (float)pz;// *len / (float)pz;

																   //triangulo 2 V2 arriba-der
			plane[col + 20] = x + len;//x
			plane[col + 21] = 0.0;	//y
			plane[col + 22] = z;//z
			plane[col + 23] = 1.0; //w
			textureCoords[texCol + 10] = ((float)i + 1) / (float)px;// *len / (float)pz;
			textureCoords[texCol + 11] = (float)j / (float)pz;


			colNorm += 18;
		}

	
	//En 1x1 debe quedar asi
	/*textureCoords[0] = 0.0f;
	textureCoords[1] = 0.0f;

	textureCoords[2] = 0.0f;
	textureCoords[3] = .5f;

	textureCoords[4] = .5f;
	textureCoords[5] = 0.0f;


	textureCoords[6] = 0.0f;
	textureCoords[7] = .5f;

	textureCoords[8] = .5f;
	textureCoords[9] = .5f;

	textureCoords[10] = .5f;
	textureCoords[11] = 0.0f;
	*/

}

int Plane::getNumVertex()
{
	return size / 4;
}

void Plane::cleanMemory()
{
	if (normals)
	{
		free(normals);
		normals = NULL;
	}

	if (plane)
	{
		free(plane);
		plane = NULL;
	}

	if (textureCoords)
	{
		free(textureCoords);
		textureCoords = NULL;
	}
}

size_t Plane::getVertexSizeInBytes()
{
	int VS = 2 * 3 * 4;	//2 triangulos de 3 vertices con 4 coords 
	size = this->side * this->side * VS; //lado por lado por las coordenadas de cada vertice
	return size * sizeof(GLfloat);
}


size_t Plane::getTextureCoordsSizeInBytes()
{
	int TS = 2 * 3 * 2;	//2 triangulos de 3 vertices con 2 coords 
	int textureSize = this->side * this->side * TS; //lado por lado por las coordenadas de textura de cada vertice

	return textureSize * sizeof(GLfloat);
}

Plane::~Plane()
{
	cleanMemory();
}

