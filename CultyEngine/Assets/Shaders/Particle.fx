// Render a particle

cbuffer ParticleBuffer : register(b0)
{
    matrix wvp;
    float4 color;
}

Texture2D textureMap : register(t0);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 position     : POSITION;
    float3 normal       : NORMAL;
    float3 tangent      : TANGENT;
    float2 textCoord    : TEXCOORD;
    int4   blendIndices : BLENDINDICES;
    int4   blendWeight  : BLENDWEIGHT;
};

struct VS_OUTPUT
{
    float4 position  : SV_Position;
    float2 textCoord : TEXCOORD;
    float4 color     : COLOR;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = mul(float4(input.position, 1.0f), wvp);
    output.textCoord = input.textCoord;
    output.color = color;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    return textureMap.Sample(textureSampler, input.textCoord) * input.color;
}