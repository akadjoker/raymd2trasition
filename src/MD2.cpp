#include "MD2.h"
#include "rlgl.h"


anim_t CMD2Model::animlist[ 21 ] =
{
	// first, last, fps
	{   0,  39,  9 },	// STAND
	{  40,  45, 10 },	// RUN
	{  46,  53, 10 },	// ATTACK
	{  54,  57,  7 },	// PAIN_A
	{  58,  61,  7 },	// PAIN_B
	{  62,  65,  7 },	// PAIN_C
	{  66,  71,  7 },	// JUMP
	{  72,  83,  7 },	// FLIP
	{  84,  94,  7 },	// SALUTE
	{  95, 111, 10 },	// FALLBACK
	{ 112, 122,  7 },	// WAVE
	{ 123, 134,  6 },	// POINTIING
	{ 135, 153, 10 },	// CROUCH_STAND
	{ 154, 159,  7 },	// CROUCH_WALK
	{ 160, 168, 10 },	// CROUCH_ATTACK
	{ 196, 172,  7 },	// CROUCH_PAIN
	{ 173, 177,  5 },	// CROUCH_DEATH
	{ 178, 183,  7 },	// DEATH_FALLBACK
	{ 184, 189,  7 },	// DEATH_FALLFORWARD
	{ 190, 197,  7 },	// DEATH_FALLBACKSLOW
	{ 198, 198,  5 },	// BOOM
};

string sMD2AnimationNames[MAX_ANIMATIONS] =
{
	"Stand",
	"Run",
	"Attack",
	"Pain A",
	"Pain B",
	"Pain C",
	"Jump",
	"Flip",
	"Salute",
	"Fallback",
	"Wave",
	"Pointing",
	"Crouch Stand",
	"Crouch Walk",
	"Crouch Attack",
	"Crouch Pain",
	"Crouch Death",
	"Death Fallback",
	"Death Fall Forward",
	"Death Fallback Slow",
	"Boom"
};

Vector3 anorms[NUMVERTEXNORMALS] =
{
	{-0.525731, 0.000000, 0.850651},
{-0.442863, 0.238856, 0.864188},
{-0.295242, 0.000000, 0.955423},
{-0.309017, 0.500000, 0.809017},
{-0.162460, 0.262866, 0.951056},
{0.000000, 0.000000, 1.000000},
{0.000000, 0.850651, 0.525731},
{-0.147621, 0.716567, 0.681718},
{0.147621, 0.716567, 0.681718},
{0.000000, 0.525731, 0.850651},
{0.309017, 0.500000, 0.809017},
{0.525731, 0.000000, 0.850651},
{0.295242, 0.000000, 0.955423},
{0.442863, 0.238856, 0.864188},
{0.162460, 0.262866, 0.951056},
{-0.681718, 0.147621, 0.716567},
{-0.809017, 0.309017, 0.500000},
{-0.587785, 0.425325, 0.688191},
{-0.850651, 0.525731, 0.000000},
{-0.864188, 0.442863, 0.238856},
{-0.716567, 0.681718, 0.147621},
{-0.688191, 0.587785, 0.425325},
{-0.500000, 0.809017, 0.309017},
{-0.238856, 0.864188, 0.442863},
{-0.425325, 0.688191, 0.587785},
{-0.716567, 0.681718, -0.147621},
{-0.500000, 0.809017, -0.309017},
{-0.525731, 0.850651, 0.000000},
{0.000000, 0.850651, -0.525731},
{-0.238856, 0.864188, -0.442863},
{0.000000, 0.955423, -0.295242},
{-0.262866, 0.951056, -0.162460},
{0.000000, 1.000000, 0.000000},
{0.000000, 0.955423, 0.295242},
{-0.262866, 0.951056, 0.162460},
{0.238856, 0.864188, 0.442863},
{0.262866, 0.951056, 0.162460},
{0.500000, 0.809017, 0.309017},
{0.238856, 0.864188, -0.442863},
{0.262866, 0.951056, -0.162460},
{0.500000, 0.809017, -0.309017},
{0.850651, 0.525731, 0.000000},
{0.716567, 0.681718, 0.147621},
{0.716567, 0.681718, -0.147621},
{0.525731, 0.850651, 0.000000},
{0.425325, 0.688191, 0.587785},
{0.864188, 0.442863, 0.238856},
{0.688191, 0.587785, 0.425325},
{0.809017, 0.309017, 0.500000},
{0.681718, 0.147621, 0.716567},
{0.587785, 0.425325, 0.688191},
{0.955423, 0.295242, 0.000000},
{1.000000, 0.000000, 0.000000},
{0.951056, 0.162460, 0.262866},
{0.850651, -0.525731, 0.000000},
{0.955423, -0.295242, 0.000000},
{0.864188, -0.442863, 0.238856},
{0.951056, -0.162460, 0.262866},
{0.809017, -0.309017, 0.500000},
{0.681718, -0.147621, 0.716567},
{0.850651, 0.000000, 0.525731},
{0.864188, 0.442863, -0.238856},
{0.809017, 0.309017, -0.500000},
{0.951056, 0.162460, -0.262866},
{0.525731, 0.000000, -0.850651},
{0.681718, 0.147621, -0.716567},
{0.681718, -0.147621, -0.716567},
{0.850651, 0.000000, -0.525731},
{0.809017, -0.309017, -0.500000},
{0.864188, -0.442863, -0.238856},
{0.951056, -0.162460, -0.262866},
{0.147621, 0.716567, -0.681718},
{0.309017, 0.500000, -0.809017},
{0.425325, 0.688191, -0.587785},
{0.442863, 0.238856, -0.864188},
{0.587785, 0.425325, -0.688191},
{0.688191, 0.587785, -0.425325},
{-0.147621, 0.716567, -0.681718},
{-0.309017, 0.500000, -0.809017},
{0.000000, 0.525731, -0.850651},
{-0.525731, 0.000000, -0.850651},
{-0.442863, 0.238856, -0.864188},
{-0.295242, 0.000000, -0.955423},
{-0.162460, 0.262866, -0.951056},
{0.000000, 0.000000, -1.000000},
{0.295242, 0.000000, -0.955423},
{0.162460, 0.262866, -0.951056},
{-0.442863, -0.238856, -0.864188},
{-0.309017, -0.500000, -0.809017},
{-0.162460, -0.262866, -0.951056},
{0.000000, -0.850651, -0.525731},
{-0.147621, -0.716567, -0.681718},
{0.147621, -0.716567, -0.681718},
{0.000000, -0.525731, -0.850651},
{0.309017, -0.500000, -0.809017},
{0.442863, -0.238856, -0.864188},
{0.162460, -0.262866, -0.951056},
{0.238856, -0.864188, -0.442863},
{0.500000, -0.809017, -0.309017},
{0.425325, -0.688191, -0.587785},
{0.716567, -0.681718, -0.147621},
{0.688191, -0.587785, -0.425325},
{0.587785, -0.425325, -0.688191},
{0.000000, -0.955423, -0.295242},
{0.000000, -1.000000, 0.000000},
{0.262866, -0.951056, -0.162460},
{0.000000, -0.850651, 0.525731},
{0.000000, -0.955423, 0.295242},
{0.238856, -0.864188, 0.442863},
{0.262866, -0.951056, 0.162460},
{0.500000, -0.809017, 0.309017},
{0.716567, -0.681718, 0.147621},
{0.525731, -0.850651, 0.000000},
{-0.238856, -0.864188, -0.442863},
{-0.500000, -0.809017, -0.309017},
{-0.262866, -0.951056, -0.162460},
{-0.850651, -0.525731, 0.000000},
{-0.716567, -0.681718, -0.147621},
{-0.716567, -0.681718, 0.147621},
{-0.525731, -0.850651, 0.000000},
{-0.500000, -0.809017, 0.309017},
{-0.238856, -0.864188, 0.442863},
{-0.262866, -0.951056, 0.162460},
{-0.864188, -0.442863, 0.238856},
{-0.809017, -0.309017, 0.500000},
{-0.688191, -0.587785, 0.425325},
{-0.681718, -0.147621, 0.716567},
{-0.442863, -0.238856, 0.864188},
{-0.587785, -0.425325, 0.688191},
{-0.309017, -0.500000, 0.809017},
{-0.147621, -0.716567, 0.681718},
{-0.425325, -0.688191, 0.587785},
{-0.162460, -0.262866, 0.951056},
{0.442863, -0.238856, 0.864188},
{0.162460, -0.262866, 0.951056},
{0.309017, -0.500000, 0.809017},
{0.147621, -0.716567, 0.681718},
{0.000000, -0.525731, 0.850651},
{0.425325, -0.688191, 0.587785},
{0.587785, -0.425325, 0.688191},
{0.688191, -0.587785, 0.425325},
{-0.955423, 0.295242, 0.000000},
{-0.951056, 0.162460, 0.262866},
{-1.000000, 0.000000, 0.000000},
{-0.850651, 0.000000, 0.525731},
{-0.955423, -0.295242, 0.000000},
{-0.951056, -0.162460, 0.262866},
{-0.864188, 0.442863, -0.238856},
{-0.951056, 0.162460, -0.262866},
{-0.809017, 0.309017, -0.500000},
{-0.864188, -0.442863, -0.238856},
{-0.951056, -0.162460, -0.262866},
{-0.809017, -0.309017, -0.500000},
{-0.681718, 0.147621, -0.716567},
{-0.681718, -0.147621, -0.716567},
{-0.850651, 0.000000, -0.525731},
{-0.688191, 0.587785, -0.425325},
{-0.587785, 0.425325, -0.688191},
{-0.425325, 0.688191, -0.587785},
{-0.425325, -0.688191, -0.587785},
{-0.587785, -0.425325, -0.688191},
{-0.688191, -0.587785, -0.425325},
};

#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

#pragma warning( once : 4305 )
void CMD2Model::free()
{
delete (faces);
delete (uvs);
UnloadTexture(tex);

/*
rlUnloadVertexArray(vaoId);

rlUnloadVertexBuffer(vboId[0]);
rlUnloadVertexBuffer(vboId[1]);
rlUnloadVertexBuffer(vboId[2]);
rlUnloadVertexBuffer(vboId[3]);


delete(vertices);
delete(normals);
delete(texcoords);
*/

}

Vector3 lerp(Vector3 start,Vector3 end,float  amount)
{
Vector3 r;
		 r.x = start.x + ((end.x - start.x) * amount);
		 r.y = start.y + ((end.y - start.y) * amount);
		 r.z = start.z + ((end.z - start.z) * amount);
return r;

}


void Draw3DSprite( Texture2D texture, Rectangle source, Vector3 center, float size, Color tint)
{
    // NOTE: Billboard size will maintain source rectangle aspect ratio, size will represent billboard width
    Vector2 sizeRatio = { size, size*(float)source.height/source.width };

    Matrix matView = MatrixLookAt({0,0,0}, {-1,0,0}, {0,1,0});

    Vector3 right = { matView.m0, matView.m4, matView.m8 };
    //Vector3 up = { matView.m1, matView.m5, matView.m9 };

    // NOTE: Billboard locked on axis-Y
    Vector3 up = { 0.0f, 1.0f, 0.0f };
/*
    a-------b
    |       |
    |   *   |
    |       |
    d-------c
*/
    right = Vector3Scale(right, sizeRatio.x/2);
    up = Vector3Scale(up, sizeRatio.y/2);

    Vector3 p1 = Vector3Add(right, up);
    Vector3 p2 = Vector3Subtract(right, up);

    Vector3 a = Vector3Subtract(center, p2);
    Vector3 b = Vector3Add(center, p1);
    Vector3 c = Vector3Add(center, p2);
    Vector3 d = Vector3Subtract(center, p1);

    rlCheckRenderBatchLimit(4);

    //rlSetTexture(texture.id);

    rlBegin(RL_QUADS);
        rlColor4ub(tint.r, tint.g, tint.b, tint.a);

        // Bottom-left corner for texture and quad
        rlTexCoord2f((float)source.x/texture.width, (float)source.y/texture.height);
        rlVertex3f(a.x, a.y, a.z);

        // Top-left corner for texture and quad
        rlTexCoord2f((float)source.x/texture.width, (float)(source.y + source.height)/texture.height);
        rlVertex3f(d.x, d.y, d.z);

        // Top-right corner for texture and quad
        rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)(source.y + source.height)/texture.height);
        rlVertex3f(c.x, c.y, c.z);

        // Bottom-right corner for texture and quad
        rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)source.y/texture.height);
        rlVertex3f(b.x, b.y, b.z);
    rlEnd();

   // rlSetTexture(0);
}

void CMD2Model::renderLerp(int currentFrame,int nextFrame,Color color)
{



float poll = (float)GetFrameTime();


rlEnableTexture(tex.id);
rlSetTexture(tex.id);

//Draw3DSprite(tex,{0,0,tex.width,tex.height},{0,0},10,WHITE);


rlBegin(RL_TRIANGLES);
rlColor4ub(255,255,255,255);

for (int i=0;i<num_tris;i++)
{
    int f0= faces[i].vertex[0];
    int f1= faces[i].vertex[1];
    int f2= faces[i].vertex[2];



    int uvf0= faces[i].st[0];
    int uvf1= faces[i].st[1];
    int uvf2= faces[i].st[2];


    Vector3 v1= lerp(vVertices[currentFrame][f0],vVertices[nextFrame][f0],poll);
    Vector3 v2= lerp(vVertices[currentFrame][f1],vVertices[nextFrame][f1],poll);
    Vector3 v3= lerp(vVertices[currentFrame][f2],vVertices[nextFrame][f2],poll);



    Vector2 uv1= TextureCoords[uvf0];
    Vector2 uv2= TextureCoords[uvf1];
    Vector2 uv3= TextureCoords[uvf2];


    rlTexCoord2f(uv1.x,uv1.y);
    rlVertex3f(v1.x,v1.y,v1.z);



    rlTexCoord2f(uv2.x,uv2.y);
    rlVertex3f(v2.x,v2.y,v2.z);



    rlTexCoord2f(uv3.x,uv3.y);
    rlVertex3f(v3.x,v3.y,v3.z);






}


rlEnd();


rlSetTexture(0);
/*
for (int i=0;i<num_tris;i++)
{
    int f0= faces[i].vertex[0];
    int f1= faces[i].vertex[1];
    int f2= faces[i].vertex[2];



    int uvf0= faces[i].st[0];
    int uvf1= faces[i].st[1];
    int uvf2= faces[i].st[2];


    Vector3 v1= lerp(vVertices[currentFrame][f0],vVertices[nextFrame][f0],poll);
    Vector3 v2= lerp(vVertices[currentFrame][f1],vVertices[nextFrame][f1],poll);
    Vector3 v3= lerp(vVertices[currentFrame][f2],vVertices[nextFrame][f2],poll);



    Vector2 uv1= TextureCoords[uvf0];
    Vector2 uv2= TextureCoords[uvf1];
    Vector2 uv3= TextureCoords[uvf2];



    DrawLine3D(v1,v2,color);
    DrawLine3D(v2,v3,color);
    DrawLine3D(v3,v1,color);



    		//var v1:Vector3 = Vector3.Lerp(vertex[currentFrame * vertex_Count + faces[i].v0], vertex[nextFrame * vertex_Count + faces[i].v0], poll);

}
*/


}
void CMD2Model::LoadModel(char* sFilename)
{

nextAnima=false;
anim_mode=0;
anim_time=0;
render_a=0;
render_b=0;
render_t=0;



	FILE* fp = fopen(sFilename, "rb");

	fread(&header, sizeof(md2_t), 1, fp); // Read header where all info about model is stored

	char* buffer = new char[header.num_frames * header.framesize]; // Read all frame data to one big buffer
	fseek(fp, header.ofs_frames, SEEK_SET);
	fread(buffer, sizeof(char), header.num_frames * header.framesize, fp);

	vVertices.resize(header.num_frames, vector<Vector3>(header.num_xyz)); // Allocate space for vertices
	vNormals.resize(header.num_frames, vector<int>(header.num_xyz)); // And normals


	float scaleFactor =10.0f;

	// Extract vertices and normals from frame dataframe_ptr->scale.x /= scaleFactor;
	FOR(i, header.num_frames)
	{
		frame_t* frame_ptr = (frame_t*)&buffer[header.framesize * i]; // Convert buffer to frame_t pointer



        //TraceLog(LOG_INFO,"name %f %f %f ",frame_ptr->scale.x,frame_ptr->scale.y,frame_ptr->scale.z);
		FOR(j, header.num_xyz)
		{
		    Vector3 vtx;
			vtx.x = frame_ptr->translate.x + (float(frame_ptr->verts[j].v[0]) * frame_ptr->scale.x);
			vtx.z = frame_ptr->translate.y + (float(frame_ptr->verts[j].v[1]) * frame_ptr->scale.y);
			vtx.y = frame_ptr->translate.z + (float(frame_ptr->verts[j].v[2]) * frame_ptr->scale.z);
			vVertices[i][j]={vtx.x/scaleFactor,vtx.y/scaleFactor,vtx.z/scaleFactor};
			vNormals[i][j] = frame_ptr->verts[j].lightnormalindex;

			FrameVertices.push_back({vVertices[i][j].x/scaleFactor,vVertices[i][j].z/scaleFactor,vVertices[i][j].y/scaleFactor});
		}
	}

	faces  = new faces_t[header.num_tris * sizeof(faces_t)]; // Read all frame data to one big buffer
    fseek(fp, header.ofs_tris, SEEK_SET);
	fread(faces, sizeof(faces_t), header.num_tris *  sizeof(faces_t), fp);
	FOR(i,header.num_tris)
	{
	  // TraceLog(LOG_INFO,"name %d %d %d ",faces[i].vface[0],faces[i].vface[1],faces[i].vface[2]);

	}

	num_tris= header.num_tris;

	uvs= new uv_tex[header.num_st * sizeof(uv_tex)];
	fseek(fp, header.ofs_st, SEEK_SET);
	fread(uvs, sizeof(uv_tex), header.num_st *  sizeof(uv_tex), fp);

	TraceLog(LOG_INFO,"uvs %d ",header.num_st);
	TraceLog(LOG_INFO,"vertex %d ",header.num_xyz);
	TraceLog(LOG_INFO,"triangles %d ",header.num_tris);

	TraceLog(LOG_INFO,"frames %d ",header.num_frames);


    FOR(i,header.num_st)
	{
	  // TraceLog(LOG_INFO,"name %d %d ",uvs[i].t,uvs[i].s);
	  TextureCoords.push_back({(float)uvs[i].s/header.skinwidth,(float)uvs[i].t/header.skinheight});
	  // TraceLog(LOG_INFO,"name %f %f ",(float)uvs[i].t/header.skinwidth,(float)uvs[i].s/header.skinheight);

	}



delete (buffer);



	string sPath = sFilename;
	int index = sPath.find_last_of("\\/");
	string sDirectory = index != -1 ? sPath.substr(0, index+1) : "";
	string sPureFilename = index != -1 ? sPath.substr(index+1) : sFilename;

	string sTextureExtensions[] = {"jpg", "jpeg", "png", "bmp", "tga"};
	index = sPureFilename.find_last_of(".");
	if(index != -1)
	{
		string sStripped = sPureFilename.substr(0, index+1);
		FOR(i, 5)
		{
			string sTry = sDirectory+sStripped+sTextureExtensions[i];
			//if(tSkin.LoadTexture2D(sTry, true))
			//{
			//	tTextures[i].SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
              //break;
			//}
		}
	}
	fclose(fp);

	tex= LoadTexture("/media/djoker/code/linux/cpp/raylib/rayprojects/raymd2/models/blade/Blade.png");


    vaoId = 0;        // Vertex Array Object
    vboId[0] = 0;     // Vertex positions VBO
    vboId[1] = 0;     // Vertex texcoords VBO
    vboId[2] = 0;     // Vertex normals VBO


    /*
vertexCount=num_tris*3;

//vertices  = (float *)RL_MALLOC(vertexCount*3*3*sizeof(float));
//texcoords = (float *)RL_MALLOC(vertexCount*3*2*sizeof(float));
//normals   = (float *)RL_MALLOC(vertexCount*3*3*sizeof(float));

vertices  = new float[(vertexCount*3*3*sizeof(float))];
texcoords = new float[(vertexCount*3*2*sizeof(float))];
normals   = new float[(vertexCount*3*3*sizeof(float))];
colors    = new unsigned char [(vertexCount*4*sizeof(unsigned char))];


	vector<Vector3> RenderVertices;
	vector<Vector2> RenderUvs;
	vector<Vector3> RenderNormals;
	vector<Color> RenderColors;

int vtx=0;

for (int i=0;i<num_tris;i++)
{


   for (int j=0;j<3;j++)
   {
    int f0= faces[i].vertex[j];
    int uvf0= faces[i].st[j];
    Vector3 v1= vVertices[0][f0];
    Vector2 uv1= TextureCoords[uvf0];

    RenderVertices.push_back(v1);
    RenderUvs.push_back(uv1);
    RenderNormals.push_back(v1);
    RenderColors.push_back(WHITE);


        vertices[3*vtx++]       = v1.x;
        vertices[3*(vtx++) + 1] = v1.y;
        vertices[3*(vtx++) + 2] = v1.z;


     }




}

/*
vaoId = rlLoadVertexArray();
rlEnableVertexArray(vaoId);

vertexCount = 24;
// NOTE: Attributes must be uploaded considering default locations points

// Enable vertex attributes: position (shader-location = 0)
vboId[0] = rlLoadVertexBuffer(vertices, vertexCount*3*sizeof(float), true);
rlSetVertexAttribute(0, 3, RL_FLOAT, 0, 0, 0);
rlEnableVertexAttribute(0);

//rlUpdateVertexBuffer(vboId[0], vertices, vertexCount*3*sizeof(float), 0);    // Update vertex position

// Enable vertex attributes: texcoords (shader-location = 1)
vboId[1] = rlLoadVertexBuffer(texcoords, vertexCount*2*sizeof(float), false);
rlSetVertexAttribute(1, 2, RL_FLOAT, 0, 0, 0);
rlEnableVertexAttribute(1);

// Enable vertex attributes: normals (shader-location = 2)
vboId[2] = rlLoadVertexBuffer(normals, vertexCount*3*sizeof(float), true);
rlSetVertexAttribute(2, 3, RL_FLOAT, 0, 0, 0);
rlEnableVertexAttribute(2);

vboId[3] = rlLoadVertexBuffer(&RenderColors[0], vertexCount*4*sizeof(unsigned char), false);
rlSetVertexAttribute(3, 4, RL_UNSIGNED_BYTE, 1, 0, 0);
rlEnableVertexAttribute(3);

   //rlUpdateVertexBuffer(model.meshes[m].vboId[0], model.meshes[m].animVertices, model.meshes[m].vertexCount*3*sizeof(float), 0);    // Update vertex position
            //rlUpdateVertexBuffer(model.meshes[m].vboId[2], model.meshes[m].animNormals, model.meshes[m].vertexCount*3*sizeof(float), 0);     // Update vertex normals

rlDisableVertexArray();
*/
}

/*-----------------------------------------------

Name:	RenderModel

Params:	animState - structure with animation state -
		if it's NULL, then only static model is rendered

Result:	Renders model.

/*---------------------------------------------*/


void DrawTria3D(Vector3 v1, Vector3 v2, Vector3 v3,Vector2 uv1,Vector2 uv2,Vector2 uv3, Color color)
{
    rlCheckRenderBatchLimit(4);

    rlBegin(RL_QUADS);
        rlColor4ub(color.r, color.g, color.b, color.a);

        rlTexCoord2f(uv1.x,uv1.y);
        rlVertex3f(v1.x, v1.y, v1.z);

        rlTexCoord2f(uv2.x,uv2.y);
        rlVertex3f(v2.x, v2.y, v2.z);

        rlTexCoord2f(uv3.x,uv3.y);
        rlVertex3f(v3.x, v3.y, v3.z);


        rlTexCoord2f(uv1.x,uv1.y);
        rlVertex3f(v1.x, v1.y, v1.z);

    rlEnd();
}
void CMD2Model::RenderModel(animState_t* animState)
{



rlSetTexture(tex.id);




for (int i=0;i<num_tris;i++)
{
    int f0= faces[i].vertex[0];
    int f1= faces[i].vertex[1];
    int f2= faces[i].vertex[2];



    int uvf0= faces[i].st[0];
    int uvf1= faces[i].st[1];
    int uvf2= faces[i].st[2];


    Vector3 v1= lerp(vVertices[animState->curr_frame][f0],vVertices[animState->next_frame][f0],animState->interpol);
    Vector3 v2= lerp(vVertices[animState->curr_frame][f1],vVertices[animState->next_frame][f1],animState->interpol);
    Vector3 v3= lerp(vVertices[animState->curr_frame][f2],vVertices[animState->next_frame][f2],animState->interpol);



    Vector2 uv1= TextureCoords[uvf0];
    Vector2 uv2= TextureCoords[uvf1];
    Vector2 uv3= TextureCoords[uvf2];


   DrawTria3D(v1,v2,v3,uv1,uv2,uv3,WHITE);


}

//    rlEnableStatePointer(GL_VERTEX_ARRAY, vertices);
    //rlEnableStatePointer(GL_TEXTURE_COORD_ARRAY, texcoords);
    //rlEnableStatePointer(GL_NORMAL_ARRAY, normals);

/*
        if (rlEnableVertexArray(vaoId))
        {

        rlEnableVertexBuffer(vboId[0]);
        rlSetVertexAttribute(0, 3, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(0);


        // Bind mesh VBO data: vertex texcoords (shader-location = 1)
        rlEnableVertexBuffer(vboId[1]);
        rlSetVertexAttribute(1, 2, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(1);


        // Bind mesh VBO data: vertex normals (shader-location = 2)
        rlEnableVertexBuffer(vboId[2]);
        rlSetVertexAttribute(2, 3, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(2);


        rlEnableVertexBuffer(vboId[3]);
        rlSetVertexAttribute(3, 4, RL_UNSIGNED_BYTE, 1, 0, 0);
        rlEnableVertexAttribute(3);





        }
*/

      /*
        rlEnableVertexBuffer(vboId[1]);
        rlSetVertexAttribute(2, 2, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(1);

        rlEnableVertexBuffer(vboId[2]);
        rlSetVertexAttribute(1, 3, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(2);
*/


rlDrawVertexArray(0,12);

//rlEnd();


rlSetTexture(0);

rlDisableVertexArray();
rlDisableVertexBuffer();



/*
for (int i=0;i<num_tris;i++)
{
    int f0= faces[i].vertex[0];
    int f1= faces[i].vertex[1];
    int f2= faces[i].vertex[2];



    int uvf0= faces[i].st[0];
    int uvf1= faces[i].st[1];
    int uvf2= faces[i].st[2];


    Vector3 v1= vVertices[animState->curr_frame][f0];
    Vector3 v2= vVertices[animState->curr_frame][f1];
    Vector3 v3= vVertices[animState->curr_frame][f2];






    DrawLine3D(v1,v2,RED);
    DrawLine3D(v2,v3,RED);
    DrawLine3D(v3,v1,RED);




}
*/
/*
	glBindVertexArray(uiVAO);

	int iTotalOffset = 0;
	tSkin.BindTexture();
	if(animState == NULL)
	{
		glEnableVertexAttribArray(0);
		vboFrameVertices[0].BindVBO();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);
		spMD2Animation.SetUniform("fInterpolation", -1.0f); // Set interpolation to negative number, so that vertex shader knows

		FOR(i, ESZ(renderModes)) // Just render using previously extracted render modes
		{
			glDrawArrays(renderModes[i], iTotalOffset, numRenderVertices[i]);
			iTotalOffset += numRenderVertices[i];
		}
	}
	else
	{
		// Change vertices pointers to current frame
		glEnableVertexAttribArray(0);
		vboFrameVertices[animState->curr_frame].BindVBO();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);

		glEnableVertexAttribArray(3);
		vboFrameVertices[animState->next_frame].BindVBO();
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);

		// Change normal pointers to current frame

		glEnableVertexAttribArray(2);
		vboFrameVertices[animState->curr_frame].BindVBO();
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);

		glEnableVertexAttribArray(4);
		vboFrameVertices[animState->next_frame].BindVBO();
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);

		spMD2Animation.SetUniform("fInterpolation", animState->interpol);

		FOR(i, ESZ(renderModes))
		{
			glDrawArrays(renderModes[i], iTotalOffset, numRenderVertices[i]);
			iTotalOffset += numRenderVertices[i];
		}
	}
	*/
}



animState_t CMD2Model::StartAnimation(animType_t type)
{
	animState_t res;


	nextAnima=true;

	res.startframe = animlist[type].first_frame;
	res.endframe = animlist[type].last_frame;


	res.curr_frame = animlist[type].first_frame;
	res.next_frame = animlist[type].first_frame + 1;

	res.fps = animlist[type].fps;
	res.type = type;

	res.curr_time = 0.0f;
	res.old_time = 0.0f;

	res.interpol = 0.0f;

	return res;
}


animState_t CMD2Model::StartNextAnimation(animType_t type)
{
	animState_t res;

    nextAnima=true;

	res.startframe = animlist[type].first_frame;
	res.endframe = animlist[type].last_frame;


	res.curr_frame = animlist[type].first_frame;
	res.next_frame = animlist[type].first_frame + 1;

	res.fps = animlist[type].fps;
	res.type = type;

	res.curr_time = 0.0f;
	res.old_time = 0.0f;

	res.interpol = 0.0f;

	return res;
}
/*-----------------------------------------------

Name:	UpdateAnimation

Params:	animState - animation state to update
		fTimePassed - time passed since the last
		frame

Result:	Updates data in animation structure (performs
		animation basically).

/*---------------------------------------------*/

void CMD2Model::UpdateAnimation(animState_t* animState, float fTimePassed)
{
	animState->curr_time += fTimePassed;

	if (nextAnima)
	{

	if(animState->curr_time - animState->old_time > (1.0f / float(animState->fps)))
	{
		animState->old_time = animState->curr_time;

		animState->curr_frame = animState->next_frame;
		animState->next_frame++;
		if(animState->next_frame > animState->endframe)
		{
			animState->next_frame = animState->startframe;
			}
	}

	animState->interpol = float(animState->fps) * (animState->curr_time - animState->old_time);

	} else
	{


	if(animState->curr_time - animState->old_time > (1.0f / float(animState->fps)))
	{
		animState->old_time = animState->curr_time;

		animState->curr_frame = animState->next_frame;
		animState->next_frame++;
		if(animState->next_frame > animState->endframe)
		{
			animState->next_frame = animState->startframe;
			}
	}

	animState->interpol = float(animState->fps) * (animState->curr_time - animState->old_time);

	}


}


void CMD2Model::Render(int frame,float time )
{

rlSetTexture(tex.id);


for (int i=0;i<num_tris;i++)
{
    int f0= faces[i].vertex[0];
    int f1= faces[i].vertex[1];
    int f2= faces[i].vertex[2];



    int uvf0= faces[i].st[0];
    int uvf1= faces[i].st[1];
    int uvf2= faces[i].st[2];


    Vector3 v1= lerp(vVertices[latsFrame][f0],vVertices[frame][f0],time);
    Vector3 v2= lerp(vVertices[latsFrame][f1],vVertices[frame][f1],time);
    Vector3 v3= lerp(vVertices[latsFrame][f2],vVertices[frame][f2],time);




    Vector2 uv1= TextureCoords[uvf0];
    Vector2 uv2= TextureCoords[uvf1];
    Vector2 uv3= TextureCoords[uvf2];




   DrawTria3D(v1,v2,v3,uv1,uv2,uv3,WHITE);


}




rlSetTexture(0);

}

void CMD2Model::Render(int frame_a,int frame_b,float time )
{



rlSetTexture(tex.id);




for (int i=0;i<num_tris;i++)
{
    int f0= faces[i].vertex[0];
    int f1= faces[i].vertex[1];
    int f2= faces[i].vertex[2];



    int uvf0= faces[i].st[0];
    int uvf1= faces[i].st[1];
    int uvf2= faces[i].st[2];


    Vector3 v1= lerp(vVertices[frame_a][f0],vVertices[frame_b][f0],time);
    Vector3 v2= lerp(vVertices[frame_a][f1],vVertices[frame_b][f1],time);
    Vector3 v3= lerp(vVertices[frame_a][f2],vVertices[frame_b][f2],time);



    Vector2 uv1= TextureCoords[uvf0];
    Vector2 uv2= TextureCoords[uvf1];
    Vector2 uv3= TextureCoords[uvf2];


   DrawTria3D(v1,v2,v3,uv1,uv2,uv3,WHITE);


}




rlSetTexture(0);

}
bool CMD2Model::render( )
{

	if( anim_mode & 0x8000 )
	{
		Render( anim_time,trans_time );
		//TraceLog(LOG_INFO,"trans %d %f %f",latsFrame, anim_time,trans_time );
	}else{
		Render( render_a,render_b,render_t );
	}
	return false;
}


void CMD2Model::startMD2Anim(int first, int last, int mode, float speed, float trans)
{
if( last<first ) std::swap( first,last );

numFrames=178;
latsFrame=render_a;

	if  (( first>=anim_first) && (last<=anim_last)) return;


	if( first<0 ) first=0;
	else if( first>=numFrames) first=numFrames-1;

	if( last<0 ) last=0;
	else if( last>=numFrames ) last=numFrames-1;

	if( trans>0 )
	{

		if( anim_mode & 0x8000 )
		{
		// Render(anim_time,trans_time );
		}
		else
		{
		// Render( render_a,render_b,render_t );
		}

		trans_speed=1.0f/trans;
		trans_time=0;
		mode|=0x8000;
	}

	anim_first=first;
	anim_last=last;
	anim_len=last-first;
	anim_speed=speed;
	anim_time=((mode&0x7fff)==ANIM_MODE_LOOP || anim_speed>=0) ? anim_first : anim_last;
	anim_mode=mode;

	if( !anim_speed || !anim_len )
	{
		render_a=render_b=anim_time;
		render_t=0;
		anim_mode&=0x8000;
	}

}

void CMD2Model::animate( float elapsed )
{


    if( anim_time>=anim_last )
	{
	  TraceLog(LOG_INFO,"trans %f %f %d", anim_time,anim_last ,anim_mode);
	  animationEnd=true;
	}

    if( !anim_mode ) return;




	if( anim_mode & 0x8000 )
	{
		trans_time+=trans_speed;
		if( trans_time<1 ) return;
		anim_mode&=~0x8000;
		if( !anim_mode ) return;
	}
	anim_time=anim_time+anim_speed * elapsed;




	if( anim_time<anim_first )
	{
		switch( anim_mode ){
		case ANIM_MODE_LOOP:
			anim_time+=anim_len;
			break;
		case ANIM_MODE_PINGPONG:
			anim_time=anim_first+(anim_first-anim_time);
			anim_speed=-anim_speed;
			break;
		default:
			anim_time=anim_first;
			anim_mode=0;
			break;
		}
	}else if( anim_time>=anim_last )
	{
		switch( anim_mode )
		{
		case ANIM_MODE_LOOP:
			anim_time-=anim_len;
			break;
		case ANIM_MODE_PINGPONG:
			anim_time=anim_last-(anim_time-anim_last);
			anim_speed=-anim_speed;
			break;
		default:
			anim_time=anim_last;
			anim_mode=0;
			break;
		}
	}
	render_a=floor(anim_time);
	render_b=render_a+1;
	if( anim_mode==ANIM_MODE_LOOP && render_b==anim_last )
	{
	 render_b=anim_first;
	 animationEnd=false;
	}
	render_t=anim_time-render_a;

}

int CMD2Model::getMD2AnimLength() const
{

}


void CMD2Model::PauseAnimation()
{

}

void CMD2Model::StopAnimation()
{

}

