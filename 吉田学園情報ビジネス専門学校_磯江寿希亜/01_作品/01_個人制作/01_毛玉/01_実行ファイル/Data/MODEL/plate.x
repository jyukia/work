xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 79;
 0.00000;3.51300;0.00000;,
 15.31500;3.51300;-15.31500;,
 0.00000;3.51300;-21.65868;,
 0.00000;3.51300;0.00000;,
 21.65868;3.51300;0.00000;,
 0.00000;3.51300;0.00000;,
 15.31500;3.51300;15.31500;,
 0.00000;3.51300;0.00000;,
 0.00000;3.51300;21.65868;,
 0.00000;3.51300;0.00000;,
 -15.31500;3.51300;15.31496;,
 0.00000;3.51300;0.00000;,
 -21.65868;3.51300;0.00000;,
 0.00000;3.51300;0.00000;,
 -15.31500;3.51300;-15.31500;,
 0.00000;3.51300;0.00000;,
 0.00000;3.51300;-21.65868;,
 0.00000;14.03169;-78.41180;,
 55.44552;14.03169;-55.44552;,
 41.52704;4.93012;-41.52704;,
 0.00000;4.93012;-58.72812;,
 0.00000;14.03169;-78.41180;,
 0.00000;4.93012;-58.72812;,
 -41.52704;4.93012;-41.52704;,
 -55.44552;14.03169;-55.44552;,
 78.41180;14.03169;0.00000;,
 58.72812;4.93012;0.00000;,
 -58.72812;4.93012;0.00000;,
 -78.41180;14.03169;0.00000;,
 55.44552;14.03169;55.44552;,
 41.52704;4.93012;41.52704;,
 -41.52708;4.93012;41.52704;,
 -55.44552;14.03169;55.44552;,
 0.00000;14.03169;78.41180;,
 0.00000;4.93012;58.72812;,
 42.03656;12.32733;-42.03656;,
 59.44876;12.32733;0.00000;,
 0.00000;12.32733;-59.44876;,
 42.03656;12.32733;42.03656;,
 0.00000;12.32733;-59.44876;,
 -42.03656;12.32733;-42.03656;,
 0.00000;12.32733;59.44876;,
 -59.44876;12.32733;0.00000;,
 -42.03660;12.32733;42.03656;,
 58.72812;1.04264;0.00000;,
 41.52704;1.04264;41.52704;,
 39.50664;0.31776;39.50664;,
 55.87080;0.31776;0.00000;,
 39.50664;0.31776;-39.50664;,
 41.52704;1.04264;-41.52704;,
 0.00000;1.04264;58.72812;,
 0.00000;0.31776;55.87080;,
 0.00000;0.31776;-55.87080;,
 0.00000;1.04264;-58.72812;,
 -41.52708;1.04264;41.52704;,
 -39.50664;0.31776;39.50660;,
 0.00000;1.04264;-58.72812;,
 0.00000;0.31776;-55.87080;,
 -39.50664;0.31776;-39.50664;,
 -41.52704;1.04264;-41.52704;,
 -58.72812;1.04264;0.00000;,
 -55.87080;0.31776;0.00000;,
 39.50664;2.50952;-39.50664;,
 0.00000;2.50952;-55.87080;,
 0.00000;2.50952;0.00000;,
 55.87080;2.50952;0.00000;,
 0.00000;2.50952;0.00000;,
 39.50664;2.50952;39.50664;,
 0.00000;2.50952;0.00000;,
 0.00000;2.50952;55.87080;,
 0.00000;2.50952;0.00000;,
 -39.50664;2.50952;39.50660;,
 0.00000;2.50952;0.00000;,
 -55.87080;2.50952;0.00000;,
 0.00000;2.50952;0.00000;,
 -39.50664;2.50952;-39.50664;,
 0.00000;2.50952;0.00000;,
 0.00000;2.50952;-55.87080;,
 0.00000;2.50952;0.00000;;
 
 64;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;17,18,19,20;,
 4;21,22,23,24;,
 4;18,25,26,19;,
 4;24,23,27,28;,
 4;25,29,30,26;,
 4;28,27,31,32;,
 4;29,33,34,30;,
 4;32,31,34,33;,
 4;35,1,4,36;,
 4;35,36,25,18;,
 4;35,18,17,37;,
 4;35,37,2,1;,
 4;36,4,6,38;,
 4;36,38,29,25;,
 4;39,21,24,40;,
 4;39,40,14,16;,
 4;38,6,8,41;,
 4;38,41,33,29;,
 4;40,24,28,42;,
 4;40,42,12,14;,
 4;41,8,10,43;,
 4;41,43,32,33;,
 4;42,28,32,43;,
 4;42,43,10,12;,
 4;44,26,30,45;,
 4;44,45,46,47;,
 4;44,47,48,49;,
 4;44,49,19,26;,
 4;45,30,34,50;,
 4;45,50,51,46;,
 4;49,48,52,53;,
 4;49,53,20,19;,
 4;50,34,31,54;,
 4;50,54,55,51;,
 4;56,57,58,59;,
 4;56,59,23,22;,
 4;54,31,27,60;,
 4;54,60,61,55;,
 4;59,58,61,60;,
 4;59,60,27,23;,
 4;62,63,52,48;,
 3;64,63,62;,
 4;65,62,48,47;,
 3;66,62,65;,
 4;67,65,47,46;,
 3;68,65,67;,
 4;69,67,46,51;,
 3;70,67,69;,
 4;71,69,51,55;,
 3;72,69,71;,
 4;73,71,55,61;,
 3;74,71,73;,
 4;75,73,61,58;,
 3;76,73,75;,
 4;77,75,58,57;,
 3;78,75,77;;
 
 MeshMaterialList {
  1;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  58;
  0.000000;1.000000;0.000000;,
  0.000000;0.993472;0.114072;,
  -0.080661;0.993472;0.080661;,
  -0.114072;0.993472;0.000000;,
  -0.080661;0.993472;-0.080661;,
  0.000000;0.993473;-0.114071;,
  0.080661;0.993472;-0.080661;,
  0.114072;0.993473;0.000000;,
  0.080661;0.993472;0.080661;,
  0.000000;-0.969294;-0.245904;,
  0.173881;-0.969294;-0.173881;,
  0.245904;-0.969294;-0.000000;,
  0.173881;-0.969294;0.173881;,
  0.000000;-0.969294;0.245903;,
  -0.173879;-0.969295;0.173879;,
  -0.245903;-0.969294;-0.000001;,
  -0.173881;-0.969294;-0.173881;,
  0.296770;-0.907665;-0.296770;,
  0.419696;-0.907665;-0.000000;,
  0.000000;-0.907665;-0.419696;,
  0.296770;-0.907665;0.296770;,
  -0.296770;-0.907665;-0.296770;,
  0.000000;-0.907665;0.419697;,
  -0.419697;-0.907664;-0.000000;,
  -0.296770;-0.907664;0.296770;,
  -0.112140;0.987345;0.112140;,
  -0.158590;0.987345;0.000000;,
  0.000000;0.987345;0.158590;,
  -0.112140;0.987345;-0.112140;,
  0.112140;0.987345;0.112140;,
  0.000000;0.987345;-0.158590;,
  0.158590;0.987345;0.000000;,
  0.112140;0.987345;-0.112140;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;-0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;-1.000000;-0.000000;,
  -0.089517;0.995985;0.000000;,
  -0.063298;0.995985;0.063298;,
  0.000000;0.995985;0.089517;,
  -0.063298;0.995985;-0.063298;,
  0.063298;0.995985;0.063298;,
  0.000000;0.995985;-0.089517;,
  0.089517;0.995985;-0.000000;,
  0.063298;0.995985;-0.063298;,
  0.707107;0.000000;-0.707107;,
  0.000000;0.000000;-1.000000;,
  -0.707107;0.000000;-0.707107;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;19,17,17,19;,
  4;19,19,21,21;,
  4;17,18,18,17;,
  4;21,21,23,23;,
  4;18,20,20,18;,
  4;23,23,24,24;,
  4;20,22,22,20;,
  4;24,24,22,22;,
  4;25,2,3,26;,
  4;25,26,47,48;,
  4;25,48,49,27;,
  4;25,27,1,2;,
  4;26,3,4,28;,
  4;26,28,50,47;,
  4;27,49,51,29;,
  4;27,29,8,1;,
  4;28,4,5,30;,
  4;28,30,52,50;,
  4;29,51,53,31;,
  4;29,31,7,8;,
  4;30,5,6,32;,
  4;30,32,54,52;,
  4;31,53,54,32;,
  4;31,32,6,7;,
  4;33,33,34,34;,
  4;11,12,12,11;,
  4;11,11,10,10;,
  4;33,55,55,33;,
  4;34,34,35,35;,
  4;12,13,13,12;,
  4;10,10,9,9;,
  4;55,56,56,55;,
  4;35,35,36,36;,
  4;13,14,14,13;,
  4;9,9,16,16;,
  4;56,57,57,56;,
  4;36,36,37,37;,
  4;14,15,15,14;,
  4;16,16,15,15;,
  4;57,37,37,57;,
  4;39,38,38,39;,
  3;46,46,46;,
  4;40,39,39,40;,
  3;46,46,46;,
  4;41,40,40,41;,
  3;46,46,46;,
  4;42,41,41,42;,
  3;46,46,46;,
  4;43,42,42,43;,
  3;46,46,46;,
  4;44,43,43,44;,
  3;46,46,46;,
  4;45,44,44,45;,
  3;46,46,46;,
  4;38,45,45,38;,
  3;46,46,46;;
 }
 MeshTextureCoords {
  79;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.000000;0.040760;,
  0.125000;0.040760;,
  0.125000;0.442310;,
  0.000000;0.442310;,
  1.000000;0.040760;,
  1.000000;0.442310;,
  0.875000;0.442310;,
  0.875000;0.040760;,
  0.250000;0.040760;,
  0.250000;0.442310;,
  0.750000;0.442310;,
  0.750000;0.040760;,
  0.375000;0.040760;,
  0.375000;0.442310;,
  0.625000;0.442310;,
  0.625000;0.040760;,
  0.500000;0.040760;,
  0.500000;0.442310;,
  0.125000;0.003680;,
  0.250000;0.003680;,
  0.000000;0.003680;,
  0.375000;0.003680;,
  1.000000;0.003680;,
  0.875000;0.003680;,
  0.500000;0.003680;,
  0.750000;0.003680;,
  0.625000;0.003680;,
  0.250000;0.912350;,
  0.375000;0.912350;,
  0.375000;1.000000;,
  0.250000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.912350;,
  0.500000;0.912350;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.912350;,
  0.625000;0.912350;,
  0.625000;1.000000;,
  1.000000;0.912350;,
  1.000000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.912350;,
  0.750000;0.912350;,
  0.750000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.062500;1.000000;,
  0.250000;1.000000;,
  0.187500;1.000000;,
  0.375000;1.000000;,
  0.312500;1.000000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.625000;1.000000;,
  0.562500;1.000000;,
  0.750000;1.000000;,
  0.687500;1.000000;,
  0.875000;1.000000;,
  0.812500;1.000000;,
  1.000000;1.000000;,
  0.937500;1.000000;;
 }
}
