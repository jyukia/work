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
 66;
 94.11439;12.68257;-12.08677;,
 106.27322;8.05714;-11.16672;,
 -99.47628;8.05715;-11.16672;,
 -96.57069;12.68257;-12.08677;,
 100.95065;4.13591;-8.54664;,
 -91.53438;4.13593;-8.54664;,
 109.17238;1.51584;-4.62541;,
 -97.90694;1.51584;-4.62541;,
 102.79500;0.49186;-0.21070;,
 -88.51286;0.59579;0.00000;,
 112.13330;1.41192;4.41471;,
 -95.30480;1.51584;4.62541;,
 106.21780;4.13591;8.54664;,
 -105.45283;4.13593;8.54664;,
 110.23214;8.05714;11.16672;,
 -98.80704;8.05715;11.16672;,
 102.46686;12.68257;12.08677;,
 -97.41850;12.68257;12.08677;,
 106.47462;17.30797;11.16672;,
 -84.07963;17.30797;11.16672;,
 97.42929;21.22920;8.54664;,
 -100.23743;21.22920;8.54664;,
 92.18287;23.84928;4.62541;,
 -92.71503;23.84928;4.62541;,
 100.01030;24.76937;0.00000;,
 -103.23955;24.76937;0.00000;,
 107.00551;23.84928;-4.62541;,
 -92.86818;23.84928;-4.62541;,
 99.09190;21.22920;-8.54664;,
 -98.01859;21.22920;-8.54664;,
 102.26455;17.30797;-11.16672;,
 -112.17665;17.30797;-11.16672;,
 94.11439;12.68257;-12.08677;,
 -96.57069;12.68257;-12.08677;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 104.61449;12.57864;-0.21070;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;,
 -94.26289;12.68257;0.00000;;
 
 48;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 3;34,1,0;,
 3;35,4,1;,
 3;36,6,4;,
 3;37,8,6;,
 3;38,10,8;,
 3;39,12,10;,
 3;40,14,12;,
 3;41,16,14;,
 3;42,18,16;,
 3;43,20,18;,
 3;44,22,20;,
 3;45,24,22;,
 3;46,26,24;,
 3;47,28,26;,
 3;48,30,28;,
 3;49,32,30;,
 3;50,3,2;,
 3;51,2,5;,
 3;52,5,7;,
 3;53,7,9;,
 3;54,9,11;,
 3;55,11,13;,
 3;56,13,15;,
 3;57,15,17;,
 3;58,17,19;,
 3;59,19,21;,
 3;60,21,23;,
 3;61,23,25;,
 3;62,25,27;,
 3;63,27,29;,
 3;64,29,31;,
 3;65,31,33;;
 
 MeshMaterialList {
  2;
  48;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.505098;0.219608;0.203922;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/wood002.jpg";
   }
  }
  Material {
   0.500000;0.500000;0.500000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.500000;0.500000;0.500000;;
   TextureFilename {
    "data/TEXTURE/wood002.jpg";
   }
  }
 }
 MeshNormals {
  59;
  0.689789;0.412944;-0.594700;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.382684;-0.923879;,
  -0.000000;-0.707107;-0.707106;,
  -0.000198;-0.920724;-0.390215;,
  -0.000355;-0.999967;-0.008136;,
  -0.000120;-0.924443;0.381319;,
  0.000036;-0.708171;0.706041;,
  -0.000000;-0.382684;0.923879;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.382684;0.923879;,
  0.000000;0.707107;0.707107;,
  0.218156;0.959580;0.177807;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.923878;-0.382687;,
  0.000000;0.707107;-0.707107;,
  0.000000;0.382684;-0.923879;,
  0.000000;0.923878;0.382687;,
  -0.726856;0.686707;-0.010640;,
  0.358483;0.880829;-0.309241;,
  0.695350;-0.229537;0.681029;,
  0.662164;-0.652020;0.369336;,
  0.497534;0.490493;-0.715455;,
  0.576409;-0.086770;0.812541;,
  0.448171;-0.067466;-0.891398;,
  0.585899;0.756397;0.290838;,
  0.621196;0.617908;0.481980;,
  0.743912;-0.407848;-0.529392;,
  0.517228;0.851801;0.083130;,
  0.761949;-0.632673;0.138414;,
  0.524875;0.780275;-0.340112;,
  0.459829;0.790832;-0.403909;,
  0.523198;0.183216;0.832283;,
  0.486626;0.168974;0.857113;,
  0.558642;0.197063;0.805658;,
  0.510101;-0.405360;-0.758604;,
  0.801317;0.592339;0.083819;,
  0.481481;-0.762387;-0.432368;,
  -0.821932;0.547539;0.156936;,
  -0.424387;-0.645376;0.635127;,
  -0.509850;-0.684214;0.521444;,
  -0.594713;0.465556;-0.655419;,
  -0.448302;-0.213270;0.868067;,
  -0.464627;-0.297744;-0.833948;,
  -0.566724;-0.269607;-0.778548;,
  -0.491235;-0.293811;-0.819978;,
  -0.411816;-0.315665;-0.854847;,
  -0.540246;0.832193;0.124860;,
  -0.782060;0.620174;-0.061364;,
  -0.691509;0.699443;-0.180539;,
  -0.331719;0.939394;-0.086605;,
  -0.279836;-0.769584;0.573963;,
  -0.528582;0.386358;-0.755863;,
  -0.405606;-0.301237;0.862983;,
  -0.410353;-0.304762;-0.859494;,
  -0.673800;0.353033;0.649124;,
  -0.501907;0.491290;0.711845;,
  -0.303615;0.603708;0.737126;,
  -0.280852;-0.958252;0.053625;;
  48;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,17,11;,
  4;12,13,13,17;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,1,1,16;,
  3;0,19,19;,
  3;20,21,21;,
  3;0,22,22;,
  3;20,23,23;,
  3;0,24,24;,
  3;25,26,26;,
  3;0,27,27;,
  3;25,28,28;,
  3;20,29,29;,
  3;0,30,31;,
  3;0,12,30;,
  3;20,32,33;,
  3;20,34,32;,
  3;0,35,35;,
  3;0,36,36;,
  3;37,37,37;,
  3;18,38,38;,
  3;39,40,40;,
  3;18,41,41;,
  3;39,42,42;,
  3;43,44,45;,
  3;43,45,46;,
  3;18,47,48;,
  3;18,48,49;,
  3;18,49,50;,
  3;39,51,51;,
  3;18,52,52;,
  3;39,53,53;,
  3;43,54,54;,
  3;18,55,56;,
  3;18,56,57;,
  3;39,58,58;;
 }
 MeshTextureCoords {
  66;
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.187500;0.000000;,
  0.187500;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.312500;0.000000;,
  0.312500;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.437500;0.000000;,
  0.437500;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.562500;0.000000;,
  0.562500;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.687500;0.000000;,
  0.687500;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.812500;0.000000;,
  0.812500;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.937500;0.000000;,
  0.937500;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.031250;0.000000;,
  0.093750;0.000000;,
  0.156250;0.000000;,
  0.218750;0.000000;,
  0.281250;0.000000;,
  0.343750;0.000000;,
  0.406250;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.843750;0.000000;,
  0.906250;0.000000;,
  0.968750;0.000000;,
  0.031250;1.000000;,
  0.093750;1.000000;,
  0.156250;1.000000;,
  0.218750;1.000000;,
  0.281250;1.000000;,
  0.343750;1.000000;,
  0.406250;1.000000;,
  0.468750;1.000000;,
  0.531250;1.000000;,
  0.593750;1.000000;,
  0.656250;1.000000;,
  0.718750;1.000000;,
  0.781250;1.000000;,
  0.843750;1.000000;,
  0.906250;1.000000;,
  0.968750;1.000000;;
 }
}
