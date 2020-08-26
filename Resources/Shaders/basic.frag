#version 450 core

in vec3 pass_baseColor;
in vec3 surfaceNormal;
in vec3 toLightDir[3];
in vec3 cameraDir;

out vec4 output_color; 

uniform vec3 lightColor[3];
uniform vec3 attenuations[3];
uniform float reflectivity;
uniform float shineDamper;


void main()
{
        vec3 unit_normal = normalize(surfaceNormal);
        vec3 unit_cameraDir = normalize(cameraDir);

        vec3 net_diffuse = vec3(0.0, 0.0, 0.0);
        vec3 net_specular = vec3(0.0, 0.0, 0.0);

        vec3 default_attenuation = vec3(0.5, 0.0, 0.0);

        for(int i = 0; i < 1; i++)
        {
                float distToSrc = length(toLightDir[i]);
                float att_factor = default_attenuation.x + (default_attenuation.y * distToSrc) + (default_attenuation.z * distToSrc * distToSrc);
                
                vec3 unit_toLightDir = normalize(toLightDir[i]);
                float relativeDir = dot(unit_normal, unit_toLightDir);
                float brightness = max(relativeDir, 0.06f);

                vec3 lightDir = -unit_toLightDir;
                vec3 lightReflectDir = reflect(lightDir, unit_normal);
                
                
                float specular_factor = dot(lightReflectDir, unit_cameraDir);
                specular_factor = max(specular_factor, 0.0);
                float damper_factor = pow(specular_factor, shineDamper);
                
                net_diffuse = net_diffuse + (brightness * lightColor[i])/att_factor;
                net_specular = net_specular + (damper_factor * reflectivity * lightColor[i])/att_factor;
        }

        net_diffuse = max(net_diffuse, 0.05);

        output_color = vec4(net_diffuse, 1.0) * vec4(pass_baseColor, 1.0) + vec4(net_specular, 1.0);
}
