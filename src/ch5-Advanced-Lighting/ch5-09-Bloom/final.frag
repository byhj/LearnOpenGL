#version 330 core

out vec4 FragColor;

in VS_OUT 
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} fs_in;

struct Light 
{
    vec3 Position;
    vec3 Color;
};

uniform Light lights[16];

uniform sampler2D diffuseTexture;
uniform vec3 viewPos;

void main()
{           
    vec3 color = texture(diffuseTexture, fs_in.TexCoord).rgb;

    vec3 normal = normalize(fs_in.Normal);

    // Ambient
    vec3 ambient = 0.0 * color;

    // Lighting
    vec3 lighting = vec3(0.0f);
    for(int i = 0; i < 16; i++)
    {
        // Diffuse
        vec3 lightDir = normalize(lights[i].Position - fs_in.FragPos);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = lights[i].Color * diff * color;      
        vec3 result = diffuse;     
		   
        // Attenuation (use quadratic as we have gamma correction)
        float distance = length(fs_in.FragPos - lights[i].Position);
        result *= 1.0 / (distance * distance);
        lighting += result;
                
    }

    FragColor = vec4(ambient + lighting, 1.0f);
}