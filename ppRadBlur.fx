
#define NUM_SAMPLES 50

//Variables
float4 vecViewPort;
float4 vecSkill1;

//Texture
texture TargetMap;
sampler2D ColorSampler = sampler_state { texture = <TargetMap>;};

//Pixelshader
float4 PS(float2 texCoord : TEXCOORD0) : COLOR0 
{
	float2 deltaTexCoord = (texCoord - 0.5);
	deltaTexCoord *= 1.0f / NUM_SAMPLES * vecSkill1.x;
	
	float4 Color = 0;
	
	for(int i = 0; i < NUM_SAMPLES; i++)
	{
		texCoord -= deltaTexCoord;
		Color += tex2D(ColorSampler, texCoord);
	}
	
	Color /= NUM_SAMPLES;
	Color.a = 1.0;
	return Color;
}

technique Tech1
{
	pass one
	{
		PixelShader = compile ps_3_0 PS();
	}
}
