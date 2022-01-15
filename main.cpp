/*******************************************************************************************
*
*   raylib [core] example - Initialize 3d camera free
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "MD2.h"
#include "rImgui.h"

const int screenWidth = 1200;
    const int screenHeight = 850;


typedef enum STATETRASITION {TRANONE,FADEIN,FADEOUT};

class StateMachine;

class State
{

public:
    State(std::string Name):name(Name)
    {
      TraceLog(LOG_INFO,"crate state %s ",name.c_str());
    }
    virtual ~State(){};
    virtual  void enter(void* userdata){};
    virtual  void exit (void* userdata){};
    virtual void update(float dt){};
    virtual void render(){};

    virtual State* SwitchTo(std::string state_name,void* userdata)
    {
      if (fsm)
      {
//         return fsm->transition_to(name,userdata);
      }
      return NULL;
    }

public:
  std::string name;
  StateMachine* fsm;
protected:

};

class StateMachine
{
public:
    StateMachine()
    {
    curr_state=NULL;
    };
    virtual ~StateMachine()
    {
       std::vector<State*>::const_iterator it;
        for ( it=states.begin();it!=states.end();++it )
	    {
		  State *obj=*it;
		  obj->exit(NULL);
		  obj=NULL;
        }
    };

    void update(float dt)
    {
       if (curr_state)
       {
         curr_state->update(dt);
       }
    }
    void render()
    {
       if (curr_state)
       {
         curr_state->render();
       }
    }
    void addState(State* state)
    {
      states.push_back(state);
    }

    virtual State* SwitchTo(std::string state_name, void* userdata=NULL)
    {
       if (curr_state)
       {

          if (curr_state->name==state_name) return curr_state;
          TraceLog(LOG_INFO,"exti state %s ",curr_state->name.c_str());
          curr_state->exit(userdata);
          curr_state=NULL;
       }

        std::vector<State*>::const_iterator it;
        for ( it=states.begin();it!=states.end();++it )
	    {
		  State *obj=*it;
		  if (obj->name==state_name)
		  {
		    curr_state=obj;
		    curr_state->fsm=this;
		    TraceLog(LOG_INFO,"enter state %s ",curr_state->name.c_str());
		    curr_state->enter(userdata);
		    return curr_state;
		  }
        }
        return NULL;
    }
protected:
 std::vector<State*> states;
 State* curr_state;

};

class Menu: public State
{
public:
     Menu():State("menu")  {     };
     void enter(void* userdata)
     {

      isExit=false;
      isEnter=true;

      frame = 1;
     };
     void exit (void* userdata){};
     void update(float dt)
     {
        if (isExit)
        {
          frame+= 1.5f * dt;
          return ;
        }
        if (isEnter)
        {
          frame -= 1.5f * dt;
        return;
        }

        if (IsKeyDown(KEY_TWO))
        {
         //isExitfsm->transition_to("menu");
         isExit=true;
        }

     };
     void render()
     {
        if (isExit)
        {
           DrawRectangle(0,0,screenWidth,screenHeight,{255,255,255,frame*255});
          if (frame>=1.0f)
          {
            fsm->SwitchTo("game");
          }
        }
        if (isEnter)
        {
          DrawRectangle(0,0,screenWidth,screenHeight,{255,255,255,frame*255});
          if (frame<=0.0f)
          {
            isEnter=false;
            frame=0;
          }

        }


     DrawText(name.c_str(), screenWidth/2, screenHeight/2, 10, RED);
     };
private :
bool isExit;
bool isEnter;
float frame;

};

class Game: public State
{
public:

     Game():State("game"){   };
     void enter(void* userdata)
     {

      isExit=false;
      isEnter=true;

      frame = 1;
     };
     void exit (void* userdata){};
     void update(float dt)
     {
        if (isExit)
        {
          frame+= 1.5f * dt;
          return ;
        }
        if (isEnter)
        {
          frame -= 1.5f * dt;
          return;
        }

        if (IsKeyDown(KEY_TWO))
        {
         //isExitfsm->transition_to("menu");
         isExit=true;
        }

     };
     void render()
     {
        if (isExit)
        {
           DrawRectangle(0,0,screenWidth,screenHeight,{255,255,255,frame*255});
          if (frame>=1.0f)
          {
            fsm->SwitchTo("menu");
          }
        }
        if (isEnter)
        {
          DrawRectangle(0,0,screenWidth,screenHeight,{255,255,255,frame*255});
          if (frame<=0.0f)
          {
            isEnter=false;
            frame=0;
          }

        }


     DrawText(name.c_str(), screenWidth/2, screenHeight/2, 10, RED);
     };;
private :
bool isExit;
bool isEnter;
float frame;


};




int main(void)
{
    // Initialization




    //--------------------------------------------------------------------------------------


    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");



    StateMachine* fsm= new StateMachine();
    fsm->addState(new Menu());
    fsm->addState(new Game());
    fsm->SwitchTo("menu");




    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

   // SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    CMD2Model model;
    model.LoadModel("/media/djoker/code/linux/cpp/raylib/rayprojects/raymd2/models/blade/Blade.md2");
  animState_t animation =  model.StartAnimation(STAND);

model.startMD2Anim(0,39,1,9,45);





    Gui_Ini();

     float color[4]={1,0,1,1};

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);          // Update camera

        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        //----------------------------------------------------------------------------------

        static float frame=0.002f;
        static int currentFrame=1;
        static int  nextFrame=2;


        //model.UpdateAnimation(&animation,frame);

        model.animate(GetFrameTime());


        if (IsKeyDown(KEY_W))
        {

          model.startMD2Anim(40,46,1,9,45);




        } else
        if (IsKeyDown(KEY_SPACE))
        {

          model.startMD2Anim(47,53,1,9,45);

        } else
        {
      //model.startMD2Anim(0,39,1,9,45);
        }

        fsm->update(GetFrameTime());

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground({0,0,45,0});
           // ClearBackground(RAYWHITE);

            BeginMode3D(camera);

              //  DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
              //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
              rlPushMatrix();
              rlTranslatef(0,0,0);
             // model.renderLerp(currentFrame,nextFrame,{color[0]*255.0f,color[1]*255.0f,color[2]*255.0f,255});
              rlPopMatrix();

             rlPushMatrix();
              rlTranslatef(0,0,0);
              //model.renderLerp(frame,{color[0]*255.0f,color[1]*255.0f,color[2]*255.0f,255});
            //  model.RenderModel(&animation);
              model.render();
              rlPopMatrix();

                DrawGrid(10, 1.0f);

            EndMode3D();





             Gui_Begin();

             ImGui::Text("Blade animation %d", frame);
    if (ImGui::Button("Run"))
    {
     animation =  model.StartAnimation(RUN);
     model.startMD2Anim(40,46,1,9,200.1f);
    }
    if (ImGui::Button("Idle"))
    {
     animation =  model.StartAnimation(STAND);
     model.startMD2Anim(0,39,1,9,400.5f);
    }
 if (ImGui::Button("Atack"))
    {
     animation =  model.StartAnimation(STAND);
     model.startMD2Anim(46,53,3,9,12.5f);
    }

 if (ImGui::Button("Point"))
    {
     animation =  model.StartAnimation(STAND);
     model.startMD2Anim(currentFrame,nextFrame,1,9,12.5f);
    }


//ImGui::SliderInt("frame", &frame, 0, 197);
ImGui::SliderFloat("frame", &frame, 0.001f, 1.0f);
ImGui::ColorEdit4("Model Color",color);
ImGui::SliderInt("frame", &currentFrame, 0, 176);
ImGui::SliderInt("nex", &nextFrame, 0, 176);
 ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

             Gui_End();


             fsm->render();

            DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 133, BLUE);

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
            DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);

            DrawText(FormatText("Frame %d ",animation.curr_frame), screenWidth-200, 100, 10, RED);
            DrawText(FormatText("Next %d ",animation.next_frame), screenWidth-200, 110, 10, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    delete fsm;
    model.free();
    Gui_Free();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
