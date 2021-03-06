"//  ---------------------------------------------------------------------------\n"
"//\n"
"//  @file       LineRectCstColorVS.hlsl\n"
"//  @author     Egor Yusov\n"
"//	@brief		Source code of the LineRectCstColor D3D vertex shader\n"
"//  @license    This file is based on the TwDirect3D11.hlsl file \n"
"//              from the original AntTweakBar library.\n"
"//\n"
"//  ---------------------------------------------------------------------------\n"
" \n"
"cbuffer Constants\n"
"{\n"
"    float4 g_Offset;\n"
"    float4 g_CstColor;\n"
"}\n"
"\n"
"// Shaders for lines and rectangles\n"
"\n"
"struct LineRectPSInput \n"
"{ \n"
"    float4 Pos : SV_POSITION; \n"
"    float4 Color : COLOR0; \n"
"};\n"
"\n"
"LineRectPSInput main(float4 pos : ATTRIB0, float4 color : ATTRIB1) \n"
"{\n"
"    LineRectPSInput ps; \n"
"    ps.Pos = float4(pos.xy + g_Offset.xy, 0.5, 1.0);\n"
"    ps.Color = g_CstColor; \n"
"    return ps; \n"
"}\n"
