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
 136;
 59.24000;11.41000;-3.36615;,
 59.24000;11.41000;3.36610;,
 59.24000;-0.77770;2.39863;,
 59.24000;-0.77770;-4.33362;,
 -59.24000;11.41000;3.36610;,
 -59.24000;11.41000;-3.36615;,
 -59.24000;-0.77770;-4.33362;,
 -59.24000;-0.77770;2.39863;,
 -46.07110;11.41000;3.36610;,
 -59.24000;11.41000;3.36610;,
 -59.24000;-0.77770;2.39863;,
 -46.07110;-0.77770;2.39863;,
 -46.07110;11.41000;-3.36615;,
 -46.07110;-0.77770;-4.33362;,
 -59.24000;-0.77770;-4.33362;,
 -59.24000;11.41000;-3.36615;,
 -46.07110;-0.77770;2.39863;,
 -59.24000;-0.77770;-4.33362;,
 -46.07110;-0.77770;-4.33362;,
 45.84330;11.41000;3.36615;,
 45.84330;-0.77770;2.39868;,
 59.24000;-0.77770;2.39863;,
 59.24000;11.41000;3.36610;,
 45.84330;11.41000;-3.36615;,
 59.24000;11.41000;-3.36615;,
 59.24000;-0.77770;-4.33362;,
 45.84330;-0.77770;-4.33362;,
 45.84330;-0.77770;2.39868;,
 45.84330;-0.77770;-4.33362;,
 59.24000;-0.77770;-4.33362;,
 -46.07110;163.22369;24.48761;,
 -46.07110;163.22369;17.75536;,
 -59.24000;163.22369;17.75536;,
 -59.24000;163.22369;24.48761;,
 45.84330;163.22369;24.48766;,
 59.24000;163.22369;24.48761;,
 59.24000;163.22369;17.75536;,
 45.84330;163.22369;17.75536;,
 -59.24000;149.27170;15.82735;,
 -46.07110;149.27170;15.82735;,
 -46.07110;11.41000;-3.36615;,
 -59.24000;11.41000;-3.36615;,
 -59.24000;149.27170;22.55960;,
 -46.07110;11.41000;3.36610;,
 -46.07110;149.27170;22.55960;,
 45.84330;149.68330;22.55965;,
 45.84330;11.41000;3.36615;,
 59.24000;149.68330;22.55965;,
 45.84330;149.68330;15.82735;,
 59.24000;11.41000;-3.36615;,
 59.24000;149.68330;15.82735;,
 45.84330;11.41000;-3.36615;,
 45.84330;163.22369;17.75536;,
 45.84330;149.68330;15.82735;,
 45.84330;163.22369;24.48766;,
 45.84330;149.68330;22.55965;,
 -43.33030;14.26610;-1.92545;,
 43.10255;14.26610;-1.92545;,
 43.10255;14.26610;1.92545;,
 -43.33030;14.26610;1.92545;,
 -43.31905;146.41765;21.11895;,
 -43.31905;146.41765;17.26805;,
 43.11380;146.82726;17.26805;,
 43.11380;146.82726;21.11895;,
 43.11380;146.82726;21.11895;,
 43.11380;146.82726;17.26805;,
 40.52720;144.22855;17.97050;,
 40.52720;144.22855;20.41650;,
 40.52720;144.22855;20.41650;,
 40.52720;144.22855;17.97050;,
 40.86410;16.50550;-4.83435;,
 -41.09035;16.50520;-4.83490;,
 -40.73135;16.86485;-1.22300;,
 40.50360;16.86530;-1.22300;,
 -41.09035;16.50520;4.83490;,
 40.86410;16.50550;4.83435;,
 40.50360;16.86530;1.22300;,
 -40.73135;16.86485;1.22300;,
 -41.06855;144.17830;24.02840;,
 -40.70780;143.81850;20.41650;,
 -41.06855;144.17830;14.35860;,
 -40.70780;143.81850;17.97050;,
 40.88590;144.58826;14.35915;,
 40.88590;144.58826;24.02785;,
 40.88590;144.58826;24.02785;,
 40.88590;144.58826;14.35915;,
 -42.92955;14.66705;-1.22300;,
 42.70180;14.66670;-1.22300;,
 42.70180;14.66670;1.22300;,
 -42.92955;14.66705;1.22300;,
 -42.91710;146.01711;20.41650;,
 -42.91710;146.01711;17.97050;,
 42.71430;146.42630;17.97050;,
 42.71430;146.42630;20.41650;,
 42.71430;146.42630;20.41650;,
 42.71430;146.42630;17.97050;,
 -30.05585;101.29760;16.43157;,
 -7.90585;101.29760;16.43157;,
 11.07500;1.29760;49.53736;,
 -11.07500;1.29760;49.53736;,
 -7.90585;101.29760;16.43157;,
 -7.90585;101.29760;20.43157;,
 11.07500;1.29760;53.53733;,
 11.07500;1.29760;49.53736;,
 -7.90585;101.29760;20.43157;,
 -30.05585;101.29760;20.43157;,
 -11.07500;1.29760;53.53733;,
 11.07500;1.29760;53.53733;,
 -30.05585;101.29760;20.43157;,
 -30.05585;101.29760;16.43157;,
 -11.07500;1.29760;49.53736;,
 -11.07500;1.29760;53.53733;,
 -7.90585;101.29760;16.43157;,
 -30.05585;101.29760;16.43157;,
 -11.07500;1.29760;49.53736;,
 11.07500;1.29760;49.53736;,
 -57.49365;148.87825;20.95190;,
 57.49365;148.87825;20.95190;,
 57.49365;11.98745;0.86389;,
 -57.49365;11.98745;0.86389;,
 57.49365;148.87825;20.95190;,
 57.49365;148.87825;22.13870;,
 57.49365;11.98745;2.05069;,
 57.49365;11.98745;0.86389;,
 57.49365;148.87825;22.13870;,
 -57.49365;148.87825;22.13870;,
 -57.49365;11.98745;2.05069;,
 57.49365;11.98745;2.05069;,
 -57.49365;148.87825;22.13870;,
 -57.49365;148.87825;20.95190;,
 -57.49365;11.98745;0.86389;,
 -57.49365;11.98745;2.05069;,
 57.49365;148.87825;20.95190;,
 -57.49365;148.87825;20.95190;,
 -57.49365;11.98745;0.86389;,
 57.49365;11.98745;0.86389;;
 
 88;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,7,17,18;,
 4;19,8,11,20;,
 4;19,20,21,22;,
 4;23,24,25,26;,
 4;23,26,13,12;,
 4;27,16,18,28;,
 4;27,28,29,2;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,32,31,39;,
 4;38,39,40,41;,
 4;38,41,4,42;,
 4;38,42,33,32;,
 4;42,4,43,44;,
 4;42,44,30,33;,
 4;45,46,1,47;,
 4;45,47,35,34;,
 4;45,34,37,48;,
 4;47,1,49,50;,
 4;47,50,36,35;,
 4;48,37,36,50;,
 4;48,50,49,51;,
 4;52,53,39,31;,
 4;54,52,31,30;,
 4;55,54,30,44;,
 4;53,52,54,55;,
 4;56,57,51,40;,
 4;58,59,43,46;,
 4;59,60,44,43;,
 4;61,56,40,39;,
 4;62,63,45,48;,
 4;57,62,48,51;,
 4;63,58,46,45;,
 4;64,65,53,55;,
 4;60,64,55,44;,
 4;65,61,39,53;,
 4;66,67,63,62;,
 4;68,69,65,64;,
 4;70,71,72,73;,
 4;71,70,57,56;,
 4;74,75,76,77;,
 4;75,74,59,58;,
 4;78,74,77,79;,
 4;74,78,60,59;,
 4;71,80,81,72;,
 4;80,71,56,61;,
 4;82,70,73,66;,
 4;70,82,62,57;,
 4;75,83,67,76;,
 4;83,75,58,63;,
 4;84,78,79,68;,
 4;78,84,64,60;,
 4;80,85,69,81;,
 4;85,80,61,65;,
 4;86,87,73,72;,
 4;88,89,77,76;,
 4;88,87,86,89;,
 4;89,90,79,77;,
 4;91,86,72,81;,
 4;91,90,89,86;,
 4;92,93,67,66;,
 4;87,92,66,73;,
 4;93,88,76,67;,
 4;93,92,87,88;,
 4;94,95,69,68;,
 4;90,94,68,79;,
 4;95,91,81,69;,
 4;95,94,90,91;,
 3;63,67,83;,
 3;64,84,68;,
 3;62,82,66;,
 3;65,69,85;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;108,101,112,113;,
 4;114,115,102,111;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;128,121,132,133;,
 4;134,135,122,131;;
 
 MeshMaterialList {
  2;
  88;
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
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.414400;0.210400;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  93;
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.095640;0.006089;0.995397;,
  0.094018;0.179402;-0.979273;,
  -0.000000;-0.079132;0.996864;,
  0.000000;0.079132;-0.996864;,
  -0.095897;0.006279;0.995372;,
  -0.094405;0.179254;-0.979263;,
  0.000002;-0.079132;0.996864;,
  0.000000;1.000000;0.000000;,
  0.000000;0.137390;-0.990517;,
  0.096177;0.018528;-0.995192;,
  0.094383;-0.203199;0.974578;,
  0.000002;-0.139228;0.990260;,
  -0.928155;0.372195;0.000000;,
  -0.093664;-0.203882;0.974505;,
  -0.000004;0.995076;0.099111;,
  -0.000004;0.995076;-0.099111;,
  0.994963;0.014770;-0.099149;,
  0.994957;-0.015125;0.099155;,
  -0.825552;0.563716;-0.026247;,
  -0.829217;0.558305;0.026362;,
  0.245758;0.174868;0.953428;,
  0.237940;0.299761;-0.923866;,
  -0.246421;0.175152;0.953204;,
  -0.238944;0.299602;-0.923658;,
  0.246618;-0.174874;-0.953204;,
  0.239146;-0.299749;0.923558;,
  -0.586953;0.792209;-0.167006;,
  -0.586953;0.792209;0.167006;,
  -0.919704;0.388941;-0.053571;,
  -0.925390;0.375165;0.053897;,
  0.001021;0.073716;-0.997279;,
  -0.001021;-0.073716;0.997279;,
  0.001019;0.073486;-0.997296;,
  -0.001019;-0.073486;0.997296;,
  0.386011;-0.922494;-0.000000;,
  0.000000;-0.314283;-0.949329;,
  0.982459;0.186479;0.000000;,
  0.000000;0.314283;0.949329;,
  0.000000;-0.108560;0.994090;,
  0.000000;-0.079132;0.996864;,
  0.000000;0.079132;-0.996864;,
  0.000000;0.108560;-0.994090;,
  0.000000;-1.000000;0.000000;,
  0.000004;-0.079132;0.996864;,
  0.000003;-0.108358;0.994112;,
  0.000000;0.108358;-0.994112;,
  0.000000;0.079132;-0.996864;,
  0.000000;0.136888;-0.990587;,
  -0.000153;0.137908;-0.990445;,
  0.000000;-0.137390;0.990517;,
  0.000153;-0.137908;0.990445;,
  0.000000;-0.136888;0.990587;,
  0.000002;-0.140966;0.990015;,
  0.000154;-0.139947;0.990159;,
  -0.095843;0.019209;-0.995211;,
  -0.000153;0.139948;-0.990159;,
  0.000000;0.140967;-0.990014;,
  0.000000;0.139229;-0.990260;,
  0.928155;-0.372195;-0.000000;,
  -0.245532;-0.175246;-0.953416;,
  -0.237777;-0.299700;0.923928;,
  0.789799;-0.590992;0.164151;,
  0.713523;-0.700631;0.000045;,
  0.564948;-0.824709;0.026237;,
  0.564948;-0.824709;-0.026237;,
  0.000004;-0.792438;-0.609953;,
  0.000004;-0.792438;0.609953;,
  -0.786675;-0.090053;0.610764;,
  -0.786642;0.090254;-0.610777;,
  -0.994963;0.015071;-0.099104;,
  0.788251;0.089483;-0.608813;,
  -0.994969;-0.014715;0.099095;,
  0.831186;-0.441481;0.337971;,
  0.788215;-0.089684;0.608830;,
  0.005001;-0.995063;0.099118;,
  -0.003857;0.792398;0.609992;,
  0.005001;-0.995063;-0.099118;,
  0.386476;-0.920741;-0.053595;,
  -0.003857;0.792398;-0.609992;,
  0.000004;1.000000;0.000000;,
  1.000000;-0.000095;-0.000000;,
  -0.924326;0.381605;0.000000;,
  -1.000000;0.000095;0.000000;,
  0.004779;-0.999989;-0.000000;,
  -0.982459;-0.186479;0.000000;,
  0.000000;0.145190;-0.989404;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.145190;0.989404;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  88;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;2,40,41,4;,
  4;3,5,42,43;,
  4;44,44,44,44;,
  4;6,2,4,8;,
  4;6,8,45,46;,
  4;7,47,48,5;,
  4;7,5,5,3;,
  4;44,44,44,44;,
  4;44,44,44,44;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;10,49,50,11;,
  4;10,11,3,43;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;51,40,2,12;,
  4;51,12,52,53;,
  4;15,6,46,13;,
  4;15,13,54,55;,
  4;14,0,0,14;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;56,57,58,59;,
  4;56,59,47,7;,
  4;57,56,11,50;,
  4;9,9,9,9;,
  4;15,55,52,12;,
  4;60,1,1,60;,
  4;23,25,7,3;,
  4;24,22,2,6;,
  4;22,27,12,2;,
  4;26,23,3,11;,
  4;28,29,14,14;,
  4;25,61,56,7;,
  4;62,24,6,15;,
  4;63,64,60,60;,
  4;27,62,15,12;,
  4;61,26,11,56;,
  4;20,21,29,28;,
  4;65,66,64,63;,
  4;17,17,17,17;,
  4;67,67,67,67;,
  4;16,16,16,16;,
  4;68,68,68,68;,
  4;19,19,19,19;,
  4;69,69,69,69;,
  4;18,18,18,18;,
  4;70,70,70,70;,
  4;30,71,71,20;,
  4;72,72,72,72;,
  4;73,31,21,73;,
  4;74,75,75,63;,
  4;76,76,76,65;,
  4;77,77,29,77;,
  4;78,79,66,78;,
  4;80,80,80,28;,
  4;33,35,35,33;,
  4;34,32,32,34;,
  4;81,81,81,81;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;82,82,82,82;,
  4;36,36,65,66;,
  4;35,35,35,35;,
  4;34,34,34,34;,
  4;83,83,84,84;,
  4;83,83,20,21;,
  4;32,34,34,32;,
  4;35,33,33,35;,
  4;36,36,85,85;,
  3;29,21,31;,
  3;63,74,65;,
  3;28,30,20;,
  3;64,66,79;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;86,86,86,86;,
  4;9,9,9,9;,
  4;44,44,44,44;,
  4;87,87,87,87;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;91,91,91,91;,
  4;92,92,92,92;;
 }
 MeshTextureCoords {
  136;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.853780;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.853780;1.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.146220;1.000000;,
  0.000000;0.000000;,
  0.146220;0.000000;,
  0.148140;0.000000;,
  0.148140;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.851860;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.851860;1.000000;,
  0.851860;1.000000;,
  0.851860;0.000000;,
  1.000000;0.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.851860;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.851860;1.000000;,
  0.000000;1.000000;,
  0.146220;1.000000;,
  0.146220;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.146220;0.000000;,
  0.146220;0.000000;,
  0.851860;0.000000;,
  0.851860;0.000000;,
  1.000000;0.000000;,
  0.851860;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.851860;1.000000;,
  0.146220;1.000000;,
  0.146220;1.000000;,
  0.146220;0.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.851860;1.000000;,
  0.851860;0.000000;,
  0.146220;0.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.851860;1.000000;,
  0.851860;0.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.851860;1.000000;,
  0.851860;0.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.851860;1.000000;,
  0.146220;1.000000;,
  0.146220;1.000000;,
  0.851860;1.000000;,
  0.146220;0.000000;,
  0.851860;0.000000;,
  0.851860;0.000000;,
  0.146220;0.000000;,
  0.146220;0.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.146220;1.000000;,
  0.851860;1.000000;,
  0.851860;0.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.146220;1.000000;,
  0.851860;1.000000;,
  0.851860;0.000000;,
  0.146220;0.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.851860;1.000000;,
  0.851860;0.000000;,
  0.146220;0.000000;,
  0.146220;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
