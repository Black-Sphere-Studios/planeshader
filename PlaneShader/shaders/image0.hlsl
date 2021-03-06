cbuffer PSobj : register(b0) {
  float4x4 matViewProj;
  float4x4 matWorld;
}

struct VS_INPUT
{
  float4 pos : POSITION0;
  float4 dimpivot : TEXCOORD0;
  float4 color : COLOR0;
};

struct PS_INPUT
{
  float4 p : SV_POSITION;
  float4 color : COLOR;
};

VS_INPUT mainVS(VS_INPUT input)
{
  return input;
}

[maxvertexcount(4)]
void mainGS(point VS_INPUT sprite[1], inout TriangleStream<PS_INPUT> triStream)
{
  float4 pos = sprite[0].pos;
  float2 pivot = sprite[0].dimpivot.zw;
  float2 dim = sprite[0].dimpivot.xy;
  float c = cos(pos[3]);
  float s = sin(pos[3]);
  float4x4 matTransform ={
    c, -s, 0, pos[0] - c*pivot[0] + pivot[0] + pivot[1]*s,
    s,  c, 0, pos[1] - c*pivot[1] + pivot[1] - pivot[0]*s,
    0,  0, 1, pos[2],
    0,  0, 0, 1
  };
  float4x4 m = mul(matViewProj, matWorld);
    m = mul(m, matTransform);

  PS_INPUT v;
  v.color = sprite[0].color;

  //top left
  v.p = float4(0, 0, 0, 1);
  v.p = mul(m, v.p);
  triStream.Append(v);

  //bottom left
  v.p = float4(0, dim.y, 0, 1);
  v.p = mul(m, v.p);
  triStream.Append(v);

  //top right
  v.p = float4(dim.x, 0, 0, 1);
  v.p = mul(m, v.p);
  triStream.Append(v);

  //bottom right
  v.p = float4(dim.x, dim.y, 0, 1);
  v.p = mul(m, v.p);
  triStream.Append(v);
}

float4 mainPS(PS_INPUT input) : SV_Target
{
  return input.color;
}