#include "rImgui.h"
#include <stdint.h>





ImVec2 operator*(const float f, const ImVec2& v)
{
	return ImVec2{f * v.x, f * v.y};
}

ImVec2 operator+(const ImVec2& a, const ImVec2& b)
{
	return ImVec2{a.x + b.x, a.y + b.y};
}

ImVec2 operator-(const ImVec2& a, const ImVec2& b)
{
	return ImVec2{a.x - b.x, a.y - b.y};
}

bool operator!=(const ImVec2& a, const ImVec2& b)
{
	return a.x != b.x || a.y != b.y;
}

ImVec4 operator*(const float f, const ImVec4& v)
{
	return ImVec4{f * v.x, f * v.y, f * v.z, f * v.w};
}

ImVec4 operator+(const ImVec4& a, const ImVec4& b)
{
	return ImVec4{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}
float min3(float a, float b, float c)
{
	if (a < b && a < c) { return a; }
	return b < c ? b : c;
}

float max3(float a, float b, float c)
{
	if (a > b && a > c) { return a; }
	return b > c ? b : c;
}




	struct Rect
	{
		float MinX, MinY, MaxX, MaxY;
		float MinU, MinV, MaxU, MaxV;

		bool IsOnExtreme(const ImVec2& point) const
		{
			return (point.x == MinX || point.x == MaxX) && (point.y == MinY || point.y == MaxY);
		}

		bool UsesOnlyColor() const
		{
			const ImVec2& whitePixel = ImGui::GetIO().Fonts->TexUvWhitePixel;
			return MinU == MaxU && MinU == whitePixel.x && MinV == MaxV && MaxV == whitePixel.y;
		}


		static Rect CalculateBoundingBox(const ImDrawVert& v0, const ImDrawVert& v1, const ImDrawVert& v2)
		{
			 Rect r;

			 r.MinX =min3(v0.pos.x, v1.pos.x, v2.pos.x );
			 r.MinY =min3(v0.pos.y, v1.pos.y, v2.pos.y );
			 r.MaxX =max3(v0.pos.x, v1.pos.x, v2.pos.x );
			 r.MaxY =max3(v0.pos.y, v1.pos.y, v2.pos.y );

			 r.MinU =min3( v0.uv.x, v1.uv.x, v2.uv.x);
			 r.MinV =min3( v0.uv.y, v1.uv.y, v2.uv.y);
			 r.MaxU=max3 ( v0.uv.x, v1.uv.x, v2.uv.x);
			 r.MaxV=max3 ( v0.uv.y, v1.uv.y, v2.uv.y);
			 return r;
		}
	};






static bool         g_MousePressed[3] = { false, false, false };
static char*        g_ClipboardTextData = NULL;
static bool         g_MouseCanUseGlobalState = false;
Texture2D*  g_FontTexture;
Texture2D*   testeimage;
Image image ;




Color GetColor2(int hexValue)
{
    Color color;

    color.r = (unsigned char)(hexValue >> 0) & 0xFF ;
    color.g = (unsigned char)(hexValue >> 8) & 0xFF ;
    color.b = (unsigned char)(hexValue >> 16) & 0xFF ;
    color.a = (unsigned char)(hexValue >> 24) & 0xFF ;

    return color;
}


 const char* ImGui_Impl_GetClipboardText(void*)
{
    if (g_ClipboardTextData)
        delete(g_ClipboardTextData);
    g_ClipboardTextData =(char*) GetClipboardText();
    return g_ClipboardTextData;
}

 void ImGui_Impl_SetClipboardText(void*, const char* text)
{
    SetClipboardText(text);
}

// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
// If you have multiple SDL events and some of them are not meant to be used by dear imgui, you may need to filter events based on their windowID field.
bool ImGui_Impl_ProcessEvent()
{
    ImGuiIO& io = ImGui::GetIO();







       if (IsKeyDown(KEY_TAB))
      {
          io.KeysDown[KEY_TAB] = true;
      } else io.KeysDown[KEY_TAB] = false;


      if (IsKeyDown(KEY_PAGE_UP))
      {
          io.KeysDown[KEY_PAGE_UP] = true;
      } else io.KeysDown[KEY_PAGE_UP] = false;

      if (IsKeyDown(KEY_PAGE_DOWN))
      {
          io.KeysDown[KEY_PAGE_DOWN] = true;
      } else io.KeysDown[KEY_PAGE_DOWN] = false;



      if (IsKeyDown(KEY_END))
      {
          io.KeysDown[KEY_END] = true;
      } else io.KeysDown[KEY_END] = false;


      if (IsKeyDown(KEY_HOME))
      {
          io.KeysDown[KEY_HOME] = true;
      } else io.KeysDown[KEY_HOME] = false;

      if (IsKeyDown(KEY_DELETE))
      {
          io.KeysDown[KEY_DELETE] = true;
      } else io.KeysDown[KEY_DELETE] = false;

      if (IsKeyDown(KEY_INSERT))
      {
          io.KeysDown[KEY_INSERT] = true;
      } else io.KeysDown[KEY_INSERT] = false;


      if (IsKeyDown(KEY_KP_ENTER))
      {
          io.KeysDown[KEY_KP_ENTER] = true;
      } else io.KeysDown[KEY_KP_ENTER] = false;


      if (IsKeyDown(KEY_ESCAPE))
      {
          io.KeysDown[KEY_ESCAPE] = true;
      } else io.KeysDown[KEY_ESCAPE] = false;


          if (IsKeyDown(KEY_BACKSPACE))
      {
          io.KeysDown[KEY_BACKSPACE] = true;
      } else io.KeysDown[KEY_BACKSPACE] = false;

      if (IsKeyDown(KEY_ENTER))
      {
          io.KeysDown[KEY_ENTER] = true;
      } else io.KeysDown[KEY_ENTER] = false;

      if (IsKeyDown(KEY_DELETE))
      {
          io.KeysDown[KEY_DELETE] = true;
      } else io.KeysDown[KEY_DELETE] = false;


       if (IsKeyDown(KEY_LEFT))
      {
      io.KeysDown[KEY_LEFT] = true;
      } else io.KeysDown[KEY_LEFT] = false;
      if (IsKeyDown(KEY_RIGHT))
      {
      io.KeysDown[KEY_RIGHT] = true;
      } else io.KeysDown[KEY_RIGHT] = false;


      if (IsKeyDown(KEY_UP))
      {
      io.KeysDown[KEY_UP] = true;
      } else io.KeysDown[KEY_UP] = false;

      if (IsKeyDown(KEY_DOWN))
      {
      io.KeysDown[KEY_DOWN] = true;
      } else io.KeysDown[KEY_DOWN] = false;



       int key =GetKeyPressed();
       if (key!=0)
       {
         int byteLength = 0;
         const char *textUtf8 = CodepointToUtf8(key, &byteLength);
         io.AddInputCharactersUTF8(textUtf8);

       }

       if (IsKeyDown(key))
      {
          io.WantCaptureKeyboard=true;
          io.KeysDown[key] = true;
          io.KeySuper = false;
      } else{
        io.KeysDown[key] = false;
        io.WantCaptureKeyboard=false;
      }

    return false;
}


bool ImGui_Impl_CreateFontsTexture()
{
    // Build texture atlas
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bit (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.
    g_FontTexture = new Texture();
    g_FontTexture->width = width;
    g_FontTexture->height = height;
    g_FontTexture->mipmaps = 1;
    g_FontTexture->format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    g_FontTexture->id= rlLoadTexture(pixels,width,height,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,1);
    io.Fonts->TexID = (void*)g_FontTexture;
    return true;
}

 bool ImGui_Impl_Init()
{


    // Setup backend capabilities flags
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;       // We can honor GetMouseCursor() values (optional)
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;        // We can honor io.WantSetMousePos requests (optional, rarely used)
    io.BackendPlatformName = "imgui_impl_sdl";

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = KEY_RIGHT;

    io.KeyMap[ImGuiKey_UpArrow] = KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = KEY_DOWN;

    io.KeyMap[ImGuiKey_PageUp] = KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = KEY_PAGE_DOWN;

    io.KeyMap[ImGuiKey_Home] = KEY_HOME;
    io.KeyMap[ImGuiKey_End] = KEY_END;

    io.KeyMap[ImGuiKey_Insert] = KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = KEY_DELETE;

    io.KeyMap[ImGuiKey_Backspace] = KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = KEY_A;
    io.KeyMap[ImGuiKey_C] = KEY_C;
    io.KeyMap[ImGuiKey_V] = KEY_V;
    io.KeyMap[ImGuiKey_X] = KEY_X;
    io.KeyMap[ImGuiKey_Y] = KEY_Y;
    io.KeyMap[ImGuiKey_Z] = KEY_Z;

    io.SetClipboardTextFn = ImGui_Impl_SetClipboardText;
    io.GetClipboardTextFn = ImGui_Impl_GetClipboardText;
    io.ClipboardUserData = NULL;

    // Load mouse cursors
/*    g_MouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    g_MouseCursors[ImGuiMouseCursor_TextInput] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    g_MouseCursors[ImGuiMouseCursor_ResizeAll] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    g_MouseCursors[ImGuiMouseCursor_ResizeNS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    g_MouseCursors[ImGuiMouseCursor_ResizeEW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
    g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    g_MouseCursors[ImGuiMouseCursor_Hand] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    g_MouseCursors[ImGuiMouseCursor_NotAllowed] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);*/

    // Check and store if we are on Wayland
    g_MouseCanUseGlobalState =true;// strncmp(SDL_GetCurrentVideoDriver(), "wayland", 7) != 0;

    ImGui_Impl_CreateFontsTexture();

return true;
}



void ImGui_Impl_Shutdown()
{

    // Destroy last known clipboard data
    if (g_ClipboardTextData)
        delete(g_ClipboardTextData);
    g_ClipboardTextData = NULL;

    // Destroy SDL mouse cursors
  //  for (ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT; cursor_n++)
//        SDL_FreeCursor(g_MouseCursors[cursor_n]);
//    memset(g_MouseCursors, 0, sizeof(g_MouseCursors));
}

 void ImGui_Impl_UpdateMousePosAndButtons()
{
    ImGuiIO& io = ImGui::GetIO();


           float delta = GetMouseWheelMove();
            if (delta > 0) io.MouseWheelH += 1;
            if (delta < 0) io.MouseWheelH -= 1;
            if (delta > 0) io.MouseWheel += 1;
            if (delta < 0) io.MouseWheel -= 1;


    // Set OS mouse position if requested (rarely used, only when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
    if (io.WantSetMousePos)
        //SDL_WarpMouseInWindow(GetWindowHandle(), (int)io.MousePos.x, (int)io.MousePos.y);
        SetMousePosition((int)io.MousePos.x, (int)io.MousePos.y);
    else
        io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);

    int mx, my;
    //Uint32 mouse_buttons = SDL_GetMouseState(&mx, &my);

    Vector2 mouse = GetMousePosition();

    mx=(int)mouse.x;
    my=(int)mouse.y;



    io.MouseDown[0] = g_MousePressed[0] || IsMouseButtonDown(0);
    io.MouseDown[1] = g_MousePressed[1] || IsMouseButtonDown(1);
    io.MouseDown[2] = g_MousePressed[2] || IsMouseButtonDown(2);
    g_MousePressed[0] = g_MousePressed[1] = g_MousePressed[2] = false;
    io.MousePos = ImVec2((float)mx, (float)my);


    // SDL_CaptureMouse() let the OS know e.g. that our imgui drag outside the SDL window boundaries shouldn't e.g. trigger the OS window resize cursor.
    // The function is only supported from SDL 2.0.4 (released Jan 2016)
    bool any_mouse_button_down = ImGui::IsAnyMouseDown();
//    SDL_CaptureMouse(any_mouse_button_down ? SDL_TRUE : SDL_FALSE);




}

 void ImGui_Impl_UpdateMouseCursor()
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
        return;

    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
    if (io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None)
    {
     HideCursor();
    }
    else
    {
        // Show OS mouse cursor
      ////  SDL_SetCursor(g_MouseCursors[imgui_cursor] ? g_MouseCursors[imgui_cursor] : g_MouseCursors[ImGuiMouseCursor_Arrow]);

      ShowCursor();
    }
}


void ImGui_Impl_NewFrame()
{
    ImGuiIO& io = ImGui::GetIO();
    IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer backend. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

    // Setup display size (every frame to accommodate for window resizing)
    int w, h;
    int display_w, display_h;

    w=GetScreenWidth();
    h=GetScreenHeight();



    if (IsWindowMinimized())
    {
        w = h = 0;
    } else{

    }



    display_w=w;//GetMonitorWidth(0);
    display_h=h;//GetMonitorHeight(0);


    io.DisplaySize = ImVec2((float)w, (float)h);
    if (w > 0 && h > 0)
        io.DisplayFramebufferScale = ImVec2((float)display_w / w, (float)display_h / h);

   io.DeltaTime=GetFrameTime();


    ImGui_Impl_UpdateMousePosAndButtons();
    ImGui_Impl_UpdateMouseCursor();
    ImGui_Impl_ProcessEvent();
    ImGui::NewFrame();
}



void DrawUniformColorTriangle(const ImDrawVert& v0, const ImDrawVert& v1, const ImDrawVert& v2)
{



rlBegin(RL_TRIANGLES);




                    Color colora= GetColor2(v0.col);
                    Color colorb= GetColor2(v1.col);
                    Color colorc= GetColor2(v2.col);


                   rlVertex2f(v0.pos.x,v0.pos.y);
             //      rlTexCoord2f(v0.uv.x,v0.uv.y);
                   rlColor4ub(colora.r,colora.g,colora.b,colora.a);

                   rlVertex2f(v1.pos.x,v1.pos.y);
              //     rlTexCoord2f(v1.uv.x,v1.uv.y);
                   rlColor4ub(colorb.r,colorb.g,colorb.b,colorb.a);

                   rlVertex2f(v2.pos.x,v2.pos.y);
               //    rlTexCoord2f(v2.uv.x,v2.uv.y);
                   rlColor4ub(colorc.r,colorc.g,colorc.b,colorc.a);




//


               rlEnd();



}



void render_primitive(const Rect& bounding, Texture* texture, const Color& color, bool doHorizontalFlip, bool doVerticalFlip)
{

int textureWidth=texture->width;
int textureHeight=texture->height;

Rectangle destination = {
			(bounding.MinX),
			(bounding.MinY),
			(bounding.MaxX - bounding.MinX),
			(bounding.MaxY - bounding.MinY)
		};


Rectangle source = {
				(bounding.MinU * textureWidth),
				(bounding.MinV * textureHeight),
				((bounding.MaxU - bounding.MinU) * textureWidth),
				((bounding.MaxV - bounding.MinV) * textureHeight)



};

	    if (bounding.UsesOnlyColor())
		{


             DrawTexturePro(*texture,source,destination,{0,0},0,color);
		}
		else
		{


        DrawTexturePro(*texture,source,destination,{0,0},0,color);
}

}


void BeginScissor(int x, int y, int width, int height)
{
    rlDrawRenderBatchActive(); // Force drawing elements

    rlEnableScissorTest();
   // rlScissor(x, GetScreenHeight() - (y + height), width, height);
    rlScissor(x, y, width, height);
}

// End scissor mode
void EndScissor(void)
{
    rlDrawRenderBatchActive(); // Force drawing elements
    rlDisableScissorTest();
}

void ImGui_Impl_RenderDrawData(ImDrawData* drawData)
{

rlDisableDepthTest();
rlDisableBackfaceCulling();


    const float width_points = ImGui::GetIO().DisplaySize.x;
	const float height_points = ImGui::GetIO().DisplaySize.y;
//	const ImVec2 scale{width_pixels / width_points, height_pixels / height_points};
	//PaintTarget target{pixels, width_pixels, height_pixels, scale};
//	const ImDrawData* draw_data = ImGui::GetDrawData();


    int fb_width = (int)(drawData->DisplaySize.x * drawData->FramebufferScale.x);
    int fb_height = (int)(drawData->DisplaySize.y * drawData->FramebufferScale.y);
    if (fb_width == 0 || fb_height == 0)
        return;


    ImVec2 clip_off = drawData->DisplayPos;         // (0,0) unless using multi-viewports
    ImVec2 clip_scale = drawData->FramebufferScale; // (1,1) unless using retina display which are often (2,2)



		ImGuiIO& io = ImGui::GetIO();

		for (int n = 0; n < drawData->CmdListsCount; n++)
		{
			auto commandList = drawData->CmdLists[n];
			auto vertexBuffer = commandList->VtxBuffer;
			auto indexBuffer = commandList->IdxBuffer.Data;

			for (int cmd_i = 0; cmd_i < commandList->CmdBuffer.Size; cmd_i++)
			{
				const ImDrawCmd* drawCommand = &commandList->CmdBuffer[cmd_i];



				if (drawCommand->UserCallback)
				{
					drawCommand->UserCallback(commandList, drawCommand);
				}
				else
				{
					const bool isWrappedTexture = drawCommand->TextureId == io.Fonts->TexID;
				//	rlEnableTexture((unsigned int)(intptr_t)drawCommand->TextureId);

  			   ImVec4 clip_rect;
                clip_rect.x = (drawCommand->ClipRect.x - clip_off.x) * clip_scale.x;
                clip_rect.y = (drawCommand->ClipRect.y - clip_off.y) * clip_scale.y;
                clip_rect.z = (drawCommand->ClipRect.z - clip_off.x) * clip_scale.x;
                clip_rect.w = (drawCommand->ClipRect.w - clip_off.y) * clip_scale.y;


    		     if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f)
                {

                BeginScissor((int)clip_rect.x, (int)(fb_height - clip_rect.w), (int)(clip_rect.z - clip_rect.x), (int)(clip_rect.w - clip_rect.y));
             //   BeginScissorMode((int)clip_rect.x, (int)(clip_rect.y), (int)(clip_rect.z), (int)( clip_rect.w));


					// Loops over triangles.
					for (unsigned int i = 0; i + 3 <= drawCommand->ElemCount; i += 3)
					{
						const ImDrawVert& v0 = vertexBuffer[indexBuffer[i + 0]];
						const ImDrawVert& v1 = vertexBuffer[indexBuffer[i + 1]];
						const ImDrawVert& v2 = vertexBuffer[indexBuffer[i + 2]];

						const Rect& bounding = Rect::CalculateBoundingBox(v0, v1, v2);

						const bool isTriangleUniformColor = v0.col == v1.col && v1.col == v2.col;
						const bool doesTriangleUseOnlyColor = bounding.UsesOnlyColor();

						// Actually, since we render a whole bunch of rectangles, we try to first detect those, and render them more efficiently.
						// How are rectangles detected? It's actually pretty simple: If all 6 vertices lie on the extremes of the bounding box,
						// it's a rectangle.
						if (i + 6 <= drawCommand->ElemCount)
						{
							const ImDrawVert& v3 = vertexBuffer[indexBuffer[i + 3]];
							const ImDrawVert& v4 = vertexBuffer[indexBuffer[i + 4]];
							const ImDrawVert& v5 = vertexBuffer[indexBuffer[i + 5]];

							const bool isUniformColor = isTriangleUniformColor && v2.col == v3.col && v3.col == v4.col && v4.col == v5.col;
	                     if (isUniformColor
							&& bounding.IsOnExtreme(v0.pos)
							&& bounding.IsOnExtreme(v1.pos)
							&& bounding.IsOnExtreme(v2.pos)
							&& bounding.IsOnExtreme(v3.pos)
							&& bounding.IsOnExtreme(v4.pos)
							&& bounding.IsOnExtreme(v5.pos)
							)
							{
								// ImGui gives the triangles in a nice order: the first vertex happens to be the topleft corner of our rectangle.
								// We need to check for the orientation of the texture, as I believe in theory ImGui could feed us a flipped texture,
								// so that the larger texture coordinates are at topleft instead of bottomright.
								// We don't consider equal texture coordinates to require a flip, as then the rectangle is mostlikely simply a colored rectangle.
								const bool doHorizontalFlip = v2.uv.x < v0.uv.x;
								const bool doVerticalFlip = v2.uv.x < v0.uv.x;





								//printf(" %i %i \n",doHorizontalFlip,doVerticalFlip);
                                  Color color= GetColor2(v0.col);
								if (isWrappedTexture)
								{


									render_primitive(bounding, static_cast<Texture*>(drawCommand->TextureId),color, false,false);
//									drawTriangle(v0, v1, v2,v3, v4, v5);

								}
								else
								{
								//printf(" no texture \n");
									render_primitive(bounding, static_cast<Texture*>(drawCommand->TextureId),color, doHorizontalFlip, doVerticalFlip);
								//	DrawRectangle(bounding, static_cast<SDL_Texture*>(drawCommand->TextureId), Color(v0.col), doHorizontalFlip, doVerticalFlip);
								}

								i += 3;  // Additional increment to account for the extra 3 vertices we consumed.
								continue;
							}
						}


						if (isTriangleUniformColor)
						{
							DrawUniformColorTriangle(v0, v1, v2);
							}
						else
						{

							DrawUniformColorTriangle(v0, v1, v2);
						}
					}//lop
					EndScissor();
                  } //clip
				}// else

				indexBuffer += drawCommand->ElemCount;
			}
		}






}


void Gui_Ini()
{

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  //  ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    //ImGui::StyleColorsLight();
     ImGui_Impl_Init();


}
void Gui_Begin()
{
ImGui_Impl_NewFrame();
}

void Gui_End()
{
ImGui::Render();
ImGui_Impl_RenderDrawData(ImGui::GetDrawData());

}


void Gui_Free()
{
        ImGui_Impl_Shutdown();
        ImGui::DestroyContext();

}

