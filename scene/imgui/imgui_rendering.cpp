#include "imgui_rendering.h"


ImGuiRendering::ImGuiRendering(/* args */)
{
    new_frame_rendering=false;
    // set_process_input(true);
	// set_process(true);
	set_anchors_and_offsets_preset(PRESET_WIDE,PRESET_MODE_KEEP_SIZE,0);
    set_as_top_level(true);
    set_position(Vector2(0, 0));	
    // Vector2i control_window_size = DisplayServer::get_singleton()->window_get_size();
	// set_position(Vector2(0, 0));
	// set_size(Vector2(control_window_size.x,control_window_size.y));
	// set_focus_mode(FOCUS_ALL);

    this->rendering_server = RenderingServer::get_singleton();

    context = ImGui::CreateContext();
    // ImGui::SetCurrentContext(context);

    ImGuiIO &io = ImGui::GetIO();
    io.BackendFlags = 0;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#ifdef JAVASCRIPT_ENABLED
    io.IniFilename = NULL; 
#else
    // io.IniFilename=EditorPaths::get_singleton()->get_config_dir().plus_file("imgui.ini").ascii().get_data();
    // print_line(io.IniFilename);
#endif
    io.MouseDrawCursor = false;
    Vector2i window_size = DisplayServer::get_singleton()->window_get_size();
    io.DisplaySize = ImVec2(window_size.x, window_size.y);
    io.Fonts->AddFontDefault();
    int width, height, bytesPerPixel;
    unsigned char *pixels = NULL;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &bytesPerPixel);
    Vector<uint8_t> textureDataRaw;
    for (int i = 0; i < width * height * bytesPerPixel; i++) 
    {
        textureDataRaw.push_back(pixels[i]);
    }
    Image img(width, height, false, Image::Format::FORMAT_RGBA8, textureDataRaw);
    font_imgtex.create_from_image(img.duplicate());
    io.Fonts->SetTexID(&font_imgtex);

	io.KeyMap[(int)ImGuiKey_Tab] = FixKey(Key::TAB);
	io.KeyMap[(int)ImGuiKey_LeftArrow] = FixKey(Key::LEFT);
	io.KeyMap[(int)ImGuiKey_RightArrow] = FixKey(Key::RIGHT);
	io.KeyMap[(int)ImGuiKey_UpArrow] = FixKey(Key::UP);
	io.KeyMap[(int)ImGuiKey_DownArrow] = FixKey(Key::DOWN);
	io.KeyMap[(int)ImGuiKey_PageUp] = FixKey(Key::PAGEUP);
	io.KeyMap[(int)ImGuiKey_PageDown] = FixKey(Key::PAGEDOWN);
	io.KeyMap[(int)ImGuiKey_Home] = FixKey(Key::HOME);
	io.KeyMap[(int)ImGuiKey_End] = FixKey(Key::END);
	io.KeyMap[(int)ImGuiKey_Insert] = FixKey(Key::INSERT);
	io.KeyMap[(int)ImGuiKey_Delete] = FixKey(Key::KEY_DELETE);
	io.KeyMap[(int)ImGuiKey_Backspace] = FixKey(Key::BACKSPACE);
	io.KeyMap[(int)ImGuiKey_Space] = FixKey(Key::SPACE);
	io.KeyMap[(int)ImGuiKey_Enter] = FixKey(Key::ENTER);
	io.KeyMap[(int)ImGuiKey_Escape] = FixKey(Key::ESCAPE);
	io.KeyMap[(int)ImGuiKey_KeyPadEnter] = FixKey(Key::KP_ENTER);
	io.KeyMap[(int)ImGuiKey_A] = FixKey(Key::A);
	io.KeyMap[(int)ImGuiKey_C] = FixKey(Key::C);
	io.KeyMap[(int)ImGuiKey_V] = FixKey(Key::V);
	io.KeyMap[(int)ImGuiKey_X] = FixKey(Key::X);
	io.KeyMap[(int)ImGuiKey_Y] = FixKey(Key::Y);
	io.KeyMap[(int)ImGuiKey_Z] = FixKey(Key::Z);
		
	limit = 1024;
	strings.push_back(memnew_arr(char, limit));
	pos_strings.push_back(0);
	curr_pos = 0;
}

ImGuiRendering::~ImGuiRendering()
{
    for (int i = 0; i < mesh_dict.size(); i++)
	{
		for (int j = 0; j < mesh_dict[i].size(); j++) 
		{
			Vector<ArrayMesh *> &dict = const_cast<Vector<ArrayMesh *> &>(mesh_dict[i]);
			memdelete(dict[j]);
		}
	}
	for (size_t i = 0; i < strings.size(); i++)
		memdelete_arr(strings[i]);
	strings.clear();
}

void ImGuiRendering::NewFrame()
{
    if (new_frame_rendering)
    {
        return;
    }
    
    Prepare();
    ImGui::NewFrame();
    //OnImGui
    for (int i = 0; i < get_child_count(); i++) 
    {
        ImGuiControl *imgui_control = Object::cast_to<ImGuiControl>(get_child(i));
        if (!imgui_control) 
        {
            continue;
        }
        imgui_control->OnImGui();
    }
    new_frame_rendering=true;
}

void ImGuiRendering::EndFrame()
{
    if (!new_frame_rendering)
    {
        return;
    }

    ImGui::EndFrame();
    Render();
    curr_pos = 0;
	
	for (auto it = pos_strings.begin(); it !=pos_strings.end(); it++)
	{
		*it = 0;
	}
    
	for (auto it = strings.begin(); it !=strings.end(); it++)
	{
		for (uint32_t i = 0; i < limit; i++)
			*it[i] = '\0';
	}

    new_frame_rendering=false;
}

void ImGuiRendering::ReceiveInput(const Ref<InputEvent> &p_event)
{
    bool consumed = false; 
	ImGuiIO &io = ImGui::GetIO();

	Ref<InputEventKey> keyevt = p_event;

	if (keyevt != nullptr && keyevt->is_pressed() /* Pressed */) 
    {
		unsigned int code = (unsigned int)keyevt->get_unicode();

		if (code < 256) {
			io.AddInputCharacter(code);
		} else {
			code = FixKey((Key)code);
			io.KeysDown[code] = keyevt->is_pressed();
		}

		consumed = io.WantCaptureKeyboard; 
	 
	}

	Ref<InputEventMouseMotion> mm = p_event;

	if (mm.is_valid()) {
		Vector2 godot_mouse_pos = mm->get_position();

		ImVec2 mousePos(godot_mouse_pos.x, godot_mouse_pos.y);
		consumed = io.WantCaptureMouse; 
		io.MousePos = mousePos;
	}

	Ref<InputEventMouseButton> mp = p_event;

	if (mp.is_valid()) {

		if (mp->is_pressed()) {
			int _index = (int)mp->get_button_index();

			io.MouseDown[0] = _index == 1 ? true : false;
			io.MouseDown[1] = _index == 2 ? true : false;
			mouse_wheel = - (_index == 5) + (_index == 4);
		 
		} else {
			io.MouseDown[0] = false;
			io.MouseDown[1] = false;

		}

		consumed = io.WantCaptureMouse;
	}

	if (consumed)
	{
		get_tree()->get_root()->set_input_as_handled();
	}
}

void ImGuiRendering::Prepare()
{
    //io.DisplaySize
    Size2 size = get_size();
    ImGui::GetIO().DisplaySize = ImVec2(size.x,size.y);
    //io.Scale
}

void ImGuiRendering::Render()
{
    ImGui::Render();
    ImDrawData *draw_dat = ImGui::GetDrawData();

	// validate data
	if (!draw_dat->Valid) 
    {
		print_error("IMGUI: DRAW DATA NOT VALID");
		return;
	}

    ImGuiIO &io = ImGui::GetIO();
	Input *input = Input::get_singleton();
	
    //process imgui
	// Because reasons
	io.MouseWheel = mouse_wheel;
	mouse_wheel = 0;
	io.KeysDown[FixKey(Key::TAB)] = input->is_key_pressed(Key::TAB);
	io.KeysDown[FixKey(Key::LEFT)] = input->is_key_pressed(Key::LEFT);
	io.KeysDown[FixKey(Key::RIGHT)] = input->is_key_pressed(Key::RIGHT);
	io.KeysDown[FixKey(Key::UP)] = input->is_key_pressed(Key::UP);
	io.KeysDown[FixKey(Key::DOWN)] = input->is_key_pressed(Key::DOWN);
	io.KeysDown[FixKey(Key::PAGEUP)] = input->is_key_pressed(Key::PAGEUP);
	io.KeysDown[FixKey(Key::PAGEDOWN)] = input->is_key_pressed(Key::PAGEDOWN);
	io.KeysDown[FixKey(Key::HOME)] = input->is_key_pressed(Key::HOME);
	io.KeysDown[FixKey(Key::END)] = input->is_key_pressed(Key::END);
	io.KeysDown[FixKey(Key::INSERT)] = input->is_key_pressed(Key::INSERT);
	io.KeysDown[FixKey(Key::KEY_DELETE)] = input->is_key_pressed(Key::KEY_DELETE);
	io.KeysDown[FixKey(Key::BACKSPACE)] = input->is_key_pressed(Key::BACKSPACE);
	io.KeysDown[FixKey(Key::SPACE)] = input->is_key_pressed(Key::SPACE);
	io.KeysDown[FixKey(Key::ENTER)] = input->is_key_pressed(Key::ENTER);
	io.KeysDown[FixKey(Key::ESCAPE)] = input->is_key_pressed(Key::ESCAPE);
	io.KeysDown[FixKey(Key::KP_ENTER)] = input->is_key_pressed(Key::KP_ENTER);


	if (get_process_delta_time() < 1e-10) 
    {
		io.DeltaTime = 0.0016;
	} 
    else 
    {
		io.DeltaTime = get_process_delta_time(); // Sometimes it's too fast and ImGui freaks out
	}

    //imgui draw
    Draw();
}
    
void ImGuiRendering::Draw()
{
    ImDrawData *drawData = ImGui::GetDrawData();
	
	for (int i = 0; i < mesh_dict.size(); i++) 
    {
		for (int j = 0; j < mesh_dict[i].size(); j++) 
        {
			mesh_dict[i][j]->clear_surfaces();
		}
	}

	drawData->ScaleClipRects(ImGui::GetIO().DisplayFramebufferScale);
	
	for (int i = child_dict.size(); i < drawData->CmdListsCount; i++)
    { 
		child_dict.push_back(Vector<RID>());
		mesh_dict.push_back(Vector<ArrayMesh *>());

		 RID item_parent = rendering_server->canvas_item_create();
		 rendering_server->canvas_item_set_parent(item_parent, get_canvas_item());
		 child_dict_parent.push_back(item_parent);
	}


	for (int i = 0; i < drawData->CmdListsCount; i++) 
    {  
		// Per triangle data
		Vector<Vector2> vertices;
		Vector<Color> colors;
		Vector<Vector2> uvs;

		// Per drawcall data
		Vector<int> indices;

		ImDrawList *cmdList = drawData->CmdLists[i];
		// cmdList->_TextureIdStack.size()>0
		for (int j = 0; j < cmdList->VtxBuffer.size(); j++) 
        {
			// vertex pos
			ImVec2 imVert = cmdList->VtxBuffer[j].pos;
			Vector2 godotVert(imVert.x, imVert.y);

			// vertex colour
			ImU32 im_col = cmdList->VtxBuffer[j].col;
			// Bit shift magic, ImGui thinks colours are 32bit integers 0-255, Godot think they are 8 bit floats 0-1
			ImVec4 im_col_v4 = ImGui::ColorConvertU32ToFloat4(im_col);
			Color godotCol(im_col_v4.x, im_col_v4.y, im_col_v4.z, im_col_v4.w);
			// Vertex uv
			ImVec2 imUv = cmdList->VtxBuffer[j].uv;
			Vector2 godotUv(imUv.x, imUv.y);

			uvs.push_back(godotUv);
			vertices.push_back(godotVert);
			colors.push_back(godotCol);
		}

		for (int j = 0; j < cmdList->CmdBuffer.size(); j++) 
        {
			for (int k = child_dict[i].size(); k < cmdList->CmdBuffer.size(); k++) {

				RID child = rendering_server->canvas_item_create();
				const_cast<Vector<RID> &>(child_dict[i]).push_back(child);
				const_cast<Vector<ArrayMesh *> &>(mesh_dict[i]).push_back(memnew(ArrayMesh));
				rendering_server->canvas_item_set_parent(child_dict[i][k], child_dict_parent[i]);
			}
		

			ImDrawCmd *cmd = &cmdList->CmdBuffer[j];
			//ImVec2 pos = drawData->DisplayPos; will be a thing when we have more viewports
			Rect2 clippingRect = Rect2(cmdList->CmdBuffer[j].ClipRect.x,
			cmdList->CmdBuffer[j].ClipRect.y,
			cmdList->CmdBuffer[j].ClipRect.z - cmdList->CmdBuffer[j].ClipRect.x,
			cmdList->CmdBuffer[j].ClipRect.w - cmdList->CmdBuffer[j].ClipRect.y);
			
			Texture2D* texture_rid = cmdList->CmdBuffer[j].GetTexID();
			// if(texture_rid==nullptr|| texture_rid->get_rid().is_null())
			// {
			// 	texture_rid=&imgtex;
			// }

			rendering_server->canvas_item_clear(child_dict[i][j]);
			rendering_server->canvas_item_set_custom_rect(child_dict[i][j], true, clippingRect);
			rendering_server->canvas_item_set_clip(child_dict[i][j], true);
	
			for (unsigned int k = cmd->IdxOffset; k < cmd->ElemCount + cmd->IdxOffset; k++) 
            {
				indices.push_back(cmdList->IdxBuffer[k]);
			}

			Array renderData;
			renderData.resize(ArrayMesh::ARRAY_MAX);
			renderData[(int)ArrayMesh::ArrayType::ARRAY_VERTEX] = vertices;
			renderData[(int)ArrayMesh::ArrayType::ARRAY_INDEX] = indices;
			renderData[(int)ArrayMesh::ArrayType::ARRAY_COLOR] = colors;
			renderData[(int)ArrayMesh::ArrayType::ARRAY_TEX_UV] = uvs;
			 
			mesh_dict[i][j]->add_surface_from_arrays(Mesh::PrimitiveType::PRIMITIVE_TRIANGLES, renderData);
		
			rendering_server->canvas_item_add_mesh(child_dict[i][j], mesh_dict[i][j]->get_rid(), Transform2D(), Color(1,1,1,1),texture_rid->get_rid());
			indices.clear();
		}

	}
}
    
unsigned int ImGuiRendering::FixKey(Key kc)
{
    if ((int)kc < 256)
		return (int)kc;
	else
		return 256 + ((int)kc & 0xFF);
}


