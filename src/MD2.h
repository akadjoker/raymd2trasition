#ifndef MD2_H
#define MD2_H
#include <ctime>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

#define ESZ(elem) (int)elem.size()

#include "raylib.h"



enum{
		ANIM_MODE_LOOP=1,
		ANIM_MODE_PINGPONG=2,
		ANIM_MODE_ONESHOT=3
	};

// number of precalculated normals
#define NUMVERTEXNORMALS		162

// precalculated normal vectors
#define SHADEDOT_QUANT			16

// magic number "IDP2" or 844121161
#define MD2_IDENT				(('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// model version
#define	MD2_VERSION				8

// maximum number of vertices for a MD2 model
#define MAX_MD2_VERTS			2048


typedef int8_t Sint8;
typedef uint8_t Uint8;
typedef int16_t Sint16;
typedef uint16_t Uint16;
typedef int32_t Sint32;
typedef uint32_t Uint32;

// md2 header
typedef struct
{
	int     ident;              // magic number. must be equal to "IDP2"
	int     version;            // md2 version. must be equal to 8

	int     skinwidth;          // width of the texture
	int     skinheight;         // height of the texture
	int     framesize;          // size of one frame in bytes

	int     num_skins;          // number of textures
	int     num_xyz;            // number of vertices
	int     num_st;             // number of texture coordinates
	int     num_tris;           // number of triangles
	int     num_glcmds;         // number of opengl commands
	int     num_frames;         // total number of frames

	int     ofs_skins;          // offset to skin names (64 bytes each)
	int     ofs_st;             // offset to s-t texture coordinates
	int     ofs_tris;           // offset to triangles
	int     ofs_frames;         // offset to frame data
	int     ofs_glcmds;         // offset to opengl commands
	int     ofs_end;            // offset to end of file

} md2_t;

// md2 compressed vertex
typedef struct
{
	unsigned char   v[3];                // compressed vertex (x, y, z) coordinates
	unsigned char   lightnormalindex;    // index to a normal vector for the lighting

} vertex_t;

// md2 frame data (vertices are stored here)
typedef struct
{
	Vector3       scale;       // scale values
	Vector3       translate;   // translation vector
	char        name[16];       // frame name
	vertex_t    verts[1];       // first vertex of this frame

} frame_t;

typedef struct
{
	  unsigned short vertex[3];  // Triangle's vertex indices
      unsigned short st[3];      // Texture coords. indices


} faces_t;

typedef struct
{
  short s;
  short t;
} uv_tex;
// animation data - first and last frame and FPS to know how fast should it run
typedef struct
{
	int		first_frame;			// first frame of the animation
	int		last_frame;				// number of frames
	int		fps;					// number of frames per second

} anim_t;

// status animation
typedef struct
{
	int		startframe;				// first frame
	int		endframe;				// last frame
	int		fps;					// frame per second for this animation

	float	curr_time;				// current time
	float	old_time;				// old time
	float	interpol;				// percent of interpolation

	int		type;					// animation type

	int		curr_frame;				// current frame
	int		next_frame;				// next frame

} animState_t;

// animation list
typedef enum {
	STAND,
	RUN,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
	POINTING, // Had to rename this from POINT to POINTING because of POINT class in windows.h
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH,
	DEATH_FALLBACK,
	DEATH_FALLFORWARD,
	DEATH_FALLBACKSLOW,
	BOOM,

	MAX_ANIMATIONS

} animType_t;

extern string sMD2AnimationNames[MAX_ANIMATIONS];

class CMD2Model
{
public:
	void LoadModel(char* sFilename);

	void free();

	void RenderModel(animState_t* animState);

		void animate( float elapsed );

	void startMD2Anim( int first,int last,int mode,float speed,float trans );

	int getMD2AnimLength()const;
	bool getMD2Animating()const{ return !!anim_mode; }
	float getMD2AnimTime()const{ return anim_time; }

	animState_t StartAnimation(animType_t type);
	animState_t StartNextAnimation(animType_t type);
	void UpdateAnimation(animState_t* animState, float fTimePassed);
	void PauseAnimation();
	void StopAnimation();

    void Render(int frame_a,int frame_b,float time );
    void Render(int frame,float time );
    bool render( );
	void renderLerp(int currentFrame,int nextFrame,Color color);

	static anim_t	animlist[21];
private:

    int numFrames;
    float *vertices;        // Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
    float *texcoords;       // Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
    float *normals;         // Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
    unsigned char *colors;  // Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
    unsigned int vaoId;     // OpenGL Vertex Array Object id
    unsigned int vboId[4];    // OpenGL Vertex Buffer Objects id (default vertex data)
    int vertexCount;
    int num_tris;
	md2_t header;
    Texture2D tex;
	faces_t* faces;
	uv_tex* uvs;
	vector< vector<Vector3> > vVertices; // Vertices extracted for every frame
	vector <vector< int > > vNormals; // Normal indices extracted for every frame
	vector<int> glCommands; // Rendering OpenGL commands


	vector<Vector3> RenderVertices;
	vector<Vector2> RenderUvs;
	vector<Vector3> RenderNormals;
	vector<Color> RenderColors;

	vector<Vector3> FrameVertices; // All frames (keyframes) of model
	vector<Vector2> TextureCoords; // Texture coords are same for all frames

    bool nextAnima;
    bool animationEnd;
    int latsFrame=0;

    	int anim_mode;
	float anim_time,anim_speed;
	int anim_first,anim_last,anim_len;

	float render_t;
	int render_a,render_b;

	float trans_time,trans_speed;

	Texture2D tSkin;


};

#endif // MD2_H
