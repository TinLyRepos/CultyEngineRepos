#include "Precompiled.h"
#include "ComponentCameraFPS.h"

#include "GameObject.h"
#include "ComponentCamera.h"

#include "SaveUtil.h"

using namespace CultyEngine;
using namespace CultyEngine::Graphics;
using namespace CultyEngine::Input;

void ComponentCameraFPS::Initialize()
{
    mCameraComponent = GetOwner().GetComponent<ComponentCamera>();
    ASSERT(mCameraComponent != nullptr, "ComponentFPSCamera: Camera not found");
}

void ComponentCameraFPS::Terminate()
{
    mCameraComponent = nullptr;
}

void ComponentCameraFPS::Update(float deltaTime)
{
    Camera& camera = mCameraComponent->GetCamera();
    auto input = Input::InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
    const float turnSpeed = 0.1f;

    if (input->IsKeyDown(KeyCode::W))
        camera.Walk(moveSpeed * deltaTime);
    else if (input->IsKeyDown(KeyCode::S))
        camera.Walk(-moveSpeed * deltaTime);

    if (input->IsKeyDown(KeyCode::A))
        camera.Strafe(-moveSpeed * deltaTime);
    else if (input->IsKeyDown(KeyCode::D))
        camera.Strafe(moveSpeed * deltaTime);

    if (input->IsKeyDown(KeyCode::Q))
        camera.Rise(-moveSpeed * deltaTime);
    else if (input->IsKeyDown(KeyCode::E))
        camera.Rise(moveSpeed * deltaTime);

    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        camera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
        camera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
    }
}

void ComponentCameraFPS::Serialize(rapidjson::Document& doc, rapidjson::Value& value)
{
    rapidjson::Value componentValue(rapidjson::kObjectType);
    SaveUtil::SaveFloat("MoveSpeed", mMoveSpeed, doc, componentValue);
    SaveUtil::SaveFloat("ShiftSpeed", mShiftSpeed, doc, componentValue);
    SaveUtil::SaveFloat("TurnSpeed", mTurnSpeed, doc, componentValue);
    value.AddMember("ComponentCameraFPS", componentValue, doc.GetAllocator());
}

void ComponentCameraFPS::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("MoveSpeed"))
        mMoveSpeed = value["MoveSpeed"].GetFloat();

    if (value.HasMember("ShiftSpeed"))
        mShiftSpeed = value["ShiftSpeed"].GetFloat();

    if (value.HasMember("TurnSpeed"))
        mTurnSpeed = value["TurnSpeed"].GetFloat();
}