/**
 * @file        test_water_model.cpp
 * 
 * @brief       Sample application for testing the water model.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-28
 */
#include <pwd/pwd.hpp>
#include <rendering/rendering.hpp>
#include <ui/ui.hpp>
#include <io/io.hpp>


void TimerStart();
double TimerStop();

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "This executable needs an input graph file." << std::endl;
        exit(-1);
    }

    // Load the graph from file
    std::string GraphFile = argv[1];
    pwd::Graph* Graph;
    try
    {
        Graph = new pwd::Graph(GraphFile);
        Assert(Graph->Root()->Head().norm() < 1e-16);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(-1);
    }


    // Create the cylinder mesh
    io::Mesh Mesh("../sample-data/cylinder.obj");

    // Create the window and the 3D model
    render::Window Window("Test Water Model");
    render::Model Model(Mesh);

    // Create the camera
    render::Camera Camera;
    Camera.GetTransform().Translate(glm::vec3(0.0f, 0.0f, -5.0f));
    Camera.GetTransform().LookAt(glm::vec3(0.0f));

    // Create the transform for the graph
    render::Transform GraphTrans;
    // Graph is usually exported using blender coordinate system
    GraphTrans.RotateAround(glm::vec3(1, 0, 0), -90);
    GraphTrans.RotateAround(glm::vec3(0, 1, 0), 180);
    GraphTrans.SetScale(1e-1f);

    // Create the UI manager with the proper components
    ui::UIManager UIManager(&Window);
    ui::CameraProperties CamProps("Camera Settings", 0, 0, 430, 130);
    ui::ModelProperties ModProps("Graph Properties", &GraphTrans, 0, 130, 430, 360);
    ui::LightProperties LightProps("Light Properties", 0, 130 + 360, 430, 217);
    ui::ColormapProperties CMapProps("Colormap", 0, 130 + 360 + 217, 430, 400);
    ui::WaterModelProperties WModProp("Water Model", Window.Width() - 430, 0, 430, 220);
    UIManager.AttachComponent(ModProps);
    UIManager.AttachComponent(LightProps);
    UIManager.AttachComponent(CamProps);
    UIManager.AttachComponent(CMapProps);
    UIManager.AttachComponent(WModProp);


    pwd::WaterModel WaterModel(Graph, WModProp.GetLossRate(), WModProp.GetInitialWater());
    // WaterModel.Build();
    double TotWater0 = WaterModel.Water0().maxCoeff();
    size_t NumFrames = 0;
    double TotTime = 0.0;
    while (!Window.ShouldClose())
    {
        Window.PollEvents();
        Window.RegisterInput();

        // Quit app
        if (Window.KeyDown(GLFW_KEY_ESCAPE)) 
            Window.Close();

        TimerStart();
        WaterModel.Evaluate(WModProp.GetTime());
        if (!WModProp.IsPaused())
        {
            TotTime += TimerStop();
            NumFrames += 1;
        }
        if (WModProp.IsReset())
        {
            WaterModel.Initialize(WModProp.GetLossRate(), WModProp.GetInitialWater());
            // WaterModel.Build();
        }
        
        if (Window.KeyPressed(GLFW_KEY_SPACE))
            WModProp.Pause();

        // Camera aspect ratio to match window
        Camera.SetAspectRatio(Window.Width(), Window.Height());

        // Camera motion
        Camera.SetMovementSpeed(CamProps.GetMoveSpeed());
        Camera.SetRotationSpeed(CamProps.GetRotSpeed());
        Camera.SetSprintMultiplier(CamProps.GetSpeedMultiplier());
        // Movement
        glm::vec3 CamMove(0.0f);
        if (Window.KeyDown(GLFW_KEY_W)) CamMove.z += 1;
        else if (Window.KeyDown(GLFW_KEY_S)) CamMove.z -= 1;
        if (Window.KeyDown(GLFW_KEY_D)) CamMove.x += 1;
        else if (Window.KeyDown(GLFW_KEY_A)) CamMove.x -= 1;
        if (Window.KeyDown(GLFW_KEY_E)) CamMove.y += 1;
        else if (Window.KeyDown(GLFW_KEY_Q)) CamMove.y -= 1;
        Camera.RelativeMovement(CamMove, Window.KeyDown(GLFW_KEY_LEFT_SHIFT), Window.DeltaTime());
        // Rotation
        if (Window.ButtonDown(GLFW_MOUSE_BUTTON_2))
        {
            glm::dvec2 Rot = Window.CursorDelta();
            Camera.YawRotate(Rot.x, Window.KeyDown(GLFW_KEY_LEFT_SHIFT), Window.DeltaTime());
            Camera.PitchRotate(Rot.y, Window.KeyDown(GLFW_KEY_LEFT_SHIFT), Window.DeltaTime());
        }

        // Model rotation
        if (Window.ButtonDown(GLFW_MOUSE_BUTTON_1) && !Window.ButtonDown(GLFW_MOUSE_BUTTON_2))
        {
            glm::dvec2 Rot = Window.CursorDelta();
            GraphTrans.RotateAround(glm::vec3(0.0f, 1.0f, 0.0f), Rot.x);
            GraphTrans.RotateAround(GraphTrans.Right(), -Rot.y);
        }

        


        UIManager.Draw();
        Window.ClearBackground();

        // Render graph
        for (int i = 0; i < Graph->NumNodes(); ++i)
        {
            const pwd::Node* N = Graph->GetNode(i);
            Assert(Graph->GetNodeID(N) == i);
            
            Eigen::Vector3d Pos = 0.5 * (N->Head() + N->Tail());
            glm::vec3 GLPos(Pos.x(), Pos.y(), Pos.z());
            
            Eigen::Quaterniond Rot = N->Rotation();
            glm::quat GLRot(Rot.w(), Rot.x(), Rot.y(), Rot.z());

            glm::vec3 GLScale(N->Radius(), N->Length(), N->Radius());
            
            Model.Transform().SetPosition(GLPos);
            Model.Transform().SetRotation(GLRot);
            Model.Transform().SetScale(GLScale);

            render::Material Mat = ModProps.GetMaterial();
            float Val = WaterModel.Water(i) / TotWater0;
            Mat.Ambient = CMapProps.GetColor(Val);

            Model.Shader().Use();
            Model.Shader().SendMaterial("Material", Mat);
            Model.Shader().SendLight("Light", LightProps.GetLight());
            Model.Draw(Camera, GraphTrans);
        }
        
        Window.SwapBuffers();
    }

    std::cout << "Average time per frame is " << (TotTime / NumFrames) << " ms." << std::endl;

    return 0;
}





std::chrono::system_clock::time_point Start;
void TimerStart()
{
    Start = std::chrono::system_clock::now();
}
double TimerStop()
{
    std::chrono::system_clock::time_point End;
    End = std::chrono::system_clock::now();
    std::chrono::system_clock::duration ETA = End - Start;
    size_t us = std::chrono::duration_cast<std::chrono::microseconds>(ETA).count();
    return 1.0e-3 * us;
}