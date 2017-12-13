#version 430 core

layout (location = 0) in vec4 vPosition;

uniform mat4 mTransform;
uniform float fTime;
uniform vec3 newNormal;
uniform vec3 myLightPosition;
uniform vec3 vEye;
uniform vec3 lightv;
uniform vec4 vNewVec;

uniform sampler2D textura0;
uniform sampler2D textura1;

//uniform vec4 gl_Position;
out vec4 color;
in vec2 texCoord;



vec3 getAmbient(in vec3 light, in vec3 mat)
{
	return light * mat;
}

vec3 getDifusse(in vec3 light, in vec3 mat, in vec3 lightv, in vec3 Normal)
{
	return max(0.0, dot(lightv, Normal)) * mat * light;
}

vec3 getSpecular( in vec3 light, in vec3 mat, in vec3 lightv, in vec3 Normal, in float shininess, in vec3 myPos)
{
	vec3 viewv = normalize( vEye - myPos);
	vec3 refl = normalize(reflect(vEye - lightv, Normal ));

	//specular light computation
	vec3 specular = vec3( 0.0, 0.0, 0.0 );
	if( dot(lightv, viewv) > 0.0)
	{
		specular = pow(max(0.0, dot(viewv, refl)), shininess) * light * mat;
	}
	return specular;
}

void main()
{
   const vec3 lA = vec3( 0.2, 0.2, 0.2 );
   const vec3 lD = vec3( 0.4, 0.4, 0.4 );
   const vec3 lS = vec3( 1.0, 1.0, 1.0 );
   const vec3 mA = vec3( 1.0, 0.5, 0.0 );
   const vec3 mD = vec3( 1.0, 0.5, 0.0 );
   const vec3 mS = vec3( 1.0, 1.0, 1.0 );
   const float fShininess = 10.0;
  
   mat4 matForNormals = transpose(inverse(mTransform));
   vec4 normal = texture(textura1, texCoord);
   //vec4 newNormal = matForNormals * normal;

   color = clamp(vec4(getAmbient(lA, mA), 1.0) +
			vec4(getDifusse(lD, mD, lightv, newNormal), 1.0) +
			vec4(getSpecular(lS, mS, lightv, newNormal, fShininess, vNewVec.xyz), 1.0)
			,0.0, 1.0);

			   color = texture(textura0, texCoord);
			
		//	gl_Position = mTransform * vNewVec;
}