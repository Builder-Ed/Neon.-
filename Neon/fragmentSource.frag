#version 330 core								
//in vec4 vertexColor;		
//in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
struct Material{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
	
};
struct LightPoint{
	float constant;
	float linear;
	float quadratic;
};
struct LightSpot{
	float CosPhi;
};


uniform Material material;
uniform LightPoint LightPt;
uniform LightSpot lightSpt;
//uniform sampler2D TextureA;
//uniform sampler2D TextureB;
uniform vec3 objectColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightDirUniform;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;							
void main() {						
		float Dist=length(lightPos-FragPos);
		float attenuation=1.0/(LightPt.constant+LightPt.linear*Dist+LightPt.quadratic*(Dist*Dist));
		//FragColor = vertexColor;
		//FragColor = texture(TextureA,TexCoord)*texture(TextureB,TexCoord);
		
		vec3 lightDir=normalize(lightPos-FragPos);
		vec3 reflectVec=reflect(-lightDir,Normal);
		vec3 cameraVec=normalize(cameraPos-FragPos);

		float specularAmout=pow(max(dot(reflectVec,cameraVec),0),material.shininess);
		vec3 specular=texture(material.specular,TexCoord).rgb*specularAmout*lightColor;

		vec3 diffuse=texture(material.diffuse,TexCoord).rgb*max(dot(lightDir,Normal),0)*lightColor;
		//vec3 diffuse=material.diffuse*max(dot(lightDir,Normal),0)*lightColor;//*objectColor;
		//vec3 diffuse=texture(material.diffuse,TexCoord).rgb;
		//vec3 ambient=material.ambient*ambientColor;
		vec3 ambient=texture(material.diffuse,TexCoord).rgb*ambientColor;
		//FragColor=vec4(objectColor*ambientColor,1.0);//*texture(TextureA,TexCoord)*texture(TextureB,TexCoord);;
		float CosTheta=dot(normalize(FragPos-lightPos),-lightDirUniform);
		//if (CosTheta>CosPhi){
		//	
		//}else{
		//}
		FragColor=vec4((ambient+diffuse+specular)*objectColor*attenuation,1.0);
		}